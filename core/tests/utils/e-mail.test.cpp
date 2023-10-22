#include<iostream>

#include "testing/testing.hpp"
#include "utils/e-mail.cpp"

using kient::CppERP::core::utils::EMail;

EMail email;

void testing_cleanup()
{
    return;
}
int main(int argc, char** argv)
{
    TESTING_INIT()
    TEST_SUITE(argv[0])

    TEST_CASE("gives correct e-mail")
    {
        email.user("antek_kiedos")
             .domain("outlook.com");
        TEST_REQUIRE(email.to_string() == "antek_kiedos@outlook.com")
    }
    TESTING_END()
}