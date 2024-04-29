# Lichtschranke Zeitmessung
Arduino Projekt zur Zeitmessung in der Leistungsdiagnoatik für Sportvereine.

## Beschreibung
Das Ardunio Projekt soll in der Leistungsdiagnostik in Sportvereinen einsetzbar sein. Dazu kann die Zeit die zwischem dem Durchqueren der ersten und dem Durchquerden der zweiten Lichtschranke liegt gemessen werden. Die Zweit wird auf einer großen 7-Segemtanzeige dargestellt.

## Bedienungsanleitung

## Bauteilliste
Die folgenden Komponenten werden zur Umsetzung des Projektes benötigt:

 | Bauteil | Anzahl | Bezugsquelle |
 |--------|--------|--------|
 | Arduino Nano | 1 | https://www.reichelt.de/arduino-kompatibles-nano-board-atmega328-mini-usb-ard-nano-v3-p225690.html?&trstct=pos_5&nbc=1|
 | Lichtschranke | 2 | https://www.amazon.de/STBTECH-Lichtschrankensensor-Innenwandmontage-Reflektierender-induktionsabstand/dp/B0972PF2T4/ref=asc_df_B0972PF2T4/?tag=googshopde-21&linkCode=df0&hvadid=526405873369&hvpos=&hvnetw=g&hvrand=539370072361777504&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9044391&hvtargid=pla-1392124218174&mcid=b2fd8cd87eab375cb11de7d9dfb03125&th=1 |
 | WS2821b LED Streifen (Neopixel) | 29 LED | https://www.amazon.de/LOAMLIN-WS2812B-adressierbarer-RGB-LED-Streifen-Leiterplatte/dp/B0956C7KFR/ref=sr_1_1_sspa?crid=2Z06RC1AOLHKI&dib=eyJ2IjoiMSJ9.XVBM7wzVhek5OCRflE0i_PiF5qHyP5ZZL-x03iwqRRC1pt8Cy1BiuQqcF4724HcdbMcNvWoGyalWJOcx1K-IU6z_p7WQJ1jXUbkxZGlgTLyW9r1JMmENc8PpIh2bbSEUlRdM4m-U2RmO-U5rEoPVla6IK5YTzHkz9s2mXxUhwvC0AVj8gm_xN1GnE6u8uDg104fPRFagXIOxDxKSR8TWbt7fIYp4PRD2i0uA3chLtyewDaeXWBCrocNdtquORGoJWeUOgDBCMw4JX89lE4g1ISnEyPdRhPzhXfmcj5hfDCs.GlEH1pEP2d-p3W-0irTc_mszkJwKoMRUytUEx8wNYt4&dib_tag=se&keywords=ws2812b+led+strip&qid=1714398025&sprefix=ws%2Caps%2C209&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1 |
 | Spannungsregler (Step Up) | 1 | https://www.amazon.de/Converter-Spannungswandler-LAOMAO-Netzteil-Kompatibel/dp/B0B932BR7V/ref=sr_1_3?__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=VF7Z23ENKMKW&dib=eyJ2IjoiMSJ9.-FHGCeOeXh3k2PAJMw6WqXSTJsq3c941_S4cF9mQvUKbGND_lcHgVPIxZNm-TfulSsAzviVpQMFzeAvYiDl6s9qncVkT8lbjXbEYRCIluqpNhTGFF1e8aWJFFAtmuAr8mEhSo-6skwok8nUaaIdO4dHIxoKgZR0SrJLvwHlgtb5ysVKDwHAuL2EOFrtM3cge8HQXbYqwSiEVB5zcaZTpM9pyP4-CHwXFj7tLnPSJn1E.dc7jMicEJea_Gvnzh2DYWvOECyyW3L8AoqAQQe4ut38&dib_tag=se&keywords=step+up+arduino&qid=1714397799&sprefix=step+up+arduino%2Caps%2C125&sr=8-3 |
 | LogikPegelwandler | 1 | https://www.reichelt.de/entwicklerboards-ttl-logic-level-converter-3-3v-5v-debo-llc-3-3-5-p282702.html?search=logic |
 | Piezo Buzzer | 1 | https://www.amazon.de/3-Pack-3V-24V-Electric-Buzzer-Soundkabel/dp/B0761VW19B/ref=sr_1_4_sspa?__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=28LM5CV408MT3&dib=eyJ2IjoiMSJ9.xUDHJRBvkY200I4DydFo4YxOAqDk62pCFa6dH3WvcSzpUoogFXtpi8kqB19DC2pKnxAaiATS2tRgAdJTho1PPM1USqdRRKuenaPRQDtd7wR-3pav03whAztmifR0ybOZCSiWRt4GZwm6MoLA-0QG0OcK32SkFpC3SpBDmYuHca-3HsYsLsh-b9Xinsywo74lYbz54U_FVg1SOCxWxoJ4l2kzHhxzQpiWGIVcdITA_V9qQmB9OZRLP4_hTQlh132aSzF74rLOYSMdrxo4yo6zV7ZdiPlmM9vIH__mZH3KAII.zLXVZiWq1UgluNF-1ryR42n9a7N7SiEucM2lmGwV1e8&dib_tag=se&keywords=Piezo+Buzzer&qid=1714397928&sprefix=piezo+buzzer%2Caps%2C159&sr=8-4-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1 |
 | Mirco USB Buchse | 1 | https://www.amazon.de/DAOKAI-Adapter-Konverter-Breakout-Netzteil/dp/B09WQTR1H3/ref=sr_1_4?__mk_de_DE=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=3BGHN51JGT4J0&dib=eyJ2IjoiMSJ9.sB2h0WwKfKUTvxuc6bdYbMuAIaKIVkJMoWVreOXqgWbC8kK7P7f8TwSfmovkQODEZoJ9w_Q00oSz5pi9fD3cB0hdDILWPYp1Sg-D6bOgDmQv-xqPFGNcdXdv38CIGg8pTJXuUTqdecOxNm43cWYHfI9isPOvtPnJ0KXURkbacme6CsE-FoaG7NY3pVTbLL1fAkutF6ButVbIQU65auOc_LmvMDriNfbML7alW7Zp5_g.1bzd2MXYaCDacBxuL7KeKZHA13exYeG6lM-kILg78zU&dib_tag=se&keywords=micro+usb+buchse&qid=1714397972&sprefix=micro+usb+buchse%2Caps%2C142&sr=8-4 |
 | Schalter I/O | 1 | https://www.reichelt.de/wippenschalter-rund-1x-ein-aus-ws-r13-112-aaaa-p105442.html?PROVID=2788&gad_source=1&gclid=CjwKCAjwuJ2xBhA3EiwAMVjkVNzGZk13DS73n4yUYqaJXG7UAzn4JqyFZP0ZancVtsJTK8jqIQxabhoCp68QAvD_BwE  |
 | Schalter I/O/I | 1 | https://www.reichelt.de/wippenschalter-rund-1x-ein-aus-ein-ws-r13-112-daaa-p105445.html?&nbc=1&trstct=lsbght_sldr::108238 |
 | Taster | 1 | https://www.reichelt.de/drucktaster-0-1a-24vac-1x-ein-11-9-1mm-rt-rafi-107-301-p110863.html?&trstct=vrt_pdn&nbc=1  |
 | XLR Buchsen | 2 | https://www.reichelt.de/xlr-einbaustecker-3-polig-vernickelte-kontakte-xlr-3es-n-p40795.html?&nbc=1&trstct=lsbght_sldr::40796  |
 | XLR  Stecker | 2 | https://www.reichelt.de/xlr-stecker-3-polig-vernickelte-kontakte-xlr-3st-n-p40793.html?PROVID=2788&gad_source=1&gclid=Cj0KCQjwn7mwBhCiARIsAGoxjaJW0WPVTsOX5vq6f-K7-zICsXRPtCALhdti8s_yL0cJHXgOMuCXFeMaAuZYEALw_wcB  |
 | Lochrasterplatine |  | https://www.reichelt.de/lochrasterplatine-hartpapier-unbeschichtet-160x100mm-hpr-160x100-p8638.html?&trstct=pol_1&nbc=1 |
 | Kupferlitze |  | https://www.reichelt.de/de/de/kupferlitze-isoliert-10-m-1-x-0-14-mm-rot-litze-rt-p10297.html?PROVID=2788&gad_source=1&gclid=Cj0KCQjwir2xBhC_ARIsAMTXk84KqTFvcXyeQH3hf22GCGcPDzRsjltFxCcgHX8_l7VtcMEkfIx-o3waAr6kEALw_wcB&&r=1 |
 | Kupferschaltdraht |  | https://www.reichelt.de/kupferschaltdraht-verzinnt-0-6-mm-40-m-zinn-0-6-40m-p190453.html?&trstct=pol_2&nbc=1 |
 | Stativgewinde | 2 | https://www.amazon.de/-/en/ruthex-Threaded-Insert-Bushings-Ultrasonic/dp/B09MTS6ZZQ?th=1  |
 | Stativ | 2 | https://www.amazon.de/Hama-Star-Stativ-Tragetasche-Schwarz-Braun/dp/B0000WXD16/ref=asc_df_B0000WXD16/?tag=googshopde-21&linkCode=df0&hvadid=310005946786&hvpos=&hvnetw=g&hvrand=4052493414548415523&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9068265&hvtargid=pla-756317659112&psc=1&mcid=5fd900d919b535e0a350c2399254b13d&th=1&psc=1&tag=&ref=&adgrpid=62402075995&hvpone=&hvptwo=&hvadid=310005946786&hvpos=&hvnetw=g&hvrand=4052493414548415523&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9068265&hvtargid=pla-756317659112  |

 Es handelt sich bei den Links um **keine** Affiliate-Links. Ich erhalten keinerlei Provision.

## Montageanleitung

## Quellen

Vielen Dank an shiura, für das bereitstellen der STL-Files zum Erstellen des Displays. Weitere Informationen finden sich auf Thingivers (https://www.thingiverse.com/thing:5170654). Die Modelle wurden von mir noch leicht editiert und um Befestigungslöcher ergänzt.

## Lizens
Das Projekt wurde unter der CC BY-NC-SA 4.0 DEED Lizens veröffentlicht (https://creativecommons.org/licenses/by-nc-sa/4.0/).