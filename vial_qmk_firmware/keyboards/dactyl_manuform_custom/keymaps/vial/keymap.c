// SPDX-License-Identifier: GPL-2.0-or-later
// Dactyl Manuform Custom — Vial keymap
// Base layer: QWERTY
// Layer 1:    transparent (for Vial GUI customisation)

#include QMK_KEYBOARD_H

// Layer indices
enum layers {
    _QWERTY = 0,
    _FN,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /*
     * QWERTY — Layer 0
     *
     * Left half                                         Right half
     * ,------------------------------------------.     ,-------------------------------------------.
     * | Tab  |  Q   |  W   |  E   |  R   |  T   |     |  Y   |  U   |  I   |  O   |  P   | Bksp  |
     * |------+------+------+------+------+------|     |------+------+------+------+------+-------|
     * | Esc  |  A   |  S   |  D   |  F   |  G   |     |  H   |  J   |  K   |  L   |  ;   |  '    |
     * |------+------+------+------+------+------|     |------+------+------+------+------+-------|
     * | Shift|  Z   |  X   |  C   |  V   |  B   |     |  N   |  M   |  ,   |  .   |  /   | Shift |
     * |------+------+------+------+------+------|     |------+------+------+------+------+-------|
     * | Ctrl |  `   |  \   |  [   |  ]   |  -   |     |  =   | Left | Down |  Up  | Right| Ctrl  |
     * `------+------+------+------+------+------'     `------+------+------+------+------+-------'
     *                  ,---+------+------+-----.     ,-----+------+------+--.
     *                  |LGui| LAlt | Del  |     |     |     | RAlt |RGui  |
     *                  |    |      +------+-----|     |-----+------+      |
     *                  |    |      | Enter| MO1 |     | MO1 | Space|      |
     *                  `----+------+------+-----'     `-----+------+------'
     */
    [_QWERTY] = LAYOUT(
        // Left main rows (row 0..3, 6 cols each = 24 keys)
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
        KC_LCTL, KC_GRV,  KC_BSLS, KC_LBRC, KC_RBRC, KC_MINS,
        // Left thumb cluster (row 4: 3 keys, row 5: 4 keys = 7 keys)
        KC_LGUI, KC_LALT, KC_DEL,
        KC_ENT,  MO(_FN), KC_SPC,  KC_BSPC,

        // Right main rows (row 6..9, 6 cols each = 24 keys)
        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_EQL,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RCTL,
        // Right thumb cluster (row 10: 3 keys, row 11: 4 keys = 7 keys)
        KC_RALT, KC_RGUI, KC_DEL,
        KC_ENT,  MO(_FN), KC_SPC,  KC_BSPC
    ),

    /*
     * FN — Layer 1
     *
     * Bootloader (UF2): hold MO(_FN) and tap any QK_BOOT below — reboots to RPI-RP2
     * for flashing without BOOTSEL. Placed redundantly in case matrix/Vial mapping is off.
     *
     *   Left: Tab, Esc, bottom-outer thumb (Bksp), and bottom-row minus slot.
     *   Right: top Bksp, = key (often -_/physically), bottom-inner thumb (Enter).
     */
    [_FN] = LAYOUT(
        // Left main
        QK_BOOT, _______, _______, _______, _______, _______,
        QK_BOOT, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, QK_BOOT,
        // Left thumb
        _______, _______, _______,
        _______, _______, _______, QK_BOOT,

        // Right main
        _______, _______, _______, _______, _______, QK_BOOT,
        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,
        QK_BOOT, _______, _______, _______, _______, _______,
        // Right thumb
        _______, _______, _______,
        QK_BOOT, _______, _______, _______
    ),
};
// clang-format on
