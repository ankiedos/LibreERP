#include<iostream>

#include "testing/testing.hpp"
#include "utils/postal-code.cpp"

using kient::CppERP::core::utils::PostalCode;

PostalCode code;

void testing_cleanup()
{
    return;
}

int main(int argc, char** argv)
{
    TESTING_INIT()
    TEST_SUITE(argv[0])

    TEST_CASE("gives correct code")
    {
        code.city({'4', '5'})
            .local({'2', '6', '6'});
        TEST_REQUIRE(code.to_string() == "45-266")
    }
    TESTING_END()
}