#include "update.hpp"


namespace kient::lerp::sql
{
    Update& Update::where(const Cond& cnd)
    {
        cond = cnd;
        return *this;
    }
    Update& Update::from(const std::string& tbl)
    {
        table = tbl;
        return *this;
    }
    Update& Update::set(const std::map<std::string, std::string>& fields)
    {
        patch = fields;
        return *this;
    }
    Update& Update::add_field(const std::string& field, const std::string& val)
    {
        patch[field] = val;
        return *this;
    }

    std::string Update::to_str() const
    {
        std::string res{"UPDATE " + table + " SET "};
        for(const auto& [k, v] : patch)
        {
            res += k + " = " + v + ", ";
        }
        res.pop_back();
        res.pop_back();
        if(!cond.path.empty())
        {
            res += " WHERE " + cond.path;
        }

        res += ";";
        return res;
    }
    soci::row Update::exec() const
    {
        db << to_str();
        return soci::row{};
    }
}