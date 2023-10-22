#pragma once

#include<vector>


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
        std::vector<T> elements;
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
    };
}