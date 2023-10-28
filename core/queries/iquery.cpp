#pragma once

#include<vector>
#include<algorithm>

#include "repos/irepository.cpp"

namespace kient::CppERP::core
{
    template<typename T, typename IDT, typename RepoT, typename Derived>
    class IQuery
    {
    protected:
        std::string table_name_;
        std::string where_ = "";
        std::vector<IDT> view;
        pqxx::connection* db;
    public:
        virtual ~IQuery() = default;
        Derived& where(const std::string& new_where)
        {
            where_ = new_where;
            return *this;
        }
        std::string where() const { return where_; }
        Derived& append_where(const std::string& further)
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
        Derived& add(const IDT& ID)
        {
            view.push_back(ID);
            return *this;
        }
        bool contains(const T& value) const
        {
            return std::find(view.begin(), view.end(), value.get_ID()) != view.end();
        }
        Derived initialise_from_pq_result(const pqxx::result& r) const
        {
            Derived results;
            for(std::size_t i = 0; i < r.size(); i++)
            {
                results.add(r[i][0].as<IDT>());
            }
            return results;
        }
        template<typename U>
        Derived filter(const std::string& row_name, const std::vector<U>& values) const
        {
            Derived results;
            pqxx::work work{*db};
            std::string sql = IRepository<T, Derived, Repo>::filter_base(table_name_);
            auto new_where = IRepository<T, Derived, Repo>::filter_requirements(row_name, values);
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
    };
}