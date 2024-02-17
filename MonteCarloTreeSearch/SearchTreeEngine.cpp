#include "SearchTreeEngine.h"
#include "BaseNode.h"

namespace MCTS
{
	BaseAction* SearchTreeEngine::Run()
	{
		// While there are branches to explore
		while (!openBranches.empty())
		{
			// Get a branch
			BaseNode* currentNode = Select();
			openBranches.pop();

			// Expand the branch
			if (!Expand(currentNode))
				printf("Error in expanding node");

			// Simualte the branch
			if (!Simulate(currentNode))
				printf("Error in simulating node");
		}

		// After all branches expanded and simulated, return the best ones action for the AI to use
		return startingNode->getHighestRankChild()->getAction();
	}

	void SearchTreeEngine::InitEngine(BaseNode * startingNode)
	{
		// Set the starting node and pass it into the open branches
		this->startingNode = startingNode;
		openBranches.push(startingNode);
	}

	BaseNode* SearchTreeEngine::Select()
	{
		// Get the first branch in the open set
		return openBranches.front();
	}

	bool SearchTreeEngine::Expand(BaseNode* node)
	{
		// Expand the current branch
		bool success = node->Expand();

		// Get all the new branches
		auto newBranches = node->getBranches();

		// Add each new branch into the open branches
		for (auto branch : newBranches)
		{
			openBranches.push(branch);
		}

		// Return success factor
		return success;
	}

	bool SearchTreeEngine::Simulate(BaseNode* node)
	{
		// Simulate all new branch nodes
		return node->Simulate();
	}
}