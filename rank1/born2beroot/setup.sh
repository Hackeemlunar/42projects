#!/bin/bash
# Exit script on any error
set -e

# Variables
USERNAME="hmensah-"
USER_PASSWORD="Everyday42partydey"
DB_PASSWORD="born2beroot"
WORDPRESS_DB="born2beroot_db"
WORDPRESS_USER="hmensah"

echo "=== Updating System and Installing Required Packages ==="
# Update package lists and upgrade installed packages
apt-get update && apt-get upgrade -y
# Install necessary tools and security utilities
apt-get install -y sudo ufw openssh-server lvm2 apparmor auditd fail2ban \
               lighttpd mariadb-server php php-mysql wget net-tools libpam-pwquality

echo "=== Configuring Encrypted LVM Partitions ==="
# Verify that LVM is active (Assumes partitioning is done manually before running the script)
lvscan

echo "=== Configuring SSH (Port 4242, No Root Login) ==="
# Change SSH port to 4242
sed -i 's/#Port 22/Port 4242/' /etc/ssh/sshd_config
# Disable root login via SSH
sed -i 's/PermitRootLogin yes/PermitRootLogin no/' /etc/ssh/sshd_config
# Restart SSH service to apply changes
systemctl restart ssh

echo "=== Configuring Firewall (UFW) ==="
# Set default policies for UFW
ufw default deny incoming
ufw default allow outgoing
# Allow SSH on port 4242
ufw allow 4242/tcp
# Allow HTTP and HTTPS for WordPress (Bonus part requires these ports)
ufw allow 80/tcp    # HTTP
ufw allow 443/tcp   # HTTPS
# Enable UFW firewall
ufw enable

echo "=== Setting Hostname ==="

echo "=== Creating User and Configuring Sudo ==="
# Create a new user with the specified username
useradd -m -s /bin/bash -G sudo,user42 $USERNAME
# Set the user's password
echo "$USERNAME:$USER_PASSWORD" | chpasswd
# Configure sudo restrictions
echo "$USERNAME ALL=(ALL) ALL" >> /etc/sudoers
echo "Defaults passwd_tries=3" >> /etc/sudoers
echo "Defaults badpass_message=\"Incorrect password, please try again.\"" >> /etc/sudoers
echo "Defaults logfile=\"/var/log/sudo/sudo.log\"" >> /etc/sudoers
echo "Defaults requiretty" >> /etc/sudoers
echo "Defaults secure_path=\"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin\"" >> /etc/sudoers
# Create the sudo log directory and set permissions
mkdir -p /var/log/sudo && chmod 700 /var/log/sudo

echo "=== Setting Up Strong Password Policy ==="
# Enforce password expiration policies
chage -M 30 -m 2 -W 7 $USERNAME
chage -M 30 -m 2 -W 7 root
# Configure strong password rules using libpam-pwquality
sed -i '/pam_pwquality.so/ s/^#//g' /etc/pam.d/common-password
echo "password required pam_pwquality.so retry=3 minlen=10 ucredit=-1 lcredit=-1 dcredit=-1 maxrepeat=3 difok=7" >> /etc/security/pwquality.conf

echo "=== Securing MariaDB ==="
# Secure MariaDB without mysql_secure_installation
mysql -u root <<EOF
DELETE FROM mysql.user WHERE User='';
DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1', '::1');
DROP DATABASE IF EXISTS test;
DELETE FROM mysql.db WHERE Db='test' OR Db='test\\_%';
FLUSH PRIVILEGES;
ALTER USER 'root'@'localhost' IDENTIFIED BY '$DB_PASSWORD';
EOF

echo "=== Installing and Configuring WordPress ==="
# Create WordPress database and user
mysql -u root -p"$DB_PASSWORD" -e "CREATE DATABASE $WORDPRESS_DB;"
mysql -u root -p"$DB_PASSWORD" -e "CREATE USER '$WORDPRESS_USER'@'localhost' IDENTIFIED BY '$DB_PASSWORD';"
mysql -u root -p"$DB_PASSWORD" -e "GRANT ALL PRIVILEGES ON $WORDPRESS_DB.* TO '$WORDPRESS_USER'@'localhost'; FLUSH PRIVILEGES;"

# Download and set up WordPress
cd /var/www/html
wget https://wordpress.org/latest.tar.gz
tar -xzf latest.tar.gz && rm latest.tar.gz
chown -R www-data:www-data wordpress
chmod -R 755 wordpress

# Configure wp-config.php
cp /var/www/html/wordpress/wp-config-sample.php /var/www/html/wordpress/wp-config.php
sed -i "s/database_name_here/$WORDPRESS_DB/" /var/www/html/wordpress/wp-config.php
sed -i "s/username_here/$WORDPRESS_USER/" /var/www/html/wordpress/wp-config.php
sed -i "s/password_here/$DB_PASSWORD/" /var/www/html/wordpress/wp-config.php

# Configure lighttpd to serve WordPress
cat <<EOF > /etc/lighttpd/lighttpd.conf
server.document-root = "/var/www/html/wordpress"
server.port = 80
index-file.names = ("index.php")
EOF
systemctl restart lighttpd

# Test PHP installation (Remove after testing)
echo "<?php phpinfo(); ?>" > /var/www/html/info.php
echo "Please remove the PHP info file (/var/www/html/info.php) after testing."

echo "=== Configuring Fail2Ban for Security ==="
# Configure Fail2Ban to protect SSH
cat <<EOF > /etc/fail2ban/jail.local
[sshd]
enabled = true
port = 4242
maxretry = 3
bantime = 600
EOF
systemctl restart fail2ban

echo "=== Setting Up Monitoring Script ==="
# Create a monitoring script to display system information
cat <<EOF > /usr/local/bin/monitoring.sh
#!/bin/bash
echo "Architecture: \$(uname -a)"
echo "CPU physical: \$(nproc --all)"
echo "Memory Usage: \$(free -m | awk '/Mem/ {print \$3 \"/\" \$2 \"MB (\" \$3*100/\$2 \"%\" )\"}')"
echo "Disk Usage: \$(df -h / | awk 'NR==2 {print \$3\"/\"\$2 \" (\" \$5 \")\"}')"
echo "Last boot: \$(who -b | awk '{print \$3, \$4}')"
echo "LVM use: \$(lsblk | grep lvm | wc -l)"
echo "Connections TCP: \$(netstat -an | grep ESTABLISHED | wc -l)"
echo "User log: \$(who | wc -l)"
echo "Network: \$(ip -4 addr show | grep 'inet ' | awk '{print \$2}')"
echo "Sudo : \$(cat /var/log/sudo/sudo.log | wc -l) cmd"
EOF
# Make the monitoring script executable
chmod +x /usr/local/bin/monitoring.sh

echo "=== Setting Up Cron Job to Run Monitoring Script Every 10 Minutes ==="
# Schedule the monitoring script to run every 10 minutes and broadcast output using wall
(crontab -l ; echo "*/10 * * * * /usr/local/bin/monitoring.sh | wall") | crontab -

echo "=== Enabling Services on Boot ==="
# Ensure services start on boot
systemctl enable lighttpd mariadb fail2ban

echo "=== Setup Complete! ==="
echo "Please remove the PHP info file (/var/www/html/info.php) after testing."
echo "You can reboot the system now if needed."