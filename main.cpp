/* OPDRACHT:
Simuleer een hotel reserveringstool waarbij er een reservatie gemaakt wordt via vb een website, deze wordt dan naar het hotel gestuurd en het hotel voegt deze dan toe in haar database
(dit is vb een vector). Als extraatje kunnen er enkele functies toegevoegd worden aan de hotel klasse die ervoor zorgen dat de gewenste kamer klaargemaakt wordt (schrijf een tekstje 
naar de terminal die vermeld wie de gast is, kamer type en of er al dan niet ontbijt inbegrepen is) en een welkomstekstje voor de gast wanneer de kamer klaar is.
Als een gast een reservatie wil maken moet deze op een klop drukken (de blauwe knop op de nucleo) en dan gaat de reserveringstool van start. Maak het ook zo dat de gebruiker in real time 
kan communiceren met de terminal, m.a.w. dat de gebruiker user input kan leveren via de terminal, deze input wordt dan opgeslagen en gebruikt om de reservatie naar het hotel te sturen.
Als de reservatie ontvangen is moet het ledje even knipperen om aan te geven dat alles goed ontvangen is.

Laat een eerste thread de button in de gaten houden. Als deze ingedrukt wordt moet een tweede thread die de functionaliteit van de reservatie voorziet in gang gezet worden. Dit is een thread
die een site zoals booking.com voorstelt; deze is dus niet gelinkt aan 1 specifiek hotel. Deze mag niet in gang gezet worden als de button niet ingedrukt geweest is. Dan moet de gebruiker
alle details ingeven via de terminal en wordt de reservatie naar het juiste hotel gestuurd via een mail of queue. 
Kies zelf hoeveel hotels je wilt aanmaken, maar maak er minstens 2 en zorg dat er minstens 1 hotel a.d.h.v een queue werkt en 1 a.d.h.v een mail. Per hotel moet er een thread gemaakt
worden die de reservatie van de queue of mail haalt, deze toevoegt aan z'n eigen database en de kamer klaarmaakt ENKEL ALS er nog ccapaciteit is. Zijn er geen kamers vrij dan wordt de
reservatie geweigerd. Specifieer daarom bij het maken van een hotel object welke kamercapaciteit die heeft. (extra: maak verschillende kamer types - single, twin, suite, etc. - aan.)
Een alles goed doorgekomen is en de kamer klaar is mag het ledje knipperen.
Als extraatje kan er ook een thread gemaakt worden die af en toe een gast terug uit checkt uit een bepaald hotel. Dit kan a.d.h.v. een FIFO principe of random.

*/

#include "mbed.h"
#include <iostream>
#include "src/reservation.h"
#include "src/hotel.h"

// Threads
Thread reservationMaker_t;
Thread marriott_t;
Thread ibis_t;
Thread hilton_t;
Thread checkButton_t;
Thread checkOut_t;

// Mails en queues
Mail<Reservation, 5> ibis_m;
Queue<Reservation, 4> hilton_q;
Queue<Reservation, 3> marriott_q;

// Mutex
Mutex mutex;

// Flags
EventFlags event_flags;
#define FLAG_IBIS (1UL << 0)
#define FLAG_HILTON (1UL << 1)
#define FLAG_MARRIOTT (1UL << 2)
#define FLAG_RESERVATIONS (1UL << 3)

// Button en LED
DigitalIn button(BUTTON1);
DigitalOut led(LED1);

// Declaratie van de hotel objecten
Hotel marriott("Marriott", 5, 5, 5);
Hotel ibis("Ibis", 10, 15, 5);
Hotel hilton("Hilton", 15, 20, 25);

// variabel om de stand van de knop bij te houden
bool button_down = false;
int ibisReservations = ibis.getNumberOfReservations();
int marriottReservations = marriott.getNumberOfReservations();
int hiltonReservations = hilton.getNumberOfReservations();
// Functie die checkt of de knop ingedrukt is of niet. Als deze ingedrukt is wordt de flag voor de reservaties geset zodat de klant een reservatie kan beginnen maken.
// Als de knop niet ingedrukt is kan er geprobeerd worden om een gast uit te checken, dit wordt gedaan door de checkout flag te setten.
void checkButton(void) {
    while(true){
        if(!button){
            button_down = true;
            if(button_down){
                event_flags.set(FLAG_RESERVATIONS);
                wait_ns(5000000);
            }
            
        } else {
            button_down = false;
            //event_flags.set(FLAG_CHECKOUT);
        }
    }
}

