
#ifndef DEF_ABOOK_PARSER_PARSER
#define DEF_ABOOK_PARSER_PARSER

#include "storage.hpp"

namespace abook_parser
{
    typedef std::vector<Contact*> Contacts;

    Contacts load(const std::string& path);
    void free(Contacts& cts);
}

#endif

