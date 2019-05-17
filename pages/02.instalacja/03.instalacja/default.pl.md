---
title: 'Instrukcja instalacji Sonoff'
---

Poniższy przykład opisuje, jak wgrać AFE Firmware do urządzenia Sonoff Basic za pomocą NodeMCU Flasher

**Krok 1.** Ściągamy najnowszą wersję AFE Firmware, do pobrania tutaj.

**Krok 2.** Rozbieramy obudowę, aby dostać się do środka. Widzimy tutaj 5 otworów pod przyciskiem. Te 5 otworów to złącza, które wykorzystamy do załadowania firmware

Sonoff rozebrany

> Zalecam wlutowanie gniazda do przełącznika Sonoff, w które będą wkładany przewody wychodzące z konwertera TTL.

**Krok 3.** Podłączamy przewody konwertera USB-TTL z przełącznikiem. Należy zwrócić szczególną uwagę, który kabel podłączyć, z którym otworem w przełączniku i konwerterze.

* RX w adapterze łączymy z TX w urządzeniu
* TX w adapterze łączymy z RX w urządzeniu


**Krok 4.** Konfigurujemy NodeMCU  Flasher

W zakładce *Advanced* ustawiamy następujące parametry:

 


Ustawienia wgrywania

! Starsze wersje Sonoff (z przed maj 2017) mogą wymagać SPI Mode : QIO.  Sugeruje najpierw spróbować wgrać z DOUT, jeśli nie pójdzie lub urządzenie będzie się wieszać, działać niestabilnie to wgrać z SPI Mode: QIO.

W zakładce Config wybieramy
* w drugim wierszu firmware wciskając ikonę zębatki – po prawej stronie.
* ustawiamy adres wgrywania: 0x00000
* ustawiamy checkbox’y, jak pokazane po lewej stronie


**Krok 5.** Wgrywamy firmware. Przechodzimy do zakładki Operations.



Ważne: wprowadzamy przełącznik Sonoff w tryb wgrywania firmware.

* Kabel USB musi być odłączony od komputera
* Wciskamy i trzymamy przycisk w przełączniku Sonoff
* Wkładamy do złącza USB w komputerze kabel USB, do którego podpięty jest konwerter USB-TTL (patrz Krok 3), a do którego podpięty jest przełącznik Sonoff.
* Puszczamy przycisk w przełączniku Sonoff
* Teraz przełącznik Sonoff powinien być w trybie wgrywania firmware.

Wybieramy odpowiedni port COM, żółta ramka oraz wciskamy przycisk Flash. Powinniśmy zaobserwować wgrywanie się firmware, jak na poniższym przykładzie. Jeśli po wciśnięciu przycisku Flash nic się nie dzieję, to trzeba sprawdzić inny port COM.


Zakończenie wgrywania można rozpoznać po zaznaczonych w żółtych ramkach elementach.



W tym momencie instalacja AFE Firmware  powinna być zakończona.

!!!! Pierwsze uruchomienie może trwać do 1-2 min ze względu na formatowanie pamięci oraz ustawianie konfiguracji początkowej