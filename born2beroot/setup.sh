#!/bin/bash

# Exit script on any error
set -e

# Variables
USERNAME="hmensah-42"
USER_PASSWORD="born2beroot"
DB_PASSWORD="born2beroot"
WORDPRESS_DB="born2beroot_db"
WORDPRESS_USER="hmensah"

echo "=== Updating System and Installing Required Packages ==="
apt update && apt upgrade -y

# Install necessary tools and security utilities
apt install -y sudo ufw openssh-server lvm2 apparmor auditd fail2ban \
               lighttpd mariadb-server php php-mysql wget net-tools

echo "=== Configuring Encrypted LVM Partitions ==="
lvscan  # Verify that LVM is active

echo "=== Configuring SSH (Port 4242, No Root Login) ==="
sed -i 's/#Port 22/Port 4242/' /etc/ssh/sshd_config
sed -i 's/PermitRootLogin yes/PermitRootLogin no/' /etc/ssh/sshd_config
systemctl restart ssh

echo "=== Configuring Firewall (UFW) ==="
ufw default deny incoming
ufw default allow outgoing
ufw allow 4242/tcp  # Allow SSH on port 4242
ufw allow 80/tcp    # Allow HTTP
ufw allow 443/tcp   # Allow HTTPS
ufw enable

echo "=== Creating User and Configuring Sudo ==="
useradd -m -s /bin/bash -G sudo,user42 $USERNAME
echo "$USERNAME:$USER_PASSWORD" | chpasswd

# Configure sudo restrictions
echo "$USERNAME ALL=(ALL) ALL" >> /etc/sudoers
echo "Defaults passwd_tries=3" >> /etc/sudoers
echo "Defaults logfile=\"/var/log/sudo/sudo.log\"" >> /etc/sudoers
mkdir -p /var/log/sudo && chmod 700 /var/log/sudo

echo "=== Setting Up Strong Password Policy ==="
apt install -y libpam-pwquality
sed -i '/pam_pwquality.so/ s/^#//g' /etc/pam.d/common-password
echo "password required pam_pwquality.so retry=3 minlen=10 ucredit=-1 lcredit=-1 dcredit=-1 maxrepeat=3 difok=7" >> /etc/security/pwquality.conf

echo "=== Installing and Configuring WordPress ==="
# Secure MariaDB
mysql_secure_installation <<EOF
y
$DB_PASSWORD
$DB_PASSWORD
y
y
y
y
EOF

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

# Test PHP installation
echo "<?php phpinfo(); ?>" > /var/www/html/info.php
systemctl restart lighttpd

echo "=== Configuring Fail2Ban for Security ==="
cat <<EOF > /etc/fail2ban/jail.local
[sshd]
enabled = true
port = 4242
maxretry = 3
bantime = 600
EOF
systemctl restart fail2ban

echo "=== Setting Up Monitoring Script ==="
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

chmod +x /usr/local/bin/monitoring.sh

echo "=== Setting Up Cron Job to Run Monitoring Script Every 10 Minutes ==="
(crontab -l ; echo "*/10 * * * * /usr/local/bin/monitoring.sh | wall") | crontab -

echo "=== Enabling Services on Boot ==="
systemctl enable lighttpd mariadb fail2ban

echo "=== Setup Complete! Rebooting System ==="
reboot
