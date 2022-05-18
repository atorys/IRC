#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <iostream>

namespace ut{
    std::string to_lower(std::string str);
    bool wildcard(std::string regex, std::string comp);
    std::vector<std::string> split(std::string &str, std::string const &sep);
    std::vector<std::string> splitForCmd(std::string &request);
}