// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseballPlayerController.h"
#include "BaseballGameModeBase.h"
#include "Net/UnrealNetwork.h"

ABaseballPlayerController::ABaseballPlayerController()
{
}

void ABaseballPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseballPlayerController, MyUserID);	
}

void ABaseballPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

// BaseballGameStateBase에서 호출되는 함수. 클라이언트만 실행되는 함수다.
void ABaseballPlayerController::ClientReceiveResult_Implementation(EGameResult Result, const FString& CurrentTurnID)
{
	FString Message = TEXT("오류가 있음");

	UE_LOG(LogTemp, Display, TEXT("ID %s"), *MyUserID);
		
	if (Result == EGameResult::None)
	{
		Message = TEXT("무승부입니다.");
	}
	else if (Result == EGameResult::ThreeStrike)
	{
		Message = (CurrentTurnID == MyUserID) ? TEXT("당신은 이겼습니다!") : TEXT("당신은 졌습니다...");
	}
	else if (Result == EGameResult::Out)
	{
		Message = (CurrentTurnID == MyUserID) ? TEXT("당신은 졌습니다...") : TEXT("당신은 이겼습니다!");
	}

	SetResultText(FText::FromString(Message)); // 위젯 텍스트 변경
}