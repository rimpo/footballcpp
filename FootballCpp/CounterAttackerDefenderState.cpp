#include "stdafx.h"
#include "CounterAttackerDefenderState.h"


void CCounterAttackerIdleState::Execute(CPlayer* pPlayer)
{
	if (ball_.IsTheirTeamControlling())
	{
		//pPlayer->MoveTo(pPlayer->GetHomePosition());
		pPlayer->ChangeState(CPlayerState::eCounterAttackerDefend);
	}
}

void CCounterAttackerGoHomeState::Execute(CPlayer* pPlayer)
{
	if (pPlayer->GetPosition().ApproxEqual(pPlayer->GetHomePosition(), POSITION_TOLERANCE))
	{

	}
}

void CCounterAttackerDefendState::Execute(CPlayer* pPlayer)
{
	if (pPlayer->GetNumber() == game_.GetClosestPlayer()->GetNumber())
	{
		if (ball_.GetStationaryPosition().x_ < 28.0)
		{
			pPlayer->MoveTo(ball_.GetStationaryPosition());
			pPlayer->ChangeState(CPlayerState::eCounterAttackerChaseBall);
			return;
		}
	}

	Position pos;
	float dist= 0.0;
	
	switch (pPlayer->GetType())
	{
		case CPlayer::eLeftDefender:
		{
			pos = pitch_.GetOurGoalCentre();
			dist = 30.0;
		}
		break;
		case CPlayer::eRightDefender:
		{
			pos = pitch_.GetOurGoalCentre();
			dist = 28.0;
		}
		break;
	}
	
	Vector vec = pos.VectorTo(ball_.GetPosition());

	Vector vecScaled = vec.Scale(dist);

	pos.AddVector(vecScaled);
	
	if (pos.ApproxEqual(pPlayer->GetPosition(), POSITION_BIG_TOLERANCE))
	{
		pPlayer->TurnTo(270.0);
	}
	else
	{
		pPlayer->MoveTo(pos);
	}
}

void CCounterAttackerChaseBallState::Execute(CPlayer *pPlayer)
{
	//ball in range take possession
	float distanceFromBall = ball_.GetPosition().DistanceFrom(pPlayer->GetPosition());
	if (distanceFromBall < 0.5)
	{
		pPlayer->TakePossession();
		pPlayer->ChangeState(CPlayerState::eCounterAttackerTakePossession);
		return;
	}
	else if (!ball_.HasOwner())	// no owner
	{
		if (ball_.GetStationaryPosition().x_ < 28.0)
		{
			pPlayer->MoveTo(ball_.GetStationaryPosition());
			//pPlayer->ChangeState(CPlayerState::eCounterAttackerChaseBall);
		}
		else
			pPlayer->ChangeState(CPlayerState::eCounterAttackerDefend);
	}
	else if (ball_.IsTheirTeamControlling()) // not our team member
	{
		//possession is not with our team..hell! go run.. gaurd goal.
		//pPlayer->MoveToGuardGoal();
		pPlayer->ChangeState(CPlayerState::eCounterAttackerDefend);
	}

}

void CCounterAttackerTakePossessionState::Execute(CPlayer* pPlayer)
{
	//ball in range take possession
	if (ball_.GetOwner() == pPlayer->GetNumber())
	{
		// Note: need to wait and kick
		// For testing - kick towards centre (clearance)
		pPlayer->Kick(pitch_.GetOurGoalCentre(), 100.0);
		//pPlayer->MoveTo({ 8.0f, 25.0 });
		pPlayer->ChangeState(CPlayerState::eCounterAttackerDefend);
		return;
	}
	else if (ball_.GetPosition().DistanceFrom(pPlayer->GetPosition()) < 0.5)
	{
		pPlayer->TakePossession();
		pPlayer->ChangeState(CPlayerState::eCounterAttackerTakePossession);
		return;
	}
	else if (ball_.IsTheirTeamControlling())
	{
		//pPlayer->MoveToGuardGoal();
		pPlayer->ChangeState(CPlayerState::eCounterAttackerDefend);
	}
}