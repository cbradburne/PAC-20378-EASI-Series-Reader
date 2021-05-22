# PAC-20378-EASI-Series-Reader
Reader for PAC 20378 Easi Series

Needed:
3.3v Arduino Pro Micro (ATmega32U4 3.3V/8MHz) - https://www.amazon.co.uk/gp/product/B07DF5CPTB <br>
12k resistor <br>
TBC - 2N2222 transistor

Wiring:
```
    12v PSU   -     Transistor (2N2222)     -     Arduino     -     20378
      GND     -              TBC            -       GND       -       -V
              -              TBC            -       RX0       -       SIG
              -              TBC            -                 -       +V
              -              TBC            -                 -       VCA
              -              TBC            -                 -
```
Will add transistor pull-down for LED (VCA).

Tests for 3 consecutive identical results, outputs code via keyboard and carriage return.
