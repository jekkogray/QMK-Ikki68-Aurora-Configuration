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
        RGB_TOG, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, KC_HOME,
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
        _______,  AG_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
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

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

uint32_t anim_timer         = 0;
uint32_t anim_sleep         = 0;
uint8_t  current_idle_frame = 0;

bool tap_anim        = false;
bool tap_anim_toggle = false;

// Decompress and write a precompressed bitmap frame to the OLED.
// Documentation and python compression script available at:
// https://github.com/nullbitsco/squeez-o
#    ifdef USE_OLED_BITMAP_COMPRESSION
static void oled_write_compressed_P(const char *input_block_map, const char *input_block_list) {
    uint16_t block_index = 0;
    for (uint16_t i = 0; i < NUM_OLED_BYTES; i++) {
        uint8_t bit          = i % 8;
        uint8_t map_index    = i / 8;
        uint8_t _block_map   = (uint8_t)pgm_read_byte_near(input_block_map + map_index);
        uint8_t nonzero_byte = (_block_map & (1 << bit));
        if (nonzero_byte) {
            const char data = (const char)pgm_read_byte_near(input_block_list + block_index++);
            oled_write_raw_byte(data, i);
        } else {
            const char data = (const char)0x00;
            oled_write_raw_byte(data, i);
        }
    }
}
#    endif

static void render_anim(void) {
    // Idle animation
    void animation_phase(void) {
        if (!tap_anim) {
            current_idle_frame = (current_idle_frame + 1) % NUM_IDLE_FRAMES;
            uint8_t idx        = abs((NUM_IDLE_FRAMES - 1) - current_idle_frame);
#    ifdef USE_OLED_BITMAP_COMPRESSION
            oled_write_compressed_P(idle_block_map[idx], idle_frames[idx]);
#    else
            oled_write_raw_P(idle_frames[idx], NUM_OLED_BYTES);
#    endif
        }
    }

    // Idle behaviour
    if (get_current_wpm() != 000) {  // prevent sleep
        oled_on();
        if (timer_elapsed32(anim_timer) > IDLE_FRAME_DURATION) {
            anim_timer = timer_read32();
            animation_phase();
        }
        anim_sleep = timer_read32();
    } else {  // Turn off screen when timer threshold elapsed or reset time since last input
        if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
            oled_off();
        } else {
            if (timer_elapsed32(anim_timer) > IDLE_FRAME_DURATION) {
                anim_timer = timer_read32();
                animation_phase();
            }
        }
    }
}

static void print_status_narrow(void) {
    /* Print current mode */
    oled_set_cursor(0, 0);
    if (keymap_config.swap_lalt_lgui) {
        oled_write_raw_P(mac_logo, sizeof(mac_logo));
    } else {
        oled_write_raw_P(windows_logo, sizeof(windows_logo));
    }

    // oled_set_cursor(0, 3);

    // switch (get_highest_layer(default_layer_state)) {
    //     case _QWERTY:
    //         oled_write("QWRTY", false);
    //         break;
    //     case _GAMING:
    //         oled_write("GAMES", false);
    //         break;
    //     default:
    //         oled_write("UNDEF", false);
    // }

    // oled_set_cursor(0, 5);

    // /* Print current layer */
    // oled_write("LAYER", false);

    // oled_set_cursor(0, 6);

    // switch (get_highest_layer(layer_state)) {
    //     case _QWERTY:
    //         oled_write("Base ", false);
    //         break;
    //     case _GAMING:
    //         oled_write("Games", false);
    //         break;
    //     case _RAISE:
    //         oled_write("Raise", false);
    //         break;
    //     case _LOWER:
    //         oled_write("Lower", false);
    //         break;
    //     case _ADJUST:
    //         oled_write("Adj  ", false);
    //         break;
    //     default:
    //         oled_write("Undef", false);
    // }

    // /* caps lock */
    // oled_set_cursor(0, 8);
    // oled_write("CPSLK", led_usb_state.caps_lock);

    // /* KEYBOARD PET RENDER START */

    // render_luna(0, 13);

    // /* KEYBOARD PET RENDER END */
}

void oled_task_user(void) {
    render_anim();

    oled_set_cursor(0, 14);
    uint8_t n = get_current_wpm();
    char    wpm_counter[6];
    wpm_counter[5] = '\0';
    wpm_counter[4] = '0' + n % 10;
    wpm_counter[3] = '0' + (n /= 10) % 10;
    wpm_counter[2] = '0' + n / 10;
    wpm_counter[1] = '0';
    wpm_counter[0] = '>';
    oled_write_ln(wpm_counter, false);
    print_status_narrow();
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
#ifdef OLED_ENABLE
    // Check if non-mod
    if ((keycode >= KC_A && keycode <= KC_0) || (keycode >= KC_TAB && keycode <= KC_SLASH)) {
        if (record->event.pressed) {
            // Display tap frames
            tap_anim_toggle = !tap_anim_toggle;
#    ifdef USE_OLED_BITMAP_COMPRESSION
            oled_write_compressed_P(tap_block_map[tap_anim_toggle], tap_frames[tap_anim_toggle]);
#    else
            oled_write_raw_P(tap_frames[tap_anim_toggle], NUM_OLED_BYTES);
#    endif
        }
    }
#endif

    switch (keycode){
        case ENCDR_TOG:
            if (record->event.pressed) {
                toggleEncoder();
            }
            break;

        case ART_TOG:
            if (record->event.pressed) {
                toggleArt();
            }
            break;
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
