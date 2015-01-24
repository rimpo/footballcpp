#pragma once

#include"Logger.h"

#include"Team.h"
#include"Pitch.h"
#include"Ball.h"
#include"Action.h"
#include"CounterAttackerAI.h"

#define MAX_NO_OF_PLAYERS  12
#define GAME_AI_CALCULATION_INTERVAL  0.01
#define FRICTION 10.0
#define APPROX_TOLERANCE  0.00001
#define PI 3.14159265359
#define MAX_TURN_ANGLE 6.0
#define MAX_PLAYER_SPEED 10.0



class CGame
{
public:
	

	enum eGameConstants{
		
	};
	
	CGame();
	virtual ~CGame();
	
	inline const CPlayer::Ptr& GetPlayer(int playerNumber) { return allPlayers_[playerNumber];}
	inline const CStrategyAI::Ptr& GetStrategy() { return strategyPtr_; }
	inline const CTeam::Ptr& GetOurTeamPtr() { return ourTeamPtr_; }
	inline const CTeam::Ptr& GetTheirTeamPtr() { return theirTeamPtr_; }
	
	inline CPlayerState::PtrVec& GetStateVec() { return allStatesVec_;}

	inline const CPlayer::Ptr& GetClosestPlayer(){ return closestPlayer_; }
	inline const CPlayer::PtrVec& GetTheirTeamSortedX() { return theirTeamSortedX_; }
	inline const CPlayer::PtrVec& GetAllPlayersToBallSortedDist() { return allPlayersToBallSortedDist_; }

	
	inline CPitch& GetPitch() { return pitch_; }
	inline CBall& GetBall() { return ball_; }

	int Process(const string& sJsonMsg);

	void PrintCapabilityResponse();
	void PrintKickOffResponse();
	void PrintPlayResponse();

	void CalculateAllPlayerToBallSortedDistance();

	void SortTheirTeamX();
	
	
private:
	CTeam::PtrVec teams_;
	CTeam::Ptr	  ourTeamPtr_, theirTeamPtr_;

	CPlayer::PtrVec allPlayers_;

	CPitch pitch_;

	CBall  ball_;

	float gameLengthSeconds_;
	float currentTimeSeconds_;

	CStrategyAI::Ptr strategyPtr_;

	CPlayer::Ptr closestPlayer_;	//player who reaches the ball first (including goal keepers)

	CPlayer::PtrVec theirTeamSortedX_; //x co-oridnate ascending sort

	CPlayer::PtrVec allPlayersToBallSortedDist_;
	
	CPlayerState::PtrVec allStatesVec_;
public:
	int noOfGoalAttempts;
};

