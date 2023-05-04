// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlockingManager.h"
#include "FlockingGameModeBase.generated.h"

UCLASS(Blueprintable, BlueprintType)
class FLOCKING_API AFlockingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
		AFlockingGameModeBase();

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* AgentMesh;
public:
	UPROPERTY(BlueprintReadWrite) UFlockingManager* Manager;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};