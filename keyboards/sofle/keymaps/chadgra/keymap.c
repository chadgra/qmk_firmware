 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
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
  */

#include QMK_KEYBOARD_H

#include "oled.c"
#include "encoder.c"

// Base layer is the number of layers CYCLE selects from.
#define BASE_LAYERS 2

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE,   // can always be here (4 bytes)
    MOUSE_SCREEN_RIGHT,         // Move mouse to the right screen
    MOUSE_SCREEN_LEFT,          // Move mouse to the left screen
    MOUSE_MOVE_UP,
    MOUSE_MOVE_DOWN,
    MOUSE_MOVE_RIGHT,
    MOUSE_MOVE_LEFT,
};

enum custom_layers {
    _BASE,
    _MOVE,
    _LOWER,
    _RAISE
};

#define MS_SC_R     MOUSE_SCREEN_RIGHT
#define MS_SC_L     MOUSE_SCREEN_LEFT
#define MS_U        MOUSE_MOVE_UP
#define MS_D        MOUSE_MOVE_DOWN
#define MS_R        MOUSE_MOVE_RIGHT
#define MS_L        MOUSE_MOVE_LEFT

//Default keymap. This can be changed in Via. Use oled.c to change beavior that Via cannot change.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * BASE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |-------.  E  ,-------|   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|C+Right|< N >|SCRN_LT|------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |-------.  C  ,-------|   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|       |< O >|MS_BTN1|------+------+------+------+------+------|
 * | MOVE |   A  |   S  |   D  |   F  |   G  |-------.  D  ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|C+Left |< E >|SCRN_RT|------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|  R  |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /      \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /        \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /          \      \ |      |      |      |      |
 *            `-----------------------------------'            '------''---------------------------'
 */

[_BASE] = LAYOUT_via(
   KC_ESC, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,                         KC_6    , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV ,
   KC_TAB, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,C(KC_RGHT),     MS_SC_L, KC_Y    , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
TT(_MOVE), KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , XXXXXXX,       KC_BTN1, KC_H    , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
  KC_LSPO, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,C(KC_LEFT),     MS_SC_R, KC_N    , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSPC,
                KC_LGUI, KC_LAPO, KC_LCPO,TT(_LOWER), KC_ENT ,           KC_SPC ,TT(_RAISE), KC_RCPC, KC_RAPC, KC_RGUI
),

/*
 * MOVE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | BASE |      |      |      |      |      |-------.  E  ,-------|      |      | PgUp |      | Home |      |
 * |------+------+------+------+------+------| Pg Up |< N >| VolDn |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.  C  ,-------|      |      |      |      |      | Bspc |
 * |------+------+------+------+------+------| Mute  |< O >|       |------+------+------+------+------+------|
 * |      | LGUI | LCTR | LAlt | CAPS |      |-------.  D  ,-------| Left | Down |  Up  | Right|      | End  |
 * |------+------+------+------+------+------| Pg Dn |< E >| VolUp |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|  R  |-------|      |      |PgDown|      |      |      |
 * `-----------------------------------------/       /      \      \-----------------------------------------'
 *            |      |      |      |      | /LShift /        \      \  | Menu |      |      |      |
 *            |      |      |      |      |/       /          \      \ |      |      |      |      |
 *            `-----------------------------------'            '------''---------------------------'
 */
[_MOVE] = LAYOUT_via(
TO(_BASE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX,G(KC_LEFT), XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP,       KC_VOLD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
  _______, KC_LGUI, KC_LCTL, KC_LALT, KC_CAPS, XXXXXXX,   KC_NO,       KC_MPLY, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, XXXXXXX,G(KC_RGHT),
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN,       KC_VOLU, XXXXXXX, XXXXXXX, KC_PGDN, XXXXXXX, XXXXXXX, XXXXXXX,
                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT,           XXXXXXX,  KC_APP, XXXXXXX, XXXXXXX, XXXXXXX
),

/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |-------.  E  ,-------|  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|       |< N >|       |------+------+------+------+------+------|
 * |  `   |   1  |   2  |   3  |   4  |   5  |-------.  C  ,-------|   6  |   7  |   8  |   -  |   =  | F12  |
 * |------+------+------+------+------+------|       |< O >|       |------+------+------+------+------+------|
 * | Tab  |   !  |   @  |   #  |   $  |   %  |-------.  D  ,-------|   ^  |   &  |   *  |   {  |   }  |   \  |
 * |------+------+------+------+------+------|       |< E >|       |------+------+------+------+------+------|
 * | Shift|  =   |  -   |  +   |   {  |   }  |-------|  R  |-------|   [  |   ]  |   ;  |   :  |   \  |      |
 * `-----------------------------------------/       /      \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /        \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /          \      \ |      |      |      |      |
 *            `-----------------------------------'            '------''---------------------------'
 */
