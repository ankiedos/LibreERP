#ifndef KIENT_LIBREERP_UTILS_DB_MODULES_HPP
#define KIENT_LIBREERP_UTILS_DB_MODULES_HPP

#include<memory>

#include<soci/mysql/soci-mysql.h>

#include "sql/table.hpp"

namespace kient::lerp::db
{
    struct Modules
    {
        std::shared_ptr<soci::session> db;
        sql::Table global_modules;
    };
}


#endif