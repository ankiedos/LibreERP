#include<iostream>

#include "testing/testing.hpp"

#include "utils/glueable-string-vector.cpp"

using kient::CppERP::core::utils::GlueableStringVector;

GlueableStringVector vec;

#define BEFORE(value) vec.push_back(value);
void testing_cleanup()
{
    vec.clear();
}
int main(int argc, char** argv)
{
    TESTING_INIT()

    TEST_SUITE(argv[0])

    TEST_CASE("one element + empty link")
    {
        BEFORE("a")
        TEST_REQUIRE(vec.glue("") == "a")
    }
    TEST_CASE("one element + one-character link")
    {
        BEFORE("rwvr")
        TEST_REQUIRE(vec.glue(" ") == "rwvr")
    }
    TEST_CASE("one element + multi-character link")
    {
        BEFORE("irwcvbiv")
        TEST_REQUIRE(vec.glue(" dc ") == "irwcvbiv")
    }
    TEST_CASE("two elements + empty link")
    {
        BEFORE("a")
        BEFORE("b")
        TEST_REQUIRE(vec.glue("") == "ab")
    }
    TEST_CASE("two elements + one-character link")
    {
        BEFORE("avr")
        BEFORE("gij")
        TEST_REQUIRE(vec.glue(" ") == "avr gij")
    }
    TEST_CASE("two elements + multi-character link")
    {
        BEFORE("erin")
        BEFORE("fvnie")
        TEST_REQUIRE(vec.glue(" OR ") == "erin OR fvnie")
    }
    TEST_CASE("multiple elements + empty link")
    {
        BEFORE("ieth")
        BEFORE("vrb")
        BEFORE("rgbv")
        BEFORE("erih")
        TEST_REQUIRE(vec.glue("") == "iethvrbrgbverih")
    }
    TEST_CASE("multiple elements + one-character link")
    {
        BEFORE("ihpf")
        BEFORE("3ri")
        BEFORE("43ih")
        BEFORE("ebj")
        TEST_REQUIRE(vec.glue(" ") == "ihpf 3ri 43ih ebj")
    }
    TEST_CASE("multiple elements + multi-character link")
    {
        BEFORE("rgih")
        BEFORE("rb")
        BEFORE("eifbwv")
        BEFORE("rvuobioub")
        BEFORE("wvbi")
        TEST_REQUIRE(vec.glue(" OR and d") == "rgih OR and drb OR and deifbwv OR and drvuobioub OR and dwvbi")
    }
    TESTING_END()
}