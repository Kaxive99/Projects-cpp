#pragma once
#include <cstdint>
#include <cstdlib>

enum class flightTrjacetory {Climb, Cruise, Descent  };
constexpr  int32_t SAFE_DISTANCE = 100;
constexpr  int32_t CLEAR_DISTANCE = 150;


inline const char* trajectoryName(flightTrjacetory state) {
    switch (state) {
        case flightTrjacetory::Climb : return "Climb";
        case flightTrjacetory::Cruise : return "Cruise";
        case flightTrjacetory::Descent : return "Descent";
    }
    return "Unknown";
}


inline bool isCollisionRisk(int ownAltitude, int intruderAltitude, int thresholdCm) { return  ((std::abs(ownAltitude - intruderAltitude)) < thresholdCm); }

inline flightTrjacetory updateTrajectory( flightTrjacetory current, int32_t ownAltitudeCm, int32_t intruderAltitudeCm) {



    bool isAvoiding {current == flightTrjacetory::Climb  || current == flightTrjacetory::Descent};

    int32_t threshold = isAvoiding ?  CLEAR_DISTANCE : SAFE_DISTANCE;


    if (!isCollisionRisk(ownAltitudeCm, intruderAltitudeCm, threshold)) {
        return flightTrjacetory::Cruise;
    } else if ( ownAltitudeCm > intruderAltitudeCm) {
        return flightTrjacetory::Climb;
    } return flightTrjacetory::Descent; // ownAltitude < intruderAltitude && ownAltitude == intruderAltitude
    }
