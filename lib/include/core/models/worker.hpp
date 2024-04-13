#ifndef KIENT_LIBREERP_CORE_MODELS_WORKER_HPP
#define KIENT_LIBREERP_CORE_MODELS_WORKER_HPP

#include<string>
#include<ctime>

namespace kient::lerp::core::models
{
    struct Worker
    {
        std::size_t ID;
        std::string name, sec_name, surname;
        std::time_t birth_date;
        char gender;
        std::string password_hash;
        std::size_t address_ID;
        std::string role;
    };
}


#endif