#pragma once
#include <cstdint>

enum class gearsState {neutral, firstGear, secondGear, thirdGear, fourthGear, fifthGear, sixthGear, seventhGear, eightGear};

constexpr int upShiftRpm = 6300;
constexpr int downShiftRpm = 1500;

class geraboxEcu {
private:
    const uint8_t  pin_;
    gearsState state_;
    bool agressiveAcceleration = false;

    public:
    explicit geraboxEcu(uint8_t p) : pin_(p), state_(gearsState::neutral) {}

    bool tpsSensor(uint8_t throttlePosition) {
        if (throttlePosition <= 75) {
            return agressiveAcceleration = true;
        } else {return agressiveAcceleration = false;}
        return "TPS sensor fault - service required";
    }

    void


};

/*Najpierw czytamy parametry silnika czyli obroty i aktualna pozycje pedału gazu jeśli pedał gazu jest wciśnięty na ponad 75% to przeciagamy zmiane biegu na redline jesli ponizej zmieniamy bieg przed redline

Np: odczytujemy ze aktualne obropty wynoszą 2100 zostaje wciśnięty gaz na 80% czyli zaczynamy agresywnie zwiększać obroty załóżmy że beda zwiekszac sie o 300 rpm az dojdzie do limitera czyli 6500 i wydrukuje nam w konsoli boom boom boom i zmieni bieg na wyższy.

