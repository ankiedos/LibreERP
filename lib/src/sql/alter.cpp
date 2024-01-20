#include "alter.hpp"


namespace kient::lerp::sql
{
    Alter& Alter::table(const std::string& tbl)
    {
        table_ = tbl;
        return *this;
    }
    AlterAdd& Alter::add()
    {
        AlterAdd aa;
        aa.table = table_;
        return aa;
    }
    AlterModify& Alter::modify()
    {
        AlterModify am;
        am.table = table_;
        return am;
    }
    AlterDrop& Alter::drop()
    {
        AlterDrop ad;
        ad.table = table_;
        return ad;
    }
    AlterRename& Alter::rename()
    {
        AlterRename ar;
        ar.table = table_;
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

    AlterModify& AlterModify::column(const std::string& fieldspec)
    {
        fspc = fieldspec;
        return *this;
    }
    std::string AlterModify::to_str() const
    {
        return "ALTER TABLE " + table + " MODIFY COLUMN " + fspc + ";";
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
}