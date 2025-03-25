// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseballBlueprintFunctionLibrary.h"

TMap<int32, int32> UBaseballBlueprintFunctionLibrary::GetRandomNumbers()
{
	TMap<int32, int32> Results;

	TArray<int32> Numbers;
    
	// 1~9의 숫자를 추가
	for (int32 i = 1; i < 10; i++)
	{
		Numbers.Add(i);
	}

	/*
	 * 랜덤 숫자를 고르는 방법
	 * 1. 1~9까지의 숫자가 들어있는 배열을 준비한다.
	 *
	 * 2. 무작위 숫자를 고른다.
	 *    - i번째 자리부터 배열의 끝까지 중 무작위로 인덱스를 하나 선택해 i번째 자리와 스왑.
	 *    - 스왑 후 i의 값에 +1을 하여 다음 선택에선 i번째 자리를 제외
	 *    - 이걸 뽑고 싶은 갯수만큼 반복 (여기선 3번)
	 *    - 이를 통해 0~2번째 위치에는 무작위로 선택된 3개의 숫자가 들어감.
	 *    
	 * 3. 앞에서 3개 숫자를 선택하여 정답으로 저장.
	 */
	for (int32 i = 0; i < 3; ++i)
	{
		int32 RandomIndex = FMath::RandRange(i, Numbers.Num() - 1);
		Numbers.Swap(i, RandomIndex);
	}

	// Answer에 처음 3개 저장 (키: 숫자, 값: 위치)
	Results.Empty();
	FString Log;	
	for (int32 i = 0; i < 3; i++)
	{
		Results.Add(Numbers[i], i);
		Log += FString::FromInt(Numbers[i]);
	}

	// 디버깅용 정답 프린트
	UE_LOG(LogTemp, Warning, TEXT("정답은 %s 입니다."), *Log);
	
	return Results;
}

void UBaseballBlueprintFunctionLibrary::CheckAnswer(const TMap<int32, int32>& SecretNumbers, const FString& PlayerGuess, int32& Strike, int32& Ball)
{
	Strike = 0;
	Ball = 0;

	// TMap에 해당 키(숫자)가 포함하는지 Contains로 확인.
	// 있다면 자리까지 체크
	for (int i = 0; i < PlayerGuess.Len(); i++)
	{
		int32 GuessNum = PlayerGuess[i] - '0';
		if (SecretNumbers.Contains(GuessNum))
		{
			if (SecretNumbers[GuessNum] == i) Strike++;
			else Ball++;
		}
	}
	
	FString Message = FString::Printf(TEXT("Strike: %d, Ball: %d"), Strike, Ball);
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message);
	}
}
