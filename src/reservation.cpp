#include "reservation.h"

/*
Constructors van de reservation klasse. Een default constructor en een constructor die argumenten binnenneemt. De default constructor maakt gebruik van de andere constructor.
De tweede constructor gaat eerst de naam, ontbijt en kamer type van de reservatie opslaan.
*/

Reservation::Reservation() : Reservation("No name", false, singleRoom) {}

Reservation::Reservation(std::string name, bool breakfast, RoomType room){
    this->_client = name;
    this->_breakfastIncluded = breakfast;
    this->_roomType = room;
}

/*
Functie om het ontbijt attribuut aan te passen.
*/

void Reservation::setBreakfast(bool breakfast){
    this->_breakfastIncluded = breakfast;
}

/*
Functie om het gasten attribuut aan te passen.
*/

void Reservation::setClient(std::string name){
    this->_client = name;
}  

/*
Functie om het kamer type attribuut aan te passen.
*/

void Reservation::setRoomType(RoomType room){
    this->_roomType = room;
}

/*
Functie om de gastnaam weer te geven
*/

std::string Reservation::getClient(void){
    return this->_client;
}

/*
Functie om weer te geven als er ontbijt moet zijn.
*/

bool Reservation::getBreakfast(void){
    return this->_breakfastIncluded;
}

/*
Functie om het kamertype weer te geven. 
*/

Reservation::RoomType Reservation::getRoom(void){
    
    return this->_roomType;
}
