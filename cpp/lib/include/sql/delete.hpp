#ifndef KIENT_LIBREERP_UTILS_SQL_DELETE_HPP
#define KIENT_LIBREERP_UTILS_SQL_DELETE_HPP

#include<string>
#include "statement.hpp"

namespace kient::lerp::sql
{
    struct Delete : public Statement
    {
        std::string table;
        Cond cond;
        Delete& from(const std::string& tbl) override;
        Delete& where(const Cond& cnd) override;

        std::string to_str() const override;
    };
}


#endif