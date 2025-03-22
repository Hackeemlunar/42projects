#!/bin/bash
# Exit script on any error
set -e

##############################
# Variables - Customize below
##############################
USERNAME="hmensah"              # Your login name
USER_PASSWORD="Everyday42partydey"
DB_PASSWORD="born2beroot"
WORDPRESS_DB="born2beroot_db"
WORDPRESS_USER="hmensah"
MY_NAME="hmensah"               # Your name to show on the WordPress page
PROJECT_NAME="Born2beRoot"      # Your project name to show on the WordPress page

##############################
# Update System and Install Packages
##############################
echo "=== Updating System and Installing Required Packages ==="
apt-get update && apt-get upgrade -y
apt-get install -y sudo ufw openssh-server lvm2 apparmor auditd fail2ban \
                   lighttpd mariadb-server php php-mysql wget net-tools \
                   libpam-pwquality

##############################
# Verify Encrypted LVM Partitions (Assumes manual partitioning beforehand)
##############################
echo "=== Verifying Encrypted LVM Partitions ==="
lvscan

##############################
# SSH Configuration (Port 4242, Disable Root Login)
##############################
echo "=== Configuring SSH (Port 4242, No Root Login) ==="
# Change SSH port to 4242 (if not already set)
if grep -q "^#*Port" /etc/ssh/sshd_config; then
    sed -i 's/^#*Port .*/Port 4242/' /etc/ssh/sshd_config
else
    echo "Port 4242" >> /etc/ssh/sshd_config
fi
# Disable root login via SSH
if grep -q "^#*PermitRootLogin" /etc/ssh/sshd_config; then
    sed -i 's/^#*PermitRootLogin .*/PermitRootLogin no/' /etc/ssh/sshd_config
else
    echo "PermitRootLogin no" >> /etc/ssh/sshd_config
fi
systemctl restart ssh

##############################
# Firewall Configuration (UFW)
##############################
echo "=== Configuring UFW Firewall ==="
ufw default deny incoming
ufw default allow outgoing
# Allow SSH on port 4242
ufw allow 4242/tcp
# Allow HTTP and HTTPS (required for bonus WordPress installation)
ufw allow 80/tcp
ufw allow 443/tcp
ufw --force enable

##############################
# User and Sudo Configuration
##############################
echo "=== Creating Group and User, and Configuring Sudo ==="
# Create the user42 group if it does not exist
if ! getent group user42 >/dev/null; then
    groupadd user42
fi

# Create the new user and add to sudo and user42 groups
if ! id -u "$USERNAME" >/dev/null 2>&1; then
    useradd -m -s /bin/bash -G sudo,user42 "$USERNAME"
fi
echo "$USERNAME:$USER_PASSWORD" | chpasswd

# Instead of appending to /etc/sudoers directly, use a dedicated file
cat <<EOF > /etc/sudoers.d/99_custom_sudo
$USERNAME ALL=(ALL) ALL
Defaults passwd_tries=3
Defaults badpass_message="Incorrect password, please try again."
Defaults logfile="/var/log/sudo/sudo.log"
Defaults requiretty
Defaults secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"
EOF
chmod 440 /etc/sudoers.d/99_custom_sudo

# Create sudo log directory with proper permissions
mkdir -p /var/log/sudo && chmod 700 /var/log/sudo

##############################
# Strong Password Policy
##############################
echo "=== Setting Up Strong Password Policy ==="
# Set password aging policies for both the user and root
chage -M 30 -m 2 -W 7 "$USERNAME"
chage -M 30 -m 2 -W 7 root

# Ensure PAM uses pwquality. Uncomment any commented pam_pwquality.so lines in common-password
sed -i '/pam_pwquality.so/ s/^#*//' /etc/pam.d/common-password
# Append the strong password rules in /etc/security/pwquality.conf
cat <<EOF >> /etc/security/pwquality.conf
minlen = 10
ucredit = -1
lcredit = -1
dcredit = -1
maxrepeat = 3
difok = 7
# Note: The rule "password must not include the user name" must be enforced manually
EOF

##############################
# MariaDB Hardening
##############################
echo "=== Securing MariaDB ==="
mysql -u root <<EOF
DELETE FROM mysql.user WHERE User='';
DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1', '::1');
DROP DATABASE IF EXISTS test;
DELETE FROM mysql.db WHERE Db='test' OR Db='test\\_%';
FLUSH PRIVILEGES;
ALTER USER 'root'@'localhost' IDENTIFIED BY '$DB_PASSWORD';
EOF

##############################
# WordPress Installation and Custom Homepage
##############################
echo "=== Installing and Configuring WordPress ==="
# Create WordPress database and user
mysql -u root -p"$DB_PASSWORD" -e "CREATE DATABASE IF NOT EXISTS $WORDPRESS_DB;"
mysql -u root -p"$DB_PASSWORD" -e "CREATE USER IF NOT EXISTS '$WORDPRESS_USER'@'localhost' IDENTIFIED BY '$DB_PASSWORD';"
mysql -u root -p"$DB_PASSWORD" -e "GRANT ALL PRIVILEGES ON $WORDPRESS_DB.* TO '$WORDPRESS_USER'@'localhost'; FLUSH PRIVILEGES;"

