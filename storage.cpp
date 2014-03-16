
#include "storage.hpp"
#include <sstream>
#include <algorithm>

std::vector<std::string> Contact::mails() const
{
    std::map<std::string,std::string>::const_iterator it = keys.find("email");
    if(it == keys.end())
        return std::vector<std::string>();

    std::istringstream iss(it->second);
    std::string line;
    std::vector<std::string> ret;
    while(std::getline(iss, line, ','))
        ret.push_back(line);
    return ret;
}

void Contact::addMail(const std::string& m)
{
    std::map<std::string,std::string>::const_iterator it = keys.find("email");
    if(it == keys.end()) {
        keys["email"] = m;
        return;
    }

    keys["email"] += ',';
    keys["email"] += m;
}

void Contact::setMail(const std::vector<std::string>& ms)
{
    if(ms.empty()) {
        keys["email"].clear();
        return;
    }

    std::ostringstream oss;
    oss << ms[0];
    for(size_t i = 1; i < ms.size(); ++i)
        oss << ',' << ms[i];
    keys["email"] = oss.str();
}

void Contact::rmMail(size_t id)
{
    std::vector<std::string> ms = mails();
    if(id >= ms.size())
        return;

    ms.erase(ms.begin() + id);
    setMail(ms);
}

void Contact::rmMail(const std::string& m)
{
    std::vector<std::string> ms = mails();
    std::vector<std::string>::iterator it = std::find(ms.begin(), ms.end(), m);
    if(it == ms.end())
        return;

    ms.erase(it);
    setMail(ms);
}


