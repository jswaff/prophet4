#include <prophet/error_codes.h>
#include <prophet/position/position.h>

#include <gtest/gtest.h>

#include "../../src/command/command_internal.h"

extern position gpos;

TEST(command_test, command_db_incorrect_cmd)
{
    EXPECT_EQ(P4_ERROR_CMD_INCORRECT_COMMAND, command_db("bla"));
}

TEST(command_test, command_db)
{
    reset_pos(&gpos);
    EXPECT_EQ(0, command_db("db"));
}
