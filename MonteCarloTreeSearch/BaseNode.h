#ifndef _BASE_NODE_H_
#define _BASE_NODE_H_

#include <vector>

namespace MCTS
{
	class BaseAction;
	class BaseWorldState;

	class BaseNode
	{
	public:
		BaseNode();
		~BaseNode();

		BaseNode* getHighestRankChild();

		void BackPropagate(int childRanking);

		virtual bool Expand() = 0;
		bool Simulate();

	public:
		inline void setAction(BaseAction* newAction) { action = newAction; }
		inline BaseAction* getAction() { return action; }

		inline void setWorldState(BaseWorldState* newWorldState) { worldState = newWorldState; }
		inline BaseWorldState* getWorldState() { return worldState; }

		inline std::vector<BaseNode*> getBranches() { return branches; }

		inline int getRanking() { return ranking; }

		inline void setParent(BaseNode* newParent) { parent = newParent; }

	protected:
		int ranking;
		std::vector<BaseNode*> branches;
		BaseNode* parent;
		BaseAction* action;
		BaseWorldState* worldState;

	protected:
		virtual bool SimulateChildBranch(BaseNode* node) = 0;
	};
}

#endif