// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Agent.h"
#include "CoreMinimal.h"
#include "FlockingManager.generated.h"

UCLASS()
class FLOCKING_API UFlockingManager : public UObject
{

public:

	GENERATED_BODY()

		void Init(UWorld* world, UStaticMeshComponent* mesh);
	void Flock();
	FVector rule1(int boidNum);
	FVector rule2(int boidNum);

	FVector rule3(int boidNum);
	FVector rule4(int boidNum);
	UPROPERTY(BlueprintReadWrite) FVector currentCenter;
	UPROPERTY(BlueprintReadWrite) FVector dirVector;
private:
	UWorld* World;
	bool initialized;
	TArray<class AAgent*> Agents;

};