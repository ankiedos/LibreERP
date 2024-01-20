#ifndef KIENT_LIBREERP_UTILS_SQL_INSERT_HPP
#define KIENT_LIBREERP_UTILS_SQL_INSERT_HPP

#include<memory>
#include<map>
#include<string>

#include<soci/mysql/soci-mysql.h>

#include "statement.hpp"
#include "cond.hpp"

namespace kient::lerp::sql
{
    struct Insert : public Statement
    {
        std::shared_ptr<soci::session> db;
        std::string table;
        std::map<std::string, std::string> row;
        Insert& from(const std::string& tbl) override;
        Insert& where(const Cond& cnd) override;
        Insert& into(const std::string& tbl);
        Insert& values(const std::map<std::string, std::string>& fields);
        Insert& add_field(const std::string& field, const std::string& val);

        std::string to_str() const override;
        soci::row exec() const override;
    };
}

#endif