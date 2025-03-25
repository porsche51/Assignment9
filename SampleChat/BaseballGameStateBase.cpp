// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseballGameStateBase.h"

#include "BaseballGameModeBase.h"
#include "BaseballPlayerController.h"

FBaseballGameResult::FBaseballGameResult()
{
}

FBaseballGameResult::FBaseballGameResult(EGameResult GameResult, const FString& CurrentTurnPlayerID)
	:Result(GameResult), CurrentTurnID(CurrentTurnPlayerID)
{
}

ABaseballGameStateBase::ABaseballGameStateBase()
{
}

void ABaseballGameStateBase::ServerReceiveResult_Implementation(EGameResult NewResult, const FString& NewCurrentTurnID)
{
	if (!HasAuthority()) return;
	
	GameResult = FBaseballGameResult(NewResult, NewCurrentTurnID);

	//모든 컨트롤러를 가져와서 게임 결과를 보내줌.
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		ABaseballPlayerController* BPC = Cast<ABaseballPlayerController>(*Iterator);
		if (BPC)
		{
			// ClientReceiveResult 함수는 Client, Reliable이다.
			// 의도는 서버에서 이 함수를 호출해 각 클라이언트에서 ClientReceiveResult가 호출하는 것.
			BPC->ClientReceiveResult(GameResult.Result, GameResult.CurrentTurnID);
		}
	}
}