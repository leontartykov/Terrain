#ifndef _BASE_USER_H_
#define _BASE_USER_H_

class BaseUser
{
    public:
        virtual ~BaseUser() = default;
        virtual void do_action() = 0;
};

#endif
