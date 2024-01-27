#include<iostream>
#include<cstring>

#include "state.hpp"
#include "db.hpp"

void db_connect(soci::session& db, const db_conn_data& cdata)
{
    db.open(soci::mysql, "db=" + cdata.db + " user=" + cdata.user + " pass=" + cdata.passw + " host=" + cdata.host + " port=" + std::to_string(cdata.port));
}