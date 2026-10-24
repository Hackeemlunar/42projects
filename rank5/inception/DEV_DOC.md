# Developer documentation — Inception

## Setting up the environment from scratch

1. Install Docker and the Docker Compose plugin on the VM.
2. Clone the repository.
3. Create the non-sensitive environment file:
   ```sh
   cp srcs/.env.example srcs/.env
   ```
   Adjust `DOMAIN_NAME`, `WP_URL`, `WP_PORT`, the user names, and `DATA_PATH` to your login. Passwords must not be added to this file.
4. Create the local secret files (they are ignored by Git):
   ```sh
   mkdir -p secrets
   printf '%s\n' 'replace-with-a-strong-root-password' > secrets/db_root_password.txt
   printf '%s\n' 'replace-with-a-strong-db-password'   > secrets/db_password.txt
   printf '%s\n' 'replace-with-a-strong-admin-pass'    > secrets/credentials.txt
   printf '%s\n' 'replace-with-a-strong-author-pass'   > secrets/wp_user_password.txt
   chmod 600 secrets/*.txt srcs/.env
   ```
   - `secrets/db_root_password.txt` → MariaDB root password.
   - `secrets/db_password.txt` → password of the WordPress database user (`MYSQL_USER`).
   - `secrets/credentials.txt` → WordPress administrator password.
   - `secrets/wp_user_password.txt` → password of the second WordPress user.
5. Create the data directories:
   ```sh
   mkdir -p /home/<login>/data/wordpress /home/<login>/data/mariadb
   ```

The Makefile checks that all four secret files exist and are non-empty before starting the stack.

## How secrets are wired

Docker Compose mounts the secret files read-only under `/run/secrets/<name>` inside the relevant containers:

- MariaDB receives `db_root_password` and `db_password`.
- WordPress receives `db_password`, `wp_admin_password`, and `wp_user_password`.

The container environment only contains file paths such as `MYSQL_PASSWORD_FILE=/run/secrets/db_password`; the startup scripts read the actual value from those files. No password is written into a Dockerfile, `docker-compose.yml`, or `.env`.

## Building and launching the project

From the project root:

```sh
make          # creates data dirs, builds images, starts containers
make build    # build images (--no-cache)
make up       # start containers in detached mode
```

## Managing containers and volumes

```sh
make start    # start existing containers
make stop     # stop containers
make restart  # restart containers
make down     # stop and remove containers
make clean    # down + remove project volumes
make fclean   # full cleanup (containers, images, project volumes, host data)
make re       # fclean + all
make logs     # follow container logs
make status   # list containers
```

## Data storage and persistence

Data is stored in two Docker named volumes, both mapped onto the host under `/home/<login>/data`:

- `/home/<login>/data/wordpress` — WordPress files (mounted at `/var/www/html`)
- `/home/<login>/data/mariadb` — database files (mounted at `/var/lib/mysql`)

Because they are named volumes, the data survives container restarts and rebuilds (`make clean` removes the volumes; `make fclean` also removes the host data).

## WordPress account rules

- The administrator account is created from `WP_ADMIN_USER`, and its username does not contain `admin`/`administrator`.
- `WP_USER` is created as a second account with the `author` role.
- Changing a password in `secrets/` requires either updating it inside WordPress/MariaDB or recreating the data volumes with `make clean` and starting again.
