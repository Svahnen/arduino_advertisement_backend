# arduino_advertisement_backend
This is the backend for displaying advertisements on displays driven by arduinos.

## Improvements
Kör en delete på alla "new" vi kör
:Done

- Rensa kod som inte används
:Done

- Fånga ctrl-c signal för att avsluta print loopen
:Done

- skapa compile och run Shell skripts
:Done

- Visa ett error meddelande och stäng av om användaren inte skickar in några argument vid start

- Ändra namn och text i menyer till att återspegla ads istället för arrayer, så användaren kan ange tex delete ad nr 1, istället för array 0

- Bryt ner programmet i mindre filer.

- Kolla om vi inte skulle få något minne?(om null osv) vid allokering med "new"

- Fixa så ctrl-c avbryter loopen direkt

- Fixa till variabel och funktions namn så att dom blir tydligare

### Bugs

- Det går att komma in i delete menyn även när det inte finns några ads

- Oändlig loop när man skriver text i sum rutan

- Ctrl-C fångas i alla menyer, inte bara i print loopen: done

- Programmet stängs av om man skriver in text i huvudmenyn

- ctr-c stänger ibland av loopen direkt, trots att den INTE är i slutet av sin sleep timer, Ctrl-C avbryter nuvarande sleep, så om det finns flera sleep kvar i loopen får man ändå vänta