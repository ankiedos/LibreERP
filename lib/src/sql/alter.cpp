#include "alter.hpp"


namespace kient::lerp::sql
{
    Alter& Alter::table(const std::string& tbl, const std::shared_ptr<soci::session>& ptr)
    {
        table_ = tbl;
        db = ptr;
        return *this;
    }
    AlterAdd& Alter::add()
    {
        AlterAdd aa;
        aa.table = table_;
        aa.db = db;
        return aa;
    }
    AlterModify& Alter::modify()
    {
        AlterModify am;
        am.table = table_;
        am.db = db;
        return am;
    }
    AlterDrop& Alter::drop()
    {
        AlterDrop ad;
        ad.table = table_;
        am.db = db;
        return ad;
    }
    AlterRename& Alter::rename()
    {
        AlterRename ar;
        ar.table = table_;
        ar.db = db;
        return ar;
    }

    AlterAdd& AlterAdd::column(const std::string& fieldspec)
    {
        fspc = fieldspec;
        return *this;
    }
    std::string AlterAdd::to_str() const
    {
        return "ALTER TABLE " + table + " ADD " + fspc + ";";
    }
    soci::row AlterAdd::exec() const
    {
        db << to_str();
        return soci::row{};
    }

    AlterModify& AlterModify::column(const std::string& fieldspec)
    {
        fspc = fieldspec;
        return *this;
    }
    std::string AlterModify::to_str() const
    {
        return "ALTER TABLE " + table + " MODIFY COLUMN " + fspc + ";";
    }
    soci::row AlterModify::exec() const
    {
        db << to_str();
        return soci::row{};
    }

    AlterDrop& AlterDrop::column(const std::string& field)
    {
        fn = field;
        return *this;
    }
    std::string AlterDrop::to_str() const
    {
        return "ALTER TABLE " + table + " DROP COLUMN " + fn + ";";
    }
    soci::row AlterDrop::exec() const
    {
        db << to_str();
        return soci::row{};
    }

    AlterRename& AlterRename::column(const std::string& old_name)
    {
        on = old_name;
        return *this;
    }
    AlterRename& AlterRename::to(const std::string& new_name)
    {
        nn = new_name;
        return *this;
    }
    std::string AlterRename::to_str() const
    {
        return "ALTER TABLE " + table + " RENAME COLUMN " + on + " TO " + nn + ";";
    }
    soci::row AlterRename::exec() const
    {
        db << to_str();
        return soci::row{};
    }
}