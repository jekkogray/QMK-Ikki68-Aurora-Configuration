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

/* KEYBOARD PET START */


led_t led_state;

/* settings */
#define MIN_WALK_SPEED 10
#define MIN_RUN_SPEED 50

/* advanced settings */
#define LUNA_FRAME_DURATION 230 // how long each frame lasts in ms
#define LUNA_SIZE 32 // number of bytes in array. This is how many pixels wide your image is. max is 1024 but would apply if line wrapping and not segmeting image and on 128x64 size screen, 512 is max on 128x32.

/* Setup Variables */
uint8_t current_frame = 0;
bool isSneaking = false;
bool isJumping = false;
bool showedJump = true;
int jump_height = 0;

// Loop to create line by line rendering for Horizontal display
// Input is oled_render_image(how many rows tall, how many pixels wide, what to render, X pos, Y pos, Frame offset)
	void oled_render_image(int lines, int px, const char render_line[][px], int X_pos, int Y_pos, int frame) {
	for (uint8_t i = 0; i <= (lines-1); i++){
            oled_set_cursor(X_pos, Y_pos + i);
			oled_write_raw_P(render_line[i + frame], px);
		}
	}

/* logic */
static void render_luna(int LUNA_X, int LUNA_Y) {

	/* setup some variables & timers */
	static uint8_t prev_wpm = 0;
	static uint32_t tap_timer = 0; // WPM and mod triggered
	if (get_current_wpm() > prev_wpm || get_mods()) { tap_timer = timer_read32(); }
	prev_wpm = get_current_wpm();

	// Elapsed time between key presses
	uint32_t keystroke = timer_elapsed32(tap_timer);
	static uint16_t anim_timer = 0;

    /* Sit - 32x24px */
    static const char PROGMEM sit[6][LUNA_SIZE] = {
        /* 'sit1' */
        {   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c,
		0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28,
		0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        /* 'sit2' */
        {   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c,
		0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{   0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28,
        0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
    };

    /* Walk - 32x24px */
    static const char PROGMEM walk[6][LUNA_SIZE] = {
        /* 'walk1' */
        {   0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80,
		0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00},
        {   0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
		0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00},
        {   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03,
		0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		/* 'walk2' */
        {   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00,
		0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00},
        {    0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
		0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00},
        {    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e,
		0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
    };

    /* Run - 32x24px */
    static const char PROGMEM run[6][LUNA_SIZE] = {
        /* 'run1' */
        {    0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
		0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00},
        {    0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00},
        {    0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01,
		0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00},
         /* 'run2' */
        {    0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
		0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00},
        {    0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00},
        {    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37,
		0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
    };

    /* Bark - 32x24px */
    static const char PROGMEM bark[6][LUNA_SIZE] = {
        /* 'bark1' */
        {    0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
		0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00},
        {    0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00},
        {    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02,
		0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        /* 'bark2' */
        {    0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
		0x40, 0x2c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00},
        {    0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10},
        {    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02,
		0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
    };

    /* Sneak - 32x24px */
    static const char PROGMEM sneak[6][LUNA_SIZE] = {
        /* 'sneak1' */
        {    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
        {    0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04,
		0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00},
        {    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06,
		0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00},
        /* 'sneak2' */
        {    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00},
        {    0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04,
		0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00},
        {    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04,
		0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00}
    };

    /* animation */
    void animate_luna(void) {

		/* jump */
        if (isJumping || !showedJump) {

            // Is jumping, clear the bottom line and tell animation to render 1 line up
            oled_set_cursor(LUNA_X,LUNA_Y +3);
            oled_write("     ", false);
			jump_height = 1;
            showedJump = true;
        } else {

            // Not jumping, clears the top row and tells animation to render bottom 3 rows
            oled_set_cursor(LUNA_X,LUNA_Y);
            oled_write("     ", false);
			jump_height = 0;
        }

        /* switch frame */
        // current_frame = (current_frame + <number of lines per image>) % <lines x how many frames>;
		current_frame = (current_frame + 3) % 6;

        /* current status */
        if(host_keyboard_led_state().caps_lock) {
        oled_set_cursor(17, 0);
            oled_write_P((current_frame)?PSTR("Arp!"): PSTR("    "), false);
            oled_set_cursor(LUNA_X, LUNA_Y);
            oled_render_image(3, LUNA_SIZE, bark, LUNA_X, LUNA_Y + 1, current_frame);

        } else if(isSneaking) {
			oled_render_image(3, LUNA_SIZE, sneak, LUNA_X, LUNA_Y + 1 - jump_height, current_frame);

        } else if(prev_wpm <= MIN_WALK_SPEED) {
			oled_render_image(3, LUNA_SIZE, sit, LUNA_X, LUNA_Y + 1, current_frame);

        } else if(prev_wpm <= MIN_RUN_SPEED) {
			oled_render_image(3, LUNA_SIZE, walk, LUNA_X, LUNA_Y + 1 - jump_height, current_frame);

        } else {
			oled_render_image(3, LUNA_SIZE, run, LUNA_X, LUNA_Y + 1 - jump_height, current_frame);

        }
    }

	if (keystroke > OLED_TIMEOUT) { oled_off(); }
	else if (timer_elapsed(anim_timer) > (LUNA_FRAME_DURATION - (prev_wpm/2))) {
		anim_timer = timer_read();
		animate_luna();
	}
}

/* KEYBOARD PET END */

/* LAYER STATUS START */
void render_layer_status(void){
    oled_set_cursor(0, 1);
    switch(get_highest_layer(layer_state)){
        case _BASE:
            oled_write_P(PSTR("Default"), false);
            break;
        case _FN1:
            oled_write_P(PSTR("FN1    "), false);
            break;
        case _FN2:
            oled_write_P(PSTR("FN2    "), false);
            break;

            oled_write_P(PSTR("FN3    "), false);
            break;
    }
}

// void render_lock_status(void){
//     // We need to use ln to override previous entries.
//     oled_write_P(led_state.caps_lock ? PSTR("  CAPS") : PSTR(""), false);
// }

void render_wpm(void){
    oled_set_cursor(0, 3);
    uint8_t n = get_current_wpm();
    char    wpm_counter[5];
    wpm_counter[3] = '\0';
    wpm_counter[2] = '0' + n % 10;
    wpm_counter[1] = '0' + (n /= 10) % 10;
    wpm_counter[0] = '0' + n / 10;
    oled_set_cursor(13, 3);
    oled_write(wpm_counter, false);
    // oled_write_char(wpm_counter[0], false);
    // oled_set_cursor(13, 1);
    // oled_write_char(wpm_counter[1], false);
    // oled_set_cursor(13, 2);
    // oled_write_char(wpm_counter[2], false);
    // oled_set_cursor(13, 3);
    // oled_write_char(wpm_counter[3], false);
}

void render_owner(void){
    oled_set_cursor(0, 0);
    oled_write_P(PSTR("Jekko Gray"), false);
}

void render_os_status(void){
    oled_set_cursor(0, 2);
    if (keymap_config.swap_lalt_lgui) {
        oled_write_P(PSTR("Mac"), false);
    }
    else {
        oled_write_P(PSTR("Win"), false);
    }
}

void render_encoder_status(void){
    oled_set_cursor(0, 3);
    if (is_art_mode){
        oled_write_P(PSTR("        ART "), false);
    } else {
        oled_write_P((current_encoder_layer == DEFAULT_ENCODER) ? PSTR("VOL ") : PSTR("    "), false);
        oled_write_P((current_encoder_layer ==  MEDIA_ENCODER) ? PSTR("MED ") : PSTR("    "), false);
        oled_write_P(PSTR("    "), false);
    }
}

void render_status(void){
    render_owner();
    render_layer_status();
    render_os_status();
    render_wpm();
    render_encoder_status();
}

/* LAYER STATUS END */

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_0; }

void oled_task_user(void) {
  /* KEYBOARD PET VARIABLES START */
    led_state = host_keyboard_led_state();
    render_luna(16, 0);
    oled_set_cursor(0, 0);
    render_status();
    /* KEYBOARD PET VARIABLES END */
}

#endif

// Cycle through the different encoder layers.
void toggle_encoder(void) { current_encoder_layer = (current_encoder_layer + 1) % ENCODER_LAYER_SIZE; }

// Toggle art mode.
void toggle_art(void){
    is_art_mode = !is_art_mode;
}

// Animate tap
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ENCDR_TOG:
            if (record->event.pressed) {
                toggle_encoder();
            }
            break;

        case ART_TOG:
            if (record->event.pressed) {
                toggle_art();
            }
               /* KEYBOARD PET STATUS START */

        case KC_LALT:
        case KC_RALT:
        case KC_LCTL:
        case KC_RCTL:
            if (record->event.pressed) {
                isSneaking = true;
            } else {
                isSneaking = false;
            }
            break;
        case KC_SPC:
            if (record->event.pressed) {
                isJumping  = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
            break;

            /* KEYBOARD PET STATUS END */
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
