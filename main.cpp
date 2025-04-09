#include <iostream>
#include <fstream>
#include <string>
#include "Tokenizer.hpp"
#define ARGS 0
#define INPUT 1
#define OUTPUT 2

int printError(int err)
{
    if (err == INPUT)
        std::cerr << "Error: could not open input file" << std::endl;
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

void Tokenizer::ft_filled_token(std::string s1)
{
    t_type type;
    std::string value;
    std::list<t_node>::iterator it;

    value = ft_get_value(s1);
    _len = value.length();
    type = ft_get_type_token(value);
    if (type != STRING)
        _tokens_list.push_back(t_node(type, "\0"));
    else
        _tokens_list.push_back(t_node(type, value));

}



void Tokenizer::ft_tokenize(const std::string s1)
{
    std::list<t_node>::iterator it;
    std::string temp;

    int i;


    i = 0;
    _len = 0;
	while (s1[i])
	{
		if ((s1[i] <= 12 && s1[i] >= 9) || s1[i] == 32)
			i++;
		else
		{
            temp = s1.substr(i);
			ft_filled_token(temp);
		}
		i = i + _len;
		_len = 0;
	}

    std::cout << "mylist contains:\n";
    for (it = _tokens_list.begin(); it != _tokens_list.end(); ++it)
    {
        std::cout << ' ' << (*it).type;
        std::cout << ' ' << (*it).value;
        std::cout << "\nnext token:\n";
    }
    std::cout << "----------------";
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
        return printError(INPUT);

    while (getline(fileIn, buff))
    {
        tokenizer.ft_tokenize(buff + '\n');
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