# Download and set up WordPress
cd /var/www/html
wget -q https://wordpress.org/latest.tar.gz -O /tmp/latest.tar.gz
tar -xzf /tmp/latest.tar.gz
rm /tmp/latest.tar.gz
chown -R www-data:www-data wordpress
chmod -R 755 wordpress

# Configure wp-config.php with the new database credentials
cp /var/www/html/wordpress/wp-config-sample.php /var/www/html/wordpress/wp-config.php
sed -i "s/database_name_here/$WORDPRESS_DB/" /var/www/html/wordpress/wp-config.php
sed -i "s/username_here/$WORDPRESS_USER/" /var/www/html/wordpress/wp-config.php
sed -i "s/password_here/$DB_PASSWORD/" /var/www/html/wordpress/wp-config.php

# Create a custom homepage for WordPress.
# This will override the default theme by placing an index.php in the root of the WordPress folder.
cat <<EOF > /var/www/html/wordpress/index.php
<?php
/* Template Name: Custom Homepage */
get_header();
?>
<div style="text-align: center; margin-top: 50px;">
  <h1>Welcome to $PROJECT_NAME</h1>
  <p>Developed by $MY_NAME</p>
</div>
<?php get_footer(); ?>
EOF

# Configure lighttpd to serve WordPress
cat <<EOF > /etc/lighttpd/lighttpd.conf
server.document-root = "/var/www/html/wordpress"
server.port = 80
index-file.names = ("index.php", "index.html")
EOF
systemctl restart lighttpd

# Test PHP installation (Remember to remove after testing if desired)
echo "<?php phpinfo(); ?>" > /var/www/html/info.php
echo "Please remove the PHP info file (/var/www/html/info.php) after testing."

##############################
# Fail2Ban Configuration for SSH
##############################
echo "=== Configuring Fail2Ban for SSH ==="
cat <<EOF > /etc/fail2ban/jail.local
[sshd]
enabled = true
port = 4242
maxretry = 3
bantime = 600
EOF
systemctl restart fail2ban

##############################
# Monitoring Script Setup
##############################
echo "=== Setting Up Monitoring Script ==="
cat <<'EOF' > /usr/local/bin/monitoring.sh
#!/bin/bash
# Architecture and Kernel Version
echo "Architecture: $(uname -a)"

# CPU: Physical and Virtual Count
physical=$(grep "physical id" /proc/cpuinfo | sort -u | wc -l)
virtual=$(nproc)
echo "CPU physical : $physical"
echo "vCPU : $virtual"

# CPU Load Percentage (using the 1-minute load average and percentage)
# Assuming load average divided by number of virtual CPUs multiplied by 100 gives an approximation
loadavg=$(awk '{print $1}' /proc/loadavg)
cpu_load=$(awk -v la="$loadavg" -v vcpu="$virtual" 'BEGIN { printf "%.1f", (la/vcpu)*100 }')
echo "CPU load: $cpu_load%"

# Memory Usage
mem_usage=$(free -m | awk '/Mem/ {printf "%d/%dMB (%.2f%%)", $3, $2, $3*100/$2}')
echo "Memory Usage: $mem_usage"

# Disk Usage on root partition
disk_usage=$(df -h / | awk 'NR==2 {print $3"/"$2" ("$5")"}')
echo "Disk Usage: $disk_usage"

# Last Boot Time
last_boot=$(who -b | awk '{print $3" "$4}')
echo "Last boot: $last_boot"

# LVM Use (yes if any LVM partitions are found)
lvm_count=$(lsblk | grep -c "lvm")
if [ "$lvm_count" -gt 0 ]; then
    echo "LVM use: yes"
else
    echo "LVM use: no"
fi

# Active TCP Connections
connections=$(netstat -an | grep ESTABLISHED | wc -l)
echo "Connections TCP: $connections ESTABLISHED"

# Number of Logged-in Users
user_log=$(who | wc -l)
echo "User log: $user_log"

# Network: IPv4 Address and MAC Address
ipv4=$(ip -4 addr show | awk '/inet / {print $2; exit}')
mac=$(ip link show | awk '/ether/ {print $2; exit}')
echo "Network: IP $ipv4 ($mac)"

# Sudo Commands Executed
sudo_cmds=$( [ -f /var/log/sudo/sudo.log ] && wc -l < /var/log/sudo/sudo.log || echo 0 )
echo "Sudo : $sudo_cmds cmd"
EOF

# Make the monitoring script executable
chmod +x /usr/local/bin/monitoring.sh

# Set up a cron job to run the monitoring script every 10 minutes and broadcast its output
(crontab -l 2>/dev/null; echo "*/10 * * * * /usr/local/bin/monitoring.sh | wall") | crontab -

##############################
# Enable Services on Boot
##############################
echo "=== Enabling Services on Boot ==="
systemctl enable lighttpd mariadb fail2ban

echo "=== Setup Complete! ==="
echo "Remember to remove /var/www/html/info.php after testing."
echo "You can now reboot the system if desired."
