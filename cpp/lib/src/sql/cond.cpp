#include "cond.hpp"


namespace kient::lerp::sql
{
    Cond& Cond::base(const std::string& val)
    {
        path = val;
        return *this;
    }
    Cond& Cond::land(const std::string& cond)
    {
        path += " AND ";
        return *this;
    }
    Cond& Cond::lor(const std::string& cond)
    {
        path += " OR ";
        return *this;
    }
    Cond& Cond::lnot(const std::string& val)
    {
        path += "NOT " + val;
        return *this;
    }
    Cond& Cond::leq(const std::string& val)
    {
        path += " = " + val;
        return *this;
    }
    Cond& Cond::lneq(const std::string& val)
    {
        path += " <> " + val;
        return *this;
    }
    Cond& Cond::lgt(const std::string& val)
    {
        path += " > " + val;
        return *this;
    }
    Cond& Cond::llt(const std::string& val)
    {
        path += " < " + val;
        return *this;
    }
    Cond& Cond::lgte(const std::string& val)
    {
        path += " >= " + val;
        return *this;
    }
    Cond& Cond::llte(const std::string& val)
    {
        path += " <= " + val;
        return *this;
    }
    Cond& Cond::like(const std::string& val)
    {
        path += " LIKE " + val;
        return *this;
    }
    Cond& Cond::in(const std::string& val)
    {
        path += " IN " + val;
        return *this;
    }
}