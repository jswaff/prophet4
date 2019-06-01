#include <gtest/gtest.h>

#include <prophet/position/position.h>

#include "../../src/movegen/movegen_internal.h"

extern bool is_in_move_list(move mv, const move* start, const move* end);

TEST(movegen_test, bishop_moves_initial_pos)
{
    position pos;
    reset_pos(&pos);

    move moves[10];
    move* mp = gen_bishop_moves(moves, &pos, true, true);

    EXPECT_EQ(mp - moves, 0);
}

TEST(movegen_test, bishop_moves)
{
    position pos;
    set_pos(&pos,"4k3/2p3P1/8/4B3/4B3/3p1P2/8/4K3 w - - 0 1");

    move moves[20];
    move* mp = gen_bishop_moves(moves, &pos, true, true);

    EXPECT_EQ(mp - moves, 18);

    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E5, F6), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E5, F4), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E5, G3), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E5, H2), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E5, D4), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E5, C3), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E5, B2), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E5, A1), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E5, D6), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_capture(BISHOP, E5, C7, PAWN), moves, mp));

    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E4, F5), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E4, G6), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E4, H7), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_capture(BISHOP, E4, D3, PAWN), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E4, D5), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E4, C6), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E4, B7), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E4, A8), moves, mp));
}

TEST(movegen_test, bishop_captures)
{
    position pos;
    set_pos(&pos,"4k3/2p3P1/8/4B3/4B3/3p1P2/8/4K3 w - - 0 1");

    move moves[20];
    move* mp = gen_bishop_moves(moves, &pos, true, false);

    EXPECT_EQ(mp - moves, 2);

    EXPECT_TRUE(is_in_move_list(to_capture(BISHOP, E5, C7, PAWN), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_capture(BISHOP, E4, D3, PAWN), moves, mp));
}

TEST(movegen_test, bishop_noncaptures)
{
    position pos;
    set_pos(&pos,"4k3/2p3P1/8/4B3/4B3/3p1P2/8/4K3 w - - 0 1");

    move moves[20];
    move* mp = gen_bishop_moves(moves, &pos, false, true);

    EXPECT_EQ(mp - moves, 16);

    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E5, F6), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E5, F4), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E5, G3), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E5, H2), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E5, D4), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E5, C3), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E5, B2), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E5, A1), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E5, D6), moves, mp));

    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E4, F5), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E4, G6), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E4, H7), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E4, D5), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E4, C6), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E4, B7), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(BISHOP, E4, A8), moves, mp));
}
