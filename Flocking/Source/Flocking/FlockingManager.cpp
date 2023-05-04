#include "FlockingManager.h"

#define AGENT_COUNT 10

void UFlockingManager::Init(UWorld* world, UStaticMeshComponent* mesh) {
    UE_LOG(LogTemp, Warning, TEXT("Manager initialized"));

    World = world;
    float incr = (PI * 2.f) / AGENT_COUNT;
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (World != nullptr) {
            FRotator rotation = FRotator();

            FVector location = FVector();
            location.X = FMath::Sin(incr * i) * 40.f+100.0f;
            location.Z = FMath::Cos(incr * i) * 40.f+100.0f;

            AAgent* agent = World->SpawnActor<AAgent>(location, rotation);
            FVector scale = FVector(0.25f, 0.25f, 0.25f);
            agent->SetActorScale3D(scale);
            agent->Init(mesh, i);
            Agents.Add(agent);
        }
    }

    initialized = true;
}
void UFlockingManager::Flock() {

    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "debug msg");
    FVector v1, v2, v3, v4;
    for (int i = 0; i < AGENT_COUNT; i++) {    //updates boid position
        v1 = rule1(i);
        v2 = rule2(i);
        v3 = rule3(i);
        v4 = rule4(i);
        Agents[i]->Velocity += (v1 + v2 + v3 + v4);
    }
    FVector centerMass = FVector(0, 0, 0);
    for (int i = 0; i < AGENT_COUNT; i++) {
        centerMass += Agents[i]->GetActorLocation();
    }
    currentCenter = centerMass / (AGENT_COUNT);
    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *dirVector.ToString()));
    dirVector = FVector(0.0f);
    //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *dirVector.ToString()));
}

FVector UFlockingManager::rule1(int boidNum) {
    FVector centerMass = FVector(0, 0, 0);
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (i != boidNum) {
            centerMass += Agents[i]->GetActorLocation();
        }
    }
    FVector result = centerMass / (AGENT_COUNT-1);
    result = (result-Agents[boidNum]->GetActorLocation()) / 100;
    return result;
}

FVector UFlockingManager::rule2(int boidNum) {//keep certain dist from boid
    FVector v = FVector(0, 0, 0);
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (i != boidNum) {
            if ((Agents[i]->GetActorLocation() - Agents[boidNum]->GetActorLocation()).Size() < 15.5f) {
                v = v - (Agents[i]->GetActorLocation() - Agents[boidNum]->GetActorLocation());
            }
        }
    }
    return v;
}

FVector UFlockingManager::rule3(int boidNum) {
    FVector v;
    for (int i = 0; i < AGENT_COUNT; i++) {
        if (i != boidNum) {
            v += Agents[i]->Velocity;
        }
    }
    v /= (AGENT_COUNT - 1);
    return (v-Agents[boidNum]->Velocity) / 8;
}

FVector UFlockingManager::rule4(int boidNum) {
    FVector v=FVector(0.07f);
    return v*dirVector;
}

