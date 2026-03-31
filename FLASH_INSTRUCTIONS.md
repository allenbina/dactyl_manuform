# Dactyl Manuform Custom — Vial QMK Flash Instructions

## Overview

- MCU: RP2040 (Raspberry Pi Pico / VCC-GND YD-RP2040)
- Split keyboard, two halves (DACTL = left, DACTR = right)
- Firmware: Vial-QMK (Vial fork of QMK)
- Handedness: EEPROM (`EE_HANDS`) — set once per half, described below

---

## 1. Prerequisites

Install the following on your build machine:

```bash
# Python 3.10+ and pip
sudo apt install python3 python3-pip git

# QMK CLI
pip3 install --user qmk

# Initialise QMK (downloads ARM/RP2040 toolchain automatically)
qmk setup
```

> **Vial-QMK vs upstream QMK**: Vial requires its own fork of QMK.
> Do NOT use `qmk setup` with the upstream repo for Vial support.
> Follow the steps in section 2 instead.

---

## 2. Clone the Vial-QMK Fork

```bash
git clone https://github.com/vial-kb/vial-qmk.git --recurse-submodules
cd vial-qmk

# Make sure submodules are up to date
make git-submodule
```

---

## 3. Copy the Keyboard Files

From the root of the `vial-qmk` checkout:

```bash
# Assuming this repo is at ~/git/dactyl_manuform
cp -r ~/git/dactyl_manuform/vial_qmk_firmware/keyboards/dactyl_manuform_custom \
      keyboards/dactyl_manuform_custom
```

Verify the structure:

```
keyboards/dactyl_manuform_custom/
├── keyboard.json
└── keymaps/
    └── vial/
        ├── config.h
        ├── keymap.c
        ├── rules.mk
        └── vial.json
```

---

## 4. Serial Pin Note (Important — Read Before Building)

The `keyboard.json` uses **GP1 as a single-wire half-duplex serial pin**
(`SERIAL_DRIVER = vendor`, i.e. RP2040 PIO) for simplicity.

Your hardware was wired with **GP16 (RX) / GP17 (TX) full-duplex UART**.

**Option A — Use GP1 half-duplex (easier, requires re-wiring)**
Wire a single wire between GP1 on both halves.  No changes to `keyboard.json` needed.

**Option B — Use GP16/GP17 full-duplex (matches your current wiring)**
Edit `keyboard.json`:

1. Remove the `"serial"` block under `"split"`:
   ```json
   "serial": { "pin": "GP1" }
   ```
2. Add a `"usart"` block instead:
   ```json
   "usart": {
       "pin": "GP16"
   }
   ```
3. Add to `keymaps/vial/rules.mk`:
   ```makefile
   SERIAL_DRIVER = usart
   ```
4. Add to `keymaps/vial/config.h`:
   ```c
   #define SERIAL_USART_FULL_DUPLEX
   #define SERIAL_USART_TX_PIN GP17
   #define SERIAL_USART_RX_PIN GP16
   ```

---

## 5. Build the Firmware

Pre-built UF2 files are included in the repo root — you can skip this step unless you've made changes.

To rebuild from source, from inside `vial-qmk/`:

```bash
# Build left-side firmware (handedness baked in)
make dactyl_manuform_custom:vial:uf2-split-left
cp .build/dactyl_manuform_custom_vial.uf2 ~/git/dactyl_manuform/dactyl_manuform_custom_vial_left.uf2

# Build right-side firmware (handedness baked in)
make dactyl_manuform_custom:vial:uf2-split-right
cp .build/dactyl_manuform_custom_vial.uf2 ~/git/dactyl_manuform/dactyl_manuform_custom_vial_right.uf2
```

> Note: each command overwrites `.build/dactyl_manuform_custom_vial.uf2` — save the left one before building the right.

---

## 6. Flash via UF2 (BOOTSEL Method)

Two separate `.uf2` files are provided — one per half. Flash each to the correct side.

**Left half:**

1. Hold the **BOOTSEL** button on the left RP2040 board.
2. While holding BOOTSEL, plug it into USB.
3. Release BOOTSEL. A USB drive named `RPI-RP2` will appear.
4. Copy the left UF2:

```bash
cp dactyl_manuform_custom_vial_left.uf2 /media/$USER/RPI-RP2/
# The board reboots automatically.
```

**Right half:**

Repeat the same steps using the right UF2:

```bash
cp dactyl_manuform_custom_vial_right.uf2 /media/$USER/RPI-RP2/
```

> **No EEPROM step needed.** The handedness is compiled into each firmware file — there is no separate EE_HANDS flashing step. Either half can be plugged into USB.

---

## 8. Verify Split Communication

1. Plug the left half into USB only (no right USB connection).
2. Connect the two halves with the TRRS/TRS cable (or the serial wire on GP1).
3. Open a text editor and press keys on both halves — all keys should register.

If right-half keys do not register, check:
- The serial pin wiring.
- That `EE_HANDS` was set correctly on both halves.
- That the correct serial driver is configured (see Section 4).

---

## 9. Configure the Keymap with Vial

1. Download Vial from https://get.vial.today
2. Open Vial and plug in the left half.
3. Vial should detect "Dactyl Manuform Custom" automatically.
4. Use the GUI to remap keys, create macros, set tap-dance, etc.
5. All changes are saved to the keyboard's EEPROM — no reflash needed.

### Unlock the keyboard for editing

When Vial first connects, it may ask you to hold the unlock combo:
- **Hold Tab + Esc simultaneously** (matrix [0,0] and [1,0]) for 5 seconds.

This is the `VIAL_UNLOCK_COMBO` defined in `config.h`.

---

## 10. Troubleshooting

| Symptom | Likely cause | Fix |
|---|---|---|
| Only left half works | Serial pin mismatch or wrong driver | Re-check Section 4 |
| Keys on wrong side | Wrong UF2 flashed to wrong half | Re-flash with correct _left/_right UF2 |
| Vial does not recognise keyboard | `vial.json` UID mismatch | Regenerate UID in `config.h` |
| Build error: unknown pin | Wrong QMK/Vial version | Use latest `vial-qmk` main branch |

---

## Quick Reference

```
Flash left:   copy dactyl_manuform_custom_vial_left.uf2  → RPI-RP2 (BOOTSEL mode)
Flash right:  copy dactyl_manuform_custom_vial_right.uf2 → RPI-RP2 (BOOTSEL mode)
Rebuild:      make dactyl_manuform_custom:vial:uf2-split-left  (then uf2-split-right)
Vial:         https://get.vial.today
```
