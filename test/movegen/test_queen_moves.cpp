#include <gtest/gtest.h>

#include <prophet/position/position.h>

#include "../../src/movegen/movegen_internal.h"

extern bool is_in_move_list(move mv, const move* start, const move* end);

TEST(movegen_test, queen_moves_initial_pos)
{
    position pos;
    reset_pos(&pos);

    move moves[10];
    move* mp = gen_queen_moves(moves, &pos, true, true);

    EXPECT_EQ(mp - moves, 0);
}

TEST(movegen_test, queen_moves)
{
    position pos;
    set_pos(&pos, "8/8/3bk3/8/8/2K3Q1/8/8 w - - 0 1");

    move moves[20];
    move* mp = gen_queen_moves(moves, &pos, true, true);

    EXPECT_EQ(mp - moves, 18);

    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, G4), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, G5), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, G6), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, G7), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, G8), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, H4), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, H3), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, H2), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, G2), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, G1), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, F2), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, E1), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, F3), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, E3), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, D3), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, F4), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, E5), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_capture(QUEEN, G3, D6, BISHOP), moves, mp));
}

TEST(movegen_test, queen_captures)
{
    position pos;
    set_pos(&pos,"8/8/3bk3/8/8/2K3Q1/8/8 w - - 0 1");

    move moves[20];
    move* mp = gen_queen_moves(moves, &pos, true, false);

    EXPECT_EQ(mp - moves, 1);

    EXPECT_TRUE(is_in_move_list(to_capture(QUEEN, G3, D6, BISHOP), moves, mp));
}

TEST(movegen_test, queen_noncaptures)
{
    position pos;
    set_pos(&pos,"8/8/3bk3/8/8/2K3Q1/8/8 w - - 0 1");

    move moves[20];
    move* mp = gen_queen_moves(moves, &pos, false, true);

    EXPECT_EQ(mp - moves, 17);

    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, G4), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, G5), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, G6), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, G7), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, G8), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, H4), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, H3), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, H2), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, G2), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, G1), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, F2), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, E1), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, F3), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, E3), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, D3), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, F4), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(QUEEN, G3, E5), moves, mp));
}