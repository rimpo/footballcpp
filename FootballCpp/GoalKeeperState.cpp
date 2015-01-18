#include "stdafx.h"
#include "GoalkeeperState.h"


void CGoalKeeperGuardState::Execute(CPlayer *pPlayer)
{
	Position hittingAt;			//hitting on goal line

	if (ball_.GetSpeed() == 0 && pitch_.IsInsideOurGoalArea(ball_.GetPosition()))
	{
		pPlayer->MoveTo(ball_.GetPosition());
		pPlayer->ChangeState(CPlayerState::eGoalKeeperChaseBall);
	}
	else if (pitch_.IsLineHittingOurGoal(ball_.GetPosition(), ball_.GetStationaryPosition(), hittingAt))
	{
		pPlayer->MoveToSaveGoal_GoalKeeper(hittingAt);
		pPlayer->ChangeState(CPlayerState::eGoalKeeperInterceptBall);
		game_.noOfGoalAttempts++;
	}
	else
	{
		pPlayer->MoveToGuardGoal();
	}

}
void CGoalKeeperInterceptBallState::Execute(CPlayer* pPlayer)
{
	//ball in range take possession
	float distanceFromBall = ball_.GetPosition().DistanceFrom(pPlayer->GetPosition());
	
	
	if (distanceFromBall < 0.5)
	{
		pPlayer->TakePossession();
		pPlayer->ChangeState(CPlayerState::eGoalKeeperTakePossession);
		return;
	}
	else if (ball_.IsTheirTeamControlling()) // not our team member
	{
		//possession is not with our team..hell! go run.. gaurd goal.
		pPlayer->MoveToGuardGoal();
		pPlayer->ChangeState(CPlayerState::eGoalKeeperGuard);
	}
	else
	{
		//continue intercepting goal
	}
	
}

void CGoalKeeperTakePossessionState::Execute(CPlayer* pPlayer)
{
	//ball in range take possession
	if (ball_.GetOwner() == pPlayer->GetNumber())
	{
		// Note: need to wait and kick
		// For testing - kick towards centre (clearance)
		//pPlayer->Kick(pitch_.GetCentreSpot(), 100.0);
		pPlayer->MoveTo({ 8.0f, 25.0 });
		pPlayer->ChangeState(CPlayerState::eGoalKeeperKickBall);
	}
	else if (ball_.GetPosition().DistanceFrom(pPlayer->GetPosition()) < 0.5)
	{
		pPlayer->TakePossession();
		pPlayer->ChangeState(CPlayerState::eGoalKeeperTakePossession);
	}
	else
	{
		pPlayer->MoveToGuardGoal();
		pPlayer->ChangeState(CPlayerState::eGoalKeeperGuard);
	}
}
void CGoalKeeperChaseBallState::Execute(CPlayer *pPlayer)
{
	//interecpt chase same for now
	CPlayerState::GlobalPlayerState(CPlayerState::eGoalKeeperInterceptBall)->Execute(pPlayer);
}

void CGoalKeeperIdleState::Execute(CPlayer *pPlayer)
{
	
}

void CGoalKeeperKickBallState::Execute(CPlayer *pPlayer)
{
	if (ball_.GetOwner() == pPlayer->GetNumber())
	{
		if (pPlayer->GetPosition().ApproxEqual({ 8.0f, 25.0 }, POSITION_TOLERANCE))
		{
			pPlayer->Kick({ 25.0,50.0 },100.0);
		}
	}
	else
	{
		pPlayer->MoveToGuardGoal();
		pPlayer->ChangeState(CPlayerState::eGoalKeeperGuard);
	}
}
