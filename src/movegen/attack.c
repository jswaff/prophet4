#include <assert.h>
#include <stdbool.h>

#include "movegen_internal.h"

/**
 * \brief Given position \p p, is square \p sq attacked by \p player?
 *
 * \param p         The chess position
 * \param sq        The square in question
 * \param player    The attacking player
 *
 * \return - boolean indicating if there is an attack.
 */
bool attacked(const position* p, square_t sq, color_t player)
{
    if (attacked_by_pawn(p, sq, player)) return true;
    if (attacked_by_knight(p, sq, player)) return true;
    if (attacked_by_king(p, sq, player)) return true;
    if (attacked_by_rook(p, sq, player)) return true;
    if (attacked_by_bishop(p, sq, player)) return true;
    if (attacked_by_queen(p, sq, player)) return true;

    return false;
}

/**
 * \brief Given position \p p, is square \p sq attacked by one of \p player 's bishops?
 *
 * \param p         The chess position
 * \param sq        The square in question
 * \param player    The attacking player
 *
 * \return - boolean indicating if there is an attack.
 */
bool attacked_by_bishop(const position* p, square_t sq, color_t player)
{
    assert(p);
    assert(sq >= A8 && sq <= H1);
    assert(player==WHITE || player==BLACK);

    return get_bishop_moves(p, sq, (player==WHITE ? p->white_bishops : p->black_bishops)) > 0;
}

/**
 * \brief Given position \p p, is square \p sq attacked by \p player 's king?
 *
 * \param p         The chess position
 * \param sq        The square in question
 * \param player    The attacking player
 *
 * \return - boolean indicating if there is an attack.
 */
bool attacked_by_king(const position* p, square_t sq, color_t player)
{
    assert(p);
    assert(sq >= A8 && sq <= H1);
    assert(player==WHITE || player==BLACK);

    return get_king_moves(sq, square_to_bitmap(player==WHITE ? p->white_king : p->black_king)) > 0;
}

/**
 * \brief Given position \p p, is square \p sq attacked by one of \p player 's knights?
 *
 * \param p         The chess position
 * \param sq        The square in question
 * \param player    The attacking player
 *
 * \return - boolean indicating if there is an attack.
 */
bool attacked_by_knight(const position* p, square_t sq, color_t player)
{
    assert(p);
    assert(sq >= A8 && sq <= H1);
    assert(player==WHITE || player==BLACK);

    return get_knight_moves(sq, (player==WHITE ? p->white_knights : p->black_knights)) > 0;
}

/**
 * \brief Given position \p p, is square \p sq attacked by one of \p player 's pawns?
 *
 * \param p         The chess position
 * \param sq        The square in question
 * \param player    The attacking player
 *
 * \return - boolean indicating if there is an attack.
 */
bool attacked_by_pawn(const position* p, square_t sq, color_t player)
{
    assert(p);
    assert(sq >= A8 && sq <= H1);
    assert(player==WHITE || player==BLACK);

    if (player==WHITE) {
        if (((p->white_pawns & ~file_to_bitmap(FILE_A)) >> 9) & square_to_bitmap(sq)) return true;
        if (((p->white_pawns & ~file_to_bitmap(FILE_H)) >> 7) & square_to_bitmap(sq)) return true;
    } else {
        if (((p->black_pawns & ~file_to_bitmap(FILE_A)) << 7) & square_to_bitmap(sq)) return true;
        if (((p->black_pawns & ~file_to_bitmap(FILE_H)) << 9) & square_to_bitmap(sq)) return true;
    }

    return false;
}

/**
 * \brief Given position \p p, is square \p sq attacked by one of \p player 's queens?
 *
 * \param p         The chess position
 * \param sq        The square in question
 * \param player    The attacking player
 *
 * \return - boolean indicating if there is an attack.
 */
bool attacked_by_queen(const position* p, square_t sq, color_t player)
{
    assert(p);
    assert(sq >= A8 && sq <= H1);
    assert(player==WHITE || player==BLACK);

    return get_queen_moves(p, sq, (player==WHITE ? p->white_queens : p->black_queens)) > 0;
}

/**
 * \brief Given position \p p, is square \p sq attacked by one of \p player 's rooks?
 *
 * \param p         The chess position
 * \param sq        The square in question
 * \param player    The attacking player
 *
 * \return - boolean indicating if there is an attack.
 */
bool attacked_by_rook(const position* p, square_t sq, color_t player)
{
    assert(p);
    assert(sq >= A8 && sq <= H1);
    assert(player==WHITE || player==BLACK);

    return get_rook_moves(p, sq, (player==WHITE ? p->white_rooks : p->black_rooks)) > 0;
}