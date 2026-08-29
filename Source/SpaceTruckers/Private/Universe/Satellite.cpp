#include "Universe/Satellite.h"
#include "Game/GameInstanceSpaceTrucker.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Universe/Planet.h"
#include "Universe/Universe.h"


ASatelliteActor::ASatelliteActor()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ASatelliteActor::BeginPlay()
{
	Super::BeginPlay();
	
	gameInstance = GetGameInstance<UGameInstanceSpaceTrucker>();
}


void ASatelliteActor::Tick(const float DeltaTime)
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


double ASatelliteActor::GetGravity() const
{
	return massFactor * densityFactor * Universe::gravitationalConstant * Universe::satelliteMass;
}


double ASatelliteActor::GetOrbitDistance() const
{
	return FVector::Distance(orbitParent->GetActorLocation(),GetActorLocation());
}


double ASatelliteActor::GetOrbitCircularVelocity() const
{
	return sqrt(GetGravity() / GetOrbitDistance());
}


double ASatelliteActor::GetOrbitPeriod() const
{
	return orbitRadius * Universe::tau / GetOrbitCircularVelocity();
}


double ASatelliteActor::GetVelocityInRadiansPerSecond() const
{
	return GetOrbitCircularVelocity() / GetOrbitDistance(); 
}


void ASatelliteActor::OnPostInitialSpawn()
{
	// Set a rotation for the entire actor.
	const double rotationX = FMath::RandRange(0.0f, 15.0f);
	const double rotationY = FMath::RandRange(0.0f, 15.0f);
	SetActorRotation(FRotator (rotationX, rotationY,0.0f));
}


bool ASatelliteActor::OnPreSave(FActorSaveData& SaveData)
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


bool ASatelliteActor::OnPostLoad(FActorSaveData& SaveData)
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


void ASatelliteActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	// Get the static mesh which we should have.
	if (const UStaticMeshComponent* mesh = FindComponentByClass<UStaticMeshComponent>())
	{
		// Give the actor a mass based on its scale vs our sun.
		massFactor = mesh->GetComponentScale()[0];
	}
}
