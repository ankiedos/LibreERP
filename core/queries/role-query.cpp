#pragma once

#include<vector>
#include<algorithm>

#include "models/role.cpp"
#include "queries/iquery.cpp"
#include "repos/irepository.cpp"

namespace kient::CppERP::core
{
    class RoleRepository;
    class RoleQuery : public IQuery<Role, std::string, RoleRepository, RoleQuery>
    {
        std::string table_name_ = "roles";
        std::string where_ = "";
        std::vector<std::size_t> view;
        pqxx::connection* db;
    public:
        RoleQuery() = default;
        RoleQuery(const RoleQuery& other)
        {
            table_name_ = other.table_name_;
            where_ = other.where_;
            view = other.view;
            db = other.db;
        }

        ORM_FILTER_BY(ID, id, std::string, RoleQuery)
        ORM_FILTER_BY(full_name, full_name, std::string, RoleQuery)
        ORM_FILTER_BY(description, description, std::string, RoleQuery)
    };
}