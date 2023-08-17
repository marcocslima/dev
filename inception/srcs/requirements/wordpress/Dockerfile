# Define a imagem base como Debian Bullseye.
FROM debian:bullseye

# Atualiza a lista de pacotes e instala os pacotes necessários.
RUN apt-get update && apt-get install -y \
    gettext \  # Pacote para manipulação de textos internacionalizados. \
    php7.4 php7.4-fpm php7.4-cli \  # Instalação do PHP 7.4 e seus componentes. \
    wget curl procps \  # Ferramentas utilitárias, incluindo wget e curl. \
    php7.4-curl php7.4-mysql php7.4-mbstring php7.4-xml php7.4-gd \  # Extensões PHP comuns. \
    sendmail mariadb-client gettext-base \  # Instalação de cliente MariaDB e utilitários. \
    nano \  # Editor de texto nano. \
    && apt-get clean \  # Limpa o cache dos pacotes instalados. \
    && rm -rf /var/lib/apt/lists/* \  # Remove arquivos de listas de pacotes antigos. \
    && mkdir /run/php  # Criação do diretório para PHP-FPM.

# Download e instalação do WP-CLI (Interface de Linha de Comando do WordPress).
RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
        --output-document=/usr/local/bin/wp \
        && chmod +x /usr/local/bin/wp

# Criação de diretórios e definição de permissões para diretórios e arquivos.
RUN mkdir -p /run/php /var/www/html/wordpress \
    && chmod -R 755 /var/www/html/

# Copia o arquivo de configuração do PHP-FPM.
COPY ./conf/www.conf /etc/php/7.4/fpm/pool.d/www.conf
RUN chmod 755 /etc/php/7.4/fpm/pool.d/www.conf

# Define o diretório de trabalho para o diretório raiz do site WordPress.
WORKDIR /var/www/html/

# Faz o download do núcleo do WordPress usando o WP-CLI.
RUN wp core download --allow-root

# Copia o script de inicialização personalizado para a pasta /usr/local/bin/.
COPY tools/init.sh /usr/local/bin/

# Concede permissão de execução ao script de inicialização.
RUN chmod +x /usr/local/bin/init.sh

# Define o ponto de entrada do contêiner como o script de inicialização.
ENTRYPOINT [ "init.sh" ]

# Expõe a porta 9000 para o PHP-FPM.
EXPOSE 9000

# Define o comando padrão que será executado quando o contêiner for iniciado.
CMD ["/usr/sbin/php-fpm7.4", "-F", "-R"]
