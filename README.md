# Dactyl Manuform

My first large 3D printed project, handwired keyboard, ergo keyboard. I had some experience in 3D printing small things, soldering, firmware and python.

**Controller:** Raspberry Pi Pico (RP2040), one per half  
**Firmware:** Vial QMK (started with KMK/Pog, switched to QMK)  
**Matrix:** 62 keys, hand-wired with 1N4148 diodes  
**Connection:** Split via TRRS, serial UART  

---

## What I Already Had

- **3D printer** — Ender 3, got it from Microcenter for $100 a couple years ago and used it here and there. Recently I was learning Fusion 360 because TinkerCAD was not cutting it for anything serious.
- **Soldering irons** — Pinecil and cheap variety
- **Accessories** — wick, flux, wire, solder, alcohol, wire strippers

---

## 3D Printing

![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_3504.JPEG)

checking the specs to figure out what i'm doing wrong
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4025.JPEG)

still have something wrong
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4027.JPEG)

confirming that my code is correct
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4029.JPEG)

testing prints and still have an error
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4030.JPEG)

printing a calibration cube
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4032.JPEG)

found out that one of the belts was loose. problem fixed
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4045.JPEG)

a collection of failed prints
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4047.JPEG)

tolerances are almost perfect
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4051.JPEG)

printing a 2 day print for the largest part
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4070.JPEG)

---

## Assembly

testing fit of the switches
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4286.JPEG)

left side done
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4287.JPEG)

testing with keycaps. still needs to be hotglued
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4288.JPEG)

hotglue for stability, also added threaded inserts
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4306.JPEG)

two small dabs of glue for each switch
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4307.JPEG)

playing with parts again
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4309.JPEG)

---

## Hand Wiring

starting hand wiring
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4576.JPEG)

adding diodes
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4577.JPEG)

finished the switch wiring
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4579.JPEG)

adding the chip wiring
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4580.JPEG)

soldering the TRRS
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4629.JPEG)

first side wired, still works
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4655.JPEG)

testing the fit. it fits
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4658.JPEG)

repeat on the other side
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4703.JPEG)

other side diodes
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4704.JPEG)

other side switches completely soldered. one is the wrong way, but i found it and fixed it
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4705.JPEG)

wire the MCU
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4706.JPEG)

---

## Firmware

first attempt at firmware
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4710.JPEG)

somewhat of a success with firmware. this will take a long time
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4971.JPEG)

one week later, successful firmware, but missing features
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4989.JPEG)

playing with settings
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4990.JPEG)

mostly finished product
![](https://github.com/allenbina/dactyl_manuform/blob/main/pictures/IMG_4993.JPEG)

Started with KMK (Python-based, via Pog), eventually moved to Vial QMK for better features and keymap GUI support.

---

## Parts

Ordered from AliExpress:

- Black Pi Pico with USB-C (x2)
- 1N4148 diodes (100 pack)
- Keycaps
- TRRS connectors + cable
- Rainbow ribbon cable
- Assorted M3 screws
- M3 heat set inserts
- Silicone rubber bumps
- Wrist rests

Case generated with [Cosmos](https://ryanis.cool/cosmos/).

---

## What I'd Do Differently

- Pick a layout generator earlier — spent too much time on manual Fusion 360 work
- Use ribbon cable from the start instead of individual wires
- Test firmware before wiring the second half
- Start with QMK instead of KMK — the tooling and community support are much better