[_LOWER] = LAYOUT_via(
  _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,                         KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,
  KC_GRV , KC_F11 , KC_F12 , KC_3   , KC_4   , KC_5   , _______,       _______, KC_6   , KC_7   , KC_8   , KC_MINS, KC_EQL , KC_DEL ,
  _______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, _______,       _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LCBR, KC_RCBR, KC_BSLS,
  _______, KC_EQL , KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, _______,       _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
                  _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______
),
/* RAISE
 * ,----------------------------------------.                      ,-----------------------------------------.
 * |Cycle |      |      |      |      |      |-------.  E  ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |< N >|       |------+------+------+------+------+------|
 * | Esc  | Ins  | Pscr | Menu |      |      |-------.  C  ,-------|      |      |  Up  |      | DLine| Bspc |
 * |------+------+------+------+------+------|       |< O >|       |------+------+------+------+------+------|
 * | Tab  | LAt  | LCtl |LShift|      | Caps |-------.  D  ,-------|      | Left | Down | Rigth|  Del | Bspc |
 * |------+------+------+------+------+------|       |< E >|       |------+------+------+------+------+------|
 * |Shift | Undo |  Cut | Copy | Paste|      |-------|  R  |-------|      | LStr |      | LEnd |      | Shift|
 * `-----------------------------------------/      /       \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter /         \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/      /           \      \ |      |      |      |      |
 *            `----------------------------------'             '------''---------------------------'
 */
[_RAISE] = LAYOUT_via(
  _______, _______, _______, _______, _______, _______,                       _______, _______, _______, _______, _______, _______,
  _______, XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX,    MS_R,       MS_D,  XXXXXXX, KC_BTN1, XXXXXXX, KC_BTN2, _______, KC_BSPC,
  _______, XXXXXXX, KC_WH_L, KC_WH_U, KC_WH_D, KC_WH_R, _______,    _______,  KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_DEL , KC_BSPC,
  _______, XXXXXXX, XXXXXXX, KC_MS_D, XXXXXXX, XXXXXXX,    MS_L,       MS_U,  XXXXXXX, _______, XXXXXXX, _______, XXXXXXX, _______,
                   _______, _______, _______, _______, KC_BTN2,        KC_BTN1, _______, _______, _______, _______
)
};

static bool is_mouse_screen_right = false;
static bool is_mouse_screen_left = false;

static uint16_t mouse_screen_right_timer = 0;
static uint16_t mouse_screen_left_timer = 0;

static bool is_mouse_move_up = false;
static int mouse_move_up_start_timer = 0;
static int mouse_move_up_repeat_timer = 0;

static bool is_mouse_move_down = false;
static int mouse_move_down_start_timer = 0;
static int mouse_move_down_repeat_timer = 0;

static bool is_mouse_move_right = false;
static int mouse_move_right_start_timer = 0;
static int mouse_move_right_repeat_timer = 0;

static bool is_mouse_move_left = false;
static int mouse_move_left_start_timer = 0;
static int mouse_move_left_repeat_timer = 0;

#define MOUSE_SCREEN_TIME       350
#define MOUSE_MOVE_ACL2_TIME    50
#define MOUSE_MOVE_ACL1_TIME    200
#define MOUSE_MOVE_ACL0_TIME    500

void init_mouse_move(uint16_t keycode, int* start_timer, int *repeat_timer, bool *is_move) {
    if (!*is_move) {
        *is_move = true;
        *start_timer = timer_read();
        // register_code(KC_ACL0);
        register_code(keycode);
    }
    *repeat_timer = timer_read();
}

