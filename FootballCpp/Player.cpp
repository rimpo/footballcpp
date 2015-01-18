#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer() : game_(GetGame()),
					 pitch_(GetGame().GetPitch()),
					 ball_(GetGame().GetBall())
{
	SetMarkedPlayer(eNotMarking);
}


CPlayer::~CPlayer()
{

}

int CPlayer::ProcessStaticState(const Value& staticState)
{
	capability_.kickingAbility_ = staticState["kickingAbility"].GetDouble();
	capability_.runningAbility_ = staticState["runningAbility"].GetDouble();
	capability_.ballControlAbility_ = staticState["ballControlAbility"].GetDouble();
	capability_.tacklingAbility_ = staticState["tacklingAbility"].GetDouble();

	return 0;
}
int CPlayer::ProcessDynamicState(const Value& dynamicState)
{
	pos_.x_ = dynamicState["position"]["x"].GetDouble();
	pos_.y_ = dynamicState["position"]["y"].GetDouble();

	hasBall_ = dynamicState["hasBall"].GetBool();
	direction_ = dynamicState["direction"].GetDouble();

	//Flip co-ordinates
	const CTeam::Ptr& ourTeamPtr = GetGame().GetOurTeamPtr();

	if (ourTeamPtr->GetPlayingDirection() == CTeam::eLeft)
	{
		pos_.x_ = pitch_.GetWidth() - pos_.x_;
				
		direction_ = 360.0 - direction_;
	}
	return 0;
}
void CPlayer::MoveToSaveGoal_GoalKeeper(const Position& hittingAt)
{
	// try catching ball.
	Position surePos, almostPos;
	bool isSure = false, isAlmost = false;

	bool isFirstPosClosestToGoal = true;
	Position firstPosClosestToGoal;

	auto pathPos = ball_.GetPathPos(); 
	auto pathPosTime = ball_.GetPathPosTime();

	bool found = false;
	for (int i = pathPos.size() - 1; i >= 0; --i)
	{
		//ignore co-ordinate crossing our goal (i.e x < 0)
		if (hittingAt.x_ < pitch_.GetOurGoalCentre().x_)
		{
			continue;
		}

		//saving the first pos - incase of player not able to reach any coordinate
		//						 goalkeeper will attempt to go to this first pos.
		if (isFirstPosClosestToGoal)
		{
			firstPosClosestToGoal = pathPos[i];
			isFirstPosClosestToGoal = false;
		}

		float t1 = CalculateTimeToReachPosition(pathPos[i]);

		if (t1 < pathPosTime[i])
		{
			surePos = pathPos[i];
			isSure = true;
		}
		else if (ApproxEqual(t1, pathPosTime[i], 0.055f))
		{
			almostPos = pathPos[i];
			isAlmost = true;
		}
	}

	if (isSure)
	{
		MoveTo(surePos);
	}
	else if (isAlmost)
	{
		MoveTo(almostPos);
	}
	else
	{
		MoveTo(firstPosClosestToGoal);
	}
}
void CPlayer::MoveTo(const Position& dest)
{
	if (dest.ApproxEqual(pos_,POSITION_TOLERANCE))
	{
		action_.type_ = CAction::eNoAction;
		return;
	}
	action_.type_ = CAction::eMove;
	action_.destination_ = dest;
	action_.speed_ = 100.0;
}
void CPlayer::TurnTo(float direction)
{
	if (ApproxEqual(direction_, direction, DIRECTION_TOLERANCE))
	{
		action_.type_ = CAction::eNoAction;
		return;
	}

	action_.type_ = CAction::eTurn;
	action_.direction_ = direction;
}
void CPlayer::TakePossession()
{
	action_.type_ = CAction::eTakePossession;
}
float CPlayer::PredictDirection()
{
	auto theirTeamPtr = game_.GetTheirTeamPtr();
	
	if (theirTeamPtr->IsMember(ball_.GetOwner()))
	{
		auto pBallPlayer = game_.GetPlayer(ball_.GetOwner());

		Vector vecDir = GetVectorFromDirection(pBallPlayer->GetDirection());
		
		Vector vecDir40 = vecDir.Scale(40.0);

		Position dist40pos = pBallPlayer->GetPosition();
		dist40pos.AddVector(vecDir40);

		Position hitPos;
		if (pitch_.IsLineHittingOurGoal(pBallPlayer->GetPosition(), dist40pos, hitPos))
		{
			if (hitPos.y_ > 25.0)
			{
				return 225.0;
			}
			else if (hitPos.y_ < 25.0)
			{
				return 315.0;
			}
			else
				return 270.0;
		}
		else
			return 270.0;
	}

	return 270.0;
}
void CPlayer::MoveToGuardGoal_Radius()
{
	//Radius guard
	Position ourGoalCentre = pitch_.GetOurGoalCentre();
	Vector goalToBallvector(ourGoalCentre, ball_.GetPosition());


	Vector scaledVec = goalToBallvector.Scale(4.5);

	ourGoalCentre.AddVector(scaledVec);

	if (ourGoalCentre.x_ > 2.5)
		ourGoalCentre.x_ = 2.5;

	if (pos_.ApproxEqual(ourGoalCentre, POSITION_GUARD_TOLERANCE))
	{
		//already in postion. so turn to defend
		TurnTo(PredictDirection());
	}
	else{
		MoveTo(ourGoalCentre);
	}

}

