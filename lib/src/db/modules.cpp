#include "db/modules.hpp"

namespace kient::lerp::db
{
    Modules& Modules::init(soci::session& db)
    {
        Modules mod;
        mod.global_modules.db = std::make_shared<soci::session>(db);
    }
    auto Modules::list(const std::vector<std::string>& tags)
    {
    }
    auto Modules::search(const std::vector<std::string>& tags, const std::string& phrase)
    {}
    auto Modules::install(const std::string& mod_URL)
    {}
    auto Modules::uninstall(const std::size_t& mod_id)
    {}
}