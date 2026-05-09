# Dactyl Manuform — hand-wired, 3D-printed split ergo keyboard

A custom Dactyl Manuform split mechanical keyboard. Hand-wired from raw switches, an RP2040 microcontroller, and a 3D-printed shell I printed on my own Ender 3. Firmware is Vial-QMK. It's my daily driver.

This is a build log and a reference, not a product page. If you're considering your own Dactyl, hopefully the photos and the things that went wrong are useful.

![Finished keyboard](pictures/IMG_4993.JPEG)

## Build at a glance

| | |
|---|---|
| **Layout** | Dactyl Manuform 5×6, two-halves split |
| **Switches** | 62 total (31 per side), hand-wired |
| **Controller** | Raspberry Pi Pico / VCC-GND YD-RP2040 (one per half) |
| **Inter-half link** | TRRS, serial UART (TX=GP17, RX=GP16) |
| **Matrix** | 6 rows × 6 cols per half, ROW2COL diode direction |
| **Diodes** | 1N4148, 100-pack from AliExpress |
| **Shell** | 3D-printed on Ender 3, fitted with M3 heat-set inserts |
| **Firmware** | Vial-QMK (currently); previously KMK and POG firmware |
| **Layout config** | [pog_firmware/](./pog_firmware/), [vial_qmk_firmware/](./vial_qmk_firmware/) |

Detailed hardware reference: [`CLAUDE.md`](./CLAUDE.md).
Flash instructions: [`FLASH_INSTRUCTIONS.md`](./FLASH_INSTRUCTIONS.md).

## What I started with

Things I already had:

- **Ender 3** 3D printer (microcenter, $100, used here and there for a couple of years before this project)
- A working knowledge of Fusion 360 (graduated from Tinkercad once it stopped cutting it)
- Soldering irons (Pinecil + a cheap variety) and accessories — wick, flux, wire, solder, alcohol, wire strippers
- Some firmware and Python experience

I'd never hand-wired a keyboard before. I'd never printed something this big before. So this was the first project where everything had to come together at once.

## Parts I ordered

Mostly AliExpress:

- Black Pi Pico clones with USB-C (one per half)
- 1N4148 diodes (100-pack — you only need ~62 but you will lose some)
- Keycaps
- TRRS connectors and a TRRS cable
- M3 heat-set inserts and assorted M3 screws
- Rainbow ribbon cable for the matrix wiring
- Silicone rubber bumpers
- Wrist rests

## The build, with photos

### 1. Calibration and the printer fight

Before I could print the case, the printer had to actually be reliable. This was the first part of the project that humbled me.

![Checking specs](pictures/IMG_3504.JPEG)
*Checking specs — figuring out what was wrong*

![Still wrong](pictures/IMG_4025.JPEG)
*Still wrong*

![Confirming code](pictures/IMG_4029.JPEG)
*Confirming the gcode was correct, ruling out software*

![Calibration cauliflower](pictures/IMG_4032.JPEG)
*Printing a calibration cauliflower (which is exactly what it sounds like)*

![Failed prints](pictures/IMG_4047.JPEG)
*A small museum of failed prints*

![Loose belt fixed](pictures/IMG_4045.JPEG)
*Found one of the X-axis belts was loose. After tightening: tolerances were almost perfect*

### 2. Printing the case

The largest part is a two-day print. There's not much to do during a 48-hour print except check on it occasionally.

![Two-day print](pictures/IMG_4070.JPEG)
*Day one of two on the largest part*

![Switch fit test](pictures/IMG_4286.JPEG)
*Test-fitting switches into the printed case*

![Left side complete](pictures/IMG_4287.JPEG)
*Left side fully populated with switches*

![Threaded inserts and hot glue](pictures/IMG_4306.JPEG)
*Threaded inserts installed; hot glue used for switch stability*

![Two dabs of glue](pictures/IMG_4307.JPEG)
*Two small dabs per switch — enough to stop them rotating in the socket without making future swaps impossible*

### 3. Hand wiring

