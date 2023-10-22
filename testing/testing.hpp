#pragma once

#include<cstdint>

std::size_t testing_case_counter__ = 0;
std::size_t testing_failures__ = 0;

#define TESTING_INIT() std::cout << std::boolalpha;

#define TEST_SUITE(name) std::cout << "Executing test suite: " << (name) << "\n";

#define TEST_CASE(title)\
std::cout << "TESTCASE " << testing_case_counter__ << ": " << (title) << ":\n";\
testing_case_counter__++;

#define TEST_BEFORE(code) code
#define TEST_REQUIRE(condition)\
std::cout << (condition) << "\n";\
if(!(condition)) testing_failures__++;\
testing_cleanup();

#define TEST_AFTER(code) code

#define TESTING_END()\
std::cout << "\n";\
return testing_failures__;