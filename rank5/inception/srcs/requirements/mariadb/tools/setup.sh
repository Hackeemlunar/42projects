#!/bin/bash

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    setup.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/05 00:00:00 by hmensah-          #+#    #+#              #
#    Updated: 2025/10/05 00:00:00 by hmensah-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

set -e

# Data directory
DATA_DIR="/var/lib/mysql"

# Initialize MariaDB data directory if it doesn't exist
if [ ! -d "$DATA_DIR/mysql" ]; then
    echo "Initializing MariaDB data directory..."
    mysql_install_db --user=mysql --datadir="$DATA_DIR" --skip-test-db
    
    echo "Starting temporary MariaDB server for setup..."
    mysqld --user=mysql --datadir="$DATA_DIR" --skip-networking &
    MYSQL_PID=$!
    
    # Wait for MariaDB to start
    echo "Waiting for MariaDB to start..."
    for i in {1..30}; do
        if mysqladmin ping --silent; then
            echo "MariaDB is ready!"
            break
        fi
        echo "Waiting for MariaDB to be ready... ($i/30)"
        sleep 1
    done
    
    # Create database and users
    echo "Setting up database and users..."
    mysql -u root <<-EOSQL
        -- Set root password
        ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
        
        -- Create database
        CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};
        
        -- Create user and grant privileges
        CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
        GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';
        
        -- Flush privileges
        FLUSH PRIVILEGES;
EOSQL
    
    echo "Database setup complete!"
    
    # Stop temporary server
    mysqladmin -u root -p"${MYSQL_ROOT_PASSWORD}" shutdown
    wait $MYSQL_PID
else
    echo "MariaDB data directory already exists. Skipping initialization."
fi

# Start MariaDB in foreground (no daemon mode)
echo "Starting MariaDB server..."
exec mysqld --user=mysql --datadir="$DATA_DIR"
