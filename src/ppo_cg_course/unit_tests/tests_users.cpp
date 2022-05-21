#include <gtest/gtest.h>

#include "../core/data_access/users/users.hpp"

TEST(tests_users_add_user, positive)
{
    int result = 0;
    Admin admin;
    admin.connect_to_db();

    std::string user = "user_1";
    int error = admin.add_user(user);

    EXPECT_EQ(error, result);
}

TEST(tests_users_block_user, positive)
{
    int result = 0;
    Admin admin;
    admin.connect_to_db();

    std::string user = "user_1";
    int error = admin.block_user(user);

    EXPECT_EQ(error, result);
}

TEST(tests_users_unblock_user, positive)
{
    int result = 0;
    Admin admin;
    admin.connect_to_db();

    std::string user = "user_1";
    admin.block_user(user);
    int error = admin.unblock_user(user);

    EXPECT_EQ(error, result);
}

TEST(tests_users_delete_user, positive)
{
    int result = 0;
    Admin admin;
    admin.connect_to_db();

    std::string user = "user_1";
    int error = admin.delete_user(user);

    EXPECT_EQ(error, result);
}
