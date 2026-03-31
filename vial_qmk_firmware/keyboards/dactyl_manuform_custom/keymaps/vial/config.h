// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// ── Vial ────────────────────────────────────────────────────────────────────
// Unique 8-byte UID — generated randomly for this keyboard.
// Re-generate with: python3 -c "import os; print(', '.join(hex(b) for b in os.urandom(8)))"
#define VIAL_KEYBOARD_UID {0x4A, 0xC3, 0x1F, 0xE7, 0x82, 0x5B, 0xD9, 0x06}

// Security: require two keys to be held simultaneously before Vial can make
// changes.  Keys are identified by (row, col) in the full 12-row matrix.
// Here: L00 = matrix [0,0] and L10 = matrix [1,0] (Tab + Esc on left half).
#define VIAL_UNLOCK_COMBO_ROWS {0, 1}
#define VIAL_UNLOCK_COMBO_COLS {0, 0}

// Number of layers exposed to Vial
#define DYNAMIC_KEYMAP_LAYER_COUNT 2

// Handedness stored in EEPROM — set once per half with qmk flash -bl uf2-split-left/right
#define EE_HANDS
