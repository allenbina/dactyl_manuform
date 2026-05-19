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

<p>
<a href="pictures/IMG_3504.JPEG"><img src="pictures/IMG_3504.JPEG" width="200" alt="start of 3D printing"></a>
<a href="pictures/IMG_4025.JPEG"><img src="pictures/IMG_4025.JPEG" width="200" alt="checking the specs to figure out what i'm doing wrong"></a>
<a href="pictures/IMG_4027.JPEG"><img src="pictures/IMG_4027.JPEG" width="200" alt="still have something wrong"></a>
<a href="pictures/IMG_4029.JPEG"><img src="pictures/IMG_4029.JPEG" width="200" alt="confirming that my code is correct"></a>
</p>

<p>
<a href="pictures/IMG_4030.JPEG"><img src="pictures/IMG_4030.JPEG" width="200" alt="testing prints and still have an error"></a>
<a href="pictures/IMG_4032.JPEG"><img src="pictures/IMG_4032.JPEG" width="200" alt="printing a calibration cube"></a>
<a href="pictures/IMG_4045.JPEG"><img src="pictures/IMG_4045.JPEG" width="200" alt="found out that one of the belts was loose. problem fixed"></a>
<a href="pictures/IMG_4047.JPEG"><img src="pictures/IMG_4047.JPEG" width="200" alt="a collection of failed prints"></a>
</p>

<p>
<a href="pictures/IMG_4051.JPEG"><img src="pictures/IMG_4051.JPEG" width="200" alt="tolerances are almost perfect"></a>
<a href="pictures/IMG_4070.JPEG"><img src="pictures/IMG_4070.JPEG" width="200" alt="printing a 2 day print for the largest part"></a>
</p>

---

## Assembly

<p>
<a href="pictures/IMG_4286.JPEG"><img src="pictures/IMG_4286.JPEG" width="200" alt="testing fit of the switches"></a>
<a href="pictures/IMG_4287.JPEG"><img src="pictures/IMG_4287.JPEG" width="200" alt="left side done"></a>
<a href="pictures/IMG_4288.JPEG"><img src="pictures/IMG_4288.JPEG" width="200" alt="testing with keycaps. still needs to be hotglued"></a>
<a href="pictures/IMG_4306.JPEG"><img src="pictures/IMG_4306.JPEG" width="200" alt="hotglue for stability, also added threaded inserts"></a>
</p>

<p>
<a href="pictures/IMG_4307.JPEG"><img src="pictures/IMG_4307.JPEG" width="200" alt="two small dabs of glue for each switch"></a>
<a href="pictures/IMG_4309.JPEG"><img src="pictures/IMG_4309.JPEG" width="200" alt="playing with parts again"></a>
</p>

---

## Hand Wiring

<p>
<a href="pictures/IMG_4576.JPEG"><img src="pictures/IMG_4576.JPEG" width="200" alt="starting hand wiring"></a>
<a href="pictures/IMG_4577.JPEG"><img src="pictures/IMG_4577.JPEG" width="200" alt="adding diodes"></a>
<a href="pictures/IMG_4579.JPEG"><img src="pictures/IMG_4579.JPEG" width="200" alt="finished the switch wiring"></a>
<a href="pictures/IMG_4580.JPEG"><img src="pictures/IMG_4580.JPEG" width="200" alt="adding the chip wiring"></a>
</p>

<p>
<a href="pictures/IMG_4629.JPEG"><img src="pictures/IMG_4629.JPEG" width="200" alt="soldering the TRRS"></a>
<a href="pictures/IMG_4655.JPEG"><img src="pictures/IMG_4655.JPEG" width="200" alt="first side wired, still works"></a>
<a href="pictures/IMG_4658.JPEG"><img src="pictures/IMG_4658.JPEG" width="200" alt="testing the fit. it fits"></a>
<a href="pictures/IMG_4703.JPEG"><img src="pictures/IMG_4703.JPEG" width="200" alt="repeat on the other side"></a>
</p>

<p>
<a href="pictures/IMG_4704.JPEG"><img src="pictures/IMG_4704.JPEG" width="200" alt="other side diodes"></a>
<a href="pictures/IMG_4705.JPEG"><img src="pictures/IMG_4705.JPEG" width="200" alt="other side switches completely soldered. one is the wrong way, but i found it and fixed it"></a>
<a href="pictures/IMG_4706.JPEG"><img src="pictures/IMG_4706.JPEG" width="200" alt="wire the MCU"></a>
</p>

---

## Firmware

<p>
<a href="pictures/IMG_4710.JPEG"><img src="pictures/IMG_4710.JPEG" width="200" alt="first attempt at firmware"></a>
<a href="pictures/IMG_4971.JPEG"><img src="pictures/IMG_4971.JPEG" width="200" alt="somewhat of a success with firmware. this will take a long time"></a>
<a href="pictures/IMG_4989.JPEG"><img src="pictures/IMG_4989.JPEG" width="200" alt="one week later, successful firmware, but missing features"></a>
<a href="pictures/IMG_4990.JPEG"><img src="pictures/IMG_4990.JPEG" width="200" alt="playing with settings"></a>
</p>

<p>
<a href="pictures/IMG_4993.JPEG"><img src="pictures/IMG_4993.JPEG" width="200" alt="mostly finished product"></a>
</p>

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
