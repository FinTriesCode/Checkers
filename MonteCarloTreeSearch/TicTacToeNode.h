#ifndef _TIC_TAC_TOE_NODE_H_
#define _TIC_TAC_TOE_NODE_H_

#include "BaseNode.h"
#include "TicTacToeTypes.h"

using MCTS::BaseNode;

class TicTacToeNode : public BaseNode
{
public:
	TicTacToeNode(BOARD_SQUARE_STATE playerState);
	virtual bool Expand() override;
	virtual bool SimulateChildBranch(BaseNode* node) override;
	int getDepth();

private:
	BOARD_SQUARE_STATE playerState;
};

#endif