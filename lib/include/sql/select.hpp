#ifndef KIENT_LIBREERP_UTILS_SQL_SELECT_HPP
#define KIENT_LIBREERP_UTILS_SQL_SELECT_HPP

#include<memory>
#include<map>
#include<string>
#include<vector>
#include<soci/mysql/soci-mysql.h>

#include "statement.hpp"
#include "cond.hpp"

namespace kient::lerp::sql
{
    struct Select : public Statement
    {
        std::shared_ptr<soci::session> db;
        std::string table;
        Cond cond;
        std::vector<std::string> queried_fields;
        std::map<std::string, std::string> order_by_;
        std::vector<std::string> group_by_;
        std::string having_;
        std::size_t limit_;
        Select& from(const std::string& tbl) override;
        Select& where(const Cond& cnd) override;
        Select& order_by(const std::map<std::string, std::string>& fields);
        Select& group_by(const std::vector<std::string>& fields);
        Select& having(const std::string& cond);
        Select& limit(const std::size_t& n);
        Select& add_field(const std::string& field);

        std::string to_str() const override;
        soci::row exec() const override;
    };
}

#endif