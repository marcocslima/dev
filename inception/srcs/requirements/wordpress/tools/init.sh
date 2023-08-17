#!/bin/sh

# Verifica se o arquivo wp-config.php já existe.
if [ -f ./wp-config.php ]
then
    echo "O WordPress já está configurado."
else
    # Substitui os placeholders no arquivo wp-config-sample.php pelos valores das variáveis.
    sed -i "s/username_here/$WORDPRESS_USER/g" wp-config-sample.php
    sed -i "s/password_here/$WORDPRESS_PASSWORD/g" wp-config-sample.php
    sed -i "s/localhost/$WORDPRESS_HOSTNAME/g" wp-config-sample.php
    sed -i "s/database_name_here/$WORDPRESS_DATABASE/g" wp-config-sample.php

    # Copia o arquivo wp-config-sample.php modificado para wp-config.php.
    cp wp-config-sample.php wp-config.php
fi

# Executa o comando passado como argumento.
exec "$@"
