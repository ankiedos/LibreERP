#ifndef KIENT_LIBREERP_UTILS_SQL_DROP_HPP
#define KIENT_LIBREERP_UTILS_SQL_DROP_HPP

#include<memory>
#include<string>
#include<soci/mysql/soci-mysql.h>

#include "statement.hpp"

namespace kient::lerp::sql
{
    struct Drop : public Statement
    {
        std::shared_ptr<soci::session> db;
        std::string table_;
        Drop& table(const std::string& tbl);

        std::string to_str() const override;
        soci::row exec() const override;
    };
}

#endif