#include "users.h"

User::User(){
    _app_facade = std::shared_ptr<AppFacade>(new AppFacade());
}

void User::show_menu(){
    std::cout << "1. Запустить приложение.\n";
    std::cout << "0. Выйти.\n";
}

void User::do_action()
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
        }
    }
}
