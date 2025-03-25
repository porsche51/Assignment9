// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseballGameModeBase.h"
#include "GameFramework/GameStateBase.h"
#include "BaseballGameStateBase.generated.h"

enum class EGameResult : uint8;

USTRUCT(BlueprintType)
struct FBaseballGameResult
{
	GENERATED_BODY()

	/** @brief 기본 생성자 */
	FBaseballGameResult();
	
	/** 
	 * @brief 게임 결과를 설정하는 생성자 
	 * @param GameResult 게임의 결과 (승리, 패배 등)
	 * @param CurrentTurnPlayerID 현재 턴을 진행한 플레이어의 ID
	 */
	FBaseballGameResult(EGameResult GameResult, const FString& CurrentTurnPlayerID);

	/** 게임 결과 (승리, 패배 등) */
	EGameResult Result;
	
	/** 현재 턴을 진행한 플레이어의 ID */
	FString CurrentTurnID;
};

UCLASS()
class SAMPLECHAT_API ABaseballGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	/** @brief 기본 생성자 */
	ABaseballGameStateBase();
	
	/**
	 * @brief 서버에서 게임 결과를 받아서 저장하는 함수
	 * @param NewResult 새로운 게임 결과 (승리, 패배 등)
	 * @param NewCurrentTurnID 해당 턴을 진행한 플레이어의 ID
	 * @note 이 함수는 서버에서 실행되며, 클라이언트에서는 이 함수를 서버에 요청할 수 있다고 함. (요청하면 실행은 서버에서)
	 */
	UFUNCTION(Server, Reliable)
	void ServerReceiveResult(EGameResult NewResult, const FString& NewCurrentTurnID);
	
	/** 현재 게임의 결과를 저장하는 구조체 */
	FBaseballGameResult GameResult;
};