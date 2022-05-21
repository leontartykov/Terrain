#ifndef _USERS_H_
#define _USERS_H_

#include <pqxx/pqxx>
#include <vector>

typedef struct users users_t;
struct users{
    std::string user_name;
    int is_blocked; //0 if is unblocked, 1 -- if blocked
};

class Admin
{
    private:
        pqxx::connection* _connect;
        std::vector<users_t> _users;

    public:
        Admin();
        ~Admin();

        int connect_to_db();
        int add_user(std::string user);
        int delete_user(std::string user);
        int block_user(std::string user);
        int unblock_user(std::string user);
        int disconnect_db();
        int check_connection();
};

#endif
