#include "core/workers.hpp"

namespace kient::lerp::core
{
    Workers& Workers::init(soci::session& db)
    {
        Workers wrk;
        wrk.core_workers.db = std::make_shared<soci::session>(db);
    }
    auto Workers::by(const std::map<std::string, std::string>& reqs)
    {
        std::string filter{};
        for(auto& [k, v] : reqs)
        {
            filter += k + v + ", ";
        }
        filter.pop_back();
        filter.pop_back();
        sql::Cond cnd;
        cnd.base(filter);
        auto r = core_workers.select()
                .add_field("id")
                .add_field("name")
                .add_field("surname")
                .add_field("role")
                .where(cnd)
                .exec();
        std::vector<models::Worker> workers;
    }
    auto Workers::login(const std::size_t& ID, const std::string& password)
    {}
    auto Workers::profile(const std::size_t& ID)
    {}
    auto Workers::change_password(const std::size_t& ID, const std::string& old_pw, const std::string& new_pw)
    {}
    auto Workers::forgot_password(const std::size_t& ID, const std::string& contact_type)
    {}
    auto Workers::change_forgotten_password(const std::string& token)
    {}
    auto Workers::birthday(const std::size_t& ID)
    {}
    auto Workers::are_in_the_same_branch(const std::size_t& worker0_ID, const std::size_t& worker1_ID)
    {}
}