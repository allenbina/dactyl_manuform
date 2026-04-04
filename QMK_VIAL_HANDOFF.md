# QMK / Vial migration — handoff notes

Use this on your **Linux server** (toolchain + `vial-qmk` already set up). It summarizes what we figured out in-repo and what still needs doing.

---

## Repo layout (this project)

| Path | Purpose |
|------|---------|
| `vial_qmk_firmware/keyboards/dactyl_manuform_custom/` | Keyboard definition + Vial keymap — **copy or symlink** this tree into your `vial-qmk` clone under `keyboards/dactyl_manuform_custom/` |
| `pog_firmware/DACTL/pog.json`, `DACTR/pog.json` | Ground truth for **matrix coord map** and **column pin difference** between halves |
| `pictures/IMG_4705.JPEG` | Underside wiring photo (diode / row-column buses) |
| `CLAUDE.md` | Hardware pin summary, split UART pins, build one-liners |

**Output UF2s** (after build) are usually copied to repo root as:

- `dactyl_manuform_custom_vial_left.uf2`
- `dactyl_manuform_custom_vial_right.uf2`

---

## Hardware (unchanged)

- **MCU**: RP2040 (VCC-GND YD RP2040), one per half  
- **Split**: UART — notes say **TX = GP17, RX = GP16** (both halves use the same pin names)  
- **Matrix**: 6×6 electrical positions per half, **31 physical keys** per side  
- **Left columns**: GP8, GP9, GP10, GP12, GP13, **GP14**  
- **Right columns**: GP8, GP9, GP10, **GP11**, GP12, GP13 (single pin difference vs left)  
- **Rows**: GP2–GP7 both sides  

**Serial pin:** `keyboard.json` now uses `"pin": "GP17"` (vendor/PIO driver), matching the physical TX wiring. This was corrected from an earlier incorrect value of `GP1`.

---

## Why Vial looked wrong and keys did not match

### 1. `LAYOUT` matrix vs Pog `coordMap` (main issue)

Pog/KMK does **not** use a naive “finger row = matrix row, left-to-right = rising column” mapping. The **`coordMap`** in `pog_firmware/DACTL/pog.json` (full split layout on the master) encodes which **flat matrix index** (0–35 per half, `row*6+col`) belongs at each **visual** position.

**Left finger block (from `coordMap`):** the first visual row maps to indices `0, 6, 12, 18, 24, 30` — i.e. **one matrix column**, stepping through **matrix rows**. That matches:

`flat_index = visual_row + 6 * visual_col`

Standard row-major labeling would be:

`flat_index = visual_row * 6 + visual_col`

So the current QMK `keyboard.json` entries that use `matrix: [visual_row, visual_col]` for labels like `Lxy` are **inconsistent** with how the keyboard is actually wired **unless** you reinterpret labels so that `matrix` row/col are **swapped** from “visual row/col” (i.e. QMK `(row,col)` must satisfy `row*6+col = vr + 6*vc` for visual row `vr`, visual col `vc` — which works out as **QMK row = visual column, QMK col = visual row** for the main grid; verify with the full `coordMap` table).

**Thumb cluster in Pog:** indices like `016`, `022`, `028`, … land in **matrix columns 4–5**, rows 2–5 — **not** the template that puts thumbs only on matrix rows 4–5, columns 0–3.

**Right half:** `DACTR/pog.json` `coordMap` is **not** the same pattern as the left (e.g. first row uses decreasing indices along one column). You cannot copy the left half’s QMK matrix block and only add +6 to rows.

**Action on Linux:** Rebuild `layouts.LAYOUT.layout` in `keyboard.json` (and keep `vial.json` in sync) by **deriving every key’s `matrix: [r,c]` from Pog’s `coordMap`:**

- Parse each three-digit string as a decimal integer `idx` (see `coordmaphelper.py` / `pog.py` `convert_coord_mapping`).
- For **left** half indices `0–35`: `row = idx // 6`, `col = idx % 6`.
- For **right** half in the **combined** DACTL `coordMap`, indices `36–71` (if present) map to right controller rows 0–5 as `row = (idx-36)//6`, `col = (idx-36)%6` — **confirm** against your exact `coordMap` numbering.

Trust **`coordMap` + working KMK** over a generic Dactyl diagram.

### 2. Diode direction (photo vs JSON)

`IMG_4705` was described as **diode cathode (band) on the row bus**. In QMK, that often corresponds to **`COL2ROW`**, not `ROW2COL`.

