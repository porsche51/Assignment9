// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseballGameModeBase.h"

#include "BaseballBlueprintFunctionLibrary.h"
#include "BaseballGameStateBase.h"
#include "BaseballPlayerController.h"

class ABaseballGameStateBase;

ABaseballGameModeBase::ABaseballGameModeBase()
{
}

void ABaseballGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

// 같은 자리면 strike, 포함하면 ball
void ABaseballGameModeBase::TryAnswer(FString UserID, FString Num)
{
	if (UserID != CurrentTurnPlayerID)
	{
		FString Message = FString::Printf(TEXT("현재는 %s님의 턴입니다."), *CurrentTurnPlayerID);

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, Message);
		}
		return;
	}
	
	int Strike = 0;
	int Ball = 0;

	UBaseballBlueprintFunctionLibrary::CheckAnswer(Answer, Num, Strike, Ball); //답 검증

	if (Strike == 3) // 본인 승 (3 스트라이크)
	{
		GameResult = EGameResult::ThreeStrike;
	}
	else if (Strike == 0 && Ball == 0) // 상대 승 (3 아웃)
	{
		GameResult = EGameResult::Out;
	}
	else // Strike나 Ball이 하나라도 있음
	{
		GameResult = EGameResult::None;
	}
	
	EndTurn();
}

void ABaseballGameModeBase::StartGame() //게임 시작
{
	GetALLUserIDs(); // 모든 유저 id 가져와 저장. 블루프린트로 구현함. 

	Answer = UBaseballBlueprintFunctionLibrary::GetRandomNumbers(); // 랜덤 넘버 3개 뽑아서 Answer에 저장
	
	CurrentRound = 0;
	UserIDIndex = 0;
	GameResult = EGameResult::None;

	StartRound();
}

void ABaseballGameModeBase::EndGame()
{
	if (ABaseballGameStateBase* BGameState = GetGameState<ABaseballGameStateBase>())
	{
		BGameState->ServerReceiveResult(GameResult, CurrentTurnPlayerID);
	}
	
	StartGame();
}

void ABaseballGameModeBase::StartRound()
{
	if (CurrentRound >= MaxRound) // 최대 턴까지 도달했다면 종료
	{
		EndGame();
		return;
	}
	
	UserIDIndex = 0;
	CurrentRound += 1;

	FString RoundMessage = FString::Printf(TEXT("Round %d 시작"), CurrentRound);
	//UE_LOG(LogTemp, Display, TEXT("%s"), *RoundMessage);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, RoundMessage);
	}
	
	StartTurn();
}

void ABaseballGameModeBase::StartTurn()
{
	// 다음 플레이어의 턴 시작 (큐를 사용할까?)
	CurrentTurnPlayerID = JoinedUserControllers[UserIDIndex]->MyUserID;

	FString RoundMessage = FString::Printf(TEXT("%s님의 턴"), *CurrentTurnPlayerID);
	//UE_LOG(LogTemp, Display, TEXT("%s"), *RoundMessage);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, RoundMessage);
	}
}

void ABaseballGameModeBase::EndTurn()
{
	if (GameResult != EGameResult::None) // 결과가 나옴. 라운드 초과는 다른 곳에서 확이ㅣㄴ함.
	{
		EndGame();
		return;
	}

	// 모든 플레이어가 턴을 마쳤다면 다음 라운드로 이동
	if (UserIDIndex >= JoinedUserControllers.Num() - 1) 
	{
		StartRound();
	}
	else // 아직 턴이 남아있으면 다음 플레이어로 이동
	{
		++UserIDIndex;
		StartTurn();
	}
}
