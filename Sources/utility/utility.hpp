#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <unistd.h>

namespace ut{
    std::string to_lower(std::string str);
    bool wildcard(std::string regex, std::string comp);
    std::vector<std::string> split(std::string const &str, std::string const &sep);
}