#pragma once

#include "PlayerState.h"

class CCounterAttackerIdleState : public CPlayerState
{
public:
	void Execute(CPlayer *pPlayer);
};
class CCounterAttackerReceivePassState : public CPlayerState
{
	public:
	void Execute(CPlayer *pPlayer);
};

class CCounterAttackerGoHomeState : public CPlayerState
{
public:
	void Execute(CPlayer *pPlayer);
};

class CCounterAttackerDefendState : public CPlayerState
{
public:
	void Execute(CPlayer *pPlayer);
};

class CCounterAttackerChaseBallState : public CPlayerState
{
public:
	void Execute(CPlayer *pPlayer);
};

class CCounterAttackerTakePossessionState : public CPlayerState
{
public:
	void Execute(CPlayer *pPlayer);
};