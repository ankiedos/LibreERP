#pragma once


#define API_PRIMARY_KEY
#define API_FOREIGN_KEY
#define API_DATA
#define API_SINK


#define API_FLUENT_GETTER(metd, name, type)\
type get_##metd() const\
{\
    return name;\
}
#define API_FLUENT_SETTER(metd, name, type, cltype)\
cltype& set_##metd (const type& new_##name)\
{\
    name##_ = new_##name;\
    return *this;\
}


#define API_FLUENT_CONST_PROPERTY(name, type)\
API_FLUENT_GETTER(name, name, type)

#define API_FLUENT_PROPERTY(name, type, cltype)\
API_FLUENT_SETTER(name, name, type, cltype)\
API_FLUENT_GETTER(name, name##_, type)

// cltype& set_##name(const type& new_##name)\
// {\
//     name##_ = new_##name;\
//     return *this;\
// }\
// type get_##name() const\
// {\
//     return name##_;\
// }

#define ORM_FILTER_BY(filter_name, field, type, query_t)\
query_t& by_##filter_name(const std::vector<type>& filter_name##s)\
{\
    return filter(#field, filter_name##s);\
}
#define ORM_FILTER_BY_ADAPTED(filter_name, field, type, query_t, adapt_t, adapter)\
query_t& by_##filter_name(const std::vector<type>& filter_name##s)\
{\
    std::vector<adapt_t> adaptation;\
    for(auto& el : filter_name##s)\
    {\
        adaptation.push_back(adapter(el));\
    }\
    return filter(#field, adaptation);\
}

#define ORM_UPDATE(method_name, field, type, repo_t, query_t)\
repo_t& update_##method_name(const query_t& query, const type& method_name)\
{\
    update(query, #field, method_name);\
    for(auto& user : elements)\
    {\
        if(query.contains(user))\
        {\
            user.set_##method_name(method_name);\
        }\
    }\
    return *this;\
}
#define ORM_UPDATE_ADAPTED(method_name, field, type, repo_t, query_t, adapter)\
repo_t& update_##method_name(const query_t& query, const type& method_name)\
{\
    update(query, #field, adapter(method_name));\
    for(auto& user : elements)\
    {\
        if(query.contains(user))\
        {\
            user.set_##method_name(method_name);\
        }\
    }\
    return *this;\
}