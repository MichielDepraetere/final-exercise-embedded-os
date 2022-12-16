#pragma once
#include "reservation.h"
#include <vector>
#include <string>

class Hotel {
    public:
        Hotel();
        Hotel(int amountOfSuits, int amountOfNormalRooms);
    
    public:
        void MakeReservation(Reservation reservation);

    private:
        int freeSuits;
        int freeNormalRooms;
        std::vector<Reservation> reservations;
};