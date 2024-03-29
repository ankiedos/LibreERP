#include "drop.hpp"

namespace kient::lerp::sql
{
    Drop& Drop::table(const std::string& tbl)
    {
        table_ = tbl;
        return *this;
    }
    std::string Drop::to_str() const
    {
        return "DROP TABLE " + table_ + ";";
    }
    soci::row Drop::exec() const
    {
        db << to_str();
        return soci::row{};
    }
}