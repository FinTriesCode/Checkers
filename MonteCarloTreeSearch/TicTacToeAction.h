#ifndef _TIC_TAC_TOE_ACTION_H_
#define _TIC_TAC_TOE_ACTION_H_

#include "BaseAction.h"
#include "TicTacToeTypes.h"

using MCTS::BaseAction;

class TicTacToeAction : public BaseAction
{
public:
	TicTacToeAction(int x, int y, BOARD_SQUARE_STATE playerMove);
public:
	int x, y;
	BOARD_SQUARE_STATE playerMove;
};

#endif