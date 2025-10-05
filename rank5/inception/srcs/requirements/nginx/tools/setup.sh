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

# Generate SSL certificate if it doesn't exist
if [ ! -f /etc/nginx/ssl/nginx.crt ]; then
    echo "Generating SSL certificate..."
    openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
        -keyout /etc/nginx/ssl/nginx.key \
        -out /etc/nginx/ssl/nginx.crt \
        -subj "/C=GH/ST=Accra/L=Accra/O=42Network/OU=42/CN=${DOMAIN_NAME}"
    echo "SSL certificate generated successfully!"
fi

# Replace ${DOMAIN_NAME} in default.conf with actual value
envsubst '${DOMAIN_NAME}' < /etc/nginx/sites-available/default > /tmp/default.conf
mv /tmp/default.conf /etc/nginx/sites-available/default

# Test NGINX configuration
echo "Testing NGINX configuration..."
nginx -t

# Start NGINX in foreground (no daemon mode, as required by Docker best practices)
echo "Starting NGINX..."
exec nginx -g "daemon off;"
