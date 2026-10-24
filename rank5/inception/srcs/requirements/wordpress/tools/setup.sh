#!/bin/bash

set -eu

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

MYSQL_PASSWORD="$(read_secret "${MYSQL_PASSWORD:-}" "${MYSQL_PASSWORD_FILE:-}")"
WP_ADMIN_PASSWORD="$(read_secret "${WP_ADMIN_PASSWORD:-}" "${WP_ADMIN_PASSWORD_FILE:-}")"
WP_USER_PASSWORD="$(read_secret "${WP_USER_PASSWORD:-}" "${WP_USER_PASSWORD_FILE:-}")"

: "${MYSQL_HOST:?MYSQL_HOST is required}"
: "${MYSQL_DATABASE:?MYSQL_DATABASE is required}"
: "${MYSQL_USER:?MYSQL_USER is required}"
: "${WP_URL:?WP_URL is required}"
: "${WP_TITLE:?WP_TITLE is required}"
: "${WP_ADMIN_USER:?WP_ADMIN_USER is required}"
: "${WP_ADMIN_EMAIL:?WP_ADMIN_EMAIL is required}"
: "${WP_USER:?WP_USER is required}"
: "${WP_USER_EMAIL:?WP_USER_EMAIL is required}"

if [ -z "$MYSQL_PASSWORD" ] || [ -z "$WP_ADMIN_PASSWORD" ] || [ -z "$WP_USER_PASSWORD" ]; then
    echo "Error: required passwords are missing or empty." >&2
    exit 1
fi

cd /var/www/html

# Wait for MariaDB with a bounded retry loop.
echo "Waiting for MariaDB to be ready..."
DB_READY=0
for i in $(seq 1 60); do
    if mariadb -h"${MYSQL_HOST}" -u"${MYSQL_USER}" -p"${MYSQL_PASSWORD}" \
        -e "SELECT 1" >/dev/null 2>&1; then
        DB_READY=1
        break
    fi
    echo "MariaDB is unavailable - sleeping ($i/60)"
    sleep 2
done

if [ "$DB_READY" -ne 1 ]; then
    echo "Error: MariaDB did not become ready in time." >&2
    exit 1
fi
echo "MariaDB is up and running."

# Download WordPress if the core files are missing.
if [ ! -f wp-includes/version.php ]; then
    echo "Downloading WordPress..."
    wp core download --allow-root --force
fi

# Create wp-config.php on the first run.
if [ ! -f wp-config.php ]; then
    echo "Creating wp-config.php..."
    wp config create \
        --dbname="${MYSQL_DATABASE}" \
        --dbuser="${MYSQL_USER}" \
        --dbpass="${MYSQL_PASSWORD}" \
        --dbhost="${MYSQL_HOST}" \
        --allow-root
fi

# Keep wp-config.php in sync with the current environment/secrets.
wp config set DB_NAME "${MYSQL_DATABASE}" --type=constant --allow-root --quiet
wp config set DB_USER "${MYSQL_USER}" --type=constant --allow-root --quiet
wp config set DB_PASSWORD "${MYSQL_PASSWORD}" --type=constant --allow-root --quiet
wp config set DB_HOST "${MYSQL_HOST}" --type=constant --allow-root --quiet
wp config set WP_HOME "${WP_URL}" --type=constant --allow-root --quiet
wp config set WP_SITEURL "${WP_URL}" --type=constant --allow-root --quiet

# Install WordPress if the database does not contain a site yet.
if ! wp core is-installed --allow-root >/dev/null 2>&1; then
    echo "Installing WordPress..."
    wp core install \
        --url="${WP_URL}" \
        --title="${WP_TITLE}" \
        --admin_user="${WP_ADMIN_USER}" \
        --admin_password="${WP_ADMIN_PASSWORD}" \
        --admin_email="${WP_ADMIN_EMAIL}" \
        --skip-email \
        --allow-root
    echo "WordPress installation complete."
fi

# Create the second (non-admin) user once.
if ! wp user get "${WP_USER}" --field=ID --allow-root >/dev/null 2>&1; then
    echo "Creating regular WordPress user..."
    wp user create \
        "${WP_USER}" \
        "${WP_USER_EMAIL}" \
        --role=author \
        --user_pass="${WP_USER_PASSWORD}" \
        --allow-root
fi

# Ensure all WordPress files remain owned and readable by PHP-FPM.
chown -R www-data:www-data /var/www/html
find /var/www/html -type d -exec chmod 755 {} +
find /var/www/html -type f -exec chmod 644 {} +
chmod 640 /var/www/html/wp-config.php

echo "Starting PHP-FPM..."
exec php-fpm8.2 -F
