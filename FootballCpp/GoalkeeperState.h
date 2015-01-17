#pragma once

#include "PlayerState.h"

class CGoalKeeperIdleState : public CPlayerState
{
public:
	CGoalKeeperIdleState() { type_ = eGoalKeeperIdle; }

	void Execute(CPlayer* pPlayer);
};


class CGoalKeeperGuardState : public CPlayerState
{
public:
	CGoalKeeperGuardState() { type_ = eGoalKeeperGuardState; }

	void Execute(CPlayer* pPlayer);
};


class CGoalKeeperInterceptBall : public CPlayerState
{
public:
	CGoalKeeperInterceptBall() { type_ = eGoalKeeperInterceptBall; }

	 void Execute(CPlayer* pPlayer);
};

class CGoalKeeperTakePossession : public CPlayerState
{
public:
	CGoalKeeperTakePossession() { type_ = eGoalKeeperTakePossession; }

	void Execute(CPlayer* pPlayer);
};


class CGoalKeeperKickBall : public CPlayerState
{
public:
	CGoalKeeperKickBall() { type_ = eGoalKeeperKickBall; }

	void Execute(CPlayer* pPlayer);
};

class CGoalKeeperChaseBall : public CPlayerState
{
public:
	CGoalKeeperChaseBall() { type_ = eGoalKeeperChaseBall; }

	void Execute(CPlayer* pPlayer);
};