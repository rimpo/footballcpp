#include"stdafx.h"
#include"PlayerState.h"

#include "Player.h"
#include "GoalkeeperState.h"
#include "CounterAttackerDefenderState.h"


CGoalKeeperIdleState gGKIdleState;
CGoalKeeperGuardState gGKGuardState;
CGoalKeeperInterceptBall gGKInterceptState;
CGoalKeeperTakePossession gGKTakePossession;
CGoalKeeperKickBall gGKKickBall;
CGoalKeeperChaseBall gGKChaseBall;

CCounterAttackerDefenderIdleState gCAIdleState;
CCounterAttackerDefenderGoHomeState gCAGoHomeState;
CCounterAttackerDefenderDefendState gCADefendState;
CCounterAttackerDefenderChaseBallState gCAChaseBallState;
CCounterAttackerDefenderTakePossessionState gCATakePossessionState;

CPlayerState::PtrVec CPlayerState::globalPlayerStates;


CPlayerState::CPlayerState(int type) : type_(type),
									   game_(GetGame()),
									   pitch_(GetGame().GetPitch()),
									   ball_(GetGame().GetBall())
{
	//pre-allocate the whole vector
	if (globalPlayerStates.empty())
	{
		globalPlayerStates.resize(CPlayerState::eLastStateIndex);
	}
	
	globalPlayerStates[type_] = this;
}

CPlayerState *CPlayerState::GlobalPlayerState(int type)
{
	if( type <= CPlayerState::eLastStateIndex)
		return globalPlayerStates[type];
		
	return nullptr;
}

