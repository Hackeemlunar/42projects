*This project has been created as part of the 42 curriculum by `hmensah-`.*

# Inception

## Description

Inception is a system administration project whose goal is to broaden knowledge of Docker by virtualizing a small, multi-container infrastructure. The project sets up three dedicated services — **NGINX**, **WordPress (with PHP-FPM)** and **MariaDB** — each running in its own container, built from scratch (no ready-made images), communicating over a dedicated Docker network and persisting data through Docker named volumes.

The infrastructure is entirely described and orchestrated with Docker Compose, and the whole stack is built and launched through a single `make` command.

## Instructions

### Prerequisites

- A Linux virtual machine with Docker and the Docker Compose plugin installed.
- The `.env` file in `srcs/` (copy `srcs/.env.example` to `srcs/.env` and adjust the non-sensitive values for your login).
- The password files in `secrets/` (`db_root_password.txt`, `db_password.txt`, `credentials.txt`, `wp_user_password.txt`). They are ignored by Git and must be created locally — see `DEV_DOC.md`.

### Build and run

```sh
make          # build the images and start the containers
make build    # build the images only
make up       # start the containers
make down     # stop and remove the containers
make re       # full rebuild from scratch
```

Once running, the website is available at `https://hmensah-.42.fr` (add an entry for `hmensah-.42.fr` in `/etc/hosts` pointing to your local IP address).

## Project description

This project uses Docker to package each service into its own image, guaranteeing isolation, reproducibility and portability. The images are all built from the same base (`debian:12`), each with its own `Dockerfile` and startup script. The sources are organised under `srcs/requirements/<service>`.

Main design choices and comparisons:

### Virtual Machines vs Docker

A virtual machine virtualises an entire operating system (kernel included): each VM carries a full guest OS, which is heavy in CPU/RAM and slow to boot. Docker virtualises only at the OS level by sharing the host kernel and isolating processes (namespaces, cgroups): containers are lightweight, start in seconds and share resources efficiently. Docker is therefore better suited to running isolated application services, while VMs remain useful when full isolation or a different kernel/OS is needed.

### Secrets vs Environment Variables

Environment variables are convenient and readable but are stored in plaintext and are easily leaked (committed by mistake, or visible through `docker inspect`). Docker secrets keep sensitive data out of images and environment variables and mount it only into the containers that need it, reducing the risk of exposure. In this project, `.env` contains only non-sensitive configuration (domain, database name, user names, paths), while the database root password, the database user password, and the two WordPress account passwords are stored in `secrets/*.txt`, mounted through Docker Compose secrets and read by the entrypoint scripts from `/run/secrets/`. The secret files are excluded from Git.

### Docker Network vs Host Network

The default Docker bridge network creates an isolated, internal network where containers communicate by service name and only explicitly published ports are exposed to the host. The `host` network shares the host's network stack, removing isolation and causing port conflicts; it is forbidden here. The project uses a dedicated bridge network (`inception_network`) so that NGINX remains the sole entry point.

### Docker Volumes vs Bind Mounts

Named volumes are managed by Docker (stored under `/var/lib/docker/volumes`), are portable and are the recommended way to persist data. Bind mounts map an arbitrary host path into the container, coupling the container to the host filesystem layout. The project uses named volumes for the database and for the WordPress files, so that data survives container restarts and rebuilds.

## Resources

- [Docker documentation](https://docs.docker.com/)
- [Docker Compose documentation](https://docs.docker.com/compose/)
- [NGINX documentation](https://nginx.org/en/docs/)
- [WordPress documentation](https://wordpress.org/documentation/)
- [MariaDB documentation](https://mariadb.com/kb/en/documentation/)
- [WP-CLI](https://wp-cli.org/)

AI was used to help draft the initial Dockerfiles and startup scripts, to explain container/volume/network concepts and to review the configuration for common pitfalls. Every generated snippet was read, tested and adapted by hand before being included.
