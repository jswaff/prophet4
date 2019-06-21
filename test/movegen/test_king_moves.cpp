#include <gtest/gtest.h>

#include <prophet/position/position.h>

#include "../../src/movegen/movegen_internal.h"

extern bool is_in_move_list(move mv, const move* start, const move* end);


TEST(movegen_test, king_moves_initial_position)
{
    position pos;
    reset_pos(&pos);

    move moves[10];
    move *mp = gen_king_moves(moves, &pos, true, true);

    EXPECT_EQ(mp - moves, 0); // no moves
}

TEST(movegen_test, king_moves_mostly_open)
{
    position pos;
    set_pos(&pos,"8/8/3k4/2n1P3/8/8/3rP3/R3K2R b KQ - 0 1");

    move moves[20];
    move* mp = gen_king_moves(moves, &pos, true, true);

    EXPECT_EQ(mp - moves, 7); // just one friendly piece close by

    EXPECT_TRUE(is_in_move_list(to_move(KING, D6, D7), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, D6, E7), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, D6, E6), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_capture(KING, D6, E5, PAWN), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, D6, D5), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, D6, C6), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, D6, C7), moves, mp));
}

TEST(movegen_test, king_moves_includes_castle)
{
    position pos;
    set_pos(&pos,"8/8/3k4/2n1P3/8/8/3rP3/RN2K2R w KQ - 0 1");

    move moves[20];
    move* mp = gen_king_moves(moves, &pos, true, true);

    EXPECT_EQ(mp - moves, 5);

    EXPECT_TRUE(is_in_move_list(to_move(KING, E1, F2), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, E1, F1), moves, mp)); // NOTE: illegal move
    EXPECT_TRUE(is_in_move_list(to_move(KING, E1, D1), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_capture(KING, E1, D2, ROOK), moves, mp));

    move mv = to_move(KING, E1, G1);
    set_castle(&mv);
    EXPECT_TRUE(is_in_move_list(mv, moves, mp));
}

TEST(movegen_test, king_moves_in_a_corner_white)
{
    position pos;
    set_pos(&pos,"k7/8/8/8/8/8/8/7K w - - 0 1");

    move moves[10];
    move* mp = gen_king_moves(moves, &pos, true, true);

    EXPECT_EQ(mp - moves, 3);

    EXPECT_TRUE(is_in_move_list(to_move(KING, H1, G1), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, H1, G2), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, H1, H2), moves, mp));
}

TEST(movegen_test, king_moves_in_a_corner_black)
{
    position pos;
    set_pos(&pos,"k7/8/8/8/8/8/8/7K b - - 0 1");

    move moves[10];
    move* mp = gen_king_moves(moves, &pos, true, true);

    EXPECT_EQ(mp - moves, 3);

    EXPECT_TRUE(is_in_move_list(to_move(KING, A8, A7), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, A8, B7), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, A8, B8), moves, mp));
}

TEST(movegen_test, king_moves_cannot_castle_while_in_check)
{
    position pos;
    set_pos(&pos,"3k4/8/8/2N1P3/7q/8/4P3/R3K2R w KQ - 0 1");

    move moves[10];
    move* mp = gen_king_moves(moves,&pos,true,true);

    EXPECT_EQ(mp - moves, 4);

    EXPECT_TRUE(is_in_move_list(to_move(KING, E1, F1), moves, mp));
    // Kf2 stays in check, but that's handled separately.
    EXPECT_TRUE(is_in_move_list(to_move(KING, E1, F2), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, E1, D1), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, E1, D2), moves, mp));
}

TEST(movegen_test, king_moves_cannot_castle_through_check)
{
    position pos;
    set_pos(&pos,"r3k2r/8/8/8/8/5Q2/8/4K3 b kq - 0 1");

    move moves[20];
    move* mp = gen_king_moves(moves, &pos, true, true);

    EXPECT_EQ(mp - moves, 6);
    EXPECT_TRUE(is_in_move_list(to_move(KING, E8, F8), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, E8, F7), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, E8, E7), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, E8, D7), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, E8, D8), moves, mp));

    move mv = to_move(KING, E8, C8); // queenside OK, but not kingside
    set_castle(&mv);
    EXPECT_TRUE(is_in_move_list(mv, moves, mp));
}

TEST(movegen_test, king_moves_captures_only_black)
{
    position pos;
    set_pos(&pos,"8/8/3k4/2n1P3/8/8/3rP3/R3K2R b KQ - 0 1");

    move moves[20];
    move* mp = gen_king_moves(moves, &pos, true, false);

    EXPECT_EQ(mp - moves, 1);
    EXPECT_TRUE(is_in_move_list(to_capture(KING, D6, E5, PAWN), moves, mp));
}

TEST(movegen_test, king_moves_captures_only_white)
{
    position pos;
    set_pos(&pos,"8/8/3k4/2n1P3/8/8/3rP3/R3K2R w KQ - 0 1");

    move moves[20];
    move* mp = gen_king_moves(moves, &pos, true, false);

    EXPECT_EQ(mp - moves, 1);
    EXPECT_TRUE(is_in_move_list(to_capture(KING, E1, D2, ROOK), moves, mp));
}

TEST(movegen_test, king_moves_noncaptures_only_black)
{
    position pos;
    set_pos(&pos,"8/8/3k4/2n1P3/8/8/3rP3/R3K2R b KQ - 0 1");

    move moves[20];
    move* mp = gen_king_moves(moves, &pos, false, true);

    EXPECT_EQ(mp - moves, 6);
    EXPECT_TRUE(is_in_move_list(to_move(KING, D6, D7), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, D6, E7), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, D6, E6), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, D6, D5), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, D6, C6), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, D6, C7), moves, mp));
}

TEST(movegen_test, king_moves_noncaptures_only_white)
{
    position pos;
    set_pos(&pos,"8/8/3k4/2n1P3/8/8/3rP3/R3K2R w KQ - 0 1");

    move moves[20];
    move* mp = gen_king_moves(moves, &pos, false, true);

    EXPECT_EQ(mp - moves, 4);
    EXPECT_TRUE(is_in_move_list(to_move(KING, E1, F2), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, E1, F1), moves, mp));
    EXPECT_TRUE(is_in_move_list(to_move(KING, E1, D1), moves, mp));
    move mv = to_move(KING, E1, G1);
    set_castle(&mv);
    EXPECT_TRUE(is_in_move_list(mv, moves, mp));
}