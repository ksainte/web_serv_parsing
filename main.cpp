#include "Tokenizer.hpp"

int main(int argc, char **argv)
{
    try
    {
        Tokenizer tokenizer("webserv.config");
    }
    catch(std::exception &error)
    {
        return (1);
        // std::cerr << error.what() << "\n";
    }
    return (0);
}

// server {
//     listen       82;
//     server_name  localhost;

//     #charset koi8-r;

//     #access_log  logs/host.access.log  main;

//     location / {
//         root   /usr/local/nginx/html;
//         index  index.html index.htm;
//     }
//}
// server {
//     listen 192.168.1.100:8080;
//     server_name test.example another.domain;

//     location / {
//         method GET;
//         index index.html main.htm;
//         autoindex off;
//         error_page 404 /errors/not_found.html;
//         root /var/www/main;
//     }

//     location /images {
//         method GET;
//         root /opt/static/pictures/;
//         autoindex on;
//     }

//     location /cgi-bin {
//         method GET POST;
//         cgi_pass /usr/bin/python3;
//         cgi_params SCRIPT_NAME /cgi-bin/my_script.py;
//         cgi_params SERVER_PORT 8080;
//     }

//     location /upload {
//         method POST;
//         client_max_body_size 10m;
//     }

//     location /old-page {
//         return 301 /new-page;
//     }

//     location /gone {
//         return 410 "This page is permanently gone.";
//     }
// }

// server {
//     listen 127.0.0.1:9000;
//     server_name localhost;

//     location /app {
//         method GET;
//         root /var/app/;
//         index application.php;
//         cgi_pass /usr/bin/php-fpm;
//         cgi_params PHP_VALUE "upload_max_filesize=2M";
//     }
// }