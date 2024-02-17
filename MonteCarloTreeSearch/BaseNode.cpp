#include "BaseNode.h"
#include "BaseAction.h"
#include "BaseWorldState.h"
#include <algorithm>

namespace MCTS
{
	BaseNode::BaseNode() :
		ranking(0),
		parent(nullptr),
		action(nullptr),
		worldState(nullptr)
	{
	}

	BaseNode::~BaseNode()
	{
		// parent will be deleted by its parent so we don't need to clean it up here
		parent = nullptr;

		// Clean up action
		delete action;
		action = nullptr;

		// Clean up world State
		delete worldState;
		worldState = nullptr;

		// Clean up and destory open branches vector
		for (auto branch : branches)
		{
			delete branch;
		}
		branches.clear();
	}

	BaseNode* BaseNode::getHighestRankChild()
	{
		// This struct manages our comparison so that nodes with the hgihest ranking are sorted to the front of the vector
		struct {
			bool operator()(BaseNode* a, BaseNode* b) {
				return (a->getRanking() > b->getRanking());
			}
		} compareRank;

		// Only sort if we have more than 1 branch
		if (branches.size() > 1) {
			std::sort(branches.begin(), branches.end(), compareRank);
			return branches.front();
		}
		return nullptr;
	}

	void BaseNode::BackPropagate(int childRanking)
	{
		// Add to the ranking and pass it back up the tree to the root
		ranking += childRanking;
		if (parent)
		{
			parent->BackPropagate(childRanking);
		}
	}

	bool BaseNode::Simulate()
	{
		bool result = true;

		// Simulate each child branch
		for (auto branch : branches)
		{
			if (!SimulateChildBranch(branch))
			{
				result = false;
				break;
			}
		}

		// Return success code
		return result;
	}
}