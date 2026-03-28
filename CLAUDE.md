# Dactyl Manuform Keyboard

## Hardware
- **Controller**: Raspberry Pi Pico (RP2040) — VCC-GND YD RP2040 variant, one per half
- **Split**: Serial UART, TX=GP17, RX=GP16 (both halves use same pins)
- **Matrix**: 6 rows × 6 cols per half = 36 positions, 31 physical keys per side (62 total)
- **Diode direction**: ROW2COL
- **Left half (DACTL)** row pins: GP2–GP7, col pins: GP8, GP9, GP10, GP12, GP13, GP14
- **Right half (DACTR)** row pins: GP2–GP7, col pins: GP8, GP9, GP10, GP11, GP12, GP13

## Current firmware
- Located in `pog_firmware/DACTL/` and `pog_firmware/DACTR/`
- Uses **KMK** (CircuitPython) configured via **POG** (pog.json)
- Each half runs independently; left half stores the combined keymap

## Goal
Convert to **Vial QMK** so the keymap can be edited live via the Vial app.
- Target: `keyboards/dactyl_manuform_custom/` inside a local Vial QMK repo
- Key layout will be reprogrammed in Vial after flashing — no need to port the existing keymap exactly
- Flash via UF2 drag-and-drop (hold BOOTSEL on RP2040, drag .uf2 to the drive)

## Repo layout
```
pog_firmware/
  DACTL/   # Left half KMK firmware
  DACTR/   # Right half KMK firmware
stls/      # 3D print files
pictures/  # Build photos
videos/    # Build videos
```
