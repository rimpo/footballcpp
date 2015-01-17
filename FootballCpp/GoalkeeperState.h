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
	CGoalKeeperGuardState() : CPlayerState(eGoalKeeperGuardState){}

	void Execute(CPlayer* pPlayer);
};


class CGoalKeeperInterceptBall : public CPlayerState
{
public:
	CGoalKeeperInterceptBall() : CPlayerState(eGoalKeeperInterceptBall){}

	 void Execute(CPlayer* pPlayer);
};

class CGoalKeeperTakePossession : public CPlayerState
{
public:
	CGoalKeeperTakePossession() : CPlayerState(eGoalKeeperTakePossession){}

	void Execute(CPlayer* pPlayer);
};


class CGoalKeeperKickBall : public CPlayerState
{
public:
	CGoalKeeperKickBall(): CPlayerState(eGoalKeeperKickBall){}

	void Execute(CPlayer* pPlayer);
};

class CGoalKeeperChaseBall : public CPlayerState
{
public:
	CGoalKeeperChaseBall(): CPlayerState(eGoalKeeperChaseBall){}

	void Execute(CPlayer* pPlayer);
};