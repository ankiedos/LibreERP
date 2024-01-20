#include "insert.hpp"


namespace kient::lerp::sql
{
    Insert& Insert::into(const std::string& tbl)
    {
        table = tbl;
        return *this;
    }
    Insert& Insert::values(const std::map<std::string, std::string>& fields)
    {
        row = fields;
        return *this;
    }
    Insert& Insert::add_field(const std::string& field, const std::string& val)
    {
        row[field] = val;
        return *this;
    }
    Insert& Insert::from(const std::string& tbl)
    {
        return into(tbl);
    }
    Insert& Insert::where(const Cond& cnd)
    {
        return *this;
    }

    std::string Insert::to_str() const
    {
        std::string res{"INSERT INTO " + table + "("};
        for(const auto& [k, _] : row)
        {
            res += k + ", ";
        }
        res.pop_back();
        res.pop_back();
        res += ") VALUES (";
        for(const auto& [_, v] : row)
        {
            res += v + ", ";
        }
        res.pop_back();
        res.pop_back();

        res += ";";
        return res;
    }
}