// Simpele functie om de led te togglen.
void toggleLed1(void) {
    for(int i = 0; i <= 10 ; i++){
        led =!led;
        ThisThread::sleep_for(200ms);
    }
    led = 0;
}

/*
Functie om de reservatie tool te starten.
Deze start pas wanneer de knop ingedrukt wordt. Dan wordt de flag geset en kan de reservatie van start gaan.
Eerst wordt een default object van de reservatie klasse gemaakt; deze wordt later gevuld met de gegevens die de gebruiker intypt.
er worden enkele variabelen aangemaakt om de input van de user in op te slaan.
Dan verschijnen de vragen op de terminal en kan de gebruiker deze beantwoorden. Disclaimer: via putty verschijnt de eigen getypte tekst niet op het scherm, maar deze wordt weldegelijk ontvangen.
Door de switch cases in zowel de hotel klasse als in deze functie blijft de reservatietool werken, ook als de gebruiker een ander getal ingeeft buiten de range van geaccepteerde getallen.
Dan worden alle gegevens opgeslagen in de reservatie, en wordt deze reservatie in de correcte mail of queue geplaatst. Hierbij wordt ook de flag van het juiste hotel geset zodat deze de 
"melding" van een nieuwe reservatie binnenkrijgt en deze kan beginnen verwerken.
*/
void reservationTerminal(void) {
    while(true) {
        event_flags.wait_any(FLAG_RESERVATIONS);
        Reservation newReservation1("No name", false, Reservation::singleRoom);
        int hotel = 0;
        std::string clientName= "";
        bool breakfast = 0;
        int chosenRoom = 0;
        Reservation::RoomType room = Reservation::singleRoom;
        std::cout << "Welcome on this online reservation tool!" << std::endl;
        std::cout << "In which hotel would you like to stay? Type '0' for Marriott, '1' for Ibis or '2' for Hilton: ";
        std::cin >> hotel;
        std::cout << std::endl;
        std::cout << "Please enter the name under which you would like a reservation: ";
        std::cin >> clientName;
        std::cout << std::endl;
        std::cout << "Would you like breakfast? Type '1' for yes, '0' for no: ";
        std::cin >> breakfast;
        std::cout << std::endl;
        std::cout << "What room would you like? Type '0' for single, '1' for twin or '2' for king: ";
        std::cin >> chosenRoom;
        std::cout << std::endl;
        switch (chosenRoom)
        {
        case 0:
            room = Reservation::singleRoom;
            break;
        case 1:
            room = Reservation::twinRoom;
            break;
        case 2:
            room = Reservation::kingRoom;
            break;
        default:
            room = Reservation::singleRoom;
            break;
        }
        newReservation1.setClient(clientName);
        newReservation1.setBreakfast(breakfast);
        newReservation1.setRoomType(room);
        ThisThread::sleep_for(200ms);
        std::cout << std::endl;
        std::cout << "Thank you for your reservation. Details:" << std::endl;
        std::cout << "Client: " << newReservation1.getClient() << std::endl;
        std::cout << "Room type: " << newReservation1.getRoom() << std::endl;
        std::cout << "Breakfast: " << newReservation1.getBreakfast() << std::endl;
        std::cout << std::endl;
        if (hotel == 0) {
            ThisThread::sleep_for(2s);
            marriott_q.try_put_for(Kernel::wait_for_u32_forever, &newReservation1);
            event_flags.set(FLAG_MARRIOTT);
            std::cout << "Sent reservation to Marriott!" << std::endl;
            mutex.lock();
            marriottReservations++;
            mutex.unlock();

        } else if (hotel == 1) {
            ThisThread::sleep_for(2s);
            Reservation *reservation = ibis_m.try_alloc_for(Kernel::wait_for_u32_forever);
            reservation = &newReservation1;
            ibis_m.put(reservation);
            event_flags.set(FLAG_IBIS);
            std::cout << "Sent reservation to Ibis!" << std::endl;
            mutex.lock();
            ibisReservations++;
            mutex.unlock();

        } else if (hotel == 2){
            ThisThread::sleep_for(2s);
            hilton_q.try_put_for(Kernel::wait_for_u32_forever, &newReservation1);
            event_flags.set(FLAG_HILTON);
            std::cout << "Sent reservation to Hilton!" << std::endl;
            mutex.lock();
            hiltonReservations++;
            mutex.unlock();
        } else {
            std::cout << "Error in reservation, please try again." << std::endl;
        }
        std::cout << std::endl;
        ThisThread::sleep_for(5s);
    }
}

