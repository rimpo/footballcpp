#include"stdafx.h"
#include"PlayerState.h"

#include "Player.h"
#include "GoalkeeperState.h"
#include "CounterAttackerState.h"

CIdleState gIdleState;
CShootAtGoalState gShootAtGoalState;
CGoToHomePositionState gGoToHomePositionState;
CGoToAttackPositionState gGoToAttackPositionState;
CShortKickState gShortKickState;

CGoalKeeperIdleState gGKIdleState;
CGoalKeeperGuardState gGKGuardState;
CGoalKeeperInterceptBall gGKInterceptState;
CGoalKeeperTakePossession gGKTakePossession;
CGoalKeeperKickBall gGKKickBall;
CGoalKeeperChaseBall gGKChaseBall;

CCounterAttackerIdleState gCAIdleState;
CCounterAttackerGoHomeState gCAGoHomeState;
CCounterAttackerDefendState gCADefendState;
CCounterAttackerChaseBallState gCAChaseBallState;
CCounterAttackerTakePossessionState gCATakePossessionState;

CPlayerState::CPlayerState() : game_(GetGame()),
							   pitch_(GetGame().GetPitch()),
							   ball_(GetGame().GetBall())
{

}

CPlayerState *CPlayerState::GlobalPlayerState(int type)
{
	switch (type)
	{
	case CPlayerState::eIdle:
		return &gIdleState;
	case CPlayerState::eShootAtGoal:
		return &gShootAtGoalState;
	case CPlayerState::eGoToHome:
		return &gGoToHomePositionState;
	case CPlayerState::eGoToAttack:
		return &gGoToAttackPositionState;
	case CPlayerState::eShortKick:
		return &gShortKickState;
	case CPlayerState::eGoalKeeperIdle:
		return &gGKIdleState;
	case CPlayerState::eGoalKeeperGuardState:
		return &gGKGuardState;
	case CPlayerState::eGoalKeeperInterceptBall:
		return &gGKInterceptState;
	case CPlayerState::eGoalKeeperTakePossession:
		return &gGKTakePossession;
	case CPlayerState::eGoalKeeperKickBall:
		return &gGKKickBall;
	case CPlayerState::eGoalKeeperChaseBall:
		return &gGKChaseBall;
	case CPlayerState::eCounterAttackerIdle:
		return &gCAIdleState;
	case CPlayerState::eCounterAttackerGoHome:
		return &gCAGoHomeState;
	case CPlayerState::eCounterAttackerDefend:
		return &gCADefendState;
	case CPlayerState::eCounterAttackerChaseBall:
		return &gCAChaseBallState;
	case CPlayerState::eCounterAttackerTakePossession:
		return &gCATakePossessionState;
	}

	return NULL;
}



void CShootAtGoalState::Execute(CPlayer* pPlayer)
{
	//pPlayer->MoveTo(pPlayer->GetHomePosition());
}


void CGoToHomePositionState::Execute(CPlayer* pPlayer)
{
	pPlayer->MoveTo(pPlayer->GetHomePosition());
}


void CGoToAttackPositionState::Execute(CPlayer* pPlayer)
{
	pPlayer->MoveTo(pPlayer->GetAttackPosition());
}


void CShortKickState::Execute(CPlayer* pPlayer)
{

}

void CChaseBallState::Execute(CPlayer* pPlayer)
{

}
