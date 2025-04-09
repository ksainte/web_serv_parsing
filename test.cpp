#include <iostream>


void ft_test(std::string &s1)
{
    std::cout <<&s1 << "\n";
    s1 = "ccc";
}

int main()
{
    std::string s1;

    s1 = "a";
    std::cout <<&s1 << "\n";
    ft_test(s1);
    std::cout <<&s1 << "\n";
    std::cout <<s1 << "\n";

    
    return (0);

}