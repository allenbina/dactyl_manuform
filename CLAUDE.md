# Dactyl Manuform Keyboard

## Hardware
- **Controller**: Raspberry Pi Pico (RP2040) — VCC-GND YD RP2040 variant, one per half
- **Split**: Serial UART, TX=GP17, RX=GP16 (both halves use same pins)
- **Matrix**: 6 rows × 6 cols per half = 36 positions, 31 physical keys per side (62 total)
- **Diode direction**: ROW2COL
- **Left half (DACTL)** row pins: GP2–GP7, col pins: GP8, GP9, GP10, GP12, GP13, GP14
- **Right half (DACTR)** row pins: GP2–GP7, col pins: GP8, GP9, GP10, GP11, GP12, GP13

## Current firmware
- **Vial QMK** — compiled and ready to flash
- Flash files (repo root):
  - `dactyl_manuform_custom_vial_left.uf2` — for left half (handedness baked in)
  - `dactyl_manuform_custom_vial_right.uf2` — for right half (handedness baked in)
- Keyboard source: `vial_qmk_firmware/keyboards/dactyl_manuform_custom/`
- Old KMK firmware (no longer active): `pog_firmware/DACTL/` and `pog_firmware/DACTR/`

## Vial QMK build notes
- Serial driver must be set to `vendor` (RP2040 PIO) in `keyboard.json` — bitbang does not work
- `EE_HANDS` is defined in `keymaps/vial/config.h` — do NOT use `split.handedness.method` in `keyboard.json` (not valid in this QMK schema)
- Build machine requires `libnewlib-arm-none-eabi` for ARM C stdlib headers
- vial-qmk repo cloned to `~/git/vial-qmk`

## Rebuilding firmware
```bash
export PATH="$PATH:$HOME/.local/bin"
cd ~/git/vial-qmk

# Build left (save before building right — both overwrite same .build output file)
make dactyl_manuform_custom:vial:uf2-split-left
cp .build/dactyl_manuform_custom_vial.uf2 ~/git/dactyl_manuform/dactyl_manuform_custom_vial_left.uf2

# Build right
make dactyl_manuform_custom:vial:uf2-split-right
cp .build/dactyl_manuform_custom_vial.uf2 ~/git/dactyl_manuform/dactyl_manuform_custom_vial_right.uf2
```

## Flashing
1. Hold BOOTSEL, plug in USB, release — `RPI-RP2` drive appears
2. Copy the correct UF2 for each half:
   ```bash
   # Left half
   cp ~/git/dactyl_manuform/dactyl_manuform_custom_vial_left.uf2 /media/$USER/RPI-RP2/
   # Right half
   cp ~/git/dactyl_manuform/dactyl_manuform_custom_vial_right.uf2 /media/$USER/RPI-RP2/
   ```
3. No EEPROM step needed — handedness is baked into each UF2
4. Either half can be plugged into USB

## Repo layout
```
dactyl_manuform_custom_vial_left.uf2    # Flash to left half
dactyl_manuform_custom_vial_right.uf2   # Flash to right half
dactyl_manuform_custom_vial.uf2         # Generic (no handedness — do not use directly)
vial_qmk_firmware/
  keyboards/dactyl_manuform_custom/
    keyboard.json                 # Board config (serial driver: vendor, RP2040)
    keymaps/vial/
      config.h                   # EE_HANDS, Vial UID, unlock combo
      keymap.c                   # Default keymap (reprogrammable via Vial)
      rules.mk
      vial.json
pog_firmware/
  DACTL/                         # Old KMK left half firmware
  DACTR/                         # Old KMK right half firmware
stls/                            # 3D print files
pictures/                        # Build photos
videos/                          # Build videos
```
