#include "server-config.hpp"

namespace kient::lerp::db
{
    server_config ServerConfig::get_all()
    {
        auto r = global_config.select().add_field("*").exec();
        server_config srv_cfg;

        r >> srv_cfg.site_name;

        r >> srv_cfg.domain;

        int server_mode_int;
        r >> server_mode_int;

        srv_cfg.mode = static_cast<libreerp_mode_t>(server_mode_int);

        srv_cfg.ssl_cert = r.get<std::string>("server_ssl_cert", "");

        srv_cfg.ssl_key = r.get<std::string>("server_ssl_key", "");

        r.skip(2);
        std::clog << "skipped\n";

        r >> srv_cfg.hostname;
        srv_cfg.port = r.get<int>("server_port");
        return srv_cfg;
    }
    ServerConfig& ServerConfig::init(soci::session& db)
    {
        ServerConfig srv;
        srv.global_config.db = std::make_shared<soci::session>(db);
    }
}