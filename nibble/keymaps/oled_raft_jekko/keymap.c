/* Copyright 2021 Jonathan Law, Jay Greco
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Original: j-inc's kyria keymap
 */
#include QMK_KEYBOARD_H
#include "animation_frames.h"

enum layer_names { _BASE, _FN1, _FN2, _FN3 };
enum custom_keycodes { PROG = SAFE_RANGE, ENCDR_TOG, ART_TOG };

enum encoder_layer { DEFAULT_ENCODER, MEDIA_ENCODER};
#define ENCODER_LAYER_SIZE 2;


// Macro variables
bool     is_art_mode           = false;
bool     is_alt_tab_active     = false;
uint16_t alt_tab_timer         = 0;
bool     muted                 = false;
bool     deafened              = false;
uint16_t current_encoder_layer = DEFAULT_ENCODER;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    //,-------------------------------------------------------------------,
    //|[ ]|[====]iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii████████iii|
    //|;;;,---,---,---,---,---,---,---,---,---,---,---,---,---,-------,---,
    //|...|esc| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | + | ' | <-    | ~ |
    //,---,---'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-----,---,
    //|⚫ | Tab | Q | W | E | R | T | Y | U | I | O | P | [ | ] |  \  |del|
    //,---,-----',--',--',--',--',--',--',--',--',--',--',--',--------,---,
    //|F1 | fn1  | A | S | D | F | G | H | J | K | L | ; | " |  Enter |pu |
    //,---,------'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'----,---,---,
    //|F2 | Shift  | Z | X | C | V | B | N | M | < | > | ? |Shift | ↑ |pd |
    //|---,----,---',--'-,'---'---'-,--',--'---'--,'--,'--,'--,---,---,---,
    //|F3 |ctrl|win |alt | Space    |Ent| <-      |alt|fn2|ctl| ← | ↓ | → |
    // ---'----'----'----'----------'---'---------'---'---'---'---'---'---'

    [_BASE] = LAYOUT_iso(
                KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_GRV,
        ENCDR_TOG,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_DEL,
        ART_TOG,  MO(_FN1), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_NUHS,  KC_PGUP,
        KC_F15,  KC_LSFT, KC_BSPC, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_RSFT, KC_UP,   KC_PGDN,
        KC_F16,  KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, MO(_FN2), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    //,-------------------------------------------------------------------,
    //|[ ]|[====]iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii████████iii|
    //|;;;,---,---,---,---,---,---,---,---,---,---,---,---,---,-------,---,
    //|...|   |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|       |   |
    //,---,---'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-----,---,
    //|⚫ | Caps|   | ↑ |   |   |   |   |   |   |   |   |   |   |     |   |
    //,---,-----',--',--',--',--',--',--',--',--',--',--',--',--------,---,
    //|   |      | ← | ↓ | → |   |   |   |   |   |   |   |   |        |   |
    //,---,------'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'----,---,---,
    //|   |        |   |   |   |   |   |   |   |   |   |   |Shift |   |   |
    //|---,----,---',--'-,'---'---'-,--',--'---'--,'--,'--,'--,---,---,---,
    //|   |    |    |    |          |   | del     |   |   |   |   |   |   |
    // ---'----'----'----'----------'---'---------'---'---'---'---'---'---'

    [_FN1] = LAYOUT_iso(
                _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_DEL,  KC_INS,
        _______, KC_CAPS, _______, KC_UP, _______, _______, _______, _______, _______, KC_UP, _______, _______, _______, _______,          _______,
        _______, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, KC_HOME,
        _______, _______, KC_DEL, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,                            _______,                   _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT
    ),

    //,-------------------------------------------------------------------,
    //|[ ]|[====]iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii████████iii|
    //|;;;,---,---,---,---,---,---,---,---,---,---,---,---,---,-------,---,
    //|...|   |w/m|   |   |   |   |   |   |   |   |   |   |   |       |   |
    //,---,---'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-----,---,
    //|⚫ |     |   |   |   |   |   |   |   |   |   |   |   |   |     |   |
    //,---,-----',--',--',--',--',--',--',--',--',--',--',--',--------,---,
    //|   |      |   |   |   |   |   |   |   |   |   |   |   |        |   |
    //,---,------'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'----,---,---,
    //|   |        |   |   |   |   |   |   |   |   |   |   |      |   |   |
    //|---,----,---',--'-,'---'---'-,--',--'---'--,'--,'--,'--,---,---,---,
    //|   |    |    |    |          |   | del     |   |   |   |   |   |   |
    // ---'----'----'----'----------'---'---------'---'---'---'---'---'---'

    [_FN2] = LAYOUT_iso(
        _______,  CG_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    //,-------------------------------------------------------------------,
    //|[ ]|[====]iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii████████iii|
    //|;;;,---,---,---,---,---,---,---,---,---,---,---,---,---,-------,---,
    //|...|   |   |   |   |   |   |   |   |   |   |   |   |   |       |   |
    //,---,---'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-----,---,
    //|⚫ |     |   |   |   |   |   |   |   |   |   |   |   |   |     |   |
    //,---,-----',--',--',--',--',--',--',--',--',--',--',--',--------,---,
    //|   |      |   |   |   |   |   |   |   |   |   |   |   |        |   |
    //,---,------'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'-,-'----,---,---,
    //|   |        |   |   |   |   |   |   |   |   |   |   |      |   |   |
    //|---,----,---',--'-,'---'---'-,--',--'---'--,'--,'--,'--,---,---,---,
    //|   |    |    |    |          |   |         |   |   |   |   |   |   |
    // ---'----'----'----'----------'---'---------'---'---'---'---'---'---'

    [_FN3] = LAYOUT_iso(
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______)

};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (is_art_mode){
            if (clockwise) {  // Decrease Brush Size
                tap_code(KC_RBRC);
            } else {  // Increase Brush Size
                tap_code(KC_LBRC);
            }
    } else {
        switch (current_encoder_layer) {
            case DEFAULT_ENCODER:
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
            case MEDIA_ENCODER:
                if (clockwise) {
                    tap_code(KC_MNXT);
                } else {
                    tap_code(KC_MPRV);
                }
                break;
            default:
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
        }
    }
    return true;
}

