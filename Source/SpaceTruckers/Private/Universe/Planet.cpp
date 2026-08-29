#include "Universe/Planet.h"
#include "Game/GameInstanceSpaceTrucker.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Universe/SolarSystem.h"
#include "Universe/Universe.h"


APlanetActor::APlanetActor()
{
	PrimaryActorTick.bCanEverTick = true;
}


void APlanetActor::BeginPlay()
{
	Super::BeginPlay();
	
	gameInstance = GetGameInstance<UGameInstanceSpaceTrucker>();
}


void APlanetActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Calculate the degrees of rotation for this time delta.
	double offset = GetVelocityInRadiansPerSecond() * Universe::toDegrees * gameInstance->timeMultiplier;
	orbitRotation = FMath::Wrap(orbitRotation += offset, -180.0, 180.0);

	// Calculate a new position based on the actor we orbit.
	const double x = sin((orbitRotation) * Universe::toRadians) * orbitRadius;
	const double y = cos((orbitRotation) * Universe::toRadians) * orbitRadius;
	FVector location = orbitParent->GetActorLocation();
	location.X += x;
	location.Y += y;
	SetActorLocation(location);

	// Update the axis rotation.
	double yaw = DeltaTime * gameInstance->timeMultiplier * axialRotation;
	yaw = FMath::Fmod(yaw, 360.0f);
	const FQuat yawQuat = FQuat(FRotator(0.0, yaw, 0.0));
	SetActorRotation(GetActorQuat() * yawQuat);
}


double APlanetActor::GetGravity() const
{
	return massFactor * densityFactor * Universe::gravitationalConstant * Universe::satelliteMass;
}


double APlanetActor::GetOrbitDistance() const
{
	return FVector::Distance(orbitParent->GetActorLocation(), GetActorLocation());
}


double APlanetActor::GetOrbitCircularVelocity() const
{
	return sqrt(GetGravity() / GetOrbitDistance());
}


double APlanetActor::GetOrbitPeriod() const
{
	return orbitRadius * Universe::tau / GetOrbitCircularVelocity();
}


double APlanetActor::GetVelocityInRadiansPerSecond() const
{
	return GetOrbitCircularVelocity() / GetOrbitDistance();
}


void APlanetActor::OnPostInitialSpawn()
{
}


bool APlanetActor::OnPreSave(FActorSaveData& SaveData)
{
	SaveData.actorClass = GetClass();
	SaveData.location = GetActorTransform().GetLocation();
	SaveData.rotation = GetActorRotation();
	SaveData.name = FName(GetName());

	// Serialise variables flagged with 'SaveGame'
	FMemoryWriter MemoryWriter(SaveData.serializedData);
	FObjectAndNameAsStringProxyArchive archive(MemoryWriter, true);
	archive.ArIsSaveGame = true;
	Serialize(archive);

	return true;
}


bool APlanetActor::OnPostLoad(FActorSaveData& SaveData)
{
	// Hydrate the newly spawned actor.
	FMemoryReader memoryReader(SaveData.serializedData);
	FObjectAndNameAsStringProxyArchive Archive(memoryReader, true);
	Archive.ArIsSaveGame = true;
	Serialize(Archive);

#if WITH_EDITOR
	// Set a label for the outliner and make our new actor a child of the universe.
	SetActorLabel(SaveData.name.ToString());
#endif

	return true;
}


void APlanetActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Get the static mesh which we should have.
	if (const UStaticMeshComponent* mesh = FindComponentByClass<UStaticMeshComponent>())
	{
		// Give the actor a mass based on its scale vs our sun.
		massFactor = mesh->GetComponentScale()[0];
	}
}
