---
title: 'O AFE Firmware'
media_order: '18-10-05 18-59-28 7188-1.jpg,17-12-24-14-02-17-6044-720x340.jpg'
---

AFE Firmware to alternatywne oprogramowanie dla urządzeń zbudowanych na chip’ie ESP8266 lub ESP8285 jak na przykład [Sonoff](https://www.smartnydom.pl/przelacznik-sonoff/?target=_blank), [Shelly](https://www.smartnydom.pl/wlacznik-wifi-shelly-1/?target=_blank), [GeelCreit](https://www.smartnydom.pl/geekcreit-4ch-afe-firmware/?target=_blank), ... (długa lista), czy we [własnych konstrukcjach](https://www.smartnydom.pl/bezprzewodowy-czujnik-temperatury-oraz-wilgotnosci?target=_blank). Wykorzystuję je w swoich instalacjach do różnych zastosowań.

![](18-10-05%2018-59-28%207188-1.jpg)

Dlaczego nie używam oryginalnego oprogramowania, które dostarczają producenci wraz z urządzeniami? Otóż w niektórych przypadkach urządzenie  + oryginalne oprogramowanie oznacza ograniczone możliwości lub konieczność używania jednej gamy produktów. Ktoś kto używał przykładowo oryginalnego oprogramowania dostarczonego z urządzeniem Sonoff wie, że z oryginalnej aplikacji można korzystać tylko z produktami Sonoff. Otrzymuje się  funkcjonalności tylko te, które dostarcza producent. Nie podłączy się do niej TV, „inteligentnej” żarówki innej firmy, kamery IP itp. Gdy nazbiera się w domu trochę tych sprzętów, okazuje się, że konieczne jest posiadanie X aplikacji do sterowania różnymi urządzeniami, a w dodatku urządzenia różnych producentów nie „gadają” ze sobą. Nie da się nimi wszystkimi sterować jako jedną całością.

Dlatego głównie korzystam z rozwiązań, które są na tyle otwarte, aby można było nimi sterować z jednego systemu, jednej aplikacji, aby każde urządzenie niezależnie od producenta mogło „porozumiewać” się z innymi urządzeniami. Oznacza to tyle, że oprogramowanie w tych urządzenia powinno udostępniać standardowy i łatwy w dostępie mechanizm sterowania nimi. To daje możliwość podłączania tych urządzeń do bardziej lub mniej zaawansowanych systemów automatyki, inteligentnych domów, biur, jak kto woli, a nie bycie skazanym na X aplikacji.

![](17-12-24-14-02-17-6044-720x340.jpg)

AFE Firmware jest takim oprogramowaniem. Urządzenie z zainstalowanym AFE Firmware może być sterowany przez systemy do automatyki np. openHAB, Domoticz, Domotiga, HomeAssistant i pewnie przez wiele innych systemów do automatyki. Napisane jest z myślą o układzie WiFi serii ESP, który coraz częściej spotykany jest w komercyjnych produktach. Dodatkowo jest bardzo tani i łatwy w konstruowaniu niemalże, jak z klocków własnych urządzeń.