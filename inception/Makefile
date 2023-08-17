# Nome do arquivo Docker Compose.
COMPOSE := srcs/docker-compose.yml

# Arquivo de variáveis de ambiente.
ENV_FILE := srcs/.env

# Caminho para os diretórios de volumes.
VOLUMES_PATH :=/home/mcesar-d/data

# Nome de login.
LOGIN := mcesar-d

# Regra padrão, executada quando nenhum alvo é especificado ao chamar o make.
all: $(ENV_FILE)
	@make setup
	@make assemble

# Regra para montar e iniciar os contêineres.
assemble:
	docker-compose --file=$(COMPOSE) up --build --detach

# Regra para parar e remover os contêineres.
down:
	docker-compose --file=$(COMPOSE) down || true

# Regra para parar, remover todos os contêineres, reconstruir e reiniciar.
rb: down fclean all

# Regra para configurar o ambiente.
setup: $(ENV_FILE)
	@sudo mkdir -p $(VOLUMES_PATH)/wordpress
	@sudo mkdir -p $(VOLUMES_PATH)/mariadb
	@sudo grep $(LOGIN).42.fr /etc/hosts || sudo bash -c 'echo "127.0.0.1 $(LOGIN).42.fr" >> /etc/hosts'

# Regra para limpar arquivos temporários.
clean:
	@rm -f srcs/.env || true

# Regra para remover todos os contêineres, imagens e volumes, além de limpar os volumes no host.
fclean:
	@docker rmi -f $$(docker images -q) || true
	@docker volume rm $$(docker volume ls -q) || true
	@sudo rm -rf $(VOLUMES_PATH) || true

# Regra para remover tudo e construir novamente.
re: fclean all
	@echo "[Success]: Completely restarted."

# Define as regras que não correspondem a arquivos.
.PHONY: all assemble down setup clean fclean re
