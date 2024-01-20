#ifndef KIENT_LIBREERP_UTILS_SQL_DROP_HPP
#define KIENT_LIBREERP_UTILS_SQL_DROP_HPP

#include<string>

#include "statement.hpp"

namespace kient::lerp::sql
{
    struct Drop : public Statement
    {
        std::string table_;
        Drop& table(const std::string& tbl);

        std::string to_str() const override;
    };
}

#endif