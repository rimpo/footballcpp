#pragma once

#include "Player.h"

class CTeam
{
public:
	typedef vector<CTeam> Vec;
	typedef shared_ptr<CTeam> Ptr;
	typedef vector<Ptr> PtrVec;

	enum eDirectionType{
		eRight = 0,
		eLeft = 1
	};

	enum eTeamType{
		eOur = 0,
		eTheir = 1
	};

	CTeam();
	~CTeam();

	void SetDirectionType(eDirectionType dirType){ directionType_ = dirType; }

	const string& GetTeamIdentifier(){ return teamIdentifier_; }
	const void SetTeamIdentifier(const string& strId){ teamIdentifier_ = strId; }

	void SetTeamNumber(int teamNumber) { teamNumber_ = teamNumber; }
	int GetTeamNumber() { return teamNumber_; }

	const CPlayer::PtrVec& GetPlayers(){ return players_; }
	const CPlayer::PtrVec& GetNonGoalKeepers(){ return nonGoalKeepers_; }
	const CPlayer::Ptr&	   GetGoalKeeper(){ return goalKeeperPtr_; }

	const eDirectionType GetPlayingDirection(){ return directionType_; }

	const CCapability& GetTotalCapability(){ return totalCapability_; }

	int ProcessTeamInfo(const Document& document);
	int ProcessTeamKickOffInfo(const Document& document);
	int ProcessStartOfTurn(const Document& document);
	int ProcessCapabilitiesRequest(const Document& document);

	inline bool IsMember(int playerNumber) { return playerNumber != -1 && maxTeamNumber_ >= playerNumber && minTeamNumber_ <= playerNumber; }


	void MapPlayerTypeToPlayerPtr();
	inline const CPlayer::Ptr& GetPlayerFromPlayerType(int type) { return playerTypeToPlayer_[type]; }
private:
	int teamNumber_;
	CPlayer::PtrVec players_;
	CPlayer::PtrVec nonGoalKeepers_;
	CPlayer::Ptr	goalKeeperPtr_;

	CPlayer::PtrVec playerTypeToPlayer_;
		
	eDirectionType  directionType_;		//e.g. eLeft or eRight (i.e. LEFT or RIGHT)
	string			teamName_;			//e.g. BootAndShoot or XYZ
	string			teamIdentifier_;	//e.g. team1 or team2

	int score_;

	CCapability     totalCapability_;	//total budget for all player in the team

	bool firstTime_;					// this is dirty logic to execute code only first time. 
	int maxTeamNumber_, minTeamNumber_;


};