#ifdef OLED_ENABLE
#define IDLE_FRAME_DURATION 200  // Idle animation iteration rate in ms

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_0; }


// Decompress and write a precompressed bitmap frame to the OLED.
// Documentation and python compression script available at:
// https://github.com/nullbitsco/squeez-o

static void renderRaft(void) {
    /* Print current mode */
    oled_set_cursor(0, 0);
        oled_write_raw_P(raft, sizeof(raft));

}

void oled_task_user(void) {
    renderRaft();

    // uint8_t n = get_current_wpm();
    // char    wpm_counter[6];
    // wpm_counter[5] = '\0';
    // wpm_counter[4] = '0' + n % 10;
    // wpm_counter[3] = '0' + (n /= 10) % 10;
    // wpm_counter[2] = '0' + n / 10;
    // wpm_counter[1] = '0';
    // wpm_counter[0] = '>';
    // oled_write_ln(wpm_counter, false);
}

#endif

// Cycle through the different encoder layers.
void toggleEncoder(void) { current_encoder_layer = (current_encoder_layer + 1) % ENCODER_LAYER_SIZE; }

// Toggle art mode.
void toggleArt(void){
    is_art_mode = !is_art_mode;
}

// Animate tap
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case PROG:
            if (record->event.pressed) {
                rgblight_disable_noeeprom();
#ifdef OLED_ENABLE
                oled_off();
#endif
                bootloader_jump();
            }
            break;
        case ENCDR_TOG:
            if (record->event.pressed) {
                toggleEncoder();
            }
            break;

        case ART_TOG:
            if (record->event.pressed) {
                toggleArt();
            }
        default:
            break;
    }

    return true;
}

void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}
