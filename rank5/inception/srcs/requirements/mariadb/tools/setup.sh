#!/bin/bash

set -eu

DATA_DIR="/var/lib/mysql"

read_secret() {
    local value="$1"
    local file="$2"

    if [ -n "$file" ]; then
        if [ ! -r "$file" ]; then
            echo "Error: cannot read secret file: $file" >&2
            exit 1
        fi
        cat "$file"
    else
        printf '%s' "$value"
    fi
}

MYSQL_ROOT_PASSWORD="$(read_secret "${MYSQL_ROOT_PASSWORD:-}" "${MYSQL_ROOT_PASSWORD_FILE:-}")"
MYSQL_PASSWORD="$(read_secret "${MYSQL_PASSWORD:-}" "${MYSQL_PASSWORD_FILE:-}")"

: "${MYSQL_DATABASE:?MYSQL_DATABASE is required}"
: "${MYSQL_USER:?MYSQL_USER is required}"

if [ -z "$MYSQL_ROOT_PASSWORD" ] || [ -z "$MYSQL_PASSWORD" ]; then
    echo "Error: database passwords are missing or empty." >&2
    exit 1
fi

# The host directory behind the named volume may be created by the host user.
# MariaDB must own its data directory.
mkdir -p "$DATA_DIR"
chown -R mysql:mysql "$DATA_DIR"

# Initialize MariaDB data directory if it does not exist yet.
if [ ! -d "$DATA_DIR/mysql" ]; then
    echo "Initializing MariaDB data directory..."
    mariadb-install-db --user=mysql --datadir="$DATA_DIR" --skip-test-db

    echo "Starting temporary MariaDB server for setup..."
    mariadbd --user=mysql --datadir="$DATA_DIR" --skip-networking &
    MYSQL_PID=$!

    echo "Waiting for MariaDB to start..."
    READY=0
    for i in $(seq 1 30); do
        if mariadb-admin ping --silent >/dev/null 2>&1; then
            echo "MariaDB is ready."
            READY=1
            break
        fi
        echo "Waiting for MariaDB to be ready... ($i/30)"
        sleep 1
    done

    if [ "$READY" -ne 1 ]; then
        echo "Error: MariaDB did not start in time." >&2
        kill "$MYSQL_PID" 2>/dev/null || true
        exit 1
    fi

    echo "Setting up database and users..."
    mariadb -u root <<-EOSQL
        ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';

        CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;

        CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
        GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';

        FLUSH PRIVILEGES;
EOSQL

    echo "Database setup complete."

    mariadb-admin -u root -p"${MYSQL_ROOT_PASSWORD}" shutdown
    wait "$MYSQL_PID" || true
else
    echo "MariaDB data directory already exists. Skipping initialization."
fi

# Start MariaDB in the foreground so it stays PID 1.
echo "Starting MariaDB server..."
exec mariadbd --user=mysql --datadir="$DATA_DIR"
