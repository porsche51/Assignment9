// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseballGameModeBase.generated.h"

class ABaseballPlayerController;

UENUM(BlueprintType)
enum class EGameResult : uint8
{
	None UMETA(DisplayName = "None"), // 기본 상태 (라운드가 다 끝났는데 None이면 무승부)
	ThreeStrike UMETA(DisplayName = "ThreeStrike"), // 이김
	Out UMETA(DisplayName = "Out"), // 짐
};

UCLASS()
class SAMPLECHAT_API ABaseballGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABaseballGameModeBase();

	virtual void BeginPlay() override;
	
	/**
	 * @brief 플레이어가 숫자를 제출하면 정답과 비교하여 결과를 처리하는 함수.
	 * @param UserID 제출한 플레이어의 ID
	 * @param Num 플레이어가 제출한 숫자 (문자열 형식)
	 * 예외처리가 아직 부족함. 3개 이상으로 받거나 숫자가 아니여도 딱히 검증하지 않음.
	 */
	UFUNCTION(BlueprintCallable)
	void TryAnswer(FString UserID, FString Num);

	/**
	 * @brief 게임을 시작하는 함수.
	 *        초기화 작업을 수행하고 첫 번째 라운드를 시작함.
	 */
	UFUNCTION(BlueprintCallable)
	void StartGame();

	/**
	 * @brief 게임을 종료하는 함수.
	 *        최종 결과를 정리하고 모든 플레이어의 상태를 업데이트함.
	 */
	UFUNCTION(BlueprintCallable)
	void EndGame();
	
	/**
	 * @brief 새로운 라운드를 시작하는 함수.
	 *        최대 라운드 수를 초과하면 게임이 종료됨.
	 */
	UFUNCTION(BlueprintCallable)
	void StartRound();
	
	/**
	 * @brief 새로운 턴을 시작하는 함수.
	 *        현재 턴의 플레이어를 결정하고 진행을 알림.
	 */
	UFUNCTION(BlueprintCallable)
	void StartTurn();
	
	/**
	 * @brief 현재 턴을 종료하는 함수.
	 *        결과를 저장하고 다음 턴을 준비함.
	 */
	UFUNCTION(BlueprintCallable)
	void EndTurn();

	/**
	 * @brief 현재 게임에 참여 중인 모든 플레이어의 ID를 가져오는 함수.
	 *        블루프린트에서 구현해야 함.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category="Baseball")
	void GetALLUserIDs();
protected:
	
	/** 현재 진행 중인 라운드 번호 */
	UPROPERTY(EditDefaultsOnly, Category="Baseball")
	int CurrentRound = 0;

	/** 게임의 최대 라운드 수 */
	UPROPERTY(EditDefaultsOnly, Category="Baseball")
	int MaxRound = 3;

	/** 현재 게임에 참여한 모든 플레이어의 컨트롤러 목록 */
	UPROPERTY(BlueprintReadWrite, Category="Baseball")
	TArray<ABaseballPlayerController*> JoinedUserControllers;

	/** 현재 턴을 진행 중인 플레이어의 인덱스 */
	int32 UserIDIndex = 0;
	
	/** 현재 턴을 진행 중인 플레이어의 ID */
	UPROPERTY()
	FString CurrentTurnPlayerID;

	/** 현재 게임의 결과 (승리, 패배, 무승부) */
	EGameResult GameResult;
	
	/** 게임 정답 (숫자, 위치 매핑) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int, int> Answer;
};
