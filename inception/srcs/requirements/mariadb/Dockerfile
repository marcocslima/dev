# Define a imagem base como Debian Bullseye.
FROM debian:bullseye

# Atualiza a lista de pacotes, atualiza o sistema e instala os pacotes necessários.
RUN apt update -y && apt upgrade -y && apt install \
    mariadb-server -y \  # Instalação do servidor MariaDB. \
    nano  # Editor de texto nano.

# Remove o arquivo de configuração padrão do MariaDB.
RUN rm /etc/mysql/mariadb.conf.d/50-server.cnf

# Copia o arquivo de configuração personalizado para o MariaDB.
COPY ./conf/50-server.cnf /etc/mysql/mariadb.conf.d/

# Define permissões para o arquivo de configuração do MariaDB.
RUN chmod 644 /etc/mysql/mariadb.conf.d/50-server.cnf

# Define o proprietário e o grupo para os dados do MariaDB.
RUN chown -R mysql:mysql /var/lib/mysql

# Copia o script de inicialização personalizado para a pasta /usr/local/bin/.
COPY ./tools/init.sh /usr/local/bin/

# Concede permissão de execução ao script de inicialização.
RUN chmod +x /usr/local/bin/init.sh

# Define o ponto de entrada para iniciar o script de inicialização.
ENTRYPOINT ["init.sh"]

# Define o comando padrão para executar o MariaDB em modo seguro.
CMD ["/usr/bin/mysqld_safe"]
