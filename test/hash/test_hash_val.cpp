#include <prophet/hash.h>

#include <gtest/gtest.h>

TEST(hash_test, hash_val_upper_bound)
{
    int32_t depth = 45;
    int32_t score = 122;
    move_t mv = to_move(PAWN, E2, E4);
    uint64_t val = build_hash_val(UPPER_BOUND, 0, depth, score, mv);

    ASSERT_EQ(UPPER_BOUND, get_hash_entry_type(val));
    ASSERT_EQ(depth, get_hash_entry_depth(val));
    ASSERT_EQ(score, get_hash_entry_score(val, 0));
    ASSERT_EQ(to_move(PAWN, E2, E4), get_hash_entry_move(val));
}


TEST(hash_test, hash_val_lower_bound)
{
    int32_t depth = 14;
    int32_t score = -109;
    move_t mv = to_move(KNIGHT, B1, A3);
    uint64_t val = build_hash_val(LOWER_BOUND, 0, depth, score, mv);

    ASSERT_EQ(LOWER_BOUND, get_hash_entry_type(val));
    ASSERT_EQ(depth, get_hash_entry_depth(val));
    ASSERT_EQ(score, get_hash_entry_score(val, 0));
    ASSERT_EQ(mv, get_hash_entry_move(val));
}


TEST(hash_test, hash_val_exact_score)
{
    int32_t depth = 1;
    int32_t score = -54;
    move_t mv = to_capture(PAWN, E7, E8, BISHOP);
    set_promopiece(&mv, QUEEN);
    uint64_t val = build_hash_val(EXACT_SCORE, 0, depth, score, mv);

    ASSERT_EQ(EXACT_SCORE, get_hash_entry_type(val));
    ASSERT_EQ(depth, get_hash_entry_depth(val));
    ASSERT_EQ(score, get_hash_entry_score(val, 0));
    ASSERT_EQ(mv, get_hash_entry_move(val));
}


TEST(hash_test, mate_score)
{
    int32_t depth = 17;
    int32_t score = CHECKMATE - 9;
    move_t mv = to_move(QUEEN, A1, A8);
    // mate in 9 from ply 3, which should be stored as mate in 6 from the root
    uint64_t val = build_hash_val(LOWER_BOUND, 3, depth, score, mv);

    ASSERT_EQ(LOWER_BOUND, get_hash_entry_type(val));
    ASSERT_EQ(depth, get_hash_entry_depth(val));
    ASSERT_EQ(CHECKMATE - 6, get_hash_entry_score(val, 0));

    // when probed from 5 moves in, the score should reflect being 11 moves from the root
    ASSERT_EQ(CHECKMATE - 11, get_hash_entry_score(val, 5));    
    ASSERT_EQ(mv, get_hash_entry_move(val));    
}


TEST(hash_test, mated_score)
{
    int32_t depth = 17;
    int32_t score = -CHECKMATE + 10;
    move_t mv = to_move(QUEEN, A8, A1);
    // mated in 10 from ply 4, which should be stored as mated in 6 from root
    uint64_t val = build_hash_val(UPPER_BOUND, 4, depth, score, mv);

    ASSERT_EQ(UPPER_BOUND, get_hash_entry_type(val));
    ASSERT_EQ(depth, get_hash_entry_depth(val));
    ASSERT_EQ(-(CHECKMATE - 6), get_hash_entry_score(val, 0)); 
    ASSERT_EQ(-(CHECKMATE - 8), get_hash_entry_score(val, 2));
    ASSERT_EQ(mv, get_hash_entry_move(val));    
}
