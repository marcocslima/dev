# Define a imagem base como Debian Bullseye.
FROM debian:bullseye

# Atualiza a lista de pacotes, atualiza o sistema e instala os pacotes necessários.
RUN apt update -y && apt upgrade -y && apt install nginx -y \
        && apt install nano -y && apt install curl -y

# Cria o diretório para armazenar os certificados SSL do Nginx.
RUN mkdir -p /etc/nginx/ssl

# Instala o OpenSSL, uma ferramenta para trabalhar com criptografia SSL/TLS.
RUN apt install openssl -y

# Gera um certificado autoassinado usando o OpenSSL para uso com o Nginx.
RUN openssl req -x509 -nodes \
        -out /etc/nginx/ssl/inception.crt \
        -keyout /etc/nginx/ssl/inception.key \
        -subj "/C=BR/ST=SP/L=SP/O=42sp/CN=$DOMAIN_NAME/UID=$LOGIN_42"

# Cria o diretório para o socket (conexão) do Nginx.
RUN mkdir -p /var/run/nginx

# Copia o arquivo de configuração do Nginx para a pasta de configuração padrão.
COPY ./conf/nginx.conf /etc/nginx/nginx.conf

# Define permissões para a pasta raiz do site.
RUN chmod 755 /var/www/html

# Define o proprietário e o grupo da pasta raiz do site como www-data.
RUN chown -R www-data:www-data /var/www/html

# Expõe a porta 443 para tráfego seguro.
EXPOSE 443

# Define o comando padrão para iniciar o Nginx em modo de daemon.
CMD ["nginx", "-g", "daemon off;"]
