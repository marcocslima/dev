#!/bin/bash

# Verifica se as variáveis de ambiente necessárias foram definidas.
if [ -z "$MYSQL_ROOT_PASSWORD" ] || [ -z "$WORDPRESS_DATABASE" ] || [ -z "$WORDPRESS_USER" ] || [ -z "$WORDPRESS_PASSWORD" ]; then
    echo "Erro: Algumas variáveis de ambiente não foram definidas."
    exit 1
fi

# Inicia o servidor MariaDB em segundo plano.
mysqld_safe --skip-syslog &

# Aguarda até que o servidor MariaDB esteja pronto para aceitar comandos.
while ! mysqladmin ping -hlocalhost --silent; do
    sleep 1
done

# Verifica se o banco de dados já existe.
if ! mysql -e "USE $WORDPRESS_DATABASE;";
then
    # Cria o banco de dados e o usuário.
    mysql -e "CREATE DATABASE $WORDPRESS_DATABASE;"
    mysql -e "CREATE USER '$WORDPRESS_USER'@'%' IDENTIFIED BY '$WORDPRESS_PASSWORD';"
    mysql -e "GRANT ALL PRIVILEGES ON $WORDPRESS_DATABASE.* TO '$WORDPRESS_USER'@'%';"
    mysql -e "FLUSH PRIVILEGES;"

    echo "Banco de dados foi criado com sucesso."
else
    echo "Banco de dados '$WORDPRESS_DATABASE' já existe."
fi

# Encerra o servidor MariaDB.
mysqladmin shutdown

# Aguarda até que o servidor esteja completamente desligado.
while mysqladmin ping -hlocalhost --silent; do
    sleep 1
done

# Inicia novamente o servidor MariaDB em modo seguro.
exec mysqld_safe
