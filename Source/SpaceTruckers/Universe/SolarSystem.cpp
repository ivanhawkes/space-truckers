#include "SolarSystem.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ASolarSystemActor::ASolarSystemActor()
{
   PrimaryActorTick.bCanEverTick = true;

   // Create a mesh and make it the root of our actor.
   meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"), false);
   RootComponent = meshComponent;

   // Set the mesh.
   static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
   UStaticMesh* Asset = MeshAsset.Object;
   meshComponent->SetStaticMesh(Asset);
}


// Called when the game starts or when spawned
void ASolarSystemActor::BeginPlay()
{
   Super::BeginPlay();
}


// Called every frame
void ASolarSystemActor::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);
}
