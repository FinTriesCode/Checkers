#ifndef _SEARCH_TREE_ENGINE_H_
#define _SEARCH_TREE_ENGINE_H_

#include <queue>

namespace MCTS
{
	class BaseNode;
	class BaseAction;

	class SearchTreeEngine
	{
	public:
		BaseAction* Run();
		void InitEngine(BaseNode* startingNode);
		
	private:
		BaseNode* Select();
		bool Expand(BaseNode* node);
		bool Simulate(BaseNode* node);

	protected:
		std::queue<BaseNode*> openBranches;
		BaseNode* startingNode = nullptr;
	};
}

#endif