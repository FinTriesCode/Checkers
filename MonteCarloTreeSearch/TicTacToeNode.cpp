#include "TicTacToeNode.h"
#include "TicTacToeAction.h"
#include "TicTacToeWorldState.h"

TicTacToeNode::TicTacToeNode(BOARD_SQUARE_STATE playerState) :
	BaseNode(),
	playerState(playerState)
{
	// No nothing here
}

/*

	Local function used by this class only

*/
BOARD_SQUARE_STATE getOppositeMove(BOARD_SQUARE_STATE state)
{
	// Flip to the other player
	if (state == BOARD_SQUARE_STATE::CIRCLE)
	{
		return BOARD_SQUARE_STATE::CROSS;
	}
	else if (state == BOARD_SQUARE_STATE::CROSS)
	{
		return BOARD_SQUARE_STATE::CIRCLE;
	}
	else
		return BOARD_SQUARE_STATE::NONE;
}

bool TicTacToeNode::Expand()
{
	// Don't expand if it was a win or lose condition
	if (ranking != 0) {
		return true;
	}

	// Set the target start for the next action. Default to the player (starting node has no action)#
	// so it needs to target its own side first
	BOARD_SQUARE_STATE target_state = playerState;

	// If there is an action available, get the oppenent type so we can calculate their moves
	if (getAction())
	{
		TicTacToeAction* action = static_cast<TicTacToeAction*>(getAction());

		target_state = getOppositeMove(action->playerMove);
	}

	// Get world state
	TicTacToeWorldState* worldState = static_cast<TicTacToeWorldState*>(getWorldState());

	// Get copy of the game board
	GameBoardHandle gbh = worldState->getBoardCopy();

	// create vector to hold available moves
	std::vector<std::pair<int, int>> availableMoves;

	// Create a vector of available moves
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			if (gbh.board[j][i] == BOARD_SQUARE_STATE::NONE)
			{
				availableMoves.push_back(std::make_pair(i, j));
			}
		}
	}

	// Create as many child nodes as available moves
	for (std::pair<int, int> move : availableMoves)
	{
		TicTacToeAction* newAction = new TicTacToeAction(move.first, move.second, target_state);
		TicTacToeWorldState* newWorldState = new TicTacToeWorldState(worldState);
		TicTacToeNode* newNode = new TicTacToeNode(playerState);
		newNode->setAction(newAction);
		newNode->setWorldState(newWorldState);
		newNode->setParent(this);

		branches.push_back(newNode);
	}

	return true;
}

bool TicTacToeNode::SimulateChildBranch(BaseNode * node)
{
	// Perform analysis on what has changed verses previous world state
		// Compare this world state vs parents world state

		// get current state for this node - convert from TicTacToeState* to TicTacToeState*
	TicTacToeWorldState* state = static_cast<TicTacToeWorldState*>(node->getWorldState());
	state->performAction(node->getAction());

	GameBoardHandle gbh = state->getBoardCopy();


	// check each row for a match
	for (int i = 0; i < 3; i++)
	{
		if (gbh.board[i][0] != BOARD_SQUARE_STATE::NONE &&
			gbh.board[i][0] == gbh.board[i][1] &&
			gbh.board[i][0] == gbh.board[i][2])
		{
			node->BackPropagate(gbh.board[i][0] == playerState ? 1 : 1);
			return true;
		}
	}

	// Check each column
	for (int i = 0; i < 3; i++)
	{
		if (gbh.board[0][i] != BOARD_SQUARE_STATE::NONE &&
			gbh.board[0][i] == gbh.board[1][i] &&
			gbh.board[0][i] == gbh.board[2][i])
		{
			node->BackPropagate(gbh.board[0][i] == playerState ? 1 : 1);
			return true;
		}
	}

	// Check first diagonal
	if (gbh.board[0][0] != BOARD_SQUARE_STATE::NONE &&
		gbh.board[0][0] == gbh.board[1][1] &&
		gbh.board[0][0] == gbh.board[2][2])
	{
		node->BackPropagate(gbh.board[0][0] == playerState ? 1 : 1);
		return true;
	}

	// Check second diagonal
	if (gbh.board[0][2] != BOARD_SQUARE_STATE::NONE &&
		gbh.board[0][2] == gbh.board[1][1] &&
		gbh.board[0][2] == gbh.board[2][0])
	{
		node->BackPropagate(gbh.board[0][2] == playerState ? 1 : 1);
		return true;
	}

	return true;
}

