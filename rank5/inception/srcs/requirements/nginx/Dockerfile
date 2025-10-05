# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/05 00:00:00 by hmensah-          #+#    #+#              #
#    Updated: 2025/10/05 00:00:00 by hmensah-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Use Debian 11 (Bullseye) - penultimate stable version
FROM debian:11

# Install NGINX and OpenSSL for TLS certificate generation
RUN apt-get update && apt-get install -y \
    nginx \
    openssl \
    gettext-base \
    && rm -rf /var/lib/apt/lists/*

# Create directories for SSL certificates
RUN mkdir -p /etc/nginx/ssl

# Copy NGINX configuration
COPY conf/nginx.conf /etc/nginx/nginx.conf
COPY conf/default.conf /etc/nginx/sites-available/default

# Copy tools (SSL generation script)
COPY tools/setup.sh /usr/local/bin/setup.sh
RUN chmod +x /usr/local/bin/setup.sh

# Expose port 443 for HTTPS
EXPOSE 443

# Run setup script and start NGINX
CMD ["/usr/local/bin/setup.sh"]
