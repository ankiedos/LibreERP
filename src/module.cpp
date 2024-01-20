#include<algorithm>
#include<lua5.4/lua.hpp>
#include "module.hpp"

namespace kient::lerp::modules
{
    template<typename First, typename ...Rest>
    void exec(const std::string& modname, const std::string& procname, First& arg0, Rest... args)
    {
    }
}