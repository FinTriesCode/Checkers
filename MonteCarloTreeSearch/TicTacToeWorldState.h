#ifndef _TIC_TAC_TOE_WORLD_STATE_H_
#define _TIC_TAC_TOE_WORLD_STATE_H_

#include "BaseWorldState.h"
#include "TicTacToeTypes.h"
#include "TicTacToeAction.h"

using MCTS::BaseWorldState;

class TicTacToeWorldState : public BaseWorldState
{
public:
	TicTacToeWorldState(bool loaded = false);
	TicTacToeWorldState(TicTacToeWorldState* prevWorldState, bool loaded = false);
	virtual void copyFromPreviousState(BaseWorldState* prevState) override;
	virtual bool performAction(BaseAction* action) override;

	GameBoardHandle& getBoardRef() { return boardHandle; }
	GameBoardHandle getBoardCopy() { return boardHandle; }

private:
	GameBoardHandle boardHandle;
};

#endif