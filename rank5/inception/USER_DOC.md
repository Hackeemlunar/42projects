# User documentation — Inception

## Services provided

The stack provides three services:

- **NGINX** — reverse proxy and TLS terminator; the only public entry point, listening on port 443 with TLSv1.2/TLSv1.3.
- **WordPress + PHP-FPM** — the WordPress website and its PHP-FPM backend (internal only).
- **MariaDB** — the database engine (internal only).

## Starting and stopping the project

From the project root:

```sh
make          # build and start everything
make up       # start the containers
make stop     # stop the containers (keep them)
make down     # stop and remove the containers
make re       # rebuild everything from scratch
```

## Accessing the website and the administration panel

- Website: `https://hmensah-.42.fr`
- Admin panel: `https://hmensah-.42.fr/wp-admin`

Make sure your host resolves `hmensah-.42.fr` to the VM's IP address (add an entry in `/etc/hosts`). The TLS certificate is self-signed, so the browser will show a warning.

## Locating and managing credentials

Usernames and non-sensitive configuration are in `srcs/.env`. Passwords are **not** in that file; they are stored in the local `secrets/` directory:

- `secrets/credentials.txt` — WordPress administrator password (`WP_ADMIN_USER`, default `hmensah`)
- `secrets/wp_user_password.txt` — password of the second WordPress user (`WP_USER`, default `wp_author`)
- `secrets/db_password.txt` — WordPress database user password
- `secrets/db_root_password.txt` — MariaDB root password

These files are ignored by Git and should have `600` permissions. To change a password, edit the corresponding file. If the database has already been initialized, also update the password inside MariaDB/WordPress or recreate the volumes with `make clean` before restarting the stack.

## Checking that services are running correctly

```sh
make status   # list containers and their state
make logs     # follow the logs of all containers
```

All containers should show `Up` and restart automatically in case of a crash. The website should load over HTTPS and the administration panel should accept the administrator credentials from `secrets/credentials.txt`.
