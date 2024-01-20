#ifndef KIENT_LIBREERP_UTILS_SQL_UPDATE_HPP
#define KIENT_LIBREERP_UTILS_SQL_UPDATE_HPP


#include<string>
#include<map>

#include "statement.hpp"
#include "cond.hpp"

namespace kient::lerp::sql
{
    struct Update : public Statement
    {
        std::string table;
        Cond cond;
        std::map<std::string, std::string> patch;
        Update& where(const Cond& cnd) override;
        Update& from(const std::string& tbl) override;
        Update& set(const std::map<std::string, std::string>& fields);
        Update& add_field(const std::string& field, const std::string& val);

        std::string to_str() const override;
    };
}

#endif