#pragma once

#include<vector>
#include<algorithm>

#include "models/user.cpp"
#include "repos/irepository.cpp"

namespace kient::CppERP::core
{
    class UserRepository;
    class UserQuery
    {
        std::string where_ = "";
        std::vector<std::size_t> view;
        pqxx::connection* db;
    public:
        UserQuery() = default;
        UserQuery(const UserQuery& other)
        {
            where_ = other.where_;
            view = other.view;
            db = other.db;
        }
        UserQuery& where(const std::string& new_where)
        {
            where_ = new_where;
            return *this;
        }
        std::string where() const { return where_; }
        UserQuery& append_where(const std::string& further)
        {
            if(where_ == "")
            {
                where_ = further;
            }
            else if(where_.find(" AND ") == std::string::npos)
            {
                where_ = "(" + where_ + ") AND (" + further + ")";
            }
            else
            {
                where_ = where_ + " AND (" + further + ")";
            }
            return *this;
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
        UserQuery initialise_from_pq_result(const pqxx::result& r) const
        {
            UserQuery results;
            for(std::size_t i = 0; i < r.size(); i++)
            {
                results.add(r[i][0].as<std::size_t>());
            }
            return results;
        }
        template<typename T>
        UserQuery filter(const std::string& row_name, const std::vector<T>& values) const
        {
            UserQuery results;
            pqxx::work work{*db};
            std::string sql = IRepository<User, UserQuery, UserRepository>::filter_base("users");
            auto new_where = IRepository<User, UserQuery, UserRepository>::filter_requirements(row_name, values);
            if(where_ == "") sql += new_where;
            else if(where_.find(" AND ") == std::string::npos)
            {
                sql += "(" + where_ + ") AND (" + new_where + ");";
            }
            else
            {
                sql += where_ + " AND (" + new_where + ");";
            }
            pqxx::result r = work.exec(sql);
            work.commit();

            results = initialise_from_pq_result(r);

            results.where_ = where_;
            results.append_where(new_where);

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