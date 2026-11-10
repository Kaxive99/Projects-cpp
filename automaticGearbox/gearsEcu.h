#pragma once
#include <cstdint>
using namespace std;


enum class GearboxMode {Race, Sport, Eco};

constexpr int wotUpShiftRpm = 6500;
constexpr int sportUpShiftRpm = 4500;
constexpr int ecoUpShiftRpm = 2000;
constexpr int wotDownShiftRpm = 2900;
constexpr int sportDownShiftRpm = 2350;
constexpr int ecoDownShiftRpm = 1300;
constexpr int increasingRpmsInWot = 300;
constexpr int increasingRpmsInSport = 150;
constexpr int increasingRpmsInEco = 60;

struct ShiftProfile {
    int rpmStep;
    int upshiftRpm;
    int downshiftRpm;
};


class GeraboxEcu {
private:
    const uint8_t  pin_;
    int currentGear;
    int maxGear = 8;
    GearboxMode mode_;
    bool sportAcceleration = false;
    bool wotAcceleration = false;
    int rpm;

    public:
    //Lista inicjalizacyjna
    explicit GeraboxEcu(uint8_t p) : pin_(p), mode_(GearboxMode::Eco), rpm(600), currentGear(0) {}


    //Odczytuje nacisk na pedał gazu i ocenia czy zostało wykonane agresywne przyśpieszenie.
    bool tpsSensor(uint8_t throttlePosition) {
        if (throttlePosition == 100) {
            mode_ = GearboxMode::Race;
            return wotAcceleration = true;
        } else if (throttlePosition > 75) {
            mode_ = GearboxMode::Sport;
            return sportAcceleration = true;
        } else {mode_ = GearboxMode::Eco; return sportAcceleration = false;}
        return "TPS sensor fault - service required";
    }

    //Czyta aktualne obroty silnika
    int rpmSensor(uint8_t rpmRead) {
        return rpm = rpmRead;
    }

    void increasingRpm() {
        if (wotAcceleration == true) {
            rpm += increasingRpmsInWot;
        } else if (sportAcceleration == true) {
            rpm += increasingRpmsInSport;
        } else {rpm += increasingRpmsInEco;}
    }

    // Wyświetla nazwe aktualnego biegu
    const char* getGearState() {
        switch (currentGear) {
            case 0 : return "Neutral";
            case 1 : return "Gear 1";
            case 2 : return "Gear 2";
            case 3 : return "Gear 3";
            case 4 : return "Gear 4";
            case 5 : return "Gear 5";
            case 6 : return "Gear 6";
            case 7 : return "Gear 7";
            case 8 : return "Gear 8";
        }
        return "Unknown";
    }

    ShiftProfile getShiftProfile() const {
        switch (mode_) {
            case GearboxMode::Eco : return {60, 2000, 1000};
            case GearboxMode::Sport : return {150, 4500, 2200};
            case GearboxMode::Race : return {300, 6500, 3000};
        }
    }
    ShiftProfile profile = getShiftProfile();


    //Zwiększa bieg i oblicza rpm na nowym biegu.
    void upShift() {
        if (currentGear == maxGear) {
            cout << "[WARN] Max gear reached - rev limiter active (6500 RPM) \n";
        } else {
            cout << "[INFO] Upshift " << currentGear <<" -> " << currentGear++ <<" at " << profile.upshiftRpm << " RPM \n";
            currentGear++;
        }
    }
};

/*Najpierw czytamy parametry silnika czyli obroty i aktualna pozycje pedału gazu jeśli pedał gazu jest wciśnięty na ponad 75% to  zmieńamy bieg w trybie sport jesli ponizej zmieniamy bieg w trybue eco a jesli jest wcisniety wot to zmieniamy bieg w trybie  race

Np: odczytujemy ze aktualne obroty wynoszą 2100 zostaje wciśnięty gaz na 80% czyli zaczynamy agresywnie zwiększać obroty załóżmy że beda zwiekszac sie o 300 rpm az dojdzie do limitera czyli 6500 i wydrukuje nam w konsoli boom boom boom i zmieni bieg na wyższy.

*/