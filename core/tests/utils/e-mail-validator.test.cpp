#include<iostream>

#include "testing/testing.hpp"
#include "utils/e-mail.cpp"
#include "utils/e-mail-validator.cpp"

using kient::CppERP::core::utils::EMail;
using kient::CppERP::core::utils::EMailValidator;

EMailValidator email_validator;
EMail email;

void testing_cleanup()
{
    email.user("");
    email.domain("");
}
int main(int argc, char** argv)
{
    TESTING_INIT()
    TEST_SUITE(argv[0])

    TEST_CASE("correctly validates dots of a valid unquoted e-mail")
    {
        email.user("antek_kiedos")
             .domain("outlook.com");
        TEST_REQUIRE(email_validator.email(email).validate_dots())
    }
    TEST_CASE("correctly validates characters of a valid unquoted e-mail")
    {
        email.user("antek_kiedos")
             .domain("outlook.com");
        TEST_REQUIRE(email_validator.email(email).validate_characters())
    }
    TEST_CASE("correctly validates valid unquoted e-mail")
    {
        email.user("antek_kiedos")
             .domain("outlook.com");
        TEST_REQUIRE(email_validator.email(email).validate(EMailValidator::empty_ontrue, EMailValidator::empty_onfalse))
    }
    TESTING_END()
}