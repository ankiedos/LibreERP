#pragma once

#include "utils/e-mail.cpp"

namespace kient::CppERP::core::utils
{
    // to specialise into an actual (by IETF) e-mail address validator (ExtendedEMailValidator)
    // generalisation:
    // Validator
    // methods:
    // validation methods may validate just in a specified mode or in general
    // - contains_only
    // - contains_one
    // - contains_n
    // - not_contains
    // - only_as_separator
    // - register_mode("name", "begin", "end")
    // CommentedEMail
    // CommentedEMailAdapter - adapts CommentedEMail into EMail
    class EMailValidator
    {
        EMail email_;
        static const std::string uppercase_letters, lowercase_letters,
                                 digits, printables,
                                 whitespaces;
    public:
        EMailValidator() = default;
        EMailValidator(const EMail& email)
        : email_{email} {}
        static void empty_ontrue()
        {
            return;
        }
        static void empty_onfalse()
        {
            return;
        }
        EMailValidator& email(const EMail& email)
        {
            email_ = email;
            return *this;
        }
        bool validate_characters_unq()
        {
            if(email_.user().find_first_not_of(EMailValidator::uppercase_letters + EMailValidator::lowercase_letters + EMailValidator::digits + EMailValidator::printables)
               != std::string::npos)
            {
                return false;
            }
            return true;
        }
        bool validate_characters_q()
        {
            if(email_.user().find_first_not_of(EMailValidator::uppercase_letters + EMailValidator::lowercase_letters + EMailValidator::digits + EMailValidator::printables + EMailValidator::whitespaces)
               != std::string::npos)
            {
                return false;
            }
            return true;
        }
        bool validate_dots()
        {
            if(email_.user()[0] == '.'
            || email_.user()[email_.user().size() - 1] == '.')
            {
                return false;
            }
            if(email_.user().find("..") != std::string::npos)
            {
                return false;
            }
            return true;
        }
        template<typename T, typename U>
        bool validate_unquoted(T& ontrue, U& onfalse)
        {
            if(!validate_characters_unq())
            {
                onfalse();
                return false;
            }
            if(!validate_dots())
            {
                onfalse();
                return false;
            }
            ontrue();
            return true;
        }
        // TODO: Implement validate_quoted 
        template<typename T, typename U>
        bool validate_quoted(T& ontrue, U& onfalse)
        {
            if(!validate_characters_q())
            {
                onfalse();
                return false;
            }
            ontrue();
            return true;
        }
        template<typename T, typename U>
        bool validate(T& ontrue, U& onfalse)
        {
            if(email_.user().find("'\"")) return validate_quoted(ontrue, onfalse);
            return validate_unquoted(ontrue, onfalse);
        }
    };
    const std::string EMailValidator::uppercase_letters = "ABCDEFGHIJKLMNOPQRSTUWVXYZ";
    const std::string EMailValidator::lowercase_letters = "abcdefghijklmnopqrstuwvxyz";
    const std::string EMailValidator::digits = "0123456789";
    const std::string EMailValidator::printables = ".!#$%^&*+-=/_{|}~'";
    const std::string EMailValidator::whitespaces = " \t";
}