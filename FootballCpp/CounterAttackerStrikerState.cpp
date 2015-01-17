#include "stdafx.h"
#include "CounterAttackerStrikerState.h"


void CCounterAttackerStrikerIdleState::Execute(CPlayer* pPlayer)
{
	if (ball_.IsFreeBall())
	{
		pPlayer->MoveTo(ball_.GetPosition());
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
	else if (ball_.IsFreeBall())	// no owner
	{
		
	}
	else if (ball_.IsTheirTeamControlling()) // not our team member
	{
		//possession is not with our team..hell! go run.. gaurd goal.
		//pPlayer->MoveToGuardGoal();
		pPlayer->MoveTo(ball_.GetPosition());
		//pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderDefend);
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
				pPlayer->Kick(pitch_.GetTheirGoalCentre(), 40.0);
				//pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerShortKick);
		}
		else
		{
			pPlayer->Kick(pitch_.GetTheirGoalY1(), 100.0);
		}
		//pPlayer->MoveTo({ 8.0f, 25.0 });
		pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerChaseBall);
	}
	else if (ball_.GetPosition().DistanceFrom(pPlayer->GetPosition()) < 0.5)
	{
		pPlayer->TakePossession();
		pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderTakePossession);
	}
	else if (ball_.IsTheirTeamControlling())
	{
		pPlayer->MoveTo(ball_.GetPosition());
		pPlayer->ChangeState(CPlayerState::eCounterAttackerStrikerChaseBall);
	}
}

void CCounterAttackerStrikerShortKickState::Execute(CPlayer* pPlayer)
{
	
}

