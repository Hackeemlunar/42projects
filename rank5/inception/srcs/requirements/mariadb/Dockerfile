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

# Install MariaDB server (NO NGINX)
RUN apt-get update && apt-get install -y \
    mariadb-server \
    mariadb-client \
    && rm -rf /var/lib/apt/lists/*

# Create directory for MariaDB socket and pid
RUN mkdir -p /var/run/mysqld && \
    chown -R mysql:mysql /var/run/mysqld && \
    chmod 755 /var/run/mysqld

# Copy MariaDB configuration
COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf

# Copy setup script
COPY tools/setup.sh /usr/local/bin/setup.sh
RUN chmod +x /usr/local/bin/setup.sh

# Expose port 3306 for MariaDB
EXPOSE 3306

# Run setup script
CMD ["/usr/local/bin/setup.sh"]
