#ifndef _BASE_USER_H_
#define _BASE_USER_H_

class BaseUser
{
    public:
        virtual ~BaseUser() = default;
        virtual int do_action() = 0;
};

#endif
