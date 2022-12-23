#include "hotel.h"
#include <iostream>
#include <vector>

/*
Constructors van de hotel klasse. Een default constructor en een constructor die argumenten binnenneemt. De default constructor maakt gebruik van de andere constructor.
De tweede constructor gaat eerst de naam en capaciteit van het hotel opslaan, alsook meteen de beschikbare kamers initialiseren. In het begin is dit gelijk aan het aantal kamers
want dan zijn er nog geen reservaties gemaakt.
*/

Hotel::Hotel() : Hotel("No name", 0, 0, 0) {}
Hotel::Hotel(std::string name, int capSingle, int capTwin, int capKing) {
    this->_hotelName = name;
    this->_capacitySingleRooms = capSingle;
    this->_capacityTwinRooms = capTwin;
    this->_capacityKingRooms = capKing;
    this->_availableSingles = capSingle;
    this->_availableTwins = capTwin;
    this->_availableKings = capKing;
}

/*
Functie om een reservatie toe te voegen aan de database van het hotel. In dit geval worden de reservaties opgeslagen in een vector die de pointers opslaat.
Er zit een check in die nagaat of de gevraagde kamer nog vrij is. Als die vrij is dan wordt de reservatie opgeslagen, zo niet dan wordt de reservatie geweigerd.
Als de reservatie doorgaat dan wordt de beschikbaarheid van de kamer ook aangepast.
*/

bool Hotel::addReservation(Reservation * reservation) {
    if (checkAvailability(reservation->getRoom())){
        this->_reservationList.push_back(reservation);
        std::cout << "Reservation made for:" << std::endl;
        std::cout << "Name: " << reservation->getClient() << std::endl;
        std::cout << "Room type: " << reservation->getRoom() << std::endl;
        std::cout << "Breakfast: " << reservation->getBreakfast() << std::endl;
        std::cout << std::endl;
        updateAvailability(reservation->getRoom(), false);
        return true;
    } else {
        std::cout << "Reservation could not be made." << std::endl;
        std::cout << std::endl;
        return false;
    }
}

/*
Functie om te controleren of er nog vrije kamers zijn van het gespecifieerde type. Hierbij wordt het type kamer meegegeven in de function call en via enkele switch statements wordt
er gekeken als er nog beschikbare kamers zijn of niet. 
*/

bool Hotel::checkAvailability(int roomType){
    if (roomType == 0 && _availableSingles > 0) {
        std::cout << "Single rooms available!" << std::endl;
        return true;
    } else if (roomType == 1 && _availableTwins > 0) {
        std::cout << "Twin rooms available!" << std::endl;
        return true;
    } else if (roomType == 2 && _availableKings > 0) {
        std::cout << "King rooms available!" << std::endl;
        return true;
    } else {
        std::cout << "No rooms available!" << std::endl;
        return false;
    }
    std::cout << std::endl;
}

/*
Functie om de beschilbaarheid van een kamer type te updaten. Het type wordt meegegeven en dan wordt via een switch case het attribuut van de correcte kamer aangepast. 
Ook wordt er aangegeven of het gaat om een kamer vrijgeven of blokkeren, dit gaat via een bool. Als er 'true' wordt meegegeven dan betekent dit dat er een kamer terug
vrijkomt, anders is het dat deze gereserveerd wordt. Op die manier kan deze functie gebruikt worden om zowel kamers te blokkeren als terug vrij te geven.
*/

void Hotel::updateAvailability(int roomType, bool free){

    if(free){
        switch (roomType)
            {
            case 0:
                this->_availableSingles += 1;
                std::cout << "Current available singles: " << this->_availableSingles << std::endl;
                break;
            case 1:
                this->_availableTwins += 1;
                std::cout << "Current available twins: " << this->_availableTwins << std::endl;
                break;
            case 2:
                this->_availableKings +=1;
                std::cout << "Current available kings: " << this->_availableKings << std::endl;
                break;
            default: 
                std::cout << "Room availabilities updated" << std::endl;
                break;
            }
    } else {
        switch (roomType)
        {
        case 0:
            this->_availableSingles -= 1;
            std::cout << "Current available singles: " << this->_availableSingles << std::endl;
            break;
        case 1:
            this->_availableTwins -= 1;
            std::cout << "Current available twins: " << this->_availableTwins << std::endl;
            break;
        case 2:
            this->_availableKings -=1;
            std::cout << "Current available kings: " << this->_availableKings << std::endl;
            break;
        default: 
            std::cout << "Room availabilities updated" << std::endl;
            break;
        }
    }
    std::cout << std::endl;
}

/*
Functie om een klein tekstje naar de terminal te printen waarin de details van de kamer meegegeven worden. Hierbij worden de details uit de pointer naar de reservatie uitgelezen.
*/

void Hotel::prepareRoom(Reservation * reservation) {
    std::cout << "Room for " << reservation->getClient() << " in " << this->_hotelName << " hotel is being prepared." << std::endl;
    if(reservation->getBreakfast()){
        std::cout << "Breakfast is included." << std::endl;
    } else {
        std::cout << "Breakfast is not included" << std::endl;
    }
    std::cout << std::endl;
    switch (reservation->getRoom())
    {
    case 0:
        std::cout << "Room type: Single room" << std::endl;
        break;
    
    case 1:
        std::cout << "Room type: Twin room" << std::endl;
        break;
    
    case 2:
        std::cout << "Room type: King room" << std::endl;
        break;
    }

    std::cout << std::endl;
}

/*
Functie om de gast van een bepaalde reservatie welkom te heten. Hierbij is enkel de gastnaam nodig.
*/

void Hotel::welcomeGuests(std::string name){
    std::cout << "Reception: \"Welcome " << name << "! Please enjoy your stay at hotel " << _hotelName << "!\"" << std::endl;
    std::cout << std::endl;
}

/*
Functie die de pointer naar een bepaalde reservatie teruggeeft. Hier zit ook een check in die ervoor zorgt dat er geen reservatie opgevraagd kan worden die groter is dan het aantal bestaande
reservaties.
*/

Reservation * Hotel::getReservation(int reservationNumber){
    if(reservationNumber < _reservationList.size()){
        return _reservationList[reservationNumber];
    } else {
        return _reservationList[_reservationList.size()-1];
    } 
}

/*
Functie die een gast uit checkt. Hierbij worden alle gasten overlopen en gecontroleerd welke positie overeenkomt met de gespecifieerde gast. Deze wordt dan verwijderd uit de vector.
*/

void Hotel::checkOut(Reservation * reservation){
    for (int i = 0; i < _reservationList.size(); i++){
        if(_reservationList[i]->getClient() == reservation->getClient()){
            std::cout << "Checking out client " << _reservationList[i]->getClient() << "." << std::endl;
            this->_reservationList.erase(_reservationList.begin()+i);
            std::cout << "Checkout successful!" << std::endl;
            updateAvailability(reservation->getRoom(), true);
        }
        std::cout << std::endl;
    } 
    
}

/*
Functie die het aantal huidige reservaties teruggeeft.
*/

int Hotel::getNumberOfReservations(void){
    return _numberOfReservations;
}
