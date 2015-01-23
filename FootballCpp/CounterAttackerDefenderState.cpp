#include "stdafx.h"
#include "CounterAttackerDefenderState.h"


void CCounterAttackerDefenderIdleState::Execute(CPlayer* pPlayer)
{
	auto& pClosestToBallPlayer = game_.GetClosestPlayer();
	auto& theirTeamPtr = game_.GetTheirTeamPtr();
	auto& theirTeamSortedX = game_.GetTheirTeamSortedX();
	
	float distanceBallFromOurGoal = ball_.GetPosition().DistanceFrom(pitch_.GetOurGoalCentre());
	
	CPlayer::Ptr pBallPlayer;
	
	pPlayer->MoveToMarkedPlayer_Mark();
	pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderMark);
	
	/*if (theirTeamSortedX[1]->GetPosition().y_ < 25.0)
	{
		pPlayer->SetMarkedPlayerNumber(theirTeamSortedX[1]->GetNumber());
		pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderMark);
	}
	else
	{
		pPlayer->SetMarkedPlayerNumber(theirTeamSortedX[1]->GetNumber());
		pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderMark);
	}
	
	//their player controlling ball
	if (ball_.IsTheirTeamControlling())
	{
		pBallPlayer = game_.GetPlayer(ball_.GetOwner());
	}
	//their player close to free dead ball.	
	if (ball_.GetSpeed() == 0 && ball_.IsFreeBall() && theirTeamPtr->IsMember(pClosestToBallPlayer->GetNumber()))
	{
			pBallPlayer = pClosestToBallPlayer;
	}
	
	if (pBallPlayer)
	{
		
		if (pBallPlayer->GetNumber() == theirTeamSortedX[0]->GetNumber()
		{
			
		}
		
		else if (pBallPlayer->GetNumber() == theirTeamSortedX[1]->GetNumber())
		{
			//first/second player with/near ball.
			int supportingDefenderType = pPlayer->GetType() == CPlayer::eLeftDefender ? CPlayer::eRightDefender : CPlayer::eLeftDefender;
			auto& pSupportingPlayer = GetGame().GetOurTeamPtr()->GetPlayerFromPlayerType(supportingDefenderType);
			
			pPlayer->SetMarkedPlayerNumber(theirTeamSortedX[0]->GetNumber());
			pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderMark);

			pSupportingPlayer->SetMarkedPlayerNumber(theirTeamSortedX[1]->GetNumber());
			pSupportingPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderMark);
			
			//}
		}
		else if (distanceBallFromOurGoal > 40.0)
		{
			//third player (with/near ball) far from our goal.
			if (pPlayer->GetType() == CPlayer::eLeftDefender)
			{
				//pPlayer->MoveTo(guard pass pos);
				pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderGuardPass);
			}
			//guardpass to first and second player
		}
		else
		{
			// third player near our goal with/near ball.
		}
	}
	else
	{
		//our possession.(i think.)
	}
	*/


	/*if (ball_.IsTheirTeamControlling())
	{
		//pPlayer->MoveTo(pPlayer->GetHomePosition());
		pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderMark);
	}*/
}

void CCounterAttackerDefenderGoHomeState::Execute(CPlayer* pPlayer)
{
	if (pPlayer->GetPosition().ApproxEqual(pPlayer->GetHomePosition(), POSITION_TOLERANCE))
	{

	}
}

void CCounterAttackerDefenderDefendState::Execute(CPlayer* pPlayer)
{
	if (pPlayer->GetNumber() == game_.GetClosestPlayer()->GetNumber())
	{
		if (ball_.GetStationaryPosition().x_ < 28.0)
		{
			pPlayer->MoveTo(ball_.GetStationaryPosition());
			pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderChaseBall);
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

void CCounterAttackerDefenderChaseBallState::Execute(CPlayer *pPlayer)
{
	//ball in range take possession
	float distanceFromBall = ball_.GetPosition().DistanceFrom(pPlayer->GetPosition());
	if (distanceFromBall < 0.5)
	{
		pPlayer->TakePossession();
		pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderTakePossession);
		return;
	}
	else if (ball_.IsFreeBall())	// no owner
	{
		if (ball_.GetStationaryPosition().x_ < 28.0)
		{
			pPlayer->MoveTo(ball_.GetStationaryPosition());
			//pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderChaseBall);
		}
		else
			pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderMark);
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
	if (ball_.GetOwner() == pPlayer->GetNumber())
	{
		// Note: need to wait and kick
		// For testing - kick towards centre (clearance)
		pPlayer->Kick({50.0, 0.0}, 100.0);
		//pPlayer->MoveTo({ 8.0f, 25.0 });
		pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderMark);
		return;
	}
	else if (ball_.GetPosition().DistanceFrom(pPlayer->GetPosition()) < 0.5)
	{
		pPlayer->TakePossession();
		pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderTakePossession);
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
	auto& pClosestBallPlayer = game_.GetClosestPlayer();
	auto& ourTeamPtr = game_.GetOurTeamPtr();
	float ourGoalDistanceFromBall = ball_.GetStationaryPosition().DistanceFrom(pitch_.GetOurGoalCentre());
	
	if (ball_.GetOwner() == pPlayer->GetNumber())
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
	else if (pPlayer->GetMarkedPlayerNumber() == CPlayer::eNotMarking)
	{
		//identify close player to goal and guard pass to them
		
		auto& theirTeamSortedX = game_.GetTheirTeamSortedX();
		
		int supportingDefenderType = pPlayer->GetType() == CPlayer::eLeftDefender ? CPlayer::eRightDefender : CPlayer::eLeftDefender;
		auto& pSupportingPlayer = GetGame().GetOurTeamPtr()->GetPlayerFromPlayerType(supportingDefenderType);
			
		pPlayer->SetMarkedPlayerNumber(theirTeamSortedX[0]->GetNumber());
		pSupportingPlayer->SetMarkedPlayerNumber(theirTeamSortedX[1]->GetNumber());
		
		pPlayer->MoveToMarkedPlayer_GuardPass();
		pSupportingPlayer->MoveToMarkedPlayer_GuardPass();
		
		//remain in this state
	}
	else
	{
		pPlayer->MoveToMarkedPlayer_GuardPass();
	}
}

void CCounterAttackerDefenderMarkState::Execute(CPlayer *pPlayer)
{
	//Note: reset of marking should happen in here on change of state
	auto& pClosestBallPlayer = game_.GetClosestPlayer();
	auto& ourTeamPtr = game_.GetOurTeamPtr();
	float ourGoalDistanceFromBall = ball_.GetStationaryPosition().DistanceFrom(pitch_.GetOurGoalCentre());
	
	if (ball_.GetPosition().DistanceFrom(pPlayer->GetPosition()) < 0.5)
	{
		//my possession
		//change state
		pPlayer->TakePossession();
		pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderTakePossession);
	}
	
	/*else if (ball_.IsOurGoalKeeperControlling())
	{
		//change state
		//pPlayer->ChangeState(CPlayerState::e)
	}
	else if (ball_.IsOurTeamControlling())
	{
		//change state
	}else if (ball_.IsFreeBall() && pClosestBallPlayer->GetNumber() == pPlayer->GetNumber())
	{
		//change state
		pPlayer->MoveTo(ball_.GetStationaryPosition());
		pPlayer->ChangeState(CPlayerState::eCounterAttackerDefenderChaseBall);
	}*/
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