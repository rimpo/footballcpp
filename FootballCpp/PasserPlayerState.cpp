#include "stdafx.h"
#include "PasserPlayerState.h"


void CPasserDefenderIdleState::Execute(CPlayer* pPlayer)
{
		//ball in range take possession
	float distanceFromBall = ball_.GetPosition().DistanceFrom(pPlayer->GetPosition());
	CPlayer::Ptr pOurClosestPlayer = GetGame().GetOurClosestPlayer();
	
	auto& action = pPlayer->GetAction(); 
	
	Position perIntersection;
	
	if (pPlayer->HasBall())
	{
		pPlayer->Pass();
	}
	else if (distanceFromBall < 0.5)
	{
		pPlayer->TakePossession();
	}
	else if (GetPerpendicularIntersection(ball_.GetPosition(), ball_.GetVirtualStationaryPosition(), pPlayer->GetPosition(), perIntersection) &&
			pPlayer->IsInterceptionValid(perIntersection))
	{
		pPlayer->MoveForBall();
	}
	else if (pOurClosestPlayer && 
			 pOurClosestPlayer->GetNumber() == pPlayer->GetNumber() &&
			 action.type_ != CAction::eKick)
	{
		pPlayer->MoveTo(ball_.GetStationaryPosition());
	}
	else if(ball_.IsOurTeamControlling())
	{
		if (pPlayer->GetPosition().ApproxEqual(pPlayer->GetHomePosition(),POSITION_BIG_TOLERANCE))
		{
			pPlayer->SetHomePosition( { RandomRangeFloat(15.0, 40.0), pPlayer->GetHomePosition().y_});
		}
		
		pPlayer->MoveTo(pPlayer->GetHomePosition());
	}
	else
	{
		pPlayer->MoveTo(pPlayer->GetHomePosition());
	}
	
}


void CPasserMidfielderIdleState::Execute(CPlayer* pPlayer)
{
	float distanceFromBall = ball_.GetPosition().DistanceFrom(pPlayer->GetPosition());
	
	CPlayer::Ptr pClosestPlayer = GetGame().GetClosestPlayer();
	
	auto& action = pPlayer->GetAction(); 
	
	Position perIntersection;
	
	if (pPlayer->HasBall())
	{
		pPlayer->Pass();
	}
	else if (distanceFromBall < 0.5)
	{
		pPlayer->TakePossession();
	}
	else if (GetPerpendicularIntersection(ball_.GetPosition(), ball_.GetVirtualStationaryPosition(), pPlayer->GetPosition(), perIntersection) &&
			pPlayer->IsInterceptionValid(perIntersection))
	{
		pPlayer->MoveForBall();
	}
	else if (pClosestPlayer && 
			 pClosestPlayer->GetNumber() == pPlayer->GetNumber() &&
			 action.type_ != CAction::eKick)
	{
		pPlayer->MoveTo(ball_.GetStationaryPosition());
	}
	else if(ball_.IsOurTeamControlling()) 
	{
		if (pPlayer->GetPosition().ApproxEqual(pPlayer->GetHomePosition(),POSITION_BIG_TOLERANCE))
		{
			pPlayer->SetHomePosition( { pPlayer->GetHomePosition().x_, RandomRangeFloat(5.0, 45.0)});
		}
		pPlayer->MoveTo(pPlayer->GetHomePosition());
	}
	else
	{
		pPlayer->MoveTo(pPlayer->GetHomePosition());
	}
}

void CPasserStrikerIdleState::Execute(CPlayer* pPlayer)
{
	float distanceFromBall = ball_.GetPosition().DistanceFrom(pPlayer->GetPosition());
	CPlayer::Ptr pClosestPlayer = GetGame().GetClosestPlayer();
	
	auto& action = pPlayer->GetAction(); 
	
	Position perIntersection;
	
	if (pPlayer->HasBall())
	{
		if (pPlayer->GetPosition().x_ > 83.0f)
		{
			float direction = pPlayer->GetPosition().AngleWith(pitch_.GetTheirGoalCentre());
			if(!pPlayer->IsTheirPlayerNear(2.0f) &&
				!ApproxEqual(direction,pPlayer->GetDirection(),0.1f))
			{
				pPlayer->TurnTo(direction);
			}
			else
				pPlayer->Kick(pitch_.GetTheirGoalCentre(), 100.0f);
			
		}
		else
		{
			pPlayer->KickShort(40.0);
		}
	}
	else if (distanceFromBall < 0.5)
	{
		pPlayer->TakePossession();
	}
	else if (GetPerpendicularIntersection(ball_.GetPosition(), ball_.GetVirtualStationaryPosition(), pPlayer->GetPosition(), perIntersection) &&
			pPlayer->IsInterceptionValid(perIntersection))
	{
		pPlayer->MoveForBall();
	}
	else if (pClosestPlayer && 
			 pClosestPlayer->GetNumber() == pPlayer->GetNumber() &&
			 action.type_ != CAction::eKick)
	{
		pPlayer->MoveTo(ball_.GetStationaryPosition());
	}
	else if(ball_.IsOurTeamControlling()) 
	{
		if (pPlayer->GetPosition().ApproxEqual(pPlayer->GetHomePosition(),POSITION_BIG_TOLERANCE))
		{
			pPlayer->SetHomePosition( { pPlayer->GetHomePosition().x_, RandomRangeFloat(15.0, 35.0)});
		}
		
		pPlayer->MoveTo(pPlayer->GetHomePosition());
	}
	else
	{
		pPlayer->MoveTo(pPlayer->GetHomePosition());
	}
}
