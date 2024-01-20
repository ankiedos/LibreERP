#include<iostream>
#include<cstring>

#include "state.hpp"
#include "db.hpp"

static void printerr(const std::string& msg)
{
    std::cerr << "Error: " << msg << "\n";
}

static void cleanup(soci::session& db, soci::row& res)
{
    printerr("");
}

void db_connect(soci::session& db, const db_conn_data& cdata)
{
    db.open(soci::mysql, "db=" + cdata.db + " user=" + cdata.user + " pass=" + cdata.passw + " host=" + cdata.host + " port=" + std::to_string(cdata.port));
}

soci::row db_select(soci::session& db, const std::string& fields, const std::string& tbl, const std::string& where = "")
{
    soci::row row;
    db << "SELECT " << fields << " FROM " << tbl << (where.empty ? " " : " WHERE ") << where << ";", into(row);
    return row;
}

void db_get_global_config(soci::session& db, std::string& site_name, server_config& srv_cfg)
{
    soci::row row = db_select(db, "*", "global_config");
    std::clog << "Fetched the row\n";

    row >> site_name;
    std::clog << "site_name: " << site_name << "\n";

    row >> srv_cfg.domain;
    std::clog << "server_domain: " << srv_cfg.domain << "\n";

    int server_mode_int;
    row >> server_mode_int;

    srv_cfg.mode = static_cast<libreerp_mode_t>(server_mode_int);
    std::clog << "server_mode: " << srv_cfg.mode << "\n";

    srv_cfg.ssl_cert = row.get<std::string>("server_ssl_cert", "");
    std::clog << "server_ssl_cert: " << srv_cfg.ssl_cert << "\n";

    srv_cfg.ssl_key = row.get<std::string>("server_ssl_key", "");
    std::clog << "server_ssl_key: " << srv_cfg.ssl_key << "\n";

    row.skip(2);
    std::clog << "skipped\n";

    row >> srv_cfg.hostname;
    std::clog << "server_hostname: " << srv_cfg.hostname << "\b\n";
    srv_cfg.port = row.get<int>("server_port");
    std::clog << "server_port: " << srv_cfg.port << "\n";

    std::clog << "Read the global_config table\n";
}