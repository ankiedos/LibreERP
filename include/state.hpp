// "site-name": "",
// "businesses": {
//     "default": "kirjat",
//     "list": [
//         {
//             "table-prefix": "kirjat_",
//             "full-name": "Wydawnictwo Kirjat",
//             "URL": "kirjat"
//         }
//     ]
// }
#ifndef KIENT_LIBREERP_STATE_HPP
#define KIENT_LIBREERP_STATE_HPP

#include<iostream>
#include<fstream>
#include<string>
#include<lua5.4/lua.h>
#include "typedefs.hpp"

enum libreerp_mode_t
{
    MD_SSL = 1,
    MD_DEV = 1 << 1,
    MD_TEST = 1 << 1
};

struct business_config
{
    std::string default_name;
    std::string table_prefix;
    std::string full_name;
    std::string base_url;
};
std::vector<business_config> businesses;
struct server_config
{
    std::string domain;
    libreerp_mode_t mode;
    std::string ssl_cert, ssl_key;
    u8 ipver;
    // default:
    // 0.0.0.0 deploy
    // 127.0.0.1 dev
    // 192.168.0.1 test
    std::string hostname;
    // default:
    // 8080 not ssl
    // 443 ssl
    u16 port;
};
struct state
{
    lua_State* lua_state;
};

#endif