Repo + Pog both say **`ROW2COL`**. If the photo interpretation is correct, firmware may need **`COL2ROW`** instead — worth verifying on **one switch** (band toward row vs column) against [QMK diode direction](https://docs.qmk.fm/#/feature_matrix?id=diode-direction).

### 3. Vial “not mirrored”

The `x`/`y` fields in `keyboard.json` are a **flat ortho grid** for Vial’s UI. The right block is offset to the right; it does not need to be a geometric mirror of a sculpted Dactyl. Wrong **matrix** assignments make keys “not match” Vial; mirroring is mostly cosmetic once matrix is correct.

### 4. `EE_HANDS` / split UF2

Left vs right is baked into **separate** `uf2-split-left` / `uf2-split-right` builds (`config.h` has `EE_HANDS`). That does not fix a wrong `LAYOUT` matrix.

---

## Pog firmware: where pins are defined

- **Normal boot:** `code.py` → `POGKeyboard` in `kb.py` → **`pog.json`** on that half’s CIRCUITPY drive.  
- **Matrix pins** come from `rowPins` / `colPins` in **`pog_firmware/DACTL/pog.json`** and **`pog_firmware/DACTR/pog.json`**, not from a right-side `main.py`.  
- **`DACTL/main.py`** (explicit `row_pins` / `col_pins`) is **not** used by `code.py`; treat it as **legacy / alternate**, not the live Pog path.

UART: `splitPinA` / `splitPinB` in each `pog.json` (left `16`/`17`, right `17`/`16`).

---

## Bootloader without opening the case (`QK_BOOT`)

In `vial_qmk_firmware/.../keymaps/vial/keymap.c`, **layer `_FN`** places **`QK_BOOT`** in several positions so **hold `MO(_FN)` + tap** reboots to **UF2 (RPI-RP2)**:

| Side | Base-layer role (approx.) |
|------|---------------------------|
| Left | Tab, Esc, `-` (bottom row pinky), Bksp (outer thumb) |
| Right | Bksp (top row outer), `=` (`KC_EQL`), Enter (inner thumb, 4-key row) |

**First time:** you still need **one** physical BOOTSEL flash of a build that contains this keymap. After that, prefer **Fn + one of the above** for routine updates.

**Split:** Bootloader runs only on the **USB-connected** half; flash each half’s `.uf2` when updating both.

Do not strip all `QK_BOOT` entries in Vial or you lose software bootloader until the next wired flash.

---

## Building on Linux (typical flow)

1. Sync keyboard sources into your `vial-qmk` tree, e.g.:

   ```bash
   rsync -a --delete /path/to/dactyl_manuform/vial_qmk_firmware/keyboards/dactyl_manuform_custom/ \
     /path/to/vial-qmk/keyboards/dactyl_manuform_custom/
   ```

2. From `vial-qmk` root (adjust paths to your server):

   ```bash
   cd /path/to/vial-qmk
   make dactyl_manuform_custom:vial:uf2-split-left
   cp .build/dactyl_manuform_custom_vial.uf2 /path/to/dactyl_manuform/dactyl_manuform_custom_vial_left.uf2

   make dactyl_manuform_custom:vial:uf2-split-right
   cp .build/dactyl_manuform_custom_vial.uf2 /path/to/dactyl_manuform/dactyl_manuform_custom_vial_right.uf2
   ```

3. Dependencies (if anything fails): `arm-none-eabi-gcc`, `libnewlib-arm-none-eabi`, build essentials, and QMK/Vial env setup you already used before.

**Windows:** possible but annoying (ARM toolchain, path length, WSL). Linux server is the path of least resistance.

---

## Optional next steps (priority order)

1. ~~Recompute **`keyboard.json` `LAYOUT`** `matrix` entries from **`DACTL/pog.json` `coordMap`**~~ — **Done.** All matrix coords recomputed from both `coordMap` files; `vial.json` updated to match. UF2s rebuilt.
2. ~~Align **split UART pin** in `keyboard.json`~~ — **Done.** Fixed to `GP17` (vendor/PIO driver).
3. Confirm **`diode_direction`** against the physical photo (`IMG_4705`). Repo says `ROW2COL`; verify the diode band is on the column bus, not the row bus.
4. Flash both halves, test matrix in Vial — press each key and confirm it lights up in the correct position. Adjust keymap for comfort.

---

## Hand-drawn wiring sketch

**Not required** if you trust KMK + `coordMap` as correct. Use a sketch if KMK ever felt wrong on specific keys or after a matrix fix something still misbehaves.

---

*Generated for continuing work on the Linux build host; source state matches this repo’s `vial_qmk_firmware` and Pog configs as of the last edit to `keymap.c`.*
