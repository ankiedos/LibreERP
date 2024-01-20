#include<algorithm>
#include<lua5.4/lua.hpp>
#include "module.hpp"

namespace kient::lerp::modules
{
    std::size_t by_url(const std::string& business, const std::string& URL)
    {
        auto it = std::find_if(mods[business].begin(), mods[business].end(), [URL](auto mod){ return mod.base_url == URL; });
        return std::distance(mods[business].begin(), it);
    }

    template<typename First, typename ...Rest>
    void exec(const std::string& modname, const std::string& procname, First& arg0, Rest...& args)
    {
    }
}