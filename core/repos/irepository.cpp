#pragma once

#include<string>
#include<vector>
#include<pqxx/pqxx>

#include "utils/threaded-vector.cpp"
#include "utils/glueable-string-vector.cpp"

namespace kient::CppERP::core
{
    /*
        User user("Antoni", "", "Kiedos", Gender::Male, "dei3ff38", address, email, "owner");
        UserRepository user_repo;
        user_repo.insert(user); // Adds to the database and to user_repo
        user_repo.by_ID({1})[0].name;
        user.second_name = "Mateusz";
        user_repo.by_ID({1}).update(user);
    */
    template<typename T, typename QueryT, typename Derived>
    class IRepository
    {
    protected:
        QueryT all_elements;
        utils::ThreadedVector<T>* elements;
    public:
        virtual ~IRepository() = 0;

        virtual void refresh() = 0;
        virtual Derived& insert(const T& value) = 0;
        template<typename U>
        void update(const QueryT& query, const std::string& row_name, const U& value);
        template<typename U>
        QueryT& filter(const std::string& row_name, const std::vector<U>& values) const;
        virtual Derived& remove() = 0;
        virtual Derived& sum() = 0;
        virtual Derived& count() = 0;
        virtual Derived& max() = 0;
        virtual Derived& min() = 0;
        virtual Derived& limit(std::size_t lim) = 0;
        virtual T operator [](std::size_t idx) const
        {
            return elements.at(idx);
        }
        template<typename U>
        static std::string filter_requirements(const std::string& field, const std::vector<U>& values)
        {
            utils::GlueableStringVector vec;
            for(auto& str : values)
            {
                vec.push_back(column_value_pair(field, pqxx::to_string(str)));
            }
            return vec.glue(" OR ");
        }
        static std::string column_value_pair(const std::string& field, const std::string& value)
        {
            return field + " = " + value;
        }
        static std::string filter_base(const std::string& table) { return "SELECT * FROM `" + table + "` WHERE "; }
        static std::string insert_base(const std::string& table) { return "INSERT INTO `" + table + "` "; }
        static std::string update_base(const std::string& table) { return "UPDATE `" + table + "` SET "; }
    };
}