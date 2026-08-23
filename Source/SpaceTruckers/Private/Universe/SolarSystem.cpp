#include "SpaceTruckers/Public/Universe/SolarSystem.h"
#include "Components/StaticMeshComponent.h"


ASolarSystemActor::ASolarSystemActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create a mesh and make it the root of our actor.
	sunMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"), false);
	RootComponent = sunMeshComponent;

	// NOTE: We don't have any of the saved parameters yet. Don't set anything until those
	// are restored.
	
	// Set the mesh.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	UStaticMesh* Asset = MeshAsset.Object;
	sunMeshComponent->SetStaticMesh(Asset);
}


void ASolarSystemActor::BeginPlay()
{
	Super::BeginPlay();
	
	// We can apply the scale now.
	sunMeshComponent->SetRelativeScale3D(sunScale);
}


void ASolarSystemActor::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}
