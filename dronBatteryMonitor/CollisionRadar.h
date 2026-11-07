#pragma once
#include <cstdint>

enum class flightTrjacetory {Climb, Cruise, Descent  };

inline const char* trajectoryName(flightTrjacetory state) {
    switch (state) {
        case flightTrjacetory::Climb : return "Climb";
        case flightTrjacetory::Cruise : return "Cruise";
        case flightTrjacetory::Descent : return "Descent";
    }
    return "Unknown";
}

// Dostaje info o obiekcie na jakiej jest wysokosci jesli wysokosc koliduje o 35cm wtedy albo robi climb albo descent jesli obiekt jest na cruise dron leci do gory jesli jest na climb to leci na descent etc..