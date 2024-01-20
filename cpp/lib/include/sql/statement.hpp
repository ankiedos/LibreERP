#ifndef KIENT_LIBREERP_UTILS_SQL_STATEMENT_HPP
#define KIENT_LIBREERP_UTILS_SQL_STATEMENT_HPP

#include<string>

#include "cond.hpp"

namespace kient::lerp::sql
{
    struct Statement
    {
        virtual Statement& from(const std::string& table);
        virtual Statement& where(const Cond& cond);
        virtual std::string to_str() const;
    };
}

#endif