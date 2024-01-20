#include "table.hpp"

namespace kient::lerp::sql
{
    Select& Table::select()
    {
        Select sel;
        sel.from(name);
        return sel;
    }
    Update& Table::update()
    {
        Update upd;
        upd.from(name);
        return upd;
    }
    Insert& Table::insert()
    {
        Insert ins;
        ins.into(name);
        return ins;
    }
    Delete& Table::delete_()
    {
        Delete del;
        del.from(name);
        return del;
    }
    Alter& Table::alter()
    {
        Alter alt;
        alt.table(name);
        return alt;
    }
    Drop& Table::drop()
    {
        Drop dro;
        dro.table(name);
        return dro;
    }
}