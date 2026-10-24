#!/bin/bash

set -eu

: "${DOMAIN_NAME:?DOMAIN_NAME is required}"
: "${WP_PORT:?WP_PORT is required}"

# Generate a self-signed TLS certificate if it does not exist yet.
if [ ! -f /etc/nginx/ssl/nginx.crt ]; then
    echo "Generating SSL certificate..."
    openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
        -keyout /etc/nginx/ssl/nginx.key \
        -out /etc/nginx/ssl/nginx.crt \
        -subj "/C=GH/ST=Accra/L=Accra/O=42Network/OU=42/CN=${DOMAIN_NAME}"
    echo "SSL certificate generated successfully."
fi

# Substitute only the variables we own; NGINX variables such as $uri stay intact.
envsubst '${DOMAIN_NAME} ${WP_PORT}' \
    < /etc/nginx/sites-available/default > /tmp/default.conf
mv /tmp/default.conf /etc/nginx/sites-available/default

echo "Testing NGINX configuration..."
nginx -t

echo "Starting NGINX..."
exec nginx -g "daemon off;"
