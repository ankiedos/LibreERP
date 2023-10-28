#pragma once

#include<exception>
#include<mutex>
#include<pqxx/pqxx>

#include "models/address.cpp"
#include "repos/irepository.cpp"
#include "queries/address-query.cpp"
#include "utils/glueable-string-vector.cpp"

namespace kient::CppERP::core
{
    // TODO: Make it thread-safe
    // TODO: Get rid of SQL queries when just selecting; for that goal, implement a threaded search algorithm searching (returns indexes of all elements meeting the criteria)
    // TODO: Use part of that as SQLQueryBuilder library
    class AddressRepository : public IRepository<Address, AddressQuery, AddressRepository>
    {
        pqxx::connection* db;
        AddressQuery initialise_from_pq_result(const pqxx::result& r) const
        {
            AddressQuery results;
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
                Address address;
                address.set_ID(r[i][0].as<std::size_t>())
                    .set_country(r[i][1].as<std::string>())
                    .set_region(r[i][2].as<std::string>())
                    .set_city(r[i][3].as<std::string>())
                    .set_street(r[i][4].as<std::string>())
                    .set_building(r[i][5].as<std::string>())
                    .set_apartment(r[i][6].as<std::string>());
                auto code = r[i][7].as<std::string>();
                auto pos = code.find("-");
                auto city = code.substr(0, pos);
                auto local = code.substr(pos + 1);
                utils::PostalCode postal;
                address.set_postal_code(postal.city({city[0], city[1]}).local({local[0], local[1], local[2]}));
                elements->push_back(address);
            }
        }
    public:
        explicit AddressRepository(pqxx::connection* conn)
        : db{conn}
        {
            pqxx::work work{*db};
            pqxx::result r = work.exec("SELECT * FROM `addresses`;");
            work.commit();
            initialise_repository(r);
        }
        template<typename T>
        void update(const AddressQuery& query, const std::string& row_name, const T& value)
        {
            pqxx::work work{*db};
            std::string sql = IRepository<Address, AddressQuery, AddressRepository>::update_base("addresses");
            auto where = query.where();
            sql += IRepository<Address, AddressQuery, AddressRepository>::column_value_pair(row_name, pqxx::to_string(value));
            sql += where + ";";
            pqxx::result r = work.exec(sql);
            work.commit();
            if(r.affected_rows() == 0) throw RepositoryUpdateException(row_name.c_str(), "addresses");
        }

        AddressRepository() = default;
        ~AddressRepository() override = default;
        template<typename T>
        AddressQuery filter(const std::string& row_name, const std::vector<T>& values) const
        {
            AddressQuery results{all_elements};
            pqxx::work work{*db};
            std::string sql = IRepository<Address, AddressQuery, AddressRepository>::filter_base("addresses");
            auto where = IRepository<Address, AddressQuery, AddressRepository>::filter_requirements(row_name, values);
            sql += where + ";";
            pqxx::result r = work.exec(sql);
            work.commit();

            results = initialise_from_pq_result(r);
            results.where(where);
            return results;
        }
        void refresh()
        {}

        ORM_FILTER_BY(ID, id, std::size_t, AddressQuery)
        ORM_FILTER_BY(country, country, std::string, AddressQuery)
        ORM_FILTER_BY(region, region, std::string, AddressQuery)
        ORM_FILTER_BY(city, city, std::string, AddressQuery)
        ORM_FILTER_BY(street, street, std::string, AddressQuery)
        ORM_FILTER_BY(building, building, std::string, AddressQuery)
        ORM_FILTER_BY(apartment, apartment, std::string, AddressQuery)
        ORM_FILTER_BY_ADAPTED(postal_code, postal_code, utils::PostalCode, AddressQuery, std::string, [](const utils::PostalCode& code){ return code.to_string(); })

        AddressRepository& insert(const Address& address) override
        {
            pqxx::work work{*db};
            std::string sql = IRepository::insert_base("addresses");
            sql += "VALUES ("
            + pqxx::to_string(address.get_ID())
            + pqxx::to_string(address.get_country())
            + pqxx::to_string(address.get_region())
            + pqxx::to_string(address.get_city())
            + pqxx::to_string(address.get_street())
            + pqxx::to_string(address.get_building())
            + pqxx::to_string(address.get_apartment())
            + pqxx::to_string(address.get_postal_code())
            + ");";
            pqxx::result r = work.exec(sql);
            work.commit();
            if(r.affected_rows() != 1) throw RepositoryInsertException("", "addresses");
            elements->push_back(address);
            return *this;
        }
        ORM_UPDATE(ID, id, std::size_t, AddressRepository, AddressQuery)
        ORM_UPDATE(country, country, std::string, AddressRepository, AddressQuery)
        ORM_UPDATE(region, region, std::string, AddressRepository, AddressQuery)
        ORM_UPDATE(city, city, std::string, AddressRepository, AddressQuery)
        ORM_UPDATE(street, street, std::string, AddressRepository, AddressQuery)
        ORM_UPDATE(building, building, std::string, AddressRepository, AddressQuery)
        ORM_UPDATE(apartment, apartment, std::string, AddressRepository, AddressQuery)
        ORM_UPDATE_ADAPTED(postal_code, postal_code, utils::PostalCode, AddressRepository, AddressQuery, [](const utils::PostalCode& code){ return code.to_string(); })
        AddressRepository& remove()
        {}
        AddressRepository& sum()
        {}
        AddressRepository& count()
        {}
        AddressRepository& max()
        {}
        AddressRepository& min()
        {}
        AddressRepository& limit(std::size_t lim)
        {}
        Address operator [](std::size_t idx) const
        {
            return elements->at(idx);
        }
    };
}