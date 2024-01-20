#include<iostream>
#include<vector>
#include<thread>
#include<cstdio>
#include<cstdlib>
#include<argp.h>
#include<signal.h>
#include<unistd.h>

#include<sys/types.h>
#include<sys/select.h>
#include<sys/socket.h>
#include<netinet/in.h>

#include<boost/beast.hpp>
#include<soci/soci.h>
#include<soci/mysql/soci-mysql.h>

#include "sql/table.hpp"

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "third-party/cpp-httplib/httplib.h"
#include "typedefs.hpp"
#include "state.hpp"
#include "db.hpp"

soci::session db;

void shutdown_(int _)
{
    db.close();
}

int main(int argc, char** argv)
{
    using namespace kient::lerp;
    signal(SIGINT, shutdown_);
    signal(SIGTERM, shutdown_);
    signal(SIGKILL, shutdown_);

    sql::Table global_config;
    global_config.name = "global_config";
    sql::Table global_businesses;
    global_businesses.name = "global_businesses";
    sql::Table global_default_business;
    global_default_business.name = "global_default_business";
    sql::Table modules;

    std::vector<kient::lerp::modul> modules;
    db_conn_data cdata;
    cdata.host = "localhost";
    cdata.user = "root";
    cdata.passw = "root";
    cdata.db = "libreerp";
    cdata.port = 3306;

    db_connect(db, cdata);
    std::clog << "Successfully connected to the DB\n";

    std::string site_name;
    server_config srv_cfg;
    db << global_config.select().add_field("*").to_str();
    db_get_global_config(db, site_name, srv_cfg);

    httplib::SSLServer server{srv_cfg.ssl_cert, srv_cfg.ssl_key};
    server.Get("/dashboard", [](const httplib::Request& req, httplib::Response& res)
    {
        res.set_content("", "text/html");
    });
    server.Get("/(.*)", [](const httplib::Request& req, httplib::Response& res)
    {
        std::string path = req.matches[1].str();
        std::string bus;

        auto end = path.find('/');
        std::size_t modbeg;
        auto it = std::find_if(businesses.begin(), businesses.end(), [path, end](auto b){ return b.base_url == path.substr(0, end); });

        if(it == businesses.end())
        {
            modbeg = 0;
            auto row = db_select(db, "*", "global_default_business");
            row >> bus;
        }
        else
        {
            modbeg = end + 1;
            bus = it->base_url;
        }
        auto mod = kient::lerp::modules::by_url(bus, path.substr(modbeg, path.find('/', modbeg)));
        kient::lerp::modules::exec(kient::lerp::modules::mods[mod].name, kient::lerp::modules::mods[mod].proc_serve, req.matches[1]);
        res.set_content("", "");
    });
    server.Get("/(.*)", [](const httplib::Request& req, httplib::Response& res)
    {
        auto mod = modules
    })
    server.listen(srv_cfg.hostname, srv_cfg.port);
    std::clog << "Sent index.html\n";

    shutdown_(0);
    std::clog << "Hello, world!\n";
    return 0;
}
