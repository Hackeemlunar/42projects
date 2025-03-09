#!/bin/bash
# Exit script on any error
set -e

##############################
# Variables - Customize below
##############################
USERNAME="hmensah-"
USER_PASSWORD="Everyday42partydey"
DB_PASSWORD="Born2beroot"
WORDPRESS_DB="born2beroot_db"
MY_NAME="Hackeem M. Bosu"
WORDPRESS_USER="hmensah"
PROJECT_NAME="Born2beRoot"
WP_ADMIN="wcCSByM0b!f%bixHdI"

##############################
# Update System and Install Packages
##############################
echo "=== Updating System and Installing Required Packages ==="
apt-get update && apt-get upgrade -y
apt-get install -y sudo ufw lvm2 apparmor auditd fail2ban \
                   mariadb-server php php-fpm php-mysql wget net-tools \
                   libpam-pwquality lighttpd
sleep 3

# AppArmor (Application Armor) is a Linux security module that provides a system for restricting
# the capabilities of programs. It allows you to define fine-grained access control rules for
# individual applications, limiting what files they can access, what network operations they can
# perform, and what other system resources they can use.  It's a form of Mandatory Access Control (MAC).

# auditd (the Linux Audit daemon) is a component of the Linux Audit system. 
# It's responsible for collecting and recording system calls made by processes,
# along with other security-relevant events.  Think of it as a detailed security logging
# system that tracks what's happening at a very low level in your Linux system

# Fail2ban is a powerful intrusion prevention system (IPS) for Linux (and other Unix-like systems)
# that protects your servers from brute-force attacks.  It monitors log files for failed login 
# attempts and other suspicious activity, and if it detects too many failures from a specific 
# IP address, it automatically blocks that IP address by adding rules to your firewall (usually 
# iptables or nftables)

##############################
# Verify Encrypted LVM Partitions
##############################
echo "=== Verifying Encrypted LVM Partitions ==="
lvscan
sleep 3

##############################
# SSH Configuration (Port 4242, Disable Root Login)
##############################
echo "=== Configuring SSH (Port 4242, No Root Login) ==="
sed -i 's/^#*Port .*/Port 4242/' /etc/ssh/sshd_config
sed -i 's/^#*PermitRootLogin .*/PermitRootLogin no/' /etc/ssh/sshd_config
systemctl restart ssh
sleep 3

##############################
# Firewall Configuration (UFW)
##############################
echo "=== Configuring UFW Firewall ==="
ufw default deny incoming
ufw default allow outgoing
ufw allow 4242/tcp
ufw allow 80/tcp
ufw --force enable
sleep 3

##############################
# User and Sudo Configuration
##############################
echo "=== Creating User and Configuring Sudo ==="
groupadd -f user42
id -u "$USERNAME" &>/dev/null || useradd -m -s /bin/bash -G sudo,user42 "$USERNAME"
echo "$USERNAME:$USER_PASSWORD" | chpasswd

cat <<EOF > /etc/sudoers.d/99_custom_sudo
$USERNAME ALL=(ALL) ALL
Defaults passwd_tries=3
Defaults badpass_message="Incorrect password, please try again."
Defaults logfile="/var/log/sudo/sudo.log"
Defaults requiretty
Defaults secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"
EOF
chmod 440 /etc/sudoers.d/99_custom_sudo
mkdir -p /var/log/sudo && chmod 700 /var/log/sudo
sleep 3

##############################
# Strong Password Policy
##############################
echo "=== Setting Up Strong Password Policy ==="
chage -M 30 -m 2 -W 7 "$USERNAME"
chage -M 30 -m 2 -W 7 root
sed -i '/pam_pwquality.so/ s/^#*//' /etc/pam.d/common-password

cat <<EOF >> /etc/security/pwquality.conf
minlen = 10
ucredit = -1
lcredit = -1
dcredit = -1
maxrepeat = 3
difok = 7
EOF
sleep 3

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
sleep 3

