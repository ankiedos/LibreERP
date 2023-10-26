#pragma once

#include<exception>
#include<pqxx/pqxx>

#include "models/user.cpp"
#include "repos/irepository.cpp"
#include "queries/user-query.cpp"
#include "utils/glueable-string-vector.cpp"

namespace kient::CppERP::core
{
    class UserRepositoryInsertException : public std::exception
    {
        const char* msg_;
    public:
        UserRepositoryInsertException(const char* msg)
        : msg_{msg} {}
        const char* what() const noexcept { return msg_; }
    };
    class UserRepositoryUpdateException : public std::exception
    {
        const char* msg_;
    public:
        UserRepositoryUpdateException(const char* msg)
        : msg_{msg} {}
        const char* what() const noexcept { return msg_; }
    };
    // TODO: Make it thread-safe
    // TODO: Get rid of SQL queries when just selecting; for that goal, implement a threaded search algorithm searching (returns indexes of all elements meeting the criteria)
    // TODO: Use part of that as SQLQueryBuilder library
    class UserRepository : public IRepository<User, UserQuery, UserRepository>
    {
        pqxx::connection* db;
        UserQuery& initialise_from_pq_result(const pqxx::result& r) const
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
                    .set_gender(r[i][4].as<Gender>())
                    .set_address_ID(r[i][5].as<std::size_t>())
                    .set_email_ID(r[i][6].as<std::size_t>())
                    .set_role(r[i][7].as<std::string>());
                elements.push_back(user);
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
            std::string sql = UserRepository::update_base;
            auto where = query.where;
            sql += UserRepository::column_value_pair(row_name, pqxx::to_string(value));
            sql += where + ";";
            pqxx::result r = work.exec(sql);
            work.commit();
            if(r.affected_rows() == 0) throw UserRepositoryUpdateException(row_name);
        }
        static const std::string filter_base;
        static const std::string insert_base;
        static const std::string update_base;
        static std::string column_value_pair(const std::string& field, const std::string& value)
        {
            return field + " = " + value;
        }
        template<typename T>
        static std::string filter_requirements(const std::string& field, const std::vector<T>& values)
        {
            utils::GlueableStringVector vec;
            for(auto& str : values)
            {
                vec.push_back(column_value_pair(field, pqxx::to_string(str)));
            }
            return vec.glue(" OR ");
        }
        UserRepository() = default;
        ~UserRepository() override = default;
        template<typename T>
        UserQuery& filter(const std::string& row_name, const std::vector<T>& values) const
        {
            UserQuery results{all};
            pqxx::work work{*db};
            std::string sql = UserRepository::filter_base;
            auto where = UserRepository::filter_requirements(row_name, values);
            sql += where + ";";
            pqxx::result r = work.exec(sql);
            work.commit();

            results = initialise_from_pq_result(r);
            results.where = where;
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
            std::string sql = UserRepository::insert_base;
            sql += "VALUES ("
            + pqxx::to_string(user.get_ID())
            + pqxx::to_string(user.get_name())
            + pqxx::to_string(user.get_second_name())
            + pqxx::to_string(user.get_surname())
            + pqxx::to_string(gender_id(user.get_gender()))
            + pqxx::to_string(user.get_password_hash())
            + pqxx::to_string(user.get_address_ID())
            + pqxx::to_string(user.get_email_ID())
            + pqxx::to_string(user.get_role())
            + ");";
            pqxx::result r = work.exec(sql);
            work.commit();
            if(r.affected_rows() != 1) throw UserRepositoryInsertException("");
            elements.push_back(user);
            return *this;
        }
        ORM_UPDATE(ID, id, std::size_t, UserRepository, UserQuery)
        ORM_UPDATE(name, name, std::string, UserRepository, UserQuery)
        ORM_UPDATE(second_name, second_name, std::string, UserRepository, UserQuery)
        ORM_UPDATE_ADAPTED(gender, gender, Gender, UserRepository, UserQuery, gender_id)
        ORM_UPDATE(password_hash, password_hash, std::string, UserRepository, UserQuery)
        ORM_UPDATE(address_ID, address_id, std::size_t, UserRepository, UserQuery)
        ORM_UPDATE(email_ID, email_id, std::size_t, UserRepository, UserQuery)
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
            return elements.at(idx);
        }
    };
    const std::string UserRepository::filter_base = "SELECT * FROM `users` WHERE ";
    const std::string UserRepository::insert_base = "INSERT INTO `users` ";
    const std::string UserRepository::insert_base = "UPDATE `users` SET ";
}