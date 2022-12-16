#pragma once
#include <string>
#include "hotel.h"
#include "client.h"

class Reservation {
    public:
        Reservation();
        Reservation(Hotel * hotel, Client * client, std::string roomType);

    private:
        Hotel * hotel;
        Client * client;

};