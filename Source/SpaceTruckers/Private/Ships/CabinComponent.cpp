#include "Ships/CabinComponent.h"


UCabinComponent::UCabinComponent()
{
	// const auto actor = GetOwner();
	// const auto scroot = actor->GetRootComponent();
	
	PrimaryComponentTick.bCanEverTick = true;

	// Create a mesh component.
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	// mesh->SetupAttachment(actor->GetRootComponent());
	mesh->SetSimulatePhysics(true);
	
	// Offset the mesh slightly from the base so the constraint has space.
	// TODO: AI generated, is this needed? Also, 100.0 seems like a LOT of offset.
	mesh->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));

	// 3. Create the physics constraint component
	physicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("physicsConstraint"));
	physicsConstraint->SetupAttachment(mesh);
	
	// TODO: Another offset that is hard coded. Look into this.
	physicsConstraint->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));

	// Link the two components programmatically in code.
	// Component 1 can be None/World or point to BaseMeshComp. 
	// Passing NAME_None for ComponentName1 defaults to attaching to the parent/world safely, 
	// or you can explicitly pass the FName of the component.
	// physicsConstraint->SetConstrainedComponents(
	// 	GetOwner()->GetRootComponent(), NAME_None, 
	// 	mesh, NAME_None
	// );
}


void UCabinComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UCabinComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

