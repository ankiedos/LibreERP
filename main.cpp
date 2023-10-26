#include<iostream>

#include<pqxx/pqxx>

#include "core/repos/user-repository.cpp"

int main(int argc, char** argv)
{
    pqxx::connection db;
    kient::CppERP::core::UserRepository user_repo{&db};
    return 0;
}