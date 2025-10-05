# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmensah- <hmensah-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/05 00:00:00 by hmensah-          #+#    #+#              #
#    Updated: 2025/10/05 00:00:00 by hmensah-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                               PROJECT CONFIGURATION                          #
# **************************************************************************** #

NAME			= inception
COMPOSE_FILE	= srcs/docker-compose.yml
ENV_FILE		= srcs/.env
DATA_PATH		= /home/hmensah-/data

# Docker Compose command
DOCKER_COMPOSE	= docker compose -f $(COMPOSE_FILE)

# Colors for output
RESET			= \033[0m
GREEN			= \033[32m
YELLOW			= \033[33m
BLUE			= \033[34m
RED				= \033[31m

# **************************************************************************** #
#                               PHONY TARGETS                                  #
# **************************************************************************** #

.PHONY: all build up down start stop restart logs clean fclean re \
		status ps volumes networks prune help create-dirs

# **************************************************************************** #
#                               MAIN TARGETS                                   #
# **************************************************************************** #

all: create-dirs build up
	@echo "$(GREEN)✓ Inception infrastructure is up and running!$(RESET)"

# Build all Docker images
build:
	@echo "$(BLUE)Building Docker images...$(RESET)"
	@$(DOCKER_COMPOSE) build --no-cache
	@echo "$(GREEN)✓ Docker images built successfully!$(RESET)"

# Build and start containers in detached mode
up: create-dirs
	@echo "$(BLUE)Starting Docker containers...$(RESET)"
	@$(DOCKER_COMPOSE) up -d
	@echo "$(GREEN)✓ Docker containers started successfully!$(RESET)"

# Stop and remove containers
down:
	@echo "$(YELLOW)Stopping Docker containers...$(RESET)"
	@$(DOCKER_COMPOSE) down
	@echo "$(GREEN)✓ Docker containers stopped!$(RESET)"

# Start existing containers
start:
	@echo "$(BLUE)Starting Docker containers...$(RESET)"
	@$(DOCKER_COMPOSE) start
	@echo "$(GREEN)✓ Docker containers started!$(RESET)"

# Stop running containers without removing them
stop:
	@echo "$(YELLOW)Stopping Docker containers...$(RESET)"
	@$(DOCKER_COMPOSE) stop
	@echo "$(GREEN)✓ Docker containers stopped!$(RESET)"

# Restart all containers
restart: stop start

# **************************************************************************** #
#                               UTILITY TARGETS                                #
# **************************************************************************** #

# Show container logs
logs:
	@$(DOCKER_COMPOSE) logs -f

# Show status of containers
status:
	@$(DOCKER_COMPOSE) ps

ps: status

# List volumes
volumes:
	@echo "$(BLUE)Docker volumes:$(RESET)"
	@docker volume ls | grep inception || echo "No inception volumes found"

# List networks
networks:
	@echo "$(BLUE)Docker networks:$(RESET)"
	@docker network ls | grep inception || echo "No inception networks found"

# **************************************************************************** #
#                               CLEANUP TARGETS                                #
# **************************************************************************** #

# Stop containers and remove volumes
clean: down
	@echo "$(YELLOW)Removing Docker volumes...$(RESET)"
	@docker volume rm $$(docker volume ls -q | grep inception) 2>/dev/null || true
	@echo "$(GREEN)✓ Docker volumes removed!$(RESET)"

# Full cleanup: stop containers, remove images, volumes, networks, and data
fclean: down
	@echo "$(RED)Performing full cleanup...$(RESET)"
	@echo "$(YELLOW)Removing Docker containers...$(RESET)"
	@docker rm -f $$(docker ps -aq) 2>/dev/null || true
	@echo "$(YELLOW)Removing Docker images...$(RESET)"
	@docker rmi -f $$(docker images -q) 2>/dev/null || true
	@echo "$(YELLOW)Removing Docker volumes...$(RESET)"
	@docker volume rm $$(docker volume ls -q) 2>/dev/null || true
	@echo "$(YELLOW)Removing Docker networks...$(RESET)"
	@docker network rm $$(docker network ls -q) 2>/dev/null || true
	@echo "$(YELLOW)Removing data directories...$(RESET)"
	@sudo rm -rf $(DATA_PATH) 2>/dev/null || true
	@echo "$(GREEN)✓ Full cleanup completed!$(RESET)"

# Rebuild everything from scratch
re: fclean all

# Remove unused Docker resources
prune:
	@echo "$(YELLOW)Pruning unused Docker resources...$(RESET)"
	@docker system prune -af --volumes
	@echo "$(GREEN)✓ Docker system pruned!$(RESET)"

# **************************************************************************** #
#                               SETUP TARGETS                                  #
# **************************************************************************** #

# Create necessary data directories
create-dirs:
	@echo "$(BLUE)Creating data directories...$(RESET)"
	@sudo mkdir -p $(DATA_PATH)/wordpress
	@sudo mkdir -p $(DATA_PATH)/mariadb
	@sudo chmod -R 755 $(DATA_PATH)
	@echo "$(GREEN)✓ Data directories created!$(RESET)"

# **************************************************************************** #
#                               HELP TARGET                                    #
# **************************************************************************** #

help:
	@printf "$(BLUE)╔═══════════════════════════════════════════════════════════════╗$(RESET)\n"
	@printf "$(BLUE)║              INCEPTION - Docker Infrastructure                ║$(RESET)\n"
	@printf "$(BLUE)╚═══════════════════════════════════════════════════════════════╝$(RESET)\n"
	@printf "\n"
	@printf "$(GREEN)Main Targets:$(RESET)\n"
	@printf "  $(YELLOW)make all$(RESET)      - Create directories, build images, and start containers\n"
	@printf "  $(YELLOW)make build$(RESET)    - Build all Docker images from Dockerfiles\n"
	@printf "  $(YELLOW)make up$(RESET)       - Create and start containers in detached mode\n"
	@printf "  $(YELLOW)make down$(RESET)     - Stop and remove containers\n"
	@printf "  $(YELLOW)make start$(RESET)    - Start existing containers\n"
	@printf "  $(YELLOW)make stop$(RESET)     - Stop running containers\n"
	@printf "  $(YELLOW)make restart$(RESET)  - Restart all containers\n"
	@printf "\n"
	@printf "$(GREEN)Utility Targets:$(RESET)\n"
	@printf "  $(YELLOW)make logs$(RESET)     - Show and follow container logs\n"
	@printf "  $(YELLOW)make status$(RESET)   - Show status of all containers\n"
	@printf "  $(YELLOW)make volumes$(RESET)  - List all Docker volumes\n"
	@printf "  $(YELLOW)make networks$(RESET) - List all Docker networks\n"
	@printf "\n"
	@printf "$(GREEN)Cleanup Targets:$(RESET)\n"
	@printf "  $(YELLOW)make clean$(RESET)    - Stop containers and remove volumes\n"
	@printf "  $(YELLOW)make fclean$(RESET)   - Full cleanup (containers, images, volumes, data)\n"
	@printf "  $(YELLOW)make re$(RESET)       - Full rebuild (fclean + all)\n"
	@printf "  $(YELLOW)make prune$(RESET)    - Remove all unused Docker resources\n"
	@printf "\n"
	@printf "$(GREEN)Setup Targets:$(RESET)\n"
	@printf "  $(YELLOW)make create-dirs$(RESET) - Create necessary data directories\n"
	@printf "\n"
	@printf "$(BLUE)╚═══════════════════════════════════════════════════════════════╝$(RESET)\n"

# Default target shows help
.DEFAULT_GOAL := help