void CPlayer::MoveToGuardGoal_Centre()
{
	Position ourGoalCentre = pitch_.GetOurGoalCentre();
	if (pos_.ApproxEqual(ourGoalCentre, POSITION_GUARD_TOLERANCE))
	{
		//already in postion. so turn to defend
		TurnTo(90.0);
	}
	else{
		MoveTo(ourGoalCentre);
	}
}

void CPlayer::MoveToGuardGoal()
{
	//MoveToGuardGoal_Centre();
	//MoveToGuardGoal_LineSave();
	MoveToGuardGoal_Radius();
}
void CPlayer::MoveToGuardGoal_LineSave()
{
	Position ourGoalCentre = pitch_.GetOurGoalCentre();

	ourGoalCentre.x_ = 1.0;

	if (pos_.ApproxEqual(ourGoalCentre, POSITION_GUARD_TOLERANCE))
	{
		//already in postion. so turn to defend
		TurnTo(270.0);
	}
	else{
		MoveTo(ourGoalCentre);
	}
}

void CPlayer::Kick(const Position& destination, float speed)
{
	action_.type_ = CAction::eKick;
	action_.destination_ = destination;
	action_.speed_ = speed;
}

float CPlayer::CalculateTimeToTurn(float direction)
{
	float timeTaken = 0.0;
	
	
	if (ApproxEqual(direction_, direction, DIRECTION_TOLERANCE))
	{
		return timeTaken;
	}
	float angleToTurn = direction - direction_;
	if (angleToTurn > 180) 
	{
			// We are turning more than 180 degrees to the right,
			// so this is really a turn to the left...
			angleToTurn = angleToTurn - 360;
	}
	if (angleToTurn < -180) 
	{
			// We are turning more than 180 degrees to the left,
			// so this is really a turn to the right...
			angleToTurn = 360 + angleToTurn;
	}

	if (angleToTurn < 0.0) 
	{
		angleToTurn = -1.0 * angleToTurn;
	}

	int noOfTurn = angleToTurn / MAX_TURN_ANGLE;
	
	if ((angleToTurn - angleToTurn*noOfTurn) > 0.0)
	{
		noOfTurn += 1;
	}
	
	return noOfTurn * GAME_AI_CALCULATION_INTERVAL;
}
float CPlayer::CalculateTimeToReachPosition(const Position& dest)
{
	float timeTaken = 0.0;
	
	float destDirection = pos_.AngleWith(dest);

	float timeTakenToTurn = CalculateTimeToTurn(destDirection);

	float distanceToDest = pos_.DistanceFrom(dest);

	float speed = MAX_PLAYER_SPEED*(capability_.runningAbility_ / 100.0);

	float distanceInSingleTurn = speed*GAME_AI_CALCULATION_INTERVAL;

	float noOfTurn = distanceToDest / distanceInSingleTurn;

	if ((distanceToDest - distanceInSingleTurn * noOfTurn) > 0.0)
	{
		noOfTurn += 1;
	}
	
	timeTaken = timeTakenToTurn + noOfTurn*GAME_AI_CALCULATION_INTERVAL;

	return timeTaken;
}
void CPlayer::ChangeState(int type)
{
	pState_ = CPlayerState::GlobalPlayerState(type);
}