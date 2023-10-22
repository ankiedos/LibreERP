#pragma once

#include<vector>
#include<algorithm>

#include "repos/user-repository.cpp"

namespace kient::CppERP::core
{
    class UserQuery
    {
        std::string where = "";
        std::vector<std::size_t> view;
        pqxx::connection* db;
    public:
        UserQuery() = default;
        UserQuery(const UserQuery& other)
        {
            where = other.where;
            view = other.view;
            db = other.db;
        }
        UserQuery& add(std::size_t ID)
        {
            view.push_back(ID);
            return *this;
        }
        bool contains(const User& user) const
        {
            return std::find(view.begin(), view.end(), user.get_ID()) != view.end();
        }
        UserQuery& initialise_from_pq_result(const pqxx::result& r) const
        {
            UserQuery results;
            for(std::size_t i = 0; i < r.size(); i++)
            {
                results.add(r[i][0].as<std::size_t>());
            }
            return results;
        }
        template<typename T>
        UserQuery& filter(const std::string& row_name, const std::vector<T>& values) const
        {
            UserQuery results;
            pqxx::work work{*(repo->db)};
            std::string sql = UserRepository::filter_base;
            auto new_where = UserRepository::filter_requirements(row_name, values);
            if(where == "") sql += new_where;
            else if(where.find(" AND ") == std::string::npos)
            {
                sql += "(" + where + ") AND (" + new_where + ");";
            }
            else
            {
                sql += where + " AND (" + new_where + ");";
            }
            pqxx::result r = work.exec(sql);
            work.commit();

            results = initialise_from_pq_result(r);

            if(where == "")
            {
                results.where = new_where;
            }
            else if(where.find(" AND ") == std::string::npos)
            {
                results.where = "(" + results.where + ") AND (" + new_where + ")";
            }
            else
            {
                results.where = where + " AND (" + new_where + ")";
            }

            return results;
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