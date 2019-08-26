#include <prophet/const.h>
#include <prophet/hash.h>
#include <prophet/position/position.h>

/* the game position, or global position */
position_t gpos;

/* undo information for the game position*/
undo_t gundos[MAX_HALF_MOVES_PER_GAME];
int gundo_ind;

zobrist_keys zkeys;
