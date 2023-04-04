# Arduino Shift Register with Latch EMULATOR

This is a BU2040F chip emulator that runs on Arduino UNO / Mini PRO

# Files

### There are two Sketchs:
### Shift_register-BU2040
The sketch to upload to a production Arduino
### ShiftTester
A simple sketch to download to a second Arduino and generate CLK + DATA

## How it works

BU2040F needs 2 streams of data, CLK and DATA
first clock is Q11, next Q10..... and last is Q0
Data needs to be rised first and when rise clock to HIGH, read data bit and store in a internal storage, when clock fall LOW data must be LOW as well on first 11 bits.
When clock fall LOW and data is HIGH, that's means it's time to latch and send la storage bits to outputs.

## About this project

This proyect is under construction!
This proyect is under construction!
This proyect is under construction!
This proyect is under construction!

This Shift Register is used on Technics Audio equipment and was develop by ROHMS industries but is discontinued! Some resellers has it as brand new old stock, but its to expensive, something like U$S 10 each.

Maybe a replacement is the new BU2090F that is still on production state. 

```
