/*
Copyright 2019 @foostan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define SPLIT_MODS_ENABLE
#define SPLIT_TRANSPORT_MIRROR

#define USE_SERIAL_PD2

// milliseconds between repeated motion events
#define MOUSEKEY_INTERVAL            16
// number of pixels per move
#define MOUSEKEY_MOVE_DELTA          1
// milliseconds between the initial key press and first repeated motion event
#define MOUSEKEY_DELAY               50
// number of events (count) accelerating to steady speed
#define MOUSEKEY_TIME_TO_MAX         60
// steady speed (in move_delta units) applied each event
#define MOUSEKEY_MAX_SPEED           40

#define MOUSEKEY_WHEEL_DELAY         50
#define MOUSEKEY_WHEEL_INTERVAL      50
#define MOUSEKEY_WHEEL_TIME_TO_MAX   80

#define TAPPING_TOGGLE  1
#define TAPPING_TERM    180
#define IGNORE_MOD_TAP_INTERRUPT // this makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.)

#ifdef RGBLIGHT_ENABLE
    #undef RGBLED_NUM
    #define RGBLIGHT_ANIMATIONS
    #define RGBLED_NUM 27
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif

#if defined(RGB_MATRIX_ENABLE)
// #    define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
// #    define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
// #    define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
// #    define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#    define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120  // limits maximum brightness of LEDs to 120 out of 255. If not defined maximum brightness is set to 255
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_MATRIX_HUE_STEP 4
#    define RGB_MATRIX_SAT_STEP 4
#    define RGB_MATRIX_VAL_STEP 4
#    define RGB_MATRIX_SPD_STEP 4

// #    define ENABLE_RGB_MATRIX_SOLID_COLOR
#    define ENABLE_RGB_MATRIX_ALPHAS_MODS
// #    define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
// #    define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#endif

#ifdef CONSOLE_ENABLE
    #define DEBUG_MATRIX_SCAN_RATE
#endif

#define OLED_DISABLE_TIMEOUT
#define OLED_FONT_H "keyboards/crkbd/lib/customfont.c"
