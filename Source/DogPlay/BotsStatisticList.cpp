// Fill out your copyright notice in the Description page of Project Settings.


#include "BotsStatisticList.h"
#include "BotStatistic.h"

void UBotsStatisticList::SortChildWidgets(const bool bIsAscending)
{
	Algo::Sort(BotsStatistics, [bIsAscending](const UBotStatistic* A, const UBotStatistic* B)
	{
		if(IsValid(A) && IsValid(B))
		{
			if(bIsAscending)
			{
				return A->GetBotPoints() <= B->GetBotPoints();
			}
			else
			{
				return A->GetBotPoints() >= B->GetBotPoints();
			}
		}

		return false;
	});
	
}
