#ifndef KIENT_LIBREERP_UTILS_SQL_WHERE_HPP
#define KIENT_LIBREERP_UTILS_SQL_WHERE_HPP

#include<string>

namespace kient::lerp::sql
{
    struct Cond
    {
        std::string path;
        Cond& base(const std::string& val);
        Cond& land(const std::string& cond);
        Cond& lor(const std::string& cond);
        Cond& lnot(const std::string& val);
        Cond& leq(const std::string& val);
        Cond& lneq(const std::string& val);
        Cond& lgt(const std::string& val);
        Cond& llt(const std::string& val);
        Cond& lgte(const std::string& val);
        Cond& llte(const std::string& val);
        Cond& like(const std::string& val);
        Cond& in(const std::string& val);
    };
}

#endif