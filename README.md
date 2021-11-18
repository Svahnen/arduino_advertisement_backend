# arduino_advertisement_backend

###Improvements
Kolla om vi måste köra en delete på alla "new" vi kör.

### To do: 
- Felhantering där det inte finns (input, argument(Felhantering om porten inte finns eller om man skickar in något konstigt) minnes allokering med "new" om vi inte skulle få något minne?(Kolla om null) osv
:Done

- Rensa kod som inte används
:Done

- Fånga ctrl c signal för att avsluta programmet

- Shell skript

- Fixa till namn så att det blir mer tydligt

- Kommentarer

- Ändra texter som skrivs ut om något skulle vara otydligt eller icke relevant

- Kolla om det är några funktioner som är för stora som man kan dela upp (flytta ut i andra filer), dubbel kod?




På felhanteringen angående "öppna connection" eller skriva till filen, den skulle man typ kunna lägga i en if-sats för om något skulle hända så returnera den inte true tex