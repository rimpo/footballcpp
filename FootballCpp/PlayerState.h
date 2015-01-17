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
		eCounterAttackerDefenderIdle,
		eCounterAttackerDefenderGoHome,
		eCounterAttackerDefenderInterceptBall,
		eCounterAttackerDefenderDefend,
		eCounterAttackerDefenderChaseBall,
		eCounterAttackerDefenderTakePossession,
		
		//Note: add new state above this
		eLastStateIndex
	};

	CPlayerState(int type);

	int GetType() { return type_; }

	virtual void Execute(CPlayer* pPlayer) {};

	static CPlayerState *GlobalPlayerState(int type);
	static PtrVec globalPlayerStates;
protected:
	int type_;
	CGame& game_;
	CPitch& pitch_;
	CBall& ball_;
};

