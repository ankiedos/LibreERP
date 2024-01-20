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

#include "db/server-config.hpp"

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "third-party/cpp-httplib/httplib.h"
#include "typedefs.hpp"
#include "state.hpp"
#include "db.hpp"
#include "module.hpp"

soci::session datab;

void shutdown_(int _)
{
    datab.close();
}

int main(int argc, char** argv)
{
    using namespace kient::lerp;
    signal(SIGINT, shutdown_);
    signal(SIGTERM, shutdown_);
    signal(SIGKILL, shutdown_);

    db::ServerConfig srv_cfg;
    // sql::Table global_businesses;
    // global_businesses.name = "global_businesses";
    // sql::Table global_default_business;
    // global_default_business.name = "global_default_business";
    // sql::Table global_modules;
    // global_modules.name = "global_modules";

    std::vector<kient::lerp::modul> modules;
    db_conn_data cdata;
    cdata.host = "localhost";
    cdata.user = "root";
    cdata.passw = "root";
    cdata.db = "libreerp";
    cdata.port = 3306;

    db_connect(datab, cdata);
    std::clog << "Successfully connected to the DB\n";

    auto conf = srv_cfg.get_all();
    httplib::SSLServer server{conf.ssl_cert.c_str(), conf.ssl_key.c_str()};
    server.Get("/dashboard", [](const httplib::Request& req, httplib::Response& res)
    {
        res.set_content("", "text/html");
    });
    server.Get("/(.*)", [](const httplib::Request& req, httplib::Response& res)
    {
        std::string path = req.matches[1].str();
        auto mod = path.substr(1, path.find('/', 1));
        kient::lerp::modules::exec(kient::lerp::modules::mods[mod].name, kient::lerp::modules::mods[mod].proc_serve, req.matches[1]);
        res.set_content("", "");
    });
    server.listen(conf.hostname, conf.port);
    std::clog << "Sent index.html\n";

    shutdown_(0);
    std::clog << "Hello, world!\n";
    return 0;
}
