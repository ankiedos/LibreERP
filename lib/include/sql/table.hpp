#ifndef KIENT_LIBREERP_UTILS_SQL_TABLE_HPP
#define KIENT_LIBREERP_UTILS_SQL_TABLE_HPP

#include<string>
#include "select.hpp"
#include "update.hpp"
#include "insert.hpp"
#include "delete.hpp"
#include "alter.hpp"
#include "drop.hpp"

namespace kient::lerp::sql
{
    struct Table
    {
        std::string name;
        virtual Select& select();
        virtual Update& update();
        virtual Insert& insert();
        virtual Delete& delete_();
        virtual Alter& alter();
        virtual Drop& drop();
    };
}

#endif