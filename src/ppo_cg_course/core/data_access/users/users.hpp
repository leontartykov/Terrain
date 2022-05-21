#ifndef _USERS_HPP_
#define _USERS_HPP_

#include "users.h"

Admin::Admin(){
    _connect = nullptr;
}

Admin::~Admin(){
    this->disconnect_db();
    _connect = nullptr;
}

int Admin::connect_to_db()
{
    if (_connect){
        std::cerr << "Уже есть подключение к БД.\n"  << std::endl;
        return -1;
    }

    try
    {
        _connect = new pqxx::connection("host = localhost "
                                                        "port = 5432 "
                                                        "password = postgres "
                                                        "user = postgres "
                                                        "dbname = ppo ");
    }
    catch (std::exception const &e){
        std::cerr << e.what() << '\n';
        return -2;
    }

    return 0;
}

int Admin::disconnect_db()
{
    if (_connect){
        _connect->disconnect();
        delete _connect;
        _connect = nullptr;
        std::cout << "Отключение проведено успешно." << std::endl;
    }
    else{
        std::cout << "Не было подключения к БД." << std::endl;
    }
    return 0;
}

int Admin::add_user(std::string user)
{
    if (!_connect){
        std::cerr << "Нет подключения к БД." << std::endl;
        return -1;
    }
    else if (user.empty()){
        return -2;
    }

    pqxx::work worker(*_connect);
    worker.exec("CREATE ROLE " + user + " CREATEDB");
    worker.commit();

    return 0;
}

int Admin::delete_user(std::string user)
{
    if (!_connect){
        std::cerr << "Нет подключения к БД." << std::endl;
        return -1;
    }
    else if (user.empty()){
        return -2;
    }

    try{
        pqxx::work worker(*_connect);
        worker.exec("DROP ROLE " + user);
        worker.commit();
    }
    catch(std::exception const &e){
        std::cerr << e.what() << '\n';
        return -1;
    }

    return 0;
}

int Admin::block_user(std::string user)
{
    if (user.empty()){
        std::cerr << "Имя пользователя некорректно." << std::endl;
        return -1;
    }

    int find_user = -1;
    int count_users = _users.size();

    if (count_users == 0){
        find_user = 0;
    }
    else{
        for (int i = 0; i < count_users && find_user == -1; i++){
            if (_users[i].user_name.compare(user) == 0){
                std::cout << "Пользователь заблокирован." << std::endl;
                find_user = i;
            }
        }
    }

    if (find_user != -1){
        users_t blocked_user = {.user_name = user, .is_blocked = 0};
        _users.push_back(blocked_user);
    }

    return 0;
}

int Admin::unblock_user(std::string user)
{
    if (user.empty()){
        std::cerr << "Имя пользователя некорректно." << std::endl;
        return -1;
    }

    int find_user = -1;
    int count_users = _users.size();
    for (int i = 0; i < count_users && find_user == -1; i++){
        if (_users[i].user_name.compare(user) == 0){
            std::cout << "Пользователь разблокирован." << std::endl;
            find_user = i;
            _users[i].is_blocked = 0;
        }
    }

    if (find_user == -1){
        std::cout << "Такого пользователя нет." << std::endl;
        return -2;
    }

    return 0;
}

int Admin::check_connection(){
    if (!_connect){
        std::cout << "Подключение не установлено." << std::endl;
        return -1;
    }

    if (_connect->is_open()){
        return 1;
    }

    return 0;
}

#endif
