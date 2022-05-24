# include "entry.h"

EntrySystem::EntrySystem(){
}

EntrySystem::~EntrySystem(){
}

int EntrySystem::_verify_user(user_info_t &user){
    int error = 0;
    try
    {
        _connect = std::unique_ptr<pqxx::connection>(
                    new pqxx::connection("host = localhost "
                                                        "port = 5432 "
                                                        "password = postgres "
                                                        "user = postgres "
                                                        "dbname = ppo "));
    }
    catch (std::exception const &e){
        std::cerr << e.what() << '\n';
        return -1;
    }

    pqxx::work worker(*_connect);
    pqxx::result R {worker.exec(
                    "SELECT * FROM ppo.passwords.users "
                    "WHERE users.login = '" + user.login + "' "
                    "AND users.password = '" + user.password + "';")};

    if (R.size() == 0){
        error = -2;
        std::cerr << "Ошибка: пользователь не найден.";
    }

    _connect->disconnect();
    return error;
}

int EntrySystem::enter_system(){
    user_info_t user_info;
    int error = 1;

    while (error != 0)
    {
        std::cout << "Вход в систему." << std::endl;
        try{
            std::cout << "Логин:";
            std::cin >> user_info.login;

            std::cout << "Пароль:";
            std::cin >> user_info.password;
        }
        catch (std::exception const &e){
            std::cerr << e.what() << '\n';
            return -1;
        }

        error = this->_verify_user(user_info);
    }

    // возможно здесь лучше бы фабрику
    if (user_info.login.compare("admin") == 0){
        std::shared_ptr<Admin> admin(new Admin());
        std::shared_ptr<BaseUser> user = admin;
        user->do_action();
    }
    else{
        std::shared_ptr<User> con_user(new User());
        std::shared_ptr<BaseUser> user = con_user;
        user->do_action();
    }

    return error;
}
