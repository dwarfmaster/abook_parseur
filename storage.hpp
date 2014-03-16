
/* This file defines the structures used to
 * manipulate contacts and their fields.
 */

#ifndef DEF_ABOOK_PARSER_STORAGE
#define DEF_ABOOK_PARSER_STORAGE

#include <map>
#include <string>
#include <vector>

/* This structure represent a contact and store
 * its values.
 */
struct Contact
{
    /* Store the values of the contact. */
    std::map<std::string,std::string> keys;

    /* Special methods to handle mail. */
    std::vector<std::string> mails() const;
    void addMail(const std::string& m);
    void setMail(const std::vector<std::string>& ms);
    void rmMail(size_t id);
    void rmMail(const std::string& m);
};

#endif

