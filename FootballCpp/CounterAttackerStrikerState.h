#pragma once

#include "PlayerState.h"

class CCounterAttackerStrikerIdleState : public CPlayerState
{
public:
	CCounterAttackerStrikerIdleState() : CPlayerState(CPlayerState::eCounterAttackerStrikerIdle){}
	
	void Execute(CPlayer *pPlayer);
};

class CCounterAttackerStrikerChaseBallState : public CPlayerState
{
public:
	CCounterAttackerStrikerChaseBallState() : CPlayerState(CPlayerState::eCounterAttackerStrikerChaseBall){}
	
	void Execute(CPlayer *pPlayer);
};

class CCounterAttackerStrikerShortKickState : public CPlayerState
{
public:
	CCounterAttackerStrikerShortKickState() : CPlayerState(CPlayerState::eCounterAttackerStrikerShortKick){}
	
	void Execute(CPlayer *pPlayer);
};



class CCounterAttackerStrikerTakePossessionState : public CPlayerState
{
public:
	CCounterAttackerStrikerTakePossessionState() : CPlayerState(CPlayerState::eCounterAttackerStrikerTakePossession){}
	
	void Execute(CPlayer *pPlayer);
};