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
    typedef std::string::size_type size_type;
    std::vector<std::string> splitbystars;
    std::vector<std::string> temp = ut::split(regex, "*");
    
    size_type len = 0;
    size_type pos1 = 0;
    size_type pos2 = 0;

    if (regex[0] == '*'){
        splitbystars.push_back("*");
    }
    for (size_t i = 0; i < temp.size(); i++){
        splitbystars.push_back(temp[i]);
        splitbystars.push_back("*");
    }
    if (regex[regex.size() - 1] != '*'){
        splitbystars.pop_back();
    }
    for(size_type i = 0; i < splitbystars.size(); i++){
        if (splitbystars[i][0] == '*')
            continue;
        pos2 = std::string(comp.begin() + pos1 + len, comp.end()).find(splitbystars[i]);
        pos1 = pos2 + pos1 + len;
        if ((pos2 == std::string::npos) || (pos2 && (!i || splitbystars[i - 1][0] != '*')))
            return false;
        len = splitbystars[i].size();
        if (i + 1 == splitbystars.size())
            if (regex[regex.size() - 1] != '*')
                if (comp.size() != pos1 + len)
                    i--;
    }
    return true;
}

std::vector<std::string> ut::split(std::string &str, std::string const &sep){
    std::vector<std::string> result;
    if (str.find(sep) == std::string::npos)
        result.push_back(str);
    while (str.find(sep) != std::string::npos) {
        result.push_back(str.substr(0, str.find(sep)));
        str.erase(0, str.find(sep) + 1);
        if ((str.find(sep) == std::string::npos)){
            result.push_back(str);
            break;
        }
    }
    return result;
}