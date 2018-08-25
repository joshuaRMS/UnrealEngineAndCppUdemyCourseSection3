// Copyright Joshua Latusia 2018
#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Math/Rotator.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Door = GetOwner();
}

/// <summary>
/// Opens the door by adjusting yawn rotation.
/// </summary>
void UOpenDoor::OpenDoor()
{
	if (CurrentAngle > OpenDoorAntiClockWiseAngle)
	{
		CurrentAngle--;

		FRotator NewRotation = FRotator(0.0f, CurrentAngle, 0.0f);
		Door->SetActorRotation(NewRotation);
		FString RotationAfter = Door->GetActorRotation().ToString();
		UE_LOG(LogTemp, Error, TEXT("Rotation after : %s"), *RotationAfter);
	}
}

/// <summary>
/// Closes the door.
/// </summary>
void UOpenDoor::CloseDoor()
{
	if (CurrentAngle < 0.0f)
	{
		CurrentAngle++;
		FRotator NewRotation = FRotator(0.0f, CurrentAngle, 0.0f);
		Door->SetActorRotation(NewRotation);
	}
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(PressurePlate->IsOverlappingActor(ActorThatOpensDoor))
	{
		OpenDoor();
	}
	else
	{
		CloseDoor();
	}
}

