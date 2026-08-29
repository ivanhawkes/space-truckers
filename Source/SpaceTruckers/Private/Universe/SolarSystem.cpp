#include "Universe/SolarSystem.h"
#include "Game/GameInstanceSpaceTrucker.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Universe/Universe.h"


ASolarSystemActor::ASolarSystemActor()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ASolarSystemActor::BeginPlay()
{
	Super::BeginPlay();
	
	gameInstance = GetGameInstance<UGameInstanceSpaceTrucker>();
}


void ASolarSystemActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Update the axis rotation.
	double yaw = DeltaTime * gameInstance->timeMultiplier * axialRotation;
	yaw = FMath::Fmod(yaw, 360.0f);
	const FQuat yawQuat = FQuat(FRotator(0.0, yaw, 0.0));
	SetActorRotation(GetActorQuat() * yawQuat);
}


double ASolarSystemActor::GetGravity()
{
	return massFactor * densityFactor * Universe::gravitationalConstant * Universe::sunMass;
}


void ASolarSystemActor::OnPostInitialSpawn()
{
	// Set a rotation for the entire actor.
	const double rotationX = FMath::RandRange(0.0f, 15.0f);
	const double rotationY = FMath::RandRange(0.0f, 15.0f);
	SetActorRotation(FRotator(rotationX, rotationY, 0.0f));
}


bool ASolarSystemActor::OnPreSave(FActorSaveData& SaveData)
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


bool ASolarSystemActor::OnPostLoad(FActorSaveData& SaveData)
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


void ASolarSystemActor::PostInitProperties()
{
	Super::PostInitProperties();
}


void ASolarSystemActor::PostLoad()
{
	Super::PostLoad();
}


void ASolarSystemActor::PostActorCreated()
{
	Super::PostActorCreated();
}


void ASolarSystemActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	// Get the static mesh which we should have.
	if (const UStaticMeshComponent* mesh = FindComponentByClass<UStaticMeshComponent>())
	{
		// Give the actor a mass based on its scale vs our sun.
		massFactor = mesh->GetComponentScale()[0];
	}
}
