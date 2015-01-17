#pragma once

#include "PlayerState.h"


class CGoalKeeperIdleState : public CPlayerState
{
public:
	CGoalKeeperIdleState(): CPlayerState(eGoalKeeperIdle) { }

	void Execute(CPlayer* pPlayer);
};


class CGoalKeeperGuardState : public CPlayerState
{
public:
	CGoalKeeperGuardState() : CPlayerState(eGoalKeeperGuard){}

	void Execute(CPlayer* pPlayer);
};


class CGoalKeeperInterceptBallState : public CPlayerState
{
public:
	CGoalKeeperInterceptBallState() : CPlayerState(eGoalKeeperInterceptBall){}

	 void Execute(CPlayer* pPlayer);
};

class CGoalKeeperTakePossessionState : public CPlayerState
{
public:
	CGoalKeeperTakePossessionState() : CPlayerState(eGoalKeeperTakePossession){}

	void Execute(CPlayer* pPlayer);
};


class CGoalKeeperKickBallState : public CPlayerState
{
public:
	CGoalKeeperKickBallState(): CPlayerState(eGoalKeeperKickBall){}

	void Execute(CPlayer* pPlayer);
};

class CGoalKeeperChaseBallState : public CPlayerState
{
public:
	CGoalKeeperChaseBallState(): CPlayerState(eGoalKeeperChaseBall){}

	void Execute(CPlayer* pPlayer);
};