// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BaseballBlueprintFunctionLibrary.generated.h"

/**
 * @brief 야구 게임에서 사용할 유틸리티 함수를 제공하는 블루프린트 함수 라이브러리
 */
UCLASS()
class SAMPLECHAT_API UBaseballBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
		
	/**
	 * @brief 1부터 9까지의 숫자 중 무작위로 3개의 숫자를 선택하여 반환.
	 * 
	 * @return 키가 숫자이고 값이 위치인 TMap<int32, int32> 형태의 난수 맵
	 */
	UFUNCTION(BlueprintCallable, Category="Baseball")
	static TMap<int32, int32> GetRandomNumbers();

	/**
	 * @brief 플레이어가 입력한 답안과 정답을 비교하여 스트라이크와 볼 개수를 계산.
	 * 아직 예외처리가 부족함. 숫자 3개를 받았는지 확인하거나, 숫자대신 문자가 들어가는 등의 예외처리가 필요
	 * 
 	 * @param SecretNumbers 정답으로 설정된 숫자 목록 (키: 숫자, 값: 위치)
	 * @param PlayerGuess 플레이어가 입력한 3자리 숫자 문자열
	 * @param Strike 스트라이크 개수 (정확한 숫자+위치 일치)
	 * @param Ball 볼 개수 (숫자는 맞지만 위치 불일치)
	 */
	UFUNCTION(BlueprintCallable, Category="Baseball")
	static void CheckAnswer(const TMap<int32, int32>& SecretNumbers, const FString& PlayerGuess, int32& Strike, int32& Ball);
};
