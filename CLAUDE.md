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
- Flash file: `dactyl_manuform_custom_vial.uf2` (repo root)
- Keyboard source: `vial_qmk_firmware/keyboards/dactyl_manuform_custom/`
- Old KMK firmware (no longer active): `pog_firmware/DACTL/` and `pog_firmware/DACTR/`

## Vial QMK build notes
- Serial driver must be set to `vendor` (RP2040 PIO) in `keyboard.json` — bitbang does not work
- `EE_HANDS` is defined in `keymaps/vial/config.h` — do NOT use `split.handedness.method` in `keyboard.json` (not valid in this QMK schema)
- Build machine requires `libnewlib-arm-none-eabi` for ARM C stdlib headers
- vial-qmk repo cloned to `/home/mediafront/git/vial-qmk`

## Rebuilding firmware
```bash
export PATH="$PATH:/root/.local/bin"
export QMK_HOME=/home/mediafront/git/vial-qmk
cd /home/mediafront/git/vial-qmk
qmk compile -kb dactyl_manuform_custom -km vial
cp .build/dactyl_manuform_custom_vial.uf2 ~/git/dactyl_manuform/
```

## Flashing
1. Hold BOOTSEL, plug in USB, release — `RPI-RP2` drive appears
2. Copy the UF2:
   ```bash
   cp ~/git/dactyl_manuform/dactyl_manuform_custom_vial.uf2 /media/$USER/RPI-RP2/
   ```
3. Repeat for both halves
4. Set EEPROM handedness (one-time per half):
   ```bash
   qmk flash -kb dactyl_manuform_custom -km vial -bl uf2-split-left   # left half
   qmk flash -kb dactyl_manuform_custom -km vial -bl uf2-split-right  # right half
   ```
5. Always plug **left half** into USB — it is the master

## Repo layout
```
dactyl_manuform_custom_vial.uf2   # Compiled flash file (ready to use)
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
