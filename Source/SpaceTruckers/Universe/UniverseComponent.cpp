#include "UniverseComponent.h"
#include "Engine/Engine.h"
#include "Engine/DataTable.h"
#include "Engine/World.h"
#include "SolarSystem.h"
#include <cstdlib>

// Sets default values for this component's properties
UUniverseComponent::UUniverseComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


void UUniverseComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, "Begin Play...", true);
	}

	GenerateNewUniverse();
}


void UUniverseComponent::TickComponent(const float DeltaTime,const ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UUniverseComponent::GenerateNewUniverse() const
{
	constexpr double pi{3.14159265358979323846};
	constexpr double toRadians{pi / 180.0f};

	// Apply the seed for the randomness of this universe.
	// TODO: We should probably use a specialty class for random generation instead of the built-in one.
	srand(randomSeed);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow,
		                                 "Generate new universe using seed: " + FString::FromInt(randomSeed), true);

		if (solarSystemNames)
		{
			static const FString ContextString(TEXT("Finding Row in solar system table"));

			TArray<FName> rows = solarSystemNames->GetRowNames();

			// Randomise the array by swapping elements multiple times. This is probably not
			// very optimal, but it will do for now.
			std::srand(std::time(nullptr));
			for (int i = 0; i < rows.Max() * 3; i++)
			{
				const int32 firstRow = std::rand() % rows.Max();
				const int32 secondRow = std::rand() % rows.Max();
				std::swap(rows[firstRow], rows[secondRow]);
			}

			float rotationDegree{0.0f};
			float expansionOutward{0.0f};

			// Generate a set of solar systems.
			for (int i = 0; i < 200; i++)
			{
				// Calculate some random offsets. Allowing the offset to be positive or negative.
				float randomOutward{0.0f};
				if (randomExpansionOutward > 0.0f)
				{
					randomOutward = std::rand() % static_cast<int>(randomExpansionOutward * 2.0) -
						randomExpansionOutward;
				}
				float randomRotation{0.0f};
				if (randomRotationDegree > 0.0f)
				{
					randomRotation = std::rand() % static_cast<int>(randomRotationDegree * 2.0) - randomRotationDegree;
				}

				// Centre of the universe is based on the universe actor location.
				FVector SpawnLocation = GetOwner()->GetActorLocation();
				FRotator SpawnRotation = GetOwner()->GetActorRotation();

				// Give the new solar system an offset from the universe.
				const float distance = deadZone + expansionOutward + randomOutward;
				const float x = sin((rotationDegree + randomRotation) * toRadians) * distance;
				const float y = cos((rotationDegree + randomRotation) * toRadians) * distance;
				SpawnLocation.X += x;
				SpawnLocation.Y += y;

				// Update the rotation and expansion outwards.
				expansionOutward += fixedExpansionOutward;
				rotationDegree += fixedRotationDegree;

				auto& row = rows[i];

				FActorSpawnParameters spawnParameters;
				spawnParameters.Owner = GetOwner();
				spawnParameters.Instigator = GetOwner()->GetInstigator();
				spawnParameters.ObjectFlags |= RF_Transient;
				spawnParameters.Name = row;
				spawnParameters.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
				ASolarSystemActor* solarSystemActor = GetWorld()->SpawnActor<ASolarSystemActor>(
					SpawnLocation, SpawnRotation, spawnParameters);

#if WITH_EDITOR
				// Set a label for the outliner and make our new actor a child of the universe.
				solarSystemActor->SetActorLabel(row.ToString());
				solarSystemActor->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
#endif
			}

			// Iterate every row of the array.
			//for (auto& aRow : rows)
			//{
			//	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, aRow.ToString(), true);
			//}
		}
	}
}
