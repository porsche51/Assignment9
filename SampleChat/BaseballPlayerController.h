// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseballPlayerController.generated.h"

enum class EGameResult : uint8;
/**
 * 
 */
UCLASS()
class SAMPLECHAT_API ABaseballPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ABaseballPlayerController();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void BeginPlay() override;
	
	/**
	 * @brief 서버에서 호출하면 해당 클라이언트에서 실행되는 함수.
	 *        (클라이언트에서 직접 호출해도 실행되지 않다고 한다. 아직 클라에서 호출하는 테스트는 안해봤다.)
	 * @param Result 게임 결과 (승/패/무)
	 * @param CurrentTurnID 현재 턴을 진행한 플레이어의 ID
	 */
	UFUNCTION(Client, Reliable)
	void ClientReceiveResult(EGameResult Result, const FString& CurrentTurnID);

	/**
	 * @brief 위젯에서 결과 텍스트를 업데이트하는 함수 (블루프린트에서 구현)
	 * @param Message 표시할 메시지
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void SetResultText(const FText& Message);
	
	/**
	 * @brief 플레이어의 고유 ID (클라이언트마다 다름).
	 *        Replicated가 없으면 클라이언트에서 값이 동기화되지 않아 Empty로 나올 수 있음.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category="Baseball")
	FString MyUserID;
};
