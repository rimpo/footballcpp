#pragma once

class CPlayer;
class CGame;
class CPitch;
class CBall;


class CPlayerState
{
public:
	typedef vector<CPlayerState> Vec;
	typedef CPlayerState* Ptr;
	typedef vector<Ptr> PtrVec;

	enum ePlayerStateType{
		eIdle = 0,
		eDead,
		eShootAtGoal,
		eGoToHome,
		eGoToAttack,
		eShortKick,
		eChaseBall,
		eInterceptPass,
		//----------- goal keeper
		eGoalKeeperIdle,
		eGoalKeeperGuard,
		eGoalKeeperChaseBall,
		eGoalKeeperTakePossession,
		eGoalKeeperKickBall,
		eGoalKeeperInterceptBall,
		
		//-- counter attacker - defender
		eCounterAttackerDefenderIdle,
		eCounterAttackerDefenderGoHome,
		eCounterAttackerDefenderInterceptBall,
		eCounterAttackerDefenderDefend,
		eCounterAttackerDefenderChaseBall,
		eCounterAttackerDefenderTakePossession,
		
		//-- counter attacker - striker
		eCounterAttackerStrikerIdle,
		eCounterAttackerStrikerGoHome,
		eCounterAttackerStrikerInterceptBall,
		eCounterAttackerStrikerDefend,
		eCounterAttackerStrikerChaseBall,
		eCounterAttackerStrikerTakePossession,
		eCounterAttackerStrikerShortKick,
			
		//Note: add new state above this
		eLastStateIndex
	};

	CPlayerState(int type);

	int GetType() { return type_; }

	virtual void Execute(CPlayer* pPlayer) {}

	static CPlayerState *GlobalPlayerState(int type);
	
	static void	InitGlobalPlayerStateVector();
	
	static PtrVec globalPlayerStates;
protected:
	int type_;
	CGame& game_;
	CPitch& pitch_;
	CBall& ball_;
};


class CDeadState : public CPlayerState
{
public:	
	CDeadState() : CPlayerState(CPlayerState::eDead) {}
	
	void Execute(CPlayer* pPlayer) {}
};
