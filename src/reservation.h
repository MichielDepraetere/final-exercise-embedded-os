#pragma once

#include <string>

/* Header file van de Reservation klasse. */

class Reservation {
    // Functies van de Reservatie klasse + public attribuut 'RoomType', een enum die de verschillende kamersoorten voorstelt.
    // Meer over de functies in de .cpp file
    public:
        enum RoomType {
            singleRoom,
            twinRoom,
            kingRoom
        };
        Reservation();
        Reservation(std::string name, bool breakfast, RoomType room);
        void setBreakfast(bool breakfast);
        void setClient(std::string name);
        void setRoomType(RoomType room);
        std::string getClient(void);
        bool getBreakfast(void);
        RoomType getRoom(void);

    // Attributen van de reservatie klasse
    private:
        std::string _client = "";           // Naam van de gast
        bool _breakfastIncluded = false;    // Bool om aan te geven als er ontbijt moet zijn
        RoomType _roomType = singleRoom;    // RoomType die het type van de kamer aangeeft
};