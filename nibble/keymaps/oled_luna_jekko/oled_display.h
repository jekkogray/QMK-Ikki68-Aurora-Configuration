#pragma once

typedef enum {
    OLED_MODE_IDLE = 0,
    OLED_MODE_VOLUME_UP = 1,
    OLED_MODE_VOLUME_DOWN = 2,
} oled_mode_t;

uint16_t oled_timer;
oled_mode_t oled_mode;

void set_oled_mode(oled_mode_t mode);
void process_record_encoder_oled(uint16_t keycode);
void process_record_keymap_oled(uint16_t keycode);
void render_os_logo(void);
void render_luna(void);
void render_wpm(void);
void render_idle(void);
void render_status_mode_message(void);
void render_frame(void);