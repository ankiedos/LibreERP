#pragma once

#include<exception>
#include<mutex>
#include<pqxx/pqxx>

#include "models/user.cpp"
#include "repos/irepository.cpp"
#include "queries/user-query.cpp"
#include "utils/glueable-string-vector.cpp"

namespace kient::CppERP::core
{
    // TODO: Make it thread-safe
    // TODO: Get rid of SQL queries when just selecting; for that goal, implement a threaded search algorithm searching (returns indexes of all elements meeting the criteria)
    // TODO: Use part of that as SQLQueryBuilder library
    class UserRepository : public IRepository<User, UserQuery, UserRepository>
    {
        pqxx::connection* db;
        UserQuery initialise_from_pq_result(const pqxx::result& r) const
        {
            UserQuery results;
            for(std::size_t i = 0; i < r.size(); i++)
            {
                results.add(r[i][0].as<std::size_t>());
            }
            return results;
        }
        void initialise_repository(const pqxx::result& r)
        {
            for(std::size_t i = 0; i < r.size(); i++)
            {
                User user;
                user.set_ID(r[i][0].as<std::size_t>())
                    .set_name(r[i][1].as<std::string>())
                    .set_second_name(r[i][2].as<std::string>())
                    .set_surname(r[i][3].as<std::string>())
                    .set_gender(gender_from_id(r[i][4].as<std::size_t>()))
                    .set_address_ID(r[i][5].as<std::size_t>())
                    .set_email_ID(r[i][6].as<std::size_t>())
                    .set_role_ID(r[i][7].as<std::size_t>());
                elements->push_back(user);
            }
        }
    public:
        explicit UserRepository(pqxx::connection* conn)
        : db{conn}
        {
            pqxx::work work{*db};
            pqxx::result r = work.exec("SELECT * FROM `users`;");
            work.commit();
            initialise_repository(r);
        }
        template<typename T>
        void update(const UserQuery& query, const std::string& row_name, const T& value)
        {
            pqxx::work work{*db};
            std::string sql = IRepository<User, UserQuery, UserRepository>::update_base("users");
            auto where = query.where();
            sql += IRepository<User, UserQuery, UserRepository>::column_value_pair(row_name, pqxx::to_string(value));
            sql += where + ";";
            pqxx::result r = work.exec(sql);
            work.commit();
            if(r.affected_rows() == 0) throw RepositoryUpdateException(row_name.c_str(), "users");
        }

        UserRepository() = default;
        ~UserRepository() override = default;
        template<typename T>
        UserQuery filter(const std::string& row_name, const std::vector<T>& values) const
        {
            UserQuery results{all_elements};
            pqxx::work work{*db};
            std::string sql = IRepository<User, UserQuery, UserRepository>::filter_base("users");
            auto where = IRepository<User, UserQuery, UserRepository>::filter_requirements(row_name, values);
            sql += where + ";";
            pqxx::result r = work.exec(sql);
            work.commit();

            results = initialise_from_pq_result(r);
            results.where(where);
            return results;
        }
        void refresh()
        {}

        ORM_FILTER_BY(ID, id, std::size_t, UserQuery)
        ORM_FILTER_BY(name, name, std::string, UserQuery)
        ORM_FILTER_BY(second_name, second_name, std::string, UserQuery)
        ORM_FILTER_BY(surname, surname, std::string, UserQuery)
        ORM_FILTER_BY_ADAPTED(gender, gender, Gender, UserQuery, std::size_t, gender_id)
        ORM_FILTER_BY(password_hash, password_hash, std::string, UserQuery)
        ORM_FILTER_BY(address, address_id, std::size_t, UserQuery)
        ORM_FILTER_BY(email, email_id, std::size_t, UserQuery)
        ORM_FILTER_BY(role, role, std::string, UserQuery)

        UserRepository& insert(const User& user) override
        {
            pqxx::work work{*db};
            std::string sql = IRepository::insert_base("users");
            sql += "VALUES ("
            + pqxx::to_string(user.get_ID())
            + pqxx::to_string(user.get_name())
            + pqxx::to_string(user.get_second_name())
            + pqxx::to_string(user.get_surname())
            + pqxx::to_string(gender_id(user.get_gender()))
            + pqxx::to_string(user.get_password_hash())
            + pqxx::to_string(user.get_address_ID())
            + pqxx::to_string(user.get_email_ID())
            + pqxx::to_string(user.get_role_ID())
            + ");";
            pqxx::result r = work.exec(sql);
            work.commit();
            if(r.affected_rows() != 1) throw RepositoryInsertException("", "users");
            elements->push_back(user);
            return *this;
        }
        ORM_UPDATE(ID, id, std::size_t, UserRepository, UserQuery)
        ORM_UPDATE(name, name, std::string, UserRepository, UserQuery)
        ORM_UPDATE(second_name, second_name, std::string, UserRepository, UserQuery)
        ORM_UPDATE_ADAPTED(gender, gender, Gender, UserRepository, UserQuery, gender_id)
        ORM_UPDATE(password_hash, password_hash, std::string, UserRepository, UserQuery)
        ORM_UPDATE(address_ID, address_id, std::size_t, UserRepository, UserQuery)
        ORM_UPDATE(email_ID, email_id, std::size_t, UserRepository, UserQuery)
        ORM_UPDATE(role_ID, role_ID, std::size_t, UserRepository, UserQuery)
        UserRepository& remove()
        {}
        UserRepository& sum()
        {}
        UserRepository& count()
        {}
        UserRepository& max()
        {}
        UserRepository& min()
        {}
        UserRepository& limit(std::size_t lim)
        {}
        User operator [](std::size_t idx) const
        {
            return elements->at(idx);
        }
    };
}