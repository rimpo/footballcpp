#pragma once

#include "PlayerState.h"

class CCounterAttackerDefenderIdleState : public CPlayerState
{
public:
	CCounterAttackerDefenderIdleState() : CPlayerState(CPlayerState::eCounterAttackerDefenderIdle){}
	
	void Execute(CPlayer *pPlayer);
};


class CCounterAttackerDefenderGoHomeState : public CPlayerState
{
public:
	CCounterAttackerDefenderGoHomeState() : CPlayerState(CPlayerState::eCounterAttackerDefenderGoHome){}

	void Execute(CPlayer *pPlayer);
};

class CCounterAttackerDefenderDefendState : public CPlayerState
{
public:
	CCounterAttackerDefenderDefendState() : CPlayerState(CPlayerState::eCounterAttackerDefenderDefend){}
	
	void Execute(CPlayer *pPlayer);
};

class CCounterAttackerDefenderChaseBallState : public CPlayerState
{
public:
	CCounterAttackerDefenderChaseBallState() : CPlayerState(CPlayerState::eCounterAttackerDefenderChaseBall){}
	
	void Execute(CPlayer *pPlayer);
};

class CCounterAttackerDefenderTakePossessionState : public CPlayerState
{
public:
	CCounterAttackerDefenderTakePossessionState() : CPlayerState(CPlayerState::eCounterAttackerDefenderTakePossession){}
	
	void Execute(CPlayer *pPlayer);
};