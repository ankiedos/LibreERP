#include "delete.hpp"


namespace kient::lerp::sql
{
    Delete& Delete::from(const std::string& tbl)
    {
        table = tbl;
        return *this;
    }
    Delete& Delete::where(const Cond& cnd)
    {
        cond = cnd;
        return *this;
    }

    std::string Delete::to_str() const
    {
        std::string res{"DELETE FROM " + table};
        if(!cond.path.empty()) res += " WHERE " + cond.path;

        res += ";";
        return res;
    }
    soci::row Delete::exec() const
    {
        db << to_str();
        return soci::row{};
    }
}