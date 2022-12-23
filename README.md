# final-exercise-embedded-os

## Opdracht

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

## Oplossing

Zie code in main.cpp en src map.
