#include "stdafx.h"
#include "CounterAttackerDefenderState.h"


void CCounterAttackerDefenderIdleState::Execute(CPlayer* pPlayer)
{
	
	pPlayer->MoveToMarkedPlayer_Mark();
	pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderMark);
	
	
}

void CCounterAttackerDefenderGoHomeState::Execute(CPlayer* pPlayer)
{
	if (pPlayer->GetPosition().ApproxEqual(pPlayer->GetHomePosition(), POSITION_TOLERANCE))
	{

	}
}

void CCounterAttackerDefenderDefendState::Execute(CPlayer* pPlayer)
{
	
}

void CCounterAttackerDefenderChaseBallState::Execute(CPlayer *pPlayer)
{
	//ball in range take possession
	float distanceFromBall = ball_.GetPosition().DistanceFrom(pPlayer->GetPosition());
	if (distanceFromBall < 0.5)
	{
		if (!ball_.IsOurTeamControlling())
		{
			pPlayer->TakePossession();
			pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderTakePossession);
			
		}
		else
		{
			pPlayer->MoveToMarkedPlayer_Mark();
			pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderMark);
		}
		return;
	}
	else if (ball_.IsFreeBall())	// no owner
	{
		auto& pClosestPlayer = game_.GetClosestPlayer();
		auto& theirTeamPtr = game_.GetTheirTeamPtr();
		
		if (pClosestPlayer->IsTheirTeamMember())
		{
			pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderMark);
		}
		else if (pClosestPlayer->GetNumber() != pPlayer->GetNumber())
		{
			pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderMark);
		}
	}
	else if (ball_.IsTheirTeamControlling()) // not our team member
	{
		//possession is not with our team..hell! go run.. gaurd goal.
		//pPlayer->MoveToGuardGoal();
		pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderMark);
	}

}

void CCounterAttackerDefenderTakePossessionState::Execute(CPlayer* pPlayer)
{
	//ball in range take possession
	if (pPlayer->HasBall())
	{
		// Note: need to wait and kick
		// For testing - kick towards centre (clearance)
		if (!pPlayer->IsTheirPlayerNearMe() && 
			!ApproxEqual(pPlayer->GetDirection(),90.0,DIRECTION_TOLERANCE))
		{
			
			pPlayer->TurnTo(90.0);
		}
		else
		{
			auto& pCentrePlayer = game_.GetOurTeamPtr()->GetPlayerFromPlayerType(CPlayer::eCentreDefender);
			
			pCentrePlayer->MoveForBall();
			pCentrePlayer->ChangeState(CPlayerState::eCounterAttackerStrikerIdle);
					
		
			pPlayer->Kick(pCentrePlayer->GetPosition(), 100.0);
		//pPlayer->MoveTo({ 8.0f, 25.0 });
			pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderMark);
		}
		return;
	}
	else if (ball_.GetPosition().DistanceFrom(pPlayer->GetPosition()) < 0.5)
	{
		if (!ball_.IsOurTeamControlling())
		{
			pPlayer->TakePossession();
			pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderTakePossession);
			
		}
		else
		{
			pPlayer->MoveToMarkedPlayer_Mark();
			pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderMark);
		}
		return;
	}
	else if (ball_.IsTheirTeamControlling())
	{
		//pPlayer->MoveToGuardGoal();
		pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderMark);
	}
}


void CCounterAttackerDefenderGuardPassState::Execute(CPlayer *pPlayer)
{
	/*auto& pClosestBallPlayer = game_.GetClosestPlayer();
	auto& ourTeamPtr = game_.GetOurTeamPtr();
	float ourGoalDistanceFromBall = ball_.GetStationaryPosition().DistanceFrom(pitch_.GetOurGoalCentre());
	
	if (pPlayer->HasBall())
	{
		//my possession
		//change state
		pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderTakePossession);
	}
	else if (ball_.IsOurGoalKeeperControlling())
	{
		//change state
		//pPlayer->ChangeState(CPlayerState::e)
	}
	else if (ball_.IsOurTeamControlling())
	{
		//change state
	}
	else if (ball_.IsFreeBall() && pClosestBallPlayer->GetNumber() == pPlayer->GetNumber())
	{
		//change state
		pPlayer->MoveForBall();
		pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderChaseBall);
	}
	else if (ball_.IsFreeBall() && ourTeamPtr->IsMember(pClosestBallPlayer->GetNumber()))
	{
		//change state
	}
	else if (ourGoalDistanceFromBall < 40.0)
	{
		//change state to GuardPass
		pPlayer->MoveToMarkedPlayer_Mark();
		pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderMark);
		
	}
	else
	{
		pPlayer->MoveToMarkedPlayer_GuardPass();
	}*/
}

void CCounterAttackerDefenderMarkState::Execute(CPlayer *pPlayer)
{
	//Note: reset of marking should happen in here on change of state
	auto& pClosestBallPlayer = game_.GetClosestPlayer();
	auto& ourTeamPtr = game_.GetOurTeamPtr();
	float ourGoalDistanceFromBall = ball_.GetStationaryPosition().DistanceFrom(pitch_.GetOurGoalCentre());
	
	Position perIntersection;
	
	if (ball_.GetPosition().DistanceFrom(pPlayer->GetPosition()) < 0.5)
	{
		//my possession
		//change state
		if (!ball_.IsOurTeamControlling())
		{
			pPlayer->TakePossession();
			pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderTakePossession);
		}
		else
		{
			pPlayer->MoveToMarkedPlayer_Mark();
		}
	}
	/*else if (ball_.IsOurGoalKeeperControlling())
	{
		//change state
		//pPlayer->ChangeState(CPlayerState::e)
	}
	else if (ball_.IsOurTeamControlling())
	{
		//change state
	}
	*/else if (ball_.IsFreeBall() && pClosestBallPlayer->GetNumber() == pPlayer->GetNumber())
	{
		//change state
		pPlayer->MoveTo(ball_.GetStationaryPosition());
		pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderChaseBall);
	}
	else if (GetPerpendicularIntersection(ball_.GetPosition(), ball_.GetVirtualStationaryPosition(), pPlayer->GetPosition(), perIntersection))
	{
		pPlayer->MoveForBall();
		pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderChaseBall);
	}
	else if (pPlayer->GetMarkedPlayerNumber() != CPlayer::eNotMarking)
	{
		auto& pMarkedPlayer = game_.GetPlayer(pPlayer->GetMarkedPlayerNumber());
		
		float distanceMarkedPlayerToBall = ball_.GetStationaryPosition().DistanceFrom(pMarkedPlayer->GetPosition());
		
		if (distanceMarkedPlayerToBall > MAX_DISTANCE_MARK_TO_GAURD_PASS)
		{
			pPlayer->MoveToMarkedPlayer_GuardPass();
		}
		else
		{
			pPlayer->MoveToMarkedPlayer_Mark();
		}
	}
	else
	{
		pPlayer->MoveToMarkedPlayer_Mark();
	}
}