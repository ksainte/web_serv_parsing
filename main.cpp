#include <iostream>
#include <fstream>
#include <string>
#include "Tokenizer.hpp"
#define ARGS 0
#define INPUT 1
#define SYNTAX 2

int printError(int err)
{
    if (err == INPUT)
        std::cerr << "Error: could not open input file" << std::endl;
    if (err == SYNTAX)
        std::cerr << "Error: Syntax is wrong!" << std::endl;
    return (1);
}

std::string	ft_get_value(std::string s1)
{
    int i;

    i = 0;
    if (s1[i] == '{' || s1[i] == '}' || s1[i] == ';')
    {
        s1 = s1.substr(0, 1);
        return (s1);
    }
    while(s1[i])
    {
        if ((s1[i] <= 12 && s1[i] >= 9) || s1[i] == 32 || s1[i] == '{' || s1[i] == '}' || s1[i] == ';')
            break;
        i++;
    }
    s1 = s1.substr(0, i);
    return(s1);
}

t_type	ft_get_type_token(std::string s1)
{
	if (s1[0] == '{')
		return (LBRACE);
    if (s1[0] == '}')
		return (RBRACE);
    if (s1[0] == ';')
		return (SEMICOLON);
    if (s1.compare("location") == 0)
		return (LOCATION);
    if (s1.compare("server") == 0)
		return (SERVER);
	return (STRING);
}

void Tokenizer::ft_push_token(std::string s1)
{
    t_type type;
    std::string value;
    std::list<t_node>::iterator it;

    value = ft_get_value(s1);
    _len = value.length();
    type = ft_get_type_token(value);
    if (type != STRING)
        _tokens_list.push_back(t_node(type, value));
    else
        _tokens_list.push_back(t_node(type, value));

}



int Tokenizer::ft_tokenize(const std::string s1)
{
    std::list<t_node>::iterator it;
    std::string temp;
    t_type t1;
    t_type t2;


    int i;
    int list_len;

    list_len = 0;
    i = 0;
    _len = 0;
	while (s1[i])
	{
		if ((s1[i] <= 12 && s1[i] >= 9) || s1[i] == 32)
			i++;
		else
		{
            temp = s1.substr(i);
            if (temp[0] == '#')
                break;
			ft_push_token(temp);
		}
		i = i + _len;
		_len = 0;
	}
    std::cout << "mylist contains:\n";
    it = _tokens_list.begin();
    while (it != _tokens_list.end())
    {
        std::cout << "type is " << (*it).type;
        std::cout << "\nvalue is " << (*it).value;
        if (it != _tokens_list.begin())
        {
            it--;
            std::cout << "\nThe previous element is " << (*it).type << '\n';
            t1 = (*it).type;
            it++;
            t2 = (*it).type;
            if (t1 == t2 && t1 == SEMICOLON)
                return (0);
        }
        std::cout << "\nnext token:\n";
        it++;
    }
    std::cout << "----------------";
    return (1);
}

int main(int argc, char **argv)
{
    std::ifstream fileIn;
    std::string s1;
    std::string buff;
    std::string file;
    Tokenizer tokenizer;
    std::string test;

    file = "webserv.config";
    fileIn.open(file.c_str());
    if (!fileIn.good())
        return (printError(INPUT));

    while (getline(fileIn, buff))
    {
        if (!(tokenizer.ft_tokenize(buff + '\n')))
        {
            return (printError(SYNTAX));
        }
    }

    fileIn.close();

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