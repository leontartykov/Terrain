#ifndef _USERS_STRUCT_H_
#define _USERS_STRUCT_H_

#include <iostream>

typedef struct users users_t;
struct users{
    std::string login, password;
    bool is_blocked; //false if is unblocked, true -- if blocked
    bool is_deleted;
};

#endif
