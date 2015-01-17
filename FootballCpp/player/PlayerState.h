#pragma once

class CPlayer;
class CGame;
class CPitch;
class CBall;

class CPlayerState
{
public:
	typedef vector<CPlayerState> Vec;
	typedef shared_ptr<CPlayerState> Ptr;
	typedef vector<Ptr> PtrVec;

	enum ePlayerStateType{
		eIdle,
		eShootAtGoal,
		eGoToHome,
		eGoToAttack,
		eShortKick,
		eChaseBall,
		eInterceptPass,
		//----------- goal keeper
		eGoalKeeperIdle,
		eGoalKeeperGuardState,
		eGoalKeeperChaseBall,
		eGoalKeeperTakePossession,
		eGoalKeeperKickBall,
		eGoalKeeperInterceptBall,
		//----------- counter attacker
		eCounterAttackerIdle,
		eCounterAttackerGoHome,
		eCounterAttackerInterceptBall,
		eCounterAttackerDefend,
		eCounterAttackerChaseBall,
		eCounterAttackerTakePossession
	};

	CPlayerState();

	int GetType() { return type_ = eIdle; }

	virtual void Execute(CPlayer* pPlayer) {};

	static CPlayerState *CPlayerState::GlobalPlayerState(int type);
	
protected:
	int type_;
	CGame& game_;
	CPitch& pitch_;
	CBall& ball_;
};

typedef CPlayerState CIdleState;

class CShootAtGoalState : public CPlayerState
{
public:
	CShootAtGoalState() { type_ = eShootAtGoal; }

	virtual void Execute(CPlayer* pPlayer);
};

class CGoToHomePositionState : public CPlayerState
{
public:
	CGoToHomePositionState() { type_ = eGoToHome; }

	virtual void Execute(CPlayer* pPlayer);
};

class CGoToAttackPositionState : public CPlayerState
{
public:
	CGoToAttackPositionState() { type_ = eGoToAttack; }

	virtual void Execute(CPlayer* pPlayer);
};

class CShortKickState : public CPlayerState
{
public:
	CShortKickState() { type_ = eShortKick; }

	virtual void Execute(CPlayer* pPlayer);
};

class CChaseBallState : public CPlayerState
{
public:
	CChaseBallState() { type_ = eChaseBall; }
	
	virtual void Execute(CPlayer* pPlayer);
};

