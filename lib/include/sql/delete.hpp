#ifndef KIENT_LIBREERP_UTILS_SQL_DELETE_HPP
#define KIENT_LIBREERP_UTILS_SQL_DELETE_HPP

#include<memory>
#include<string>
#include<soci/mysql/soci-mysql.h>

#include "statement.hpp"

namespace kient::lerp::sql
{
    struct Delete : public Statement
    {
        std::shared_ptr<soci::session> db;
        std::string table;
        Cond cond;
        Delete& from(const std::string& tbl) override;
        Delete& where(const Cond& cnd) override;

        std::string to_str() const override;
        soci::row exec() const override;
    };
}


#endif