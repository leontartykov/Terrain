#include "admin.h"
#include "../../../entry/app_command/app_command.h"

Admin::Admin(){
    _connect = nullptr;
    this->_connect_to_db();
    _app_facade = std::shared_ptr<AppFacade>(new AppFacade());
}

Admin::~Admin(){
    this->disconnect_db();
    std::cout << "Admin destructor.\n";
}

int Admin::_connect_to_db()
{
    if (_connect){
        std::cout << "Уже есть подключение к БД.\n"  << std::endl;
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

int Admin::_is_user_empty(users_t &user){
    int error = 0;
    if (user.password.empty() && user.login.empty()){
        error = -1;
    }

    return error;
}

int Admin::add_user(users_t &user)
{
    if (!_connect){
        std::cout << "error: Нет подключения к БД." << std::endl;
        return -1;
    }
    else if (this->_is_user_empty(user) != 0){
        std::cout << "О пользователе нет данных.\n";
        return -2;
    }
   try{
        pqxx::work worker(*_connect);
        //std::unique_ptr<pqxx::work> worker(new pqxx::work(*_connect));
        worker.exec("insert into ppo.passwords.users values ('" + user.login + "', '" + user.password + "', false, " + "false)");
        worker.commit();
        std::cout << "пользователь был добавлен успешно.\n";
    }
    catch (std::exception const &e){
        std::cout << e.what() << '\n';
        return -3;
    }

    return 0;
}

int Admin::delete_user(users_t &user)
{
    if (!_connect){
        std::cout << "Нет подключения к БД." << std::endl;
        return -1;
    }
    else if (this->_is_user_empty(user) != 0){
        std::cout << "О пользователе нет данных.\n";
        return -2;
    }

    try{
        pqxx::work worker(*_connect);
        worker.exec("UPDATE ppo.passwords.users SET delete = true WHERE login LIKE '%" + user.login + "';");
        worker.commit();
    }
    catch(std::exception const &e){
        std::cerr << e.what() << '\n';
        return -3;
    }

    return 0;
}

int Admin::lock_user(users_t &user)
{
    if (this->_is_user_empty(user) != 0){
        std::cout << "О пользователе нет данных.\n";
        return -1;
    }

    try{
        pqxx::work worker(*_connect);
        worker.exec("UPDATE ppo.passwords.users SET lock = true WHERE login LIKE '%" + user.login + "';");
        worker.commit();
    }
    catch(std::exception const &e){
        std::cerr << e.what() << '\n';
        return -3;
    }

    return 0;
}

int Admin::unlock_user(users_t &user)
{
    if (this->_is_user_empty(user) != 0){
        std::cout << "О пользователе нет данных.\n";
        return -1;
    }

    try{
        pqxx::work worker(*_connect);
        worker.exec("UPDATE ppo.passwords.users SET lock = false WHERE login LIKE '%" + user.login + "';");
        worker.commit();
    }
    catch(std::exception const &e){
        std::cerr << e.what() << '\n';
        return -3;
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

void Admin::show_menu(){
    std::cout << "1. Запустить приложение.\n";
    std::cout << "2. Добавить пользователя.\n";
    std::cout << "3. Удалить пользователя.\n";
    std::cout << "4. Заблокировать пользователя.\n";
    std::cout << "5. Разблокировать пользователя.\n";
    std::cout << "0. Выйти.\n";
}

void Admin::do_action()
{
    this->show_menu();
    int number = -1;
    while (number != 0)
    {
        std::cout << "Введите пункт меню:\n";
        std::cin >> number;
        std::cout << "number: " << number << std::endl;

        switch (number)
        {
            case menu::QUIT:
                std::cout << "quit application.\n";
                break;
            case menu::LAUNCH:
            {
                std::shared_ptr<LaunchAppCmd> launch_cmd(new LaunchAppCmd());
                std::shared_ptr<BaseAppCommand> base_launch_cmd = launch_cmd;
                _app_facade->execute(base_launch_cmd);
                break;
            }
            case menu::ADD_USER:
            {
                //для примера
                users_t user;
                user.login = "user12";
                user.password = "qwwer";
                user.is_blocked = false;
                std::shared_ptr<Admin> admin(new Admin());
                std::cout << "проверка соединения: " << admin->check_connection();
                std::shared_ptr<BaseAppCommand> add_user_cmd(
                           new AppAddUserCmd<Admin>(admin, &Admin::add_user, user));
                _app_facade->execute(add_user_cmd);
                //this->add_user(user);
                std::cout << "end: add_user.\n";
                break;
            }
            case menu::DELETE_USER:
            {
                //для примера
                users_t user;
                user.login = "user12";
                std::shared_ptr<Admin> admin(new Admin());
                std::shared_ptr<BaseAppCommand> delete_user_cmd(
                           new AppAddUserCmd<Admin>(admin, &Admin::delete_user, user));
                _app_facade->execute(delete_user_cmd);
                std::cout << "delete_user.\n";
                break;
            }
            case menu::LOCK_USER:
            {
                //для примера
                users_t user;
                user.login = "user12";
                std::shared_ptr<Admin> admin(new Admin());
                std::shared_ptr<BaseAppCommand> lock_user_cmd(
                           new AppAddUserCmd<Admin>(admin, &Admin::lock_user, user));
                _app_facade->execute(lock_user_cmd);
                std::cout << "lock_user.\n";
                break;
            }
            case menu::UNLOCK_USER:
            {
                //для примера
                users_t user;
                user.login = "user12";
                std::shared_ptr<Admin> admin(new Admin());
                std::shared_ptr<BaseAppCommand> lock_user_cmd(
                           new AppAddUserCmd<Admin>(admin, &Admin::unlock_user, user));
                _app_facade->execute(lock_user_cmd);
                std::cout << "lock_user.\n";
            break;
            }
             default:
                std::cout << "неизвестная команда.\n";
                break;
        }
    }
}
