#include "db/modules.hpp"

namespace kient::lerp::db
{
    Modules& Modules::init(soci::session& db)
    {
        Modules mod;
        mod.global_modules.db = std::make_shared<soci::session>(db);
    }
}