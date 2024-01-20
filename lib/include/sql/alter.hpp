#ifndef KIENT_LIBREERP_UTILS_SQL_ALTER_HPP
#define KIENT_LIBREERP_UTILS_SQL_ALTER_HPP

#include<memory>
#include<string>
#include<soci/mysql/soci-mysql.h>

#include "statement.hpp"

namespace kient::lerp::sql
{
    struct AlterAdd;
    struct AlterModify;
    struct AlterDrop;
    struct AlterRename;

    struct Alter
    {
        std::shared_ptr<soci::session> db;
        std::string table_;
        Alter& table(const std::string& tbl, const std::shared_ptr<soci::session>& ptr);
        AlterAdd& add();
        AlterModify& modify();
        AlterDrop& drop();
        AlterRename& rename();
    };
    struct AlterAdd : public Statement
    {
        std::shared_ptr<soci::session> db;
        std::string table;
        std::string fspc;
        AlterAdd& column(const std::string& fieldspec);

        std::string to_str() const override;
        soci::row exec() const override;
    };
    struct AlterModify : public Statement
    {
        std::shared_ptr<soci::session> db;
        std::string table;
        std::string fspc;
        AlterModify& column(const std::string& fieldspec);

        std::string to_str() const override;
        soci::row exec() const override;
    };
    struct AlterDrop : public Statement
    {
        std::shared_ptr<soci::session> db;
        std::string table;
        std::string fn;
        AlterDrop& column(const std::string& field);

        std::string to_str() const override;
        soci::row exec() const override;
    };
    struct AlterRename : public Statement
    {
        std::shared_ptr<soci::session> db;
        std::string table;
        std::string on, nn;
        AlterRename& column(const std::string& old_name);
        AlterRename& to(const std::string& new_name);

        std::string to_str() const override;
        soci::row exec() const override;
    };
}


#endif