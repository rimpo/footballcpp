#include "stdafx.h"
#include "CounterAttackerStrikerState.h"


void CCounterAttackerStrikerIdleState::Execute(CPlayer* pPlayer)
{
	Position perIntersection;
	
	if (ball_.GetStationaryPosition().x_  < 50.0f)
	{
		pPlayer->MoveTo(pPlayer->GetHomePosition());
		return;
	}

	if (ball_.GetSpeed() == 0)
	{
		if (ball_.GetStationaryPosition().x_ > 50.0f)
		{
			pPlayer->MoveTo(ball_.GetStationaryPosition());
			pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerChaseBall);
		}
		else
		{
			pPlayer->MoveTo(pPlayer->GetHomePosition());
		}
			
	}
	else if (GetPerpendicularIntersection(ball_.GetPosition(), ball_.GetVirtualStationaryPosition(), pPlayer->GetPosition(), perIntersection))
	{
		//try intersepting ball
		pPlayer->MoveForBall();
		pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerInterceptBall);
	}
	else
	{
		//interseption is not possible. move towards ball.
		pPlayer->MoveTo(pPlayer->GetHomePosition());
		
	}
}

void CCounterAttackerStrikerChaseBallState::Execute(CPlayer* pPlayer)
{

	//ball in range take possession
	float distanceFromBall = ball_.GetPosition().DistanceFrom(pPlayer->GetPosition());
	if (distanceFromBall < 0.5)
	{
		pPlayer->TakePossession();
		pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerTakePossession);
		return;
	}
	//lost possession
	else if (ball_.IsTheirTeamControlling() &&					//their player in control of ball
			 game_.GetClosestPlayer()->IsTheirTeamMember()		//their player is closest
			) // not our team member
	{
		//lost possession. bitch go home
		pPlayer->MoveTo(pPlayer->GetHomePosition());
		pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerIdle);
	}
	else if (ball_.GetSpeed() == 0)
	{
		pPlayer->MoveTo(ball_.GetStationaryPosition());
	}
}

void CCounterAttackerStrikerInterceptBallState::Execute(CPlayer *pPlayer)
{
	//ball in range take possession
	float distanceFromBall = ball_.GetPosition().DistanceFrom(pPlayer->GetPosition());
	if (distanceFromBall < 0.5)
	{
		pPlayer->TakePossession();
		pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerTakePossession);
		return;
	}
	else if (ball_.IsTheirTeamControlling() &&					//their player in control of ball
			 game_.GetClosestPlayer()->IsTheirTeamMember()		//their player is closest
			) // not our team member
	{
		//lost possession. bitch go home
		pPlayer->MoveTo(pPlayer->GetHomePosition());
		pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerIdle);
	}
}

void CCounterAttackerStrikerTakePossessionState::Execute(CPlayer* pPlayer)
{
	//ball in range take possession
	if (ball_.GetOwner() == pPlayer->GetNumber())
	{
		// Note: need to wait and kick
		// For testing - kick towards centre (clearance)
		float distanceFromGoal = ball_.GetPosition().DistanceFrom(pitch_.GetTheirGoalCentre());
		if (distanceFromGoal > 20.0)
		{
			pPlayer->KickShort();
			pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerShortKick);
		}
		else
		{
			int randVal = RandomRangeInteger(0,1);
			float randShootYDiff = RandomRangeFloat(3.7, 3.9);
			
			Position shootAt = pitch_.GetTheirGoalCentre();
			shootAt.y_ += (randVal - 1)*randShootYDiff;
			
			pPlayer->Kick(shootAt, 100.0);
			pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerIdle);
		}
		//pPlayer->MoveTo({ 8.0f, 25.0 });
		
	}
	else if (ball_.GetPosition().DistanceFrom(pPlayer->GetPosition()) < 0.5)
	{
		pPlayer->TakePossession();
		//pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerTakePossession);
	}
	//lost possession
	else if (ball_.IsTheirTeamControlling() &&					//their player in control of ball
			 game_.GetClosestPlayer()->IsTheirTeamMember()		//their player is closest
			) // not our team member
	{
		//lost possession. bitch go home
		pPlayer->MoveTo(pPlayer->GetHomePosition());
		pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerIdle);
	}
}

void CCounterAttackerStrikerShortKickState::Execute(CPlayer* pPlayer)
{
	float distanceFromBall = ball_.GetPosition().DistanceFrom(pPlayer->GetPosition());
	
	if (ball_.GetOwner() == pPlayer->GetNumber())
	{
		
		// Note: need to wait and kick
		// For testing - kick towards centre (clearance)
		float distanceFromGoal = ball_.GetPosition().DistanceFrom(pitch_.GetTheirGoalCentre());
		if (distanceFromGoal > 20.0)
		{
			pPlayer->KickShort();
			pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerShortKick);
		}
		else
		{
			pPlayer->Kick(pitch_.GetTheirGoalY1(), 100.0);
			pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerIdle);
		}
		//pPlayer->MoveTo({ 8.0f, 25.0 });
		
	}
	else if (distanceFromBall < 0.5)
	{
		pPlayer->TakePossession();
		//pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerShortKick);
		return;
	}
	else if (ball_.IsFreeBall())	// no owner
	{
		pPlayer->MoveTo(ball_.GetStationaryPosition());
	}
	//lost possession
	else if (ball_.IsTheirTeamControlling() &&					//their player in control of ball
			 game_.GetClosestPlayer()->IsTheirTeamMember()		//their player is closest
			) // not our team member
	{
		//lost possession. bitch go home
		pPlayer->MoveTo(pPlayer->GetHomePosition());
		pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerIdle);
	}
}

