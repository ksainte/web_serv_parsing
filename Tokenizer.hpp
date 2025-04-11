#ifndef TOKEN_HPP
# define TOKEN_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <list>

typedef enum s_token_type
{
	LOCATION = 1,
	SERVER = 2,
	LBRACE = 3,
	RBRACE = 4,
	SEMICOLON = 5,
	DIRECTIVE = 6,
	STRING = 7,
	INVALID = 8
}							t_type;

typedef struct s_node
{
	t_type					type;
	std::string				value;
	s_node(t_type _type, std::string _value):type(_type), value(_value){};
}							t_node;

class Tokenizer
{
	private:
		std::list<t_node> _tokens_list;
		int				  _len;

	public:
		// Tokenizer();
		// ~Tokenizer();

		int ft_tokenize(std::string s1);
		void ft_push_token(std::string s1);
		int ft_check_basic_syntax(void);
		int ft_check_directives(void);
		int ft_check_server_blocks(void);
		int ft_compare_with_table(std::string value, std::list<t_node>::iterator &it, int flag_location_block);
	
};

#endif