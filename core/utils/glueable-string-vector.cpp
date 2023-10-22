#pragma once

#include<string>

#include "utils/glueable-vector.cpp"

namespace kient::CppERP::core::utils
{
    class GlueableStringVector : public IGlueableVector<std::string>
    {
    public:
        ~GlueableStringVector() = default;
        std::string glue(const std::string& link) override
        {
            std::string result;
            for(const_iterator it = cbegin(); it != cend(); it++)
            {
                result += *it;
                result += link;
            }
            for(auto& c : link) result.pop_back(); // so that link exists only between the elements

            return result;
        }
    };
}