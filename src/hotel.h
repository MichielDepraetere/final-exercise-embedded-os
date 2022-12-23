#pragma once

#include <vector>
#include "reservation.h"

/* Header file van de Hotel klasse. */
class Hotel
{
    /* Attributen van de Hotel klasse. */
    private:
        std::string _hotelName = "";                    // Naam van het hotel
        int _capacitySingleRooms = 0;                   // Aantal single kamers die het hotel heeft.
        int _capacityTwinRooms = 0;                     // Aantal twin kamers die het hotel heeft.
        int _capacityKingRooms = 0;                     // Aantal king kamers die het hotel heeft.
        std::vector<Reservation *> _reservationList;    // Vector waarin alle reservaties zich bevinden. 
        int _availableSingles = 0;                      // Vrije single kamers
        int _availableTwins = 0;                        // Vrije twin kamers
        int _availableKings = 0;                        // Vrije king kamers
        int _numberOfReservations = Hotel::_reservationList.size(); // aantal gasten die op dit moment in het hotel verblijven

    // Functies van de hotel klasse, meer info in .cpp file  
    public:
        Hotel();
        Hotel(std::string name, int capSingle, int capTwin, int capKing);
        bool addReservation(Reservation * reservation);
        bool checkAvailability(int roomType);
        void updateAvailability(int roomType, bool free);
        void prepareRoom(Reservation * reservation);
        void welcomeGuests(std::string name);
        void checkOut(Reservation * reservation);
        Reservation * getReservation(int reservationNumber);
        int getNumberOfReservations(void);

};