void handle_mouse_move(uint16_t keycode, int start_timer, int repeat_timer, bool *is_move) {
    if (*is_move) {
        if (timer_elapsed(repeat_timer) > 200) {
            *is_move = false;
            unregister_code(keycode);
            // unregister_code(KC_ACL0);
            // unregister_code(KC_ACL1);
            // unregister_code(KC_ACL2);
        }
        // int ms_since_start = timer_elapsed(start_timer);
        // if (ms_since_start > 400) {
        //     unregister_code(KC_ACL1);
        //     register_code(KC_ACL2);
        // }
        // else if (ms_since_start > 200) {
        //     unregister_code(KC_ACL0);
        //     register_code(KC_ACL1);
        // }
    }
}

// Custom keycode handling.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // handling this once instead of in each keycode uses less program memory.
    // if ((keycode >= SAFE_RANGE) && !(record->event.pressed)) {
    //     return false;
    // }

    switch (keycode) {
        case MOUSE_SCREEN_RIGHT:
            is_mouse_screen_right = true;
            mouse_screen_right_timer = timer_read();
            register_code(KC_ACL1);
            register_code(KC_MS_R);
            break;
        case MOUSE_SCREEN_LEFT:
            is_mouse_screen_left = true;
            mouse_screen_left_timer = timer_read();
            register_code(KC_ACL1);
            register_code(KC_MS_L);
            break;
        case MOUSE_MOVE_UP:
            init_mouse_move(KC_MS_U, &mouse_move_up_start_timer, &mouse_move_up_repeat_timer, &is_mouse_move_up);
            break;
        case MOUSE_MOVE_DOWN:
            init_mouse_move(KC_MS_D, &mouse_move_down_start_timer, &mouse_move_down_repeat_timer, &is_mouse_move_down);
            break;
        case MOUSE_MOVE_RIGHT:
            init_mouse_move(KC_MS_R, &mouse_move_right_start_timer, &mouse_move_right_repeat_timer, &is_mouse_move_right);
            break;
        case MOUSE_MOVE_LEFT:
            init_mouse_move(KC_MS_L, &mouse_move_left_start_timer, &mouse_move_left_repeat_timer, &is_mouse_move_left);
            break;
    }

    // this uses less memory than returning in each case.
    return keycode < SAFE_RANGE;
};

void matrix_scan_user(void) {
    encoder_action_unregister();

    if (is_mouse_screen_right) {
        if (timer_elapsed(mouse_screen_right_timer) > MOUSE_SCREEN_TIME) {
            unregister_code(KC_MS_R);
            unregister_code(KC_ACL1);
            is_mouse_screen_right = false;
        }
    }
    if (is_mouse_screen_left) {
        if (timer_elapsed(mouse_screen_left_timer) > MOUSE_SCREEN_TIME) {
            unregister_code(KC_MS_L);
            unregister_code(KC_ACL1);
            is_mouse_screen_left = false;
        }
    }

    handle_mouse_move(KC_MS_U, mouse_move_up_start_timer, mouse_move_up_repeat_timer, &is_mouse_move_up);
    handle_mouse_move(KC_MS_D, mouse_move_down_start_timer, mouse_move_down_repeat_timer, &is_mouse_move_down);
    handle_mouse_move(KC_MS_R, mouse_move_right_start_timer, mouse_move_right_repeat_timer, &is_mouse_move_right);
    handle_mouse_move(KC_MS_L, mouse_move_left_start_timer, mouse_move_left_repeat_timer, &is_mouse_move_left);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch(biton32(state)) {
        case _MOVE:
            rgblight_enable_noeeprom();
            rgblight_sethsv_noeeprom(HSV_GOLDENROD);
            break;
        case _LOWER:
            rgblight_enable_noeeprom();
            rgblight_sethsv_noeeprom(HSV_CORAL);
            break;
        case _RAISE:
            rgblight_enable_noeeprom();
            rgblight_sethsv_noeeprom(HSV_TEAL);
            break;
        default:
            // Default color - disabled
            rgblight_disable_noeeprom();
            break;
    }

    return state;
}

void keyboard_post_init_user(void) {
    rgblight_disable_noeeprom();
}
