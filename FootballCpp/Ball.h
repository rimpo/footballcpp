#pragma once

#include "Position.h"
#include "Vector.h"

typedef vector<float> TimeVec;

class CBall
{
public:
	CBall();
	~CBall();

	

	inline Position& GetPosition() { return pos_; }
	inline const Vector& GetVector() { return vector_; }

	inline const Position& GetStationaryPosition() { return stationaryPos_; }

	inline int GetOwner() { return controllingPlayerNumber_; }
	inline float GetSpeed() { return speed_; }


	int ProcessStartOfTurn(const Value& ballInfo);

	void CalculateStationaryPos(float& timeTaken);

	bool IsHittingOurGoal(const Position& targetPos);

	void CorrectToCatchBall_Early(Position& dest, float& timetaken);
	void CorrectToCatchBall_Late(Position& dest, float& timetaken);

	void PositionTimeTaken(const Position& dest, vector<Position>& posVec, vector<float>& timeTakenVec);

	void EstimatePath();

	inline const Position::Vec& GetPathPos() { return pathPos_; }
	inline const TimeVec& GetPathPosTime() { return pathPosTime_; }

	inline bool IsFreeBall() { return (controllingPlayerNumber_ == -1); }
	bool IsOurTeamControlling();
	bool IsTheirTeamControlling();
	
	bool IsOurGoalKeeperControlling();
	bool IsTheirGoalKeeperControlling();
	
private:
	
	Position pos_;
	Vector   vector_;
	float	  speed_;
	int		  controllingPlayerNumber_;

	Position stationaryPos_;
	float	 stationaryTimeTaken_;
	
	Position::Vec pathPos_;
	TimeVec	 pathPosTime_;
};

