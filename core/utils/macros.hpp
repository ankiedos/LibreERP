#pragma once


#define API_DATA
#define API_SINK


#define API_FLUENT_GETTER(name, type)\
type get_##name() const\
{\
    return name;\
}
#define API_FLUENT_SETTER(name, type, cltype)\
cltype& set_##name(const type& new_##name)\
{\
    name##_ = new_##name;\
    return *this;\
}


#define API_FLUENT_CONST_PROPERTY(name, type)\
API_FLUENT_GETTER(name, type)

#define API_FLUENT_PROPERTY(name, type, cltype)\
API_FLUENT_SETTER(name, type, cltype)\
API_FLUENT_GETTER(name##_, type)

// cltype& set_##name(const type& new_##name)\
// {\
//     name##_ = new_##name;\
//     return *this;\
// }\
// type get_##name() const\
// {\
//     return name##_;\
// }