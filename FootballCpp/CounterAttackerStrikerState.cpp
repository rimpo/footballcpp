#include "stdafx.h"
#include "CounterAttackerStrikerState.h"


void CCounterAttackerStrikerIdleState::Execute(CPlayer* pPlayer)
{
	Position perIntersection;
	float distanceFromBall = ball_.GetPosition().DistanceFrom(pPlayer->GetPosition());
	if (distanceFromBall < 0.5)
	{
		pPlayer->TakePossession();
		pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerTakePossession);
		return;
	}
	else if (ball_.GetSpeed() == 0 && ball_.IsFreeBall())
	{
		if (ball_.GetPosition().x_ < 25.0)
		{
			pPlayer->MoveTo({50.0,25.0});
		}
		else
		{
			pPlayer->MoveTo(ball_.GetStationaryPosition());
			//pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerChaseBall);
		};
		
	}
	else if (GetPerpendicularIntersection(ball_.GetPosition(), ball_.GetVirtualStationaryPosition(), pPlayer->GetPosition(), perIntersection))
	{
		pPlayer->MoveForBall();
		pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerChaseBall);
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
	else if (ball_.IsFreeBall() && ball_.GetSpeed() == 0)	// no owner
	{
		if (ball_.GetPosition().x_ < 25.0)
		{
			pPlayer->MoveTo({50.0,25.0});
			pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerIdle);
			return;
		}
		
		/*auto& pClosestPlayer = game_.GetClosestPlayer();
		
		if(pClosestPlayer->GetNumber() != pPlayer->GetNumber())
		{
			pPlayer->MoveTo({50.0,25.0});
			pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerIdle);
		}*/
		pPlayer->MoveTo(ball_.GetPosition());
		//pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerIdle);
	}
	else if (ball_.IsTheirTeamControlling()) // not our team member
	{
		//possession is not with our team..hell! go run.. gaurd goal.
		//pPlayer->MoveToGuardGoal();
		pPlayer->MoveTo(ball_.GetPosition());
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
	else if (ball_.IsTheirTeamControlling())
	{
		pPlayer->MoveTo(ball_.GetPosition());
		pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerChaseBall);
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
	else if (ball_.IsTheirTeamControlling())
	{
		pPlayer->MoveTo({50.0,25.0});
		pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerIdle);
	}
}

