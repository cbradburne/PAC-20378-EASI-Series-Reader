# PAC-20378-EASI-Series-Reader
Reader for PAC 20378 Easi Series

Needed:
3.3v Arduino Pro Micro (ATmega32U4 3.3V/8MHz) - https://www.amazon.co.uk/gp/product/B07DF5CPTB <br>
12k resistor between Arduino pins VCC (3.3v) and RX, as a pullup resistor.

Wiring:
```
    12v PSU   -     Arduino     -     20378
      GND     -       GND       -       -V
              -       RX0       -       SIG
              -                 -       +V
              -                 -       VCA
```


Tests for 3 consecutive identical results, outputs code via keyboard and carriage return.