##############################
# WordPress Installation and Custom Homepage
##############################
echo "=== Installing and Configuring WordPress ==="
mysql -u root -p"$DB_PASSWORD" -e "CREATE DATABASE IF NOT EXISTS $WORDPRESS_DB;"
mysql -u root -p"$DB_PASSWORD" -e "CREATE USER IF NOT EXISTS '$WORDPRESS_USER'@'localhost' IDENTIFIED BY '$DB_PASSWORD';"
mysql -u root -p"$DB_PASSWORD" -e "GRANT ALL PRIVILEGES ON $WORDPRESS_DB.* TO '$WORDPRESS_USER'@'localhost'; FLUSH PRIVILEGES;"

cd /var/www/html
wget -q https://wordpress.org/latest.tar.gz -O /tmp/latest.tar.gz
tar -xzf /tmp/latest.tar.gz
rm /tmp/latest.tar.gz
chown -R www-data:www-data wordpress
chmod -R 755 wordpress

cp /var/www/html/wordpress/wp-config-sample.php /var/www/html/wordpress/wp-config.php
sed -i "s/database_name_here/$WORDPRESS_DB/" /var/www/html/wordpress/wp-config.php
sed -i "s/username_here/$WORDPRESS_USER/" /var/www/html/wordpress/wp-config.php
sed -i "s/password_here/$DB_PASSWORD/" /var/www/html/wordpress/wp-config.php

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

cat <<EOF > /etc/lighttpd/lighttpd.conf
server.document-root = "/var/www/html/wordpress"
server.port = 80
index-file.names = ("index.php", "index.html")
EOF
systemctl restart lighttpd
sleep 3

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
sleep 3

##############################
# Monitoring Script Setup
##############################
echo "=== Setting Up Monitoring Script ==="
cat <<'EOF' > /usr/local/bin/monitoring.sh
#!/bin/bash
echo "Architecture: $(uname -a)"
physical=$(grep "physical id" /proc/cpuinfo | sort -u | wc -l)
virtual=$(nproc)
echo "CPU physical : $physical"
echo "vCPU : $virtual"
loadavg=$(awk '{print $1}' /proc/loadavg)
cpu_load=$(awk -v la="$loadavg" -v vcpu="$virtual" 'BEGIN { printf "%.1f", (la/vcpu)*100 }')
echo "CPU load: $cpu_load%"
mem_usage=$(free -m | awk '/Mem/ {printf "%d/%dMB (%.2f%%)", $3, $2, $3*100/$2}')
echo "Memory Usage: $mem_usage"
disk_usage=$(df -h / | awk 'NR==2 {print $3"/"$2" ("$5")"}')
echo "Disk Usage: $disk_usage"
last_boot=$(who -b | awk '{print $3" "$4}')
echo "Last boot: $last_boot"
lvm_count=$(lsblk | grep -c "lvm")
echo "LVM use: $(if [ "$lvm_count" -gt 0 ]; then echo "yes"; else echo "no"; fi)"
connections=$(netstat -an | grep ESTABLISHED | wc -l)
echo "Connections TCP: $connections ESTABLISHED"
user_log=$(who | wc -l)
echo "User log: $user_log"
ipv4=$(ip -4 addr show | grep -v '127.0.0.1' | awk '/inet / {print $2; exit}')
mac=$(ip link show | awk '/ether/ {print $2; exit}')
echo "Network: IP $ipv4 ($mac)"
sudo_cmds=$( [ -f /var/log/sudo/sudo.log ] && wc -l < /var/log/sudo/sudo.log || echo 0 )
echo "Sudo : $sudo_cmds cmd"
EOF

chmod +x /usr/local/bin/monitoring.sh
(crontab -l 2>/dev/null; echo "*/10 * * * * /usr/local/bin/monitoring.sh | wall") | crontab -
sleep 3

##############################
# Enable Services on Boot
##############################
echo "=== Enabling Services on Boot ==="
systemctl enable lighttpd mariadb fail2ban

echo "=== Setup Complete! ==="
