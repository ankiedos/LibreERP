#ifndef KIENT_LIBREERP_UTILS_DB_SERVERCONFIG_HPP
#define KIENT_LIBREERP_UTILS_DB_SERVERCONFIG_HPP

#include<memory>
#include "sql/table.hpp"
#include "state.hpp"

namespace kient::lerp::db
{
    struct ServerConfig
    {
        sql::Table global_config;
        server_config get_all();
        static ServerConfig& init(soci::session& db);
    };
}

#endif