#pragma once

#include<exception>
#include<mutex>
#include<pqxx/pqxx>

#include "models/role.cpp"
#include "repos/irepository.cpp"
#include "queries/role-query.cpp"
#include "utils/glueable-string-vector.cpp"

namespace kient::CppERP::core
{
    // TODO: Make it thread-safe
    // TODO: Get rid of SQL queries when just selecting; for that goal, implement a threaded search algorithm searching (returns indexes of all elements meeting the criteria)
    // TODO: Use part of that as SQLQueryBuilder library
    class RoleRepository : public IRepository<Role, RoleQuery, RoleRepository>
    {
        pqxx::connection* db;
        RoleQuery initialise_from_pq_result(const pqxx::result& r) const
        {
            RoleQuery results;
            for(std::size_t i = 0; i < r.size(); i++)
            {
                results.add(r[i][0].as<std::string>());
            }
            return results;
        }
        void initialise_repository(const pqxx::result& r)
        {
            for(std::size_t i = 0; i < r.size(); i++)
            {
                Role role;
                role.set_ID(r[i][0].as<std::string>())
                    .set_full_name(r[i][1].as<std::string>())
                    .set_description(r[i][2].as<std::string>());
                elements->push_back(role);
            }
        }
    public:
        explicit RoleRepository(pqxx::connection* conn)
        : db{conn}
        {
            pqxx::work work{*db};
            pqxx::result r = work.exec("SELECT * FROM `roles`;");
            work.commit();
            initialise_repository(r);
        }
        template<typename T>
        void update(const RoleQuery& query, const std::string& row_name, const T& value)
        {
            pqxx::work work{*db};
            std::string sql = IRepository<Role, RoleQuery, RoleRepository>::update_base("roles");
            auto where = query.where();
            sql += IRepository<Role, RoleQuery, RoleRepository>::column_value_pair(row_name, pqxx::to_string(value));
            sql += where + ";";
            pqxx::result r = work.exec(sql);
            work.commit();
            if(r.affected_rows() == 0) throw RepositoryUpdateException(row_name.c_str(), "roles");
        }

        RoleRepository() = default;
        ~RoleRepository() override = default;
        template<typename T>
        RoleQuery filter(const std::string& row_name, const std::vector<T>& values) const
        {
            RoleQuery results{all_elements};
            pqxx::work work{*db};
            std::string sql = IRepository<Role, RoleQuery, RoleRepository>::filter_base("roles");
            auto where = IRepository<Role, RoleQuery, RoleRepository>::filter_requirements(row_name, values);
            sql += where + ";";
            pqxx::result r = work.exec(sql);
            work.commit();

            results = initialise_from_pq_result(r);
            results.where(where);
            return results;
        }
        void refresh()
        {}

        ORM_FILTER_BY(ID, id, std::string, RoleQuery)
        ORM_FILTER_BY(full_name, full_name, std::string, RoleQuery)
        ORM_FILTER_BY(description, description, std::string, RoleQuery)

        RoleRepository& insert(const Role& role) override
        {
            pqxx::work work{*db};
            std::string sql = IRepository::insert_base("roles");
            sql += "VALUES ("
            + pqxx::to_string(role.get_ID())
            + pqxx::to_string(role.get_full_name())
            + pqxx::to_string(role.get_description())
            + ");";
            pqxx::result r = work.exec(sql);
            work.commit();
            if(r.affected_rows() != 1) throw RepositoryInsertException("", "roles");
            elements->push_back(role);
            return *this;
        }
        ORM_UPDATE(ID, id, std::string, RoleRepository, RoleQuery)
        ORM_UPDATE(full_name, full_name, std::string, RoleRepository, RoleQuery)
        ORM_UPDATE(description, description, std::string, RoleRepository, RoleQuery)
        RoleRepository& remove()
        {}
        RoleRepository& sum()
        {}
        RoleRepository& count()
        {}
        RoleRepository& max()
        {}
        RoleRepository& min()
        {}
        RoleRepository& limit(std::size_t lim)
        {}
        Role operator [](std::size_t idx) const
        {
            return elements->at(idx);
        }
    };
}