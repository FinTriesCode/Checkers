#include "TicTacToeWorldState.h"

TicTacToeWorldState::TicTacToeWorldState(bool loaded) :
	BaseWorldState(loaded)
{
	// No nothing here
}

TicTacToeWorldState::TicTacToeWorldState(TicTacToeWorldState * prevWorldState, bool loaded) :
	BaseWorldState(loaded)
{
	// Make a copy of the world state from a previous state
	copyFromPreviousState(prevWorldState);
}

void TicTacToeWorldState::copyFromPreviousState(BaseWorldState * prevState)
{
	// Cast to the current world state pointer
	TicTacToeWorldState* previousChessState = static_cast<TicTacToeWorldState*>(prevState);

	// Check the pointer is valid
	if (previousChessState) {
		// Pass a copy of the board across
		boardHandle = previousChessState->getBoardCopy();

		// State the gameboard has been loaded
		loadedFromPreviousState = true;
	}
}

bool TicTacToeWorldState::performAction(BaseAction * action)
{
	// Onyl perform action if game baord has been loaded
	if (loadedFromPreviousState)
	{
		// Convert the action to a TicTacToeAction
		TicTacToeAction* currentAction = static_cast<TicTacToeAction*>(action);

		// Make the change on the board
		boardHandle.board[currentAction->y][currentAction->x] = currentAction->playerMove;

		// State the action has been performed
		actionPerformed = true;

		return true;
	}
	return false;
}
