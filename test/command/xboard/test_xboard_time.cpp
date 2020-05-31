#include <prophet/error_codes.h>

#include <gtest/gtest.h>
#include <string.h>

#include "../../../src/command/xboard/xboard_internal.h"

extern bool fixed_time_per_move;
extern uint32_t time_remaining_millis;
extern uint32_t time_control_increment;
extern uint32_t max_time_ms;


TEST(xboard_test, xboard_time_incorrect_cmd)
{
    EXPECT_EQ(P4_ERROR_CMD_INCORRECT_COMMAND, xboard_time("bla"));
}


TEST(xboard_test, xboard_time_missing_parameter)
{
    EXPECT_EQ(P4_ERROR_CMD_XBOARD_TIME_MISSING_PARAMETER, xboard_time("time"));
}


TEST(xboard_test, xboard_time_fixed_time_per_move)
{
    // reset the time remaining
    time_remaining_millis = 0;

    fixed_time_per_move = true;

    ASSERT_EQ(0, xboard_time("time 1000")); // 10 seconds in centiseconds
    EXPECT_EQ(10000U, time_remaining_millis);
    EXPECT_EQ(9950U, max_time_ms);

    ASSERT_EQ(0, xboard_time("time 4")); // 40 milliseconds
    EXPECT_EQ(40U, time_remaining_millis);
    EXPECT_EQ(1U, max_time_ms);
}


TEST(xboard_test, xboard_time_not_fixed_time_per_move)
{
    // reset the time remaining
    time_remaining_millis = 0;

    fixed_time_per_move = false;

    time_control_increment = 0;
    ASSERT_EQ(0, xboard_time("time 1000")); // 10 seconds in centiseconds
    EXPECT_EQ(10000U, time_remaining_millis);
    EXPECT_EQ(400U, max_time_ms);

    ASSERT_EQ(0, xboard_time("time 25"));
    EXPECT_EQ(250U, time_remaining_millis);
    EXPECT_EQ(10U, max_time_ms);

    time_control_increment = 12;
    ASSERT_EQ(0, xboard_time("time 25"));
    EXPECT_EQ(250U, time_remaining_millis);
    EXPECT_EQ(12010U, max_time_ms);

    ASSERT_EQ(0, xboard_time("time -2"));
    EXPECT_EQ(0U, time_remaining_millis);
    EXPECT_EQ(12000U, max_time_ms);
}