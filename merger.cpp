
#include "parser.hpp"
#include <iostream>

typedef std::map<std::string,abook_parser::Contact*> SavedCts;

void addContact(SavedCts& cts, abook_parser::Contact* ct)
{
    /* Can't handle noname contacts. */
    if(ct->keys.find("name") == ct->keys.end())
        return;
    std::string name = ct->keys.find("name")->second;

    /* Is the contact already present. */
    SavedCts::iterator it = cts.find(name);
    if(it == cts.end()) {
        cts[name] = ct;
        return;
    }

    /* Merging contacts. */
    abook_parser::Contact* prev_ct = it->second;
    std::map<std::string,std::string>::iterator keys = ct->keys.begin();
    for(; keys != ct->keys.end(); ++keys) {
        /* Emails are a special case, handled later. */
        if(keys->first == "email")
            continue;

        std::map<std::string,std::string>::iterator result = prev_ct->keys.find(keys->first);
        /* The entry is only present in the new one : it is added. */
        if(result == prev_ct->keys.end())
            prev_ct->keys[keys->first] = keys->second;
        /* The value of the entry is the same in both : nothing is changed. */
        else if(result->second == keys->second)
            continue;
        /* The key is present in both with differents values : the error is printed to STDOUT
         * and the last value is kept.
         */
        else
            std::cout << "[" << name << "] : \"" << keys->first << "\"\t" << result->second << "\t" << keys->second << std::endl;
    }

    /* Merging mails. */
    std::vector<std::string> mails = ct->mails();
    for(size_t i = 0; i < mails.size(); ++i)
        prev_ct->rmMail(mails[i]);
    std::vector<std::string> other_mails = prev_ct->mails();

    size_t size = mails.size();
    mails.resize(size + other_mails.size());
    std::copy(other_mails.begin(), other_mails.end(), mails.begin() + size);
    prev_ct->setMail(mails);
}

bool saveContacts(const std::string& path, const SavedCts& cts)
{
    abook_parser::Contacts tosave;
    for(SavedCts::const_iterator it = cts.begin(); it != cts.end(); ++it)
        tosave.push_back(it->second);
    return abook_parser::save(tosave, path);
}

int main(int argc, char *argv[])
{
    if(argc < 2) {
        std::cout << "Usage : " << argv[0] << " save addressbook1 addressbook2 ..." << std::endl;
        return 1;
    }

    std::vector<abook_parser::Contacts> all_cts;
    for(int i = 2; i < argc; ++i) {
        abook_parser::Contacts cts = abook_parser::load(argv[i]);
        if(cts.empty())
            continue;
        all_cts.push_back(cts);
    }

    SavedCts saved;
    for(size_t i = 0; i < all_cts.size(); ++i) {
        for(size_t j = 0; j < all_cts[i].size(); ++j)
            addContact(saved, all_cts[i][j]);
    }
    saveContacts(argv[1], saved);

    for(size_t i = 0; i < all_cts.size(); ++i)
        abook_parser::free(all_cts[i]);

    return 0;
}

