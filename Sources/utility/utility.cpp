#include "utility.hpp"

std::string ut::to_lower(std::string str){
    std::string::iterator start, end;

    start = str.begin();
    end = str.end();

    while (start != end) {
        if ((*start) >= 'A' && (*start) <= 'Z')
            (*start) += 32;
        start++;
    }
    return str;
}

bool ut::wildcard(std::string regex, std::string comp){
    // typedef std::string::size_type size_type;
    // std::vector<std::string> splitbystars;
    // std::vector<std::string> temp = 
    return true;
}

std::vector<std::string> ut::split(std::string const &str, std::string const &sep){
    std::vector<std::string> result;
    char *str1 = new char[str.size() + 1];
    char *tmp = NULL;
    
    str1[str.size()] = '\0';
    //завтра напишу, я устал тут
}