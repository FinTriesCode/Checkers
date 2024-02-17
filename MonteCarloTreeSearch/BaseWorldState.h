#ifndef _BASE_WORLD_STATE_H_
#define _BASE_WORLD_STATE_H_

namespace MCTS
{
	class BaseAction;

	class BaseWorldState
	{
	public:
		BaseWorldState(bool loaded = false) : loadedFromPreviousState(loaded), actionPerformed(false) { /*Do nothing constructor */ };
		virtual void copyFromPreviousState(BaseWorldState* prevState) = 0;
		virtual bool performAction(BaseAction* action) = 0;
		bool hasActionBeenPerformed() { return actionPerformed; }

	protected:
		bool loadedFromPreviousState;
		bool actionPerformed;
	};
}

#endif