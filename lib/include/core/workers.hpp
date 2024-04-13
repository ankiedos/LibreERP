#ifndef KIENT_LIBREERP_CORE_WORKERS_HPP
#define KIENT_LIBREERP_CORE_WORKERS_HPP

#include<memory>

#include<soci/mysql/soci-mysql.h>

#include "sql/table.hpp"
#include "core/models/worker.hpp"

namespace kient::lerp::core
{
    struct Workers
    {
        sql::Table core_workers;
        static Workers& init(soci::session& db);
        auto by(const std::map<std::string, std::string>& reqs);
        auto login(const std::size_t& ID, const std::string& password);
        auto profile(const std::size_t& ID);
        auto change_password(const std::size_t& ID, const std::string& old_pw, const std::string& new_pw);
        auto forgot_password(const std::size_t& ID, const std::string& contact_type);
        auto change_forgotten_password(const std::string& token);
        auto birthday(const std::size_t& ID);
        auto are_in_the_same_branch(const std::size_t& worker0_ID, const std::size_t& worker1_ID);
    };
}


#endif