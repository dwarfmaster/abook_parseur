
#include "parser.hpp"
#include <fstream>
#include <sstream>

namespace abook_parser
{
    /* Indicates if the line is the beggining of a new contact. */
    bool newContact(const std::string& line)
    {
        if(line.size() < 3)
            return false;

        if(line[0] != '[' || line[line.size() - 1] != ']')
            return false;

        for(size_t i = 1; i < line.size() - 1; ++i) {
            if(line[i] < '0'
                    || line[i] > '9')
                return false;
        }

        return true;
    }

    /* Get the two elements of a line. ret.first is empty if the line
     * is invalid.
     */
    std::pair<std::string,std::string> parseLine(const std::string& line)
    {
        if(line.empty())
            return std::pair<std::string,std::string>();

        std::vector<std::string> parts;
        std::istringstream iss(line);
        std::string part;
        while(std::getline(iss, part, '='))
            parts.push_back(part);

        if(parts.size() != 2)
            return std::pair<std::string,std::string>();
        else
            return std::pair<std::string,std::string>(parts[0], parts[1]);
    }

    Contacts load(const std::string& path)
    {
        std::ifstream ifs(path.c_str());
        if(!ifs)
            return Contacts();

        Contact* act = NULL;
        std::string line;
        Contacts cts;
        while(std::getline(ifs, line)) {
            if(newContact(line)) {
                if(act != NULL)
                    cts.push_back(act);
                act = new Contact;
            }

            else if(act != NULL) {
                std::pair<std::string,std::string> p = parseLine(line);
                if(!p.first.empty())
                    act->keys[p.first] = p.second;
            }
        }

        if(act != NULL && act->keys.begin() != act->keys.end())
            cts.push_back(act);
        else if(act != NULL)
            delete act;

        return cts;
    }

    void free(Contacts& cts)
    {
        for(size_t i = 0; i < cts.size(); ++i)
            delete cts[i];
        cts.clear();
    }
    
    bool save(const Contacts& cts, const std::string& path)
    {
        std::ofstream ofs(path.c_str(), std::ios::trunc);
        if(!ofs)
            return false;

        ofs << "# abook addressbook file\n\n[format]\nprogram=abook\nversion=0.6.0pre2\n\n" << std::endl;
        int nb = 0;
        for(size_t i = 0; i < cts.size(); ++i) {
            std::map<std::string,std::string>::iterator it = cts[i]->keys.begin();
            ofs << "[" << nb << "]" << std::endl;
            for(; it != cts[i]->keys.end(); ++it)
                ofs << it->first << "=" << it->second << std::endl;
            ofs << std::endl;
            ++nb;
        }

        return true;
    }

}

