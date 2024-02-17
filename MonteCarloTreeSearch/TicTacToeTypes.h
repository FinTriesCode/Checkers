#ifndef _TIC_TAC_TOE_TYPES_H_
#define _TIC_TAC_TOE_TYPES_H_

enum BOARD_SQUARE_STATE { NONE, CIRCLE, CROSS };

struct GameBoardHandle
{
	BOARD_SQUARE_STATE board[3][3] { { BOARD_SQUARE_STATE::NONE } };
};

#endif