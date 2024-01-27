#ifndef KIENT_LIBREERP_UTILS_DB_HPP
#define KIENT_LIBREERP_UTILS_DB_HPP

#include<string>

#include<soci/soci.h>
#include<soci/mysql/soci-mysql.h>

#include "typedefs.hpp"


struct db_conn_data
{
    std::string host;
    std::string user;
    std::string passw;
    std::string db;
    u16 port;
};

void db_connect(soci::session& db, const db_conn_data& data);

#endif