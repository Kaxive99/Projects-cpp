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
constexpr double gearRatios[] = {
    1.0,    // 0
    4.56,   // 1
    2.97,   // 2
    2.08,   // 3
    1.69,   // 4
    1.27,   // 5
    1.00,   // 6
    0.85,   // 7
    0.65    // 8
};

struct ShiftProfile {
    int rpmStep;
    int upshiftRpm;
    int downshiftRpm;
};


class GeraboxEcu {
private:
    const int neutralGear_ = 0;
    const uint8_t  pin_;
    int currentGear_;
    int maxGear_ = 8;
    bool ignition_;
    int rpm_;
    GearboxMode mode_;

    public:
    //Lista inicjalizacyjna
    explicit GeraboxEcu(uint8_t p) : pin_(p), rpm_(600), currentGear_(1), ignition_(true), mode_(GearboxMode::Eco) {}

    ShiftProfile getShiftProfile() const {
        switch (mode_) {
            case GearboxMode::Eco : return {60, 2000, 1000};
            case GearboxMode::Sport : return {150, 4500, 2200};
            case GearboxMode::Race : return {300, 6500, 3000};
        }
    }
    ShiftProfile profile = getShiftProfile();

    //Odczytuje nacisk na pedał gazu i ocenia czy zostało wykonane agresywne przyśpieszenie.
    bool tpsSensor(uint8_t throttlePosition) {
        if (throttlePosition >= 100) {
            mode_ = GearboxMode::Race;
        } else if (throttlePosition > 75 && throttlePosition <= 99) {
            mode_ = GearboxMode::Sport;
        } else {mode_ = GearboxMode::Eco;}
        return "TPS sensor fault - service required";
        profile = getShiftProfile();
    }


    //Czyta aktualne obroty silnika
    int rpmSensor(uint32_t rpmRead) {
        return rpm_ = rpmRead;
    }

    void rpmCheck() {
        if (rpm_ >= profile.upshiftRpm) {
            upShift();
        }
    }

    void increasingRpm() {
        rpmCheck();
        rpm_ += profile.rpmStep;
    }

    bool isNeutral() {
        return currentGear_ == neutralGear_;
    }
    bool isRunning() {
        return ignition_ == true;
    }

    // Wyświetla nazwe aktualnego biegu
    const char* getGearState() {
        switch (currentGear_) {
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

    int getRpms() {
        return rpm_;
    }



    //Zwiększa bieg i oblicza rpm na nowym biegu.
    void upShift() {
        if (currentGear_ == maxGear_) {
            cout << "[WARN] Max gear reached - rev limiter active \n";
            ignition_ = false;
        } else {
            cout << "[INFO] Upshift " << currentGear_ <<" -> " << currentGear_ + 1 <<" at " << profile.upshiftRpm << " RPM \n";
            double oldRatio = gearRatios[currentGear_];
            currentGear_++;
            double newRatio = gearRatios[currentGear_];
            rpm_ = static_cast<uint16_t>(rpm_ * newRatio / oldRatio);
        }
    }
};

/*Najpierw czytamy parametry silnika czyli obroty i aktualna pozycje pedału gazu jeśli pedał gazu jest wciśnięty na ponad 75% to  zmieńamy bieg w trybie sport jesli ponizej zmieniamy bieg w trybue eco a jesli jest wcisniety wot to zmieniamy bieg w trybie  race

Np: odczytujemy ze aktualne obroty wynoszą 2100 zostaje wciśnięty gaz na 80% czyli zaczynamy agresywnie zwiększać obroty załóżmy że beda zwiekszac sie o 300 rpm az dojdzie do limitera czyli 6500 i wydrukuje nam w konsoli boom boom boom i zmieni bieg na wyższy.

*/