This is the part that takes the longest and where you really commit. Once the diodes are soldered in, you don't get to undo it.

![Hand wiring begins](pictures/IMG_4576.JPEG)
*Starting hand-wiring*

![Adding diodes](pictures/IMG_4577.JPEG)
*Adding diodes — ROW2COL orientation, cathode toward the column*

![Switch wiring complete](pictures/IMG_4579.JPEG)
*Switch matrix wired*

![Chip wiring](pictures/IMG_4580.JPEG)
*Wiring the RP2040 to the matrix*

![TRRS jack](pictures/IMG_4629.JPEG)
*Soldering the TRRS jack for the inter-half link*

![First side works](pictures/IMG_4655.JPEG)
*First side wired — and it works*

![Test fit](pictures/IMG_4658.JPEG)
*Test-fitting it back into the case to make sure I hadn't soldered any wires too tight*

![Right side begins](pictures/IMG_4703.JPEG)
*Repeating the whole process on the right side*

![Right side switches done](pictures/IMG_4705.JPEG)
*Right side switches soldered. One was the wrong way. Found and fixed.*

![Right MCU wiring](pictures/IMG_4706.JPEG)
*Wiring the right-half MCU*

### 4. Firmware

I tried POG firmware first (good for prototyping a Pi Pico keyboard), then KMK, then settled on Vial-QMK.

![First firmware attempt](pictures/IMG_4710.JPEG)
*First attempt at firmware*

![Partial firmware success](pictures/IMG_4971.JPEG)
*Some success. Going to take a while to get this right.*

![One week later](pictures/IMG_4989.JPEG)
*One week later — firmware boots cleanly, missing some features*

![Tweaking](pictures/IMG_4990.JPEG)
*Playing with settings, layers, and key behaviour*

![Mostly finished](pictures/IMG_4993.JPEG)
*Mostly finished. Daily driver from this point on.*

## What I'd do differently

A few things I'd change if I started again:

- **Print the case before ordering the keycaps.** I bought caps based on what I thought would fit and ended up swapping them out once the case was done. Ordering caps last would have saved a small amount of money and time.
- **Buy two MCUs and pre-flash them.** The "left half" / "right half" handedness flag confused me on the first flash. Doing both halves in the same session before assembly would have saved a lot of "is this side dead, or is the firmware wrong?" debugging.
- **Use ribbon cable everywhere instead of single-conductor.** I started with single conductor wire and switched to rainbow ribbon partway through. The ribbon is much cleaner and easier to debug visually.
- **Heat-set inserts before any wiring.** Doing them after meant heating the iron near already-soldered joints, which I should have avoided.
- **Cosmos.** Looking back I'd consider [Cosmos](https://ryanis.cool/cosmos/) for the case generator next time — Dactyl-Manuform is great but Cosmos's parametric flow is more flexible.

## Layout, layers, behaviour

The Vial layout JSON and the original POG layout config live in this repo:

- [`vial_qmk_firmware/`](./vial_qmk_firmware/) — current Vial-QMK firmware source
- [`pog_firmware/`](./pog_firmware/) — earlier POG firmware (kept for reference)
- [`dactyl_manuform_custom_vial.uf2`](./dactyl_manuform_custom_vial.uf2), [`*_left.uf2`](./dactyl_manuform_custom_vial_left.uf2), [`*_right.uf2`](./dactyl_manuform_custom_vial_right.uf2) — flashable firmware images
- [`stls/`](./stls/) — case STLs

## More

- Hardware reference (pin map, matrix, diode orientation): [`CLAUDE.md`](./CLAUDE.md)
- Flashing instructions for Vial-QMK: [`FLASH_INSTRUCTIONS.md`](./FLASH_INSTRUCTIONS.md)
- Migration / handoff notes: [`QMK_VIAL_HANDOFF.md`](./QMK_VIAL_HANDOFF.md)
- Build videos: [`videos/`](./videos/) — debugging, first firmware success, end-of-side milestones
- Build photos: [`pictures/`](./pictures/) — full set, including ones not in this README

If you're building one yourself and have questions, open an issue.
