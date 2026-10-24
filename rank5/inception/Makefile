COMPOSE = docker compose --env-file srcs/.env -f srcs/docker-compose.yml

# Read the data location from .env so the Makefile and Compose stay in sync.
DATA_PATH := $(shell sed -n 's/^DATA_PATH=//p' srcs/.env 2>/dev/null | tail -n 1)
DATA := $(if $(DATA_PATH),$(DATA_PATH),$(HOME)/data)

SECRETS = secrets/db_root_password.txt secrets/db_password.txt \
          secrets/credentials.txt secrets/wp_user_password.txt

all: check-env check-secrets
	@mkdir -p "$(DATA)/wordpress" "$(DATA)/mariadb"
	@$(COMPOSE) up -d --build

build: check-env check-secrets
	@$(COMPOSE) build --no-cache

up: check-env check-secrets
	@$(COMPOSE) up -d

down:
	@$(COMPOSE) down

start:
	@$(COMPOSE) start

stop:
	@$(COMPOSE) stop

restart:
	@$(COMPOSE) restart

logs:
	@$(COMPOSE) logs -f

status:
	@$(COMPOSE) ps

clean:
	@$(COMPOSE) down -v

fclean: clean
	@docker system prune -af
	@rm -rf "$(DATA)" 2>/dev/null || sudo rm -rf "$(DATA)"

check-secrets:
	@missing=0; \
	for f in $(SECRETS); do \
		if [ ! -s "$$f" ]; then \
			echo "Error: missing or empty secret: $$f"; \
			missing=1; \
		fi; \
	done; \
	if [ $$missing -ne 0 ]; then \
		echo "Create the secret files first (see DEV_DOC.md)."; \
		exit 1; \
	fi

check-env:
	@if [ ! -f srcs/.env ]; then \
		echo "Error: srcs/.env is missing."; \
		echo "Copy srcs/.env.example to srcs/.env first."; \
		exit 1; \
	fi

re: fclean all

.PHONY: all build up down start stop restart logs status clean fclean check-env check-secrets re
