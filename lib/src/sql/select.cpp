#include "select.hpp"


namespace kient::lerp::sql
{
    Select& Select::from(const std::string& tbl)
    {
        table = tbl;
        return *this;
    }
    Select& Select::where(const Cond& cnd)
    {
        cond = cnd;
        return *this;
    }
    Select& Select::order_by(const std::map<std::string, std::string>& fields)
    {
        order_by_ = fields;
        return *this;
    }
    Select& Select::group_by(const std::vector<std::string>& fields)
    {
        group_by_ = fields;
        return *this;
    }
    Select& Select::having(const std::string& cond)
    {
        having_ = cond;
        return *this;
    }
    Select& Select::limit(const std::size_t& n)
    {
        limit_ = n;
        return *this;
    }
    Select& Select::add_field(const std::string& field)
    {
        queried_fields.push_back(field);
        return *this;
    }

    std::string Select::to_str() const
    {
        std::string res{"SELECT "};
        for(const auto& i : queried_fields)
        {
            res += i + ", ";
        }
        res.pop_back();
        res.pop_back();
        res += " FROM " + table;
        if(!cond.path.empty()) res += " WHERE " + cond.path;
        if(!group_by_.empty())
        {
            res += " GROUP BY ";
            for(const auto& i : group_by_)
            {
                res += i + ", ";
            }
            res.pop_back();
            res.pop_back();
        }
        if(!having_.empty()) res += " HAVING " + having_;
        if(!order_by_.empty())
        {
            res += " ORDER BY ";
            for(const auto& [k, v] : order_by_)
            {
                res += k + v + ", ";
            }
            res.pop_back();
            res.pop_back();
        }
        if(limit_ != 0)
        {
            res += " LIMIT " + std::to_string(limit_);
        }

        res += ";";
        return res;
    }
    soci::row Select::exec() const
    {
        soci::row r;
        db << to_str(), into(r);
        return r;
    }
}