#pragma once

#include<vector>
#include<algorithm>

#include "models/address.cpp"
#include "queries/iquery.cpp"
#include "repos/irepository.cpp"

namespace kient::CppERP::core
{
    class AddressRepository;
    class AddressQuery : public IQuery<Address, std::size_t, AddressRepository, AddressQuery>
    {
        std::string table_name_ = "addresses";
        std::string where_ = "";
        std::vector<std::size_t> view;
        pqxx::connection* db;
    public:
        AddressQuery() = default;
        AddressQuery(const AddressQuery& other)
        {
            table_name_ = other.table_name_;
            where_ = other.where_;
            view = other.view;
            db = other.db;
        }

        ORM_FILTER_BY(ID, id, std::size_t, AddressQuery)
        ORM_FILTER_BY(country, country, std::string, AddressQuery)
        ORM_FILTER_BY(region, region, std::string, AddressQuery)
        ORM_FILTER_BY(city, city, std::string, AddressQuery)
        ORM_FILTER_BY(street, street, std::string, AddressQuery)
        ORM_FILTER_BY(building, building, std::string, AddressQuery)
        ORM_FILTER_BY(apartment, apartment, std::string, AddressQuery)
        ORM_FILTER_BY_ADAPTED(postal_code, postal_code, utils::PostalCode, AddressQuery, std::string, [](const utils::PostalCode& code){ return code.to_string(); })
    };
}