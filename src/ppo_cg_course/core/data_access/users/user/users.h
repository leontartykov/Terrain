#ifndef _USERS_H_
#define _USERS_H_

#include <iostream>
#include "../base_user.h"
#include "../../../entry/entry.h"
#include "../../../entry/app_command/app_command.h"
#include "../../../entry/app_facade/app_facade.h"

class User: public BaseUser
{
    private:
        std::shared_ptr<AppFacade> _app_facade;
        void show_menu();

    public:
        User();
        ~User() = default;

        virtual void do_action();
};

#endif
