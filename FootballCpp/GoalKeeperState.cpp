#include "stdafx.h"
#include "GoalkeeperState.h"


void CGoalKeeperGuardState::Execute(CPlayer *pPlayer)
{
	
	Position intersection, ballStationary;

	//float timeTaken = 0.0;

	if (ball_.GetSpeed() == 0)
	{
		if (pitch_.IsInsideOurGoalArea(ball_.GetPosition()))
		{
			//ball is inside our D.
			//go get the ball
			pPlayer->MoveTo(ball_.GetPosition());
			pPlayer->ChangeState(CPlayerState::eGoalKeeperChaseBall);
		}
		else
		{
			pPlayer->MoveToGuardGoal();
			//No state change as state remains the same
		}
	}
	else //ball is moving
	{
		////calculate position where ball will be stationary
		//ball_.CalculateStationaryPos(timeTaken);

		Position hittingAt;			//hitting on goal line

		if (pitch_.IsLineHittingOurGoal(ball_.GetPosition(), ball_.GetStationaryPosition(), hittingAt))
		{
			// try catching ball.
			pPlayer->MoveToSaveGoal_GoalKeeper(hittingAt);
			
			pPlayer->ChangeState(CPlayerState::eGoalKeeperInterceptBall);

			game_.noOfGoalAttempts++;
		}
		else // ball is not hitting goal
		{
			pPlayer->MoveToGuardGoal();
			// For now - No state change as state remains the same
		}
	} //else  - ball moving

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
	else if (ball_.IsFreeBall())
	{
		// no one owns the ball - continue intercepting
	}
	else if (ball_.IsTheirTeamControlling()) // not our team member
	{
		//possession is not with our team..hell! go run.. gaurd goal.
		pPlayer->MoveToGuardGoal();
		pPlayer->ChangeState(CPlayerState::eGoalKeeperGuard);
	}

	//continue intercepting goal
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
		return;
	}
	else if (ball_.GetPosition().DistanceFrom(pPlayer->GetPosition()) < 0.5)
	{
		pPlayer->TakePossession();
		pPlayer->ChangeState(CPlayerState::eGoalKeeperTakePossession);
		return;
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