/*
De onderstaande 3 functies werken op een gelijkaardige manier, maar zijn afhankelijk van het hotel. Zo worden de hotels gescheiden van elkaar. 
Wanneer een bepaalde flag geset staat zal het juiste hotel deze van de mail of queue halen, en deze dan toevoegen aan z'n eigen database. Als dit gelukt is (m.a.w. de kamer is beschikbaar)
zal dhet hotel de kamer klaarmaken en de gast verwelkomen. Het ledje knippert om aan te geven dat de alles goed verlopen is.
*/

void receiveReservationsMarriott(void){
    while(true){
        event_flags.wait_any(FLAG_MARRIOTT);
        Reservation * reservation;
        marriott_q.try_get_for(Kernel::wait_for_u32_forever, &reservation);
        if (marriott.addReservation(reservation)){
            marriott.prepareRoom(reservation);
            marriott.welcomeGuests(reservation->getClient());
            toggleLed1();
        }
        ThisThread::sleep_for(5s);
    }
}

void receiveReservationsHilton(void){
    while(true){
        event_flags.wait_any(FLAG_HILTON);
        Reservation * reservation;
        hilton_q.try_get_for(Kernel::wait_for_u32_forever, &reservation);
        if (hilton.addReservation(reservation)){
            hilton.prepareRoom(reservation);
            hilton.welcomeGuests(reservation->getClient());
            toggleLed1();
        }
        ThisThread::sleep_for(5s);
    }
}

void receiveReservationsIbis(void){
    while(true){
        event_flags.wait_any(FLAG_IBIS);
        Reservation * reservation = ibis_m.try_get_for(Kernel::wait_for_u32_forever);
        if (ibis.addReservation(reservation)) {
            ibis.prepareRoom(reservation);
            ibis.welcomeGuests(reservation->getClient());
            toggleLed1();
        }
        ibis_m.free(reservation);
        ThisThread::sleep_for(5s);
    }
}

/* EXTRA
Functie om gasten uit te checken. Deze selecteert een random hotel, gaat kijken of er wel gasten zijn en indien ja dan wordt er een random gast uit gecheckt.
*/

void checkOut(void) {
    while(true){
        if(ibisReservations > 0 && marriottReservations > 0 && hiltonReservations >0){
            std::cout << "Checking guest out process started" << std::endl;
            int randomHotel = 1 + static_cast <int> (rand()) / ( static_cast <int> (RAND_MAX/(3)));
            Hotel * hotel = nullptr;
            switch (randomHotel)
            {
            case 1:
                hotel = &ibis;
                mutex.lock();
                ibisReservations--;
                mutex.unlock();
                break;
            case 2:
                hotel = &marriott;
                mutex.lock();
                marriottReservations--;
                mutex.unlock();
                break;
            case 3: 
                hotel = &hilton;
                mutex.lock();
                hiltonReservations--;
                mutex.unlock();
                break;
            default:
                hotel = &ibis;
                mutex.lock();
                ibisReservations--;
                mutex.unlock();
                break;
            }
            if(hotel->getNumberOfReservations() > 0){
                int randomNumber = static_cast <int> (rand()) / ( static_cast <int> (RAND_MAX/(hotel->getNumberOfReservations())));
                hotel->checkOut(hotel->getReservation(randomNumber));
            }
        }
        ThisThread::sleep_for(200ms);
    }
}

int main() {
    std::cout << "Starting new process - Press the button to make a reservation" << std::endl;
    std::cout << "______________________________________________________________" << std::endl;
    checkButton_t.start(callback(checkButton));
    reservationMaker_t.start(callback(reservationTerminal));
    ibis_t.start(callback(receiveReservationsIbis));
    marriott_t.start(callback(receiveReservationsMarriott));
    hilton_t.start(callback(receiveReservationsHilton));
    reservationMaker_t.start(callback(checkOut));
}