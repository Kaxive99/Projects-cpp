#pragma once
#include <cstdint>
#include <iostream>
#include <cstdlib>

enum class flightTrjacetory {Climb, Cruise, Descent  };
uint32_t safeDistance = 100;


inline const char* trajectoryName(flightTrjacetory state) {
    switch (state) {
        case flightTrjacetory::Climb : return "Climb";
        case flightTrjacetory::Cruise : return "Cruise";
        case flightTrjacetory::Descent : return "Descent";
    }
    return "Unknown";
}


inline bool isCollisionRisk(int ownAltitude, int intruderAltitude) { return  ((std::abs(ownAltitude - intruderAltitude)) < safeDistance); }

inline flightTrjacetory updateTrajectory( flightTrjacetory current, int32_t ownAltitudeCm, int32_t intruderAltitudeCm) {
    if (!isCollisionRisk(ownAltitudeCm, intruderAltitudeCm)) {
        return current;
    } else if ( ownAltitudeCm > intruderAltitudeCm) {
        return flightTrjacetory::Climb;
    } return flightTrjacetory::Descent; // ownAltitude < intruderAltitude && ownAltitude == intruderAltitude
}