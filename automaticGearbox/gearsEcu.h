#pragma once
#include <cstdint>


enum class gearsState {neutral, firstGear, secondGear, thirdGear, fourthGear, fifthGear, sixthGear, seventhGear, eightGear};
enum class gearboxMode {Race, Sport, Eco};

constexpr int wotUpShiftRpm = 6500;
constexpr int sportUpShiftRpm = 4500;
constexpr int ecoUpShiftRpm = 2000;
constexpr int wotDownShiftRpm = 2900;
constexpr int sportDownShiftRpm = 2350;
constexpr int ecoDownShiftRpm = 1300;
constexpr int increasingRpmsInWot = 300;
constexpr int increasingRpmsInSport = 150;
constexpr int increasingRpmsInEco = 60;


class geraboxEcu {
private:
    const uint8_t  pin_;
    gearsState state_;
    bool sportAcceleration = false;
    bool wotAcceleration = false;
    int rpm;

    public:
    //Lista inicjalizacyjna
    explicit geraboxEcu(uint8_t p) : pin_(p), state_(gearsState::neutral) {}


    //Odczytuje nacisk na pedał gazu i ocenia czy zostało wykonane agresywne przyśpieszenie.
    bool tpsSensor(uint8_t throttlePosition) {
        if (throttlePosition == 100) {
            wotAcceleration = true;
        } else if (throttlePosition <= 75) {
            return sportAcceleration = true;
        } else {return sportAcceleration = false;}
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

    void getGearState(state_) {
        switch (state_) {
            case 
        }
    }

    void upShift() {
       //Zwiększa bieg i oblicza rpm na nowym biegu.
    }
};

/*Najpierw czytamy parametry silnika czyli obroty i aktualna pozycje pedału gazu jeśli pedał gazu jest wciśnięty na ponad 75% to  zmieńamy bieg w trybie sport jesli ponizej zmieniamy bieg w trybue eco a jesli jest wcisniety wot to zmieniamy bieg w trybie  race

Np: odczytujemy ze aktualne obroty wynoszą 2100 zostaje wciśnięty gaz na 80% czyli zaczynamy agresywnie zwiększać obroty załóżmy że beda zwiekszac sie o 300 rpm az dojdzie do limitera czyli 6500 i wydrukuje nam w konsoli boom boom boom i zmieni bieg na wyższy.

*/