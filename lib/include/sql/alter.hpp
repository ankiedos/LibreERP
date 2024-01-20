#ifndef KIENT_LIBREERP_UTILS_SQL_ALTER_HPP
#define KIENT_LIBREERP_UTILS_SQL_ALTER_HPP

#include<string>
#include "statement.hpp"

namespace kient::lerp::sql
{
    struct AlterAdd;
    struct AlterModify;
    struct AlterDrop;
    struct AlterRename;

    struct Alter
    {
        std::string table_;
        Alter& table(const std::string& tbl);
        AlterAdd& add();
        AlterModify& modify();
        AlterDrop& drop();
        AlterRename& rename();
    };
    struct AlterAdd : public Statement
    {
        std::string table;
        std::string fspc;
        AlterAdd& column(const std::string& fieldspec);

        std::string to_str() const override;
    };
    struct AlterModify : public Statement
    {
        std::string table;
        std::string fspc;
        AlterModify& column(const std::string& fieldspec);

        std::string to_str() const override;
    };
    struct AlterDrop : public Statement
    {
        std::string table;
        std::string fn;
        AlterDrop& column(const std::string& field);

        std::string to_str() const override;
    };
    struct AlterRename : public Statement
    {
        std::string table;
        std::string on, nn;
        AlterRename& column(const std::string& old_name);
        AlterRename& to(const std::string& new_name);

        std::string to_str() const override;
    };
}


#endif