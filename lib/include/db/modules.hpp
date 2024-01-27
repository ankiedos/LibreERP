#ifndef KIENT_LIBREERP_UTILS_DB_MODULES_HPP
#define KIENT_LIBREERP_UTILS_DB_MODULES_HPP

#include<memory>

#include<soci/mysql/soci-mysql.h>

#include "sql/table.hpp"

namespace kient::lerp::db
{
    // TODO: Specify types of the queries
    struct Modules
    {
        sql::Table global_modules;
        static Modules& init(soci::session& db);
        auto list(const std::vector<std::string>& tags);
        auto search(const std::vector<std::string>& tags, const std::string& phrase);
        auto install(const std::string& mod_URL);
        auto uninstall(const std::size_t& mod_id);
    };
}


#endif