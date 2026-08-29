#pragma once

#include "CoreMinimal.h"

class SPACETRUCKERS_API Universe
{
public:
	Universe();
	~Universe();
	
	static constexpr double gravitationalConstant {6.6743e-11};
	static constexpr double pi{3.14159265358979323846};
	static constexpr double tau{3.14159265358979323846 * 2.0f};
	static constexpr double toRadians{pi / 180.0f};
	static constexpr double toDegrees{180.0f / pi};
	
	static constexpr double sunMass {1.988e+30};
	static constexpr double sunDensity {1.0f};
	
	static constexpr double planetMass {5.9722+24};
	static constexpr double planetDensity {1.0f};
	
	static constexpr double moonMass {7.347e+22};
	static constexpr double moonDensity {1.0f};
	
	static constexpr double satelliteMass {1.0e+6};
	static constexpr double satelliteDensity {1.0f};
};
