#pragma once

#include<vector>
#include<algorithm>

#include "models/user.cpp"
#include "queries/iquery.cpp"
#include "repos/irepository.cpp"

namespace kient::CppERP::core
{
    class UserRepository;
    class UserQuery : public IQuery<User, UserRepository, UserQuery>
    {
        std::string table_name_ = "users";
        std::string where_ = "";
        std::vector<std::size_t> view;
        pqxx::connection* db;
    public:
        UserQuery() = default;
        UserQuery(const UserQuery& other)
        {
            table_name_ = other.table_name_;
            where_ = other.where_;
            view = other.view;
            db = other.db;
        }

        ORM_FILTER_BY(ID, id, std::size_t, UserQuery)
        ORM_FILTER_BY(name, name, std::string, UserQuery)
        ORM_FILTER_BY(second_name, second_name, std::string, UserQuery)
        ORM_FILTER_BY(surname, surname, std::string, UserQuery)
        ORM_FILTER_BY_ADAPTED(gender, gender, Gender, UserQuery, std::size_t, gender_id)
        ORM_FILTER_BY(password_hash, password_hash, std::string, UserQuery)
        ORM_FILTER_BY(address, address_id, std::size_t, UserQuery)
        ORM_FILTER_BY(email, email_id, std::size_t, UserQuery)
        ORM_FILTER_BY(role, role, std::string, UserQuery)
    };
}