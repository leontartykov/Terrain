#ifndef _ADMIN_H_
#define _ADMIN_H_

#include <pqxx/pqxx>
#include <vector>
#include <memory>

#include "../base_user.h"
#include "../../../entry/entry.h"
#include "../../../entry/app_facade/app_facade.h"
#include "../users_struct.h"

class Admin: public BaseUser
{
    private:
        pqxx::connection* _connect;
        std::vector<users_t> _users;

        std::shared_ptr<AppFacade> _app_facade;

        int _connect_to_db();
        int _is_user_empty(users_t &user);

        void show_menu();
    public:
        Admin();
        ~Admin();

        int add_user(users_t &user);
        int delete_user(users_t &user);
        int lock_user(users_t &user);
        int unlock_user(users_t &user);
        int disconnect_db();
        int check_connection();

        virtual int do_action() override;
};

#endif
