#include "Tokenizer.hpp"

int Tokenizer::printError(int err)
{
    if (err == INPUT)
        std::cerr << "\nError: could not open input file\n";
    if (err == BAD_SEMICOLONS)
        std::cerr << "\nSyntax Error: Misuse of Semicolons!\n";
    if (err == BRACKETS)
        std::cerr << "\nSyntax Error: Misuse of Brackets!\n";
    if (err == ORDER)
        std::cerr << "\nSyntax Error: Wrong Token Order!\n";
    if (err == BAD_LOCATION)
        std::cerr << "\nSyntax Error: Wrong Token after Location!\n";
    if (err == BAD_DIRECTIVE)
        std::cerr << "\nSyntax Error: String is not a valid Directive!\n";
    if (err == DIRECTIVE_INCOMPLETE)
        std::cerr << "\nSyntax Error: The Directive is Incomplete!\n";
    if (err == NO_LISTEN)
        std::cerr << "\nSyntax Error: There is no Listen directive in one of the Server Block(s)!\n";
    return (0);
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

int ft_check_brackets(t_type type, int &left_brackets)
{       
    if (type == LBRACE)
    {
        left_brackets++;
        if (left_brackets > 2)
            return (0);
    }
    if (type == RBRACE)
    {
        left_brackets--;
        if (left_brackets < 0)
            return (0);
    }
    return (1);
}

int Tokenizer::ft_check_basic_syntax(void)
{
    std::list<t_node>::iterator it;
    t_type t1;
    t_type t2;
    int left_brackets;

    left_brackets = 0;
    std::cout << "mylist contains:\n";
    it = _tokens_list.begin();
    while (it != _tokens_list.end())
    {
        std::cout << "type is " << (*it).type;
        std::cout << "\nvalue is " << (*it).value;
        t2 = (*it).type;
        if (t2 == LBRACE && !(ft_check_brackets(t2, left_brackets)))
            return (printError(BRACKETS));
        if (t2 == RBRACE && !(ft_check_brackets(t2, left_brackets)))
            return (printError(BRACKETS));
        if (it != _tokens_list.begin())
        {
            it--;
            std::cout << "\nThe previous element is " << (*it).type << '\n';
            t1 = (*it).type;
            it++;
            if (t1 == t2 && t1 == SEMICOLON)
                return (printError(BAD_SEMICOLONS));
            if ((t1 == SEMICOLON && t2 == LBRACE) || ((t1 == RBRACE || t1 == LBRACE) && t2 == SEMICOLON))
                return (printError(BAD_SEMICOLONS));
            if (t1 == LOCATION && t2 != STRING)
                return (printError(BAD_LOCATION));
        }
        std::cout << "\nnext token:\n";
        it++;
        // std::cout << "left brackets are " <<left_brackets << "\n";
    }
    std::cout << "----------------";
    if (left_brackets == 0)
        return (1);
    // std::cout << "left brackets are" <<left_brackets;
    return (printError(LBRACE));
}

int Tokenizer::ft_tokenize(const std::string s1)
{
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
            if (temp[0] == '#')
                break;
			ft_push_token(temp);
		}
		i = i + _len;
		_len = 0;
	}
    return (1);
}

int Tokenizer::ft_compare_with_table(std::string value, std::list<t_node>::iterator &it, int flag_location_block)
{
    const std::string server_block[10] = {"listen", "host", "port", "server_name", "error_page", "client_max_body_size", "return", "root", "index", "autoindex"};
    const std::string location_block[9] = {"error_page", "client_max_body_size", "method", "return", "root", "index", "autoindex", "cgi_pass", "cgi_params"};
    int i;

    i = 0;
    if (flag_location_block == 0)
    {
        while (i < 10)
        {
            if (value == server_block[i])
            {
                std::cout << "Matched directive in server block!\n";
                (*it).type = DIRECTIVE;
                std::cout << "New type is " << (*it).type << "\n";
                return (1);
            }
            i++;
        }
    }
    else
    {
        while (i < 9)
        {
            if (value == location_block[i])
            {
                std::cout << "Matched directive in location block!\n";
                (*it).type = DIRECTIVE;
                std::cout << "New type is " << (*it).type << "\n";
                return (1);
            }
            i++;
        }
    }
    if (flag_location_block == 0)
        std::cout << "\nSever block issue: " << (*it).value << "\n";
    else
        std::cout << "\nLocation block issue: " << (*it).value << "\n";
    return (0);
}


//compare les strings qui sont que apres un SC, LB ou RB!
int Tokenizer::ft_check_directives(std::list<t_node>::iterator &it)
{
    int flag_location_block;
    int flag_valid_server_block;
    t_type t1;
    t_type t2;

    flag_location_block = 0;
    flag_valid_server_block = 0;
    if (it != _tokens_list.end())
    {
        if ((*it).type != SERVER)
            return (printError(ORDER));
        it++;
        if (it == _tokens_list.end() || (*it).type != LBRACE)
            return (printError(ORDER));
        it++;
    }
    while (it != _tokens_list.end())
    {
        std::cout << "\ntype is " << (*it).type;
        std::cout << "\nvalue is " << (*it).value;
        t2 = (*it).type;//current token
        it--;
        std::cout << "\nThe previous element is " << (*it).type << '\n';
        t1 = (*it).type;//previous token
        it++;
        if (t2 != STRING && t1 == DIRECTIVE)
            return (printError(DIRECTIVE_INCOMPLETE));  
        if ((*it).value == "listen")//peut ne pas encore etre une directive
            flag_valid_server_block = 1;
        if (t2 == LOCATION)
            flag_location_block = 1;
        if (flag_location_block == 1 && t2 == RBRACE)
            flag_location_block = 0;
        else if (flag_location_block == 0 && t2 == RBRACE)//end of first server block
        {
            if (!(flag_valid_server_block))
                return (printError(NO_LISTEN));
            it++;// passer au server suivant ou sur null si fin!
            std::cout << "\n-----------Check new server block---------\n";
            if (!(ft_check_directives(it)))
                return (0);
            return (1);
        }
        if (t2 == STRING && (t1 == SEMICOLON || t1 == LBRACE || t1 == RBRACE))//make a current string a directive
        {
            if (!(ft_compare_with_table((*it).value, it, flag_location_block)))
                return (printError(BAD_DIRECTIVE));
        }
        it++;
    }
    return (1);

}

int Tokenizer::ft_check_server_blocks(void)
{
    std::list<t_node>::iterator it;

    it = _tokens_list.begin();
    if (!(ft_check_directives(it)))
        return (0);
    return (1);
}

const std::list<t_node> &Tokenizer::ft_get_token_list(void) const
{
    return (_tokens_list);
}


Tokenizer::Tokenizer(std::string file)
{
    std::ifstream fileIn;
    std::string buff;

    fileIn.open(file.c_str());
    if (!fileIn.good())
    {
        printError(INPUT);
        throw std::runtime_error("");
    }
    while (getline(fileIn, buff))
        ft_tokenize(buff + '\n');

    if (!(ft_check_basic_syntax()))
    {
        fileIn.close();
        throw std::runtime_error("");
    }
    std::cout << "DIRECTIVES-------------\n";
    if (!(ft_check_server_blocks()))
    {
        fileIn.close();
        throw std::runtime_error("");
    }
    else
        std::cout << "\nok!\n";

    fileIn.close();
}

Tokenizer::~Tokenizer(){}