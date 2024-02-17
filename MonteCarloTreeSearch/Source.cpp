#include <iostream>
#include <conio.h>

#include "SearchTreeEngine.h"
#include "TicTacToeNode.h"
#include "TicTacToeWorldState.h"
#include "TicTacToeAction.h"

using std::cout;
using std::endl;
using std::cin;

BOARD_SQUARE_STATE checkWin(TicTacToeWorldState* worldState)
{
	GameBoardHandle gbh = worldState->getBoardCopy();
	// check each row for a match
	for (int i = 0; i < 3; i++)
	{
		if (gbh.board[i][0] != BOARD_SQUARE_STATE::NONE &&
			gbh.board[i][0] == gbh.board[i][1] &&
			gbh.board[i][0] == gbh.board[i][2])
		{
			return gbh.board[i][0];
		}
	}

	// Check each column
	for (int i = 0; i < 3; i++)
	{
		if (gbh.board[0][i] != BOARD_SQUARE_STATE::NONE &&
			gbh.board[0][i] == gbh.board[1][i] &&
			gbh.board[0][i] == gbh.board[2][i])
		{
			return gbh.board[0][i];
		}
	}

	// Check first diagonal
	if (gbh.board[0][0] != BOARD_SQUARE_STATE::NONE &&
		gbh.board[0][0] == gbh.board[1][1] &&
		gbh.board[0][0] == gbh.board[2][2])
	{
		return gbh.board[0][0];
	}

	// Check second diagonal
	if (gbh.board[0][2] != BOARD_SQUARE_STATE::NONE &&
		gbh.board[0][2] == gbh.board[1][1] &&
		gbh.board[0][2] == gbh.board[2][0])
	{
		return gbh.board[0][2];
	}

	// If no-one wins return the default state
	return BOARD_SQUARE_STATE::NONE;
}

char printState(BOARD_SQUARE_STATE printState)
{
	// Print characters for specific states
	switch (printState)
	{
	case BOARD_SQUARE_STATE::NONE:
		return '.';
	case BOARD_SQUARE_STATE::CROSS:
		return 'X';
	case BOARD_SQUARE_STATE::CIRCLE:
		return 'O';
	}

	return ' ';
}

bool printBoard(TicTacToeWorldState* worldState)
{
	// Clear the console
	system("cls");

	// Print the board
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			cout << " " << printState(worldState->getBoardCopy().board[j][i]);
		}
		cout << endl;
	}

	// Check if there is a winner
	auto result = checkWin(worldState);

	// Print out win message if its one of the players
	switch (result)
	{
	case BOARD_SQUARE_STATE::CIRCLE:
		cout << endl << endl << "CIRCLE WINS!!!" << endl;
		return false;
		break;
	case BOARD_SQUARE_STATE::CROSS:
		cout << endl << endl << "CROSS WINS!!!" << endl;
		return false;
	case BOARD_SQUARE_STATE::NONE:
	default:
		break;
	}

	// Check that the game can continue and return true if we find a valid move is available
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			if (worldState->getBoardCopy().board[j][i] == BOARD_SQUARE_STATE::NONE)
			{
				return true;
			}
		}
	}

	// Return false if we can find more more valid moves to make (indicates draw)
	return false;
}

int main()
{
	cout << "Monte Carlo Tree Search Example..." << endl;

	// Create a world state that will represent the game map
	TicTacToeWorldState worldState(true);

	// Create an engine class for running and creating the tree
	MCTS::SearchTreeEngine engine;

	// Keep looping forever
	while(1)
	{
		// Create a new starting node - Get the AI to player as CROSS
		TicTacToeNode* startingNode = new TicTacToeNode(BOARD_SQUARE_STATE::CROSS);

		// Create a local copy of the world state for the starting Node
		// Nodes delete their world state when they are cleaned up so we need a copy
		TicTacToeWorldState* copyForDeletion = new TicTacToeWorldState(worldState);
		startingNode->setWorldState(copyForDeletion);

		// Initialise the Engine
		engine.InitEngine(startingNode);

		// Get the best result from the engine
		BaseAction* bestAction = engine.Run();
		worldState.performAction(bestAction);

		// Print the board - this functions tells us of someone has won so returns false a victor occurs
		if (!printBoard(&worldState))
		{
			break;
		}

		// Get the user to enter their X and Y co-ords
		int x = -1, y = -1;
		cout << "Enter your x position: ";
		cin >> x;

		cout << "Enter your y position: ";
		cin >> y;

		worldState.getBoardRef().board[y][x] = BOARD_SQUARE_STATE::CIRCLE;

		// Print again
		if (!printBoard(&worldState))
		{
			break;
		}

		// Delete the starting node for the next round
		delete startingNode;
	}

	// Wait for a keyboard hit before ending the program
	while (!_kbhit());

	return 0;
}


