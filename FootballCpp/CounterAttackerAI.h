#pragma once

#include "StrategyAI.h"

class CCounterAttackerAI : public CStrategyAI{
public:
	enum PlayerType
	{
		eGoalKeeper = 0,
		eLeftDefender,
		eRightDefender,
		eLeftCounterAttacker,
		eCentralCounterAttacker,
		eRightCounterAttacker
	};

	CCounterAttackerAI();

	void InitializeOurPlayers();

	void OnTeamInfoEvent();
	void OnStartOfTurnEvent();
	void OnCapabilityRequest();

protected:
	Position::Vec playersAttackPos_;
	vector<float> playersAttackDirection_;
};