    /*
     * This layout tries to enable the NEO2 layout (http://neo-layout.org/) in hardware.
     * Since Neo2 is optimized to enable input of German texts, I assume, that the PC is
     * set to German keyboard layout (QWERTZ) with dead keys. I want this, because I want
     * to be able to just connect the keybord to any PC without having to install the Neo2
     * keyboard layout.
     *
     * Neo2 uses non-standard shifted keys, like <shift>+6 for $ (<shift>+4
     * on standard QWERTZ), <shift>+7 for € (<AltGr>+E), but also allows input of chars not
     * inputable on QWERTZ.
     *
     * This is a port of my existing sollution using the firmware of Ben Blazak
     * (https://github.com/tschulte/ergodox-firmware/blob/neo2/firmware/keyboard/ergodox/layout/neo2--tschulte.c)
     * As Oleg points out in his layout file, non-standard shifted keys are problematic.
     *
     * In the above mentioned implementation I already tried this by not using <shift> but
     * instead defining one layer for the lower-case letters, and a second layer which
     * example, I can not use the real shift-key, but instead must define one layer for the
     * lowercase letters, and the next layer for the upper-case letters.
     *
     * But this has problems:
     * - at least the second layer needs to define functions for everey key (Press shift, press key,
     *   release key, release shift)
     * - Keyboard shortcuts that need shift do not work
     * - Keyboard repeating does not work
     *
     * In the end, I did not use this idea, and have not implemented Neo2 in full detail.
     * I also opted to use macros even for the lower case letters (pressing a key sends
     * key press, directly followed by key release), thus disabling keyboard repeating.
     * This was done to prevent problems with [, ], {, }, (, ), < and >, for example I
     * was not able to type "[]" or "<>".
     *
     * As I can see, the tmk firmware is a little bit less capable of defining macros
     * (everything must be defined using FN-keys, which is a bit cumbersome). So why
     * am I doing it? I want to learn Plover (http://www.openstenoproject.org/), and
     * for this I need NKRO, which is not supported by Ben Blazak's firmware.
     */
static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Keymap: Default Layer in Neo2
     * (ê, é and è stand for the dead accent key)
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |   1  |   2  |   3  |   4  |   5  |   ê  |           |   é   |   6  |   7  |   8  |   9  |   0  |   è   |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |   x  |   v  |   l  |   c  |   w  | PgUp |           | Enter|   k  |   h  |   g  |   f  |   q  |   ß    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | Tab    |   u  |   i  |   a  |   e  |   o  |------|           |------|   s  |   n  |   r  |   t  |   d  |   y    |
     * |--------+------+------+------+------+------| PgDn |           |  Del |------+------+------+------+------+--------|
     * |        |   ü  |   ö  |   ä  |   p  |   z  |      |           |      |   b  |   m  |   ,  |   .  |   j  | Backsp |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | App  | LGui |      |      |  L2  |                                       |   L3 |      |  ESC | RGui |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |  L5  |  L4  |       |  L4  |  L1  |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      | LAlt |       | RAlt |      |      |
     *                                 |  L1  |LShift|------|       |------|RShift| Space|
     *                                 |      |      | LCtrl|       | RCtrl|      |      |
     *                                 `--------------------'       `--------------------'
     */
    KEYMAP(
        // left hand
          NO,   1,   2,   3,   4,   5, GRV,
          NO,   X,   V,   L,   C,   W,PGUP,
         TAB,   U,   I,   A,   E,   O,
          NO,LBRC,SCLN,QUOT,   P,   Y,PGDN,
         APP,LGUI,  NO,  NO, FN2,
                                       FN5, FN4,
                                           LALT,
                                  FN1,LSFT,LCTL,
        // right hand
              EQL,   6,   7,   8,   9,   0, FN0,
              ENT,   K,   H,   G,   F,   Q,MINS,
                     S,   N,   R,   T,   D,   Z,
              DEL,   B,   M,COMM, DOT,   J,BSPC,
                        FN2,  NO, ESC,RGUI,  NO,
         FN4, FN1,
        RALT,
        RCTL,RSFT, SPC
    ),
    /*
     * Keymap: Layer 1: Symbols and function keys
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |      |   _  |   [  |   ]  |   ^  |      |           |      |   !  |   <  |   >  |   =  |   &  |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |   \  |   /  |   {  |   }  |   *  |------|           |------|   ?  |   (  |   )  |   -  |   :  |   @    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |   #  |   $  |   |  |   ~  |   `  |      |           |      |   +  |   %  |   "  |   '  |   ;  |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |      |      |      |      |                                       |      |      |      |      |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      |   L0 |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |   L0 |      |------|       |------|      |      |
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     */
    KEYMAP(
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS, FN1, FN2, FN3, FN4,TRNS,
        TRNS, FN5, FN6, FN7, FN8, FN9,
        TRNS,FN10,FN11,FN12,FN13,FN14,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                  FN0,TRNS,TRNS,
        // right hand
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,FN15,FN16,FN17,FN18,FN19,TRNS,
                  FN20,FN21,FN22,FN23,FN24,FN25,
             TRNS,FN26,FN27,FN28,FN29,FN30,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS, FN0,
        TRNS,
        TRNS,TRNS,TRNS
    ),
    /*
     * Keymap: Layer 2: Numbers
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * | Teensy |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      |  KP7 |  KP8 |  KP9 |   +  |    -   |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |------|           |------|      |  KP4 |  KP5 |  KP6 |   ,  |    .   |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      |  KP1 |  KP2 |  KP3 |   ;  |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |      |      |      |   L0 |                                       |  KP0 |      |      |      |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |      |      |------|       |------|      |      |
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     */
    KEYMAP(
        // left hand
         FN1,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS, FN0,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,  P7,  P8,  P9,RBRC,SLSH,
                  TRNS,  P4,  P5,  P6,COMM, DOT,
             TRNS,TRNS,  P1,  P2,  P3, FN2,TRNS,
                         P0,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),
    /*
     * Keymap: Layer 3: Keyboard functions
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        | PgUp | Backs|  Up  |  Del | PgDn |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        | Home | Left | Down | Right|  End |------|           |------|      |      |      |      |      |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |      |  Tab |      | Enter|      |      |           |      |      |      |      |      |      |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |      |      |      |      |                                       |  L0  |      |      |      |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |      |      |------|       |------|      |      |
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     */
    KEYMAP(
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,PGUP,BSPC,  UP, DEL,PGDN,TRNS,
        TRNS,HOME,LEFT,DOWN,RGHT, END,
        TRNS,TRNS, TAB,TRNS, ENT,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                        FN0,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),
    /*
     * Keymap: Layer 4: F1-F12
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |   F1 |   F2 |   F3 |   F4 |   F5 |  F6  |           |  F7  |  F8  |  F9  | F10  |  F11 |  F12 |        |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |      |      |      |      |                                       |      |      |      |      |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |  L0  |       |  L0  |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |      |      |------|       |------|      |      |
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     */
    KEYMAP(
        // left hand
        TRNS,  F1,  F2,  F3,  F4,  F5,  F6,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS, FN0,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
               F7,  F8,  F9, F10, F11, F12,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
         FN0,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),
    /*
     * Keymap: Layer 5: Plover
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |   Q  |   W  |   E  |   R  |   T  |------|           |------|   Y  |   U  |   I  |   O  |   P  |   [    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |   A  |   S  |   D  |   F  |   G  |      |           |      |   H  |   J  |   K  |   L  |   ;  |   .    |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |      |      |      |      |                                       |      |      |      |      |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |   L0 |      |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |  C   |  V   |------|       |------|  N   |   M  |
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     */
    KEYMAP(
        // left hand
          NO,  NO,  NO,  NO,  NO,  NO,  NO,
          NO,   1,   2,   3,   4,   5,  NO,
          NO,   Q,   W,   E,   R,   T,
          NO,   A,   S,   D,   F,   G,  NO,
          NO,  NO,  NO,  NO,  NO,
                                       FN0,  NO,
                                             NO,
                                    C,   V,  NO,
        // right hand
               NO,  NO,  NO,  NO,  NO,  NO,  NO,
               NO,   6,   7,   8,   9,   0,  NO,
                     Y,   U,   I,   O,   P,LBRC,
               NO,   H,   J,   K,   L,SCLN, DOT,
                         NO,  NO,  NO,  NO,  NO,
          NO,  NO,
          NO,
          NO,   N,   M
    ),
    /*
     * Keymap: Template
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |      |      |      |      |                                       |      |      |      |      |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |      |      |------|       |------|      |      |
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     */
/*
    KEYMAP(
        // left hand
        TRNS,NO,  NO,  NO,  NO,  NO,  NO,
        TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
        TRNS,NO,  NO,  NO,  NO,  NO,
        TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             NO,  NO,  NO,  NO,  NO,  NO,  TRNS,
             TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
                  NO,  NO,  NO,  NO,  NO,  TRNS,
             TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),
    KEYMAP(
        // left hand
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                  TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),
*/

};

/* id for user defined functions & macros */
enum function_id {
    TEENSY_KEY,
};

enum macro_id {
    CARET,
    GRAVE,
    LEFT_ANGLE_BRACKET,
    RIGHT_ANGLE_BRACKET,
};

/*
 * Fn action definition
 */
static const uint16_t PROGMEM fn_actions[] = {
};

static const uint16_t PROGMEM fn_actions_0[] = {
    [ 0] = ACTION_MODS_KEY(MOD_LSFT, KC_EQL),               // FN0  = dead `
    [ 1] = ACTION_LAYER_SET(1, ON_PRESS),                   // FN1  = set Layer 1
    [ 2] = ACTION_LAYER_SET(2, ON_PRESS),                   // FN2  = set Layer 2
    [ 3] = ACTION_LAYER_SET(3, ON_PRESS),                   // FN3  = set Layer 3
    [ 4] = ACTION_LAYER_SET(4, ON_PRESS),                   // FN4  = set Layer 4
    [ 5] = ACTION_LAYER_SET(5, ON_RELEASE),                 // FN5  = set Layer 5
};

// symbol-layer
static const uint16_t PROGMEM fn_actions_1[] = {
    [ 0] = ACTION_LAYER_SET(0, ON_RELEASE),                 // FN0  = Back to layer 0

    [ 1] = ACTION_MODS_KEY(MOD_LSFT, KC_SLSH),              // FN1  = Shifted Slash     // _ in Neo2
    [ 2] = ACTION_MODS_KEY(MOD_LSFT, KC_8),                 // FN2  = Shift+8           // [ in Neo2
    [ 3] = ACTION_MODS_KEY(MOD_LSFT, KC_9),                 // FN3  = Shift+9           // ] in Neo2
    [ 4] = ACTION_MACRO(CARET),                             // FN4  = GRV,SPC           // ^ in Neo2

    [ 5] = ACTION_MODS_KEY(MOD_RALT, KC_MINS),              // FN9  = AltGr+-           // \ in Neo2
    [ 6] = ACTION_MODS_KEY(MOD_LSFT, KC_7),                 // FN10 = Shift+7           // / in Neo2
    [ 7] = ACTION_MODS_KEY(MOD_RALT, KC_7),                 // FN11 = AltGr+7           // { in Neo2
    [ 8] = ACTION_MODS_KEY(MOD_RALT, KC_0),                 // FN12 = AltGr+0           // } in Neo2
    [ 9] = ACTION_MODS_KEY(MOD_LSFT, KC_RBRC),              // FN13 = Shift+]           // * in Neo2

    [10] = ACTION_KEY(KC_BSLS),                             // FN19 = BSLS              // # in Neo2
    [11] = ACTION_MODS_KEY(MOD_LSFT, KC_4),                 // FN19 = Shift+4           // $ in Neo2
    [12] = ACTION_MODS_KEY(MOD_RALT, KC_NUBS),              // FN20 = Shift+4           // | in Neo2
    [13] = ACTION_MODS_KEY(MOD_RALT, KC_RBRC),              // FN21 = Shift+4           // ~ in Neo2
    [14] = ACTION_MACRO(GRAVE),                             // FN22 = Shift+=,SPC       // ` in Neo2

    [15] = ACTION_MODS_KEY(MOD_LSFT, KC_1),                 // FN5  = Shift+1           // ! in Neo2
    [16] = ACTION_MACRO(LEFT_ANGLE_BRACKET),                // FN6  = Shift+\           // < in Neo2
    [17] = ACTION_MACRO(RIGHT_ANGLE_BRACKET),               // FN6  = Shift+\           // > in Neo2
    [18] = ACTION_MODS_KEY(MOD_LSFT, KC_0),                 // FN7  = Shift+0           // = in Neo2
    [19] = ACTION_MODS_KEY(MOD_LSFT, KC_6),                 // FN8  = Shitf+6           // & in Neo2

    [20] = ACTION_MODS_KEY(MOD_LSFT, KC_MINS),              // FN14 = Shift+-           // ? in Neo2
    [21] = ACTION_MODS_KEY(MOD_LSFT, KC_8),                 // FN15 = Shift+8           // ( in Neo2
    [22] = ACTION_MODS_KEY(MOD_LSFT, KC_9),                 // FN16 = Shift+9           // ) in Neo2
    [23] = ACTION_KEY(KC_SLSH),                             // FN16 = Shift+9           // - in Neo2
    [24] = ACTION_MODS_KEY(MOD_LSFT, KC_BSLS),              // FN17 = Shift+\           // : in Neo2
    [25] = ACTION_MODS_KEY(MOD_RALT, KC_Q),                 // FN18 = AltGr+Q           // @ in Neo2

    [26] = ACTION_KEY(KC_RBRC),                             // FN23 = Shift+5           // + in Neo2
    [27] = ACTION_MODS_KEY(MOD_LSFT, KC_5),                 // FN23 = Shift+5           // % in Neo2
    [28] = ACTION_MODS_KEY(MOD_LSFT, KC_2),                 // FN24 = Shift+2           // " in Neo2
    [29] = ACTION_MODS_KEY(MOD_LSFT, KC_BSLS),              // FN25 = Shift+\           // ' in Neo2
    [30] = ACTION_MODS_KEY(MOD_LSFT, KC_COMM),              // FN = Shift+,             // ; in Neo2
};
// Plover layer
static const uint16_t PROGMEM fn_actions_2[] = {
    [ 0] = ACTION_LAYER_SET(0, ON_RELEASE),                 // FN0  = Back to layer 0
    [ 1] = ACTION_FUNCTION(TEENSY_KEY),
    [ 2] = ACTION_MODS_KEY(MOD_LSFT, KC_COMM),              // FN2  = Shift+,           // ; in Neo2
};
static const uint16_t PROGMEM fn_actions_3[] = {
    [ 0] = ACTION_LAYER_SET(0, ON_RELEASE),                 // FN0  = Back to layer 0
};
static const uint16_t PROGMEM fn_actions_4[] = {
    [ 0] = ACTION_LAYER_SET(0, ON_RELEASE),
};
static const uint16_t PROGMEM fn_actions_5[] = {
    [ 0] = ACTION_LAYER_SET(0, ON_RELEASE),
};
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    // print("action_function called\n");
    // print("id  = "); phex(id); print("\n");
    // print("opt = "); phex(opt); print("\n");

    if (id == TEENSY_KEY) {
        clear_keyboard();
        print("\n\nJump to bootloader... ");
        _delay_ms(50);
        bootloader_jump(); // should not return
        print("not supported.\n");
    }

}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch (id) {
            case CARET:  return MACRO(I(15), T(GRV), T(SPC), END);
            case GRAVE:     return MACRO(I(15), D(LSFT), T(EQL), U(LSFT), T(SPC), END);
            case LEFT_ANGLE_BRACKET:     return MACRO(I(15), T(NUBS), END);
            case RIGHT_ANGLE_BRACKET:     return MACRO(I(15), D(LSFT), T(NUBS), U(LSFT), END);
        }
    }
    return MACRO_NONE;
}


#define FN_ACTIONS_SIZE     (sizeof(fn_actions)   / sizeof(fn_actions[0]))
#define FN_ACTIONS_0_SIZE   (sizeof(fn_actions_0) / sizeof(fn_actions_0[0]))
#define FN_ACTIONS_1_SIZE   (sizeof(fn_actions_1) / sizeof(fn_actions_1[0]))
#define FN_ACTIONS_2_SIZE   (sizeof(fn_actions_2) / sizeof(fn_actions_2[0]))
#define FN_ACTIONS_3_SIZE   (sizeof(fn_actions_3) / sizeof(fn_actions_3[0]))
#define FN_ACTIONS_4_SIZE   (sizeof(fn_actions_4) / sizeof(fn_actions_4[0]))
#define FN_ACTIONS_5_SIZE   (sizeof(fn_actions_5) / sizeof(fn_actions_5[0]))

/*
 * translates Fn keycode to action
 * for some layers, use different translation table
 */
action_t keymap_fn_to_action(uint8_t keycode)
{
    uint8_t layer = biton32(layer_state);

    action_t action;
    action.code = ACTION_NO;

    if (layer == 0 && FN_INDEX(keycode) < FN_ACTIONS_0_SIZE) {
        action.code = pgm_read_word(&fn_actions_0[FN_INDEX(keycode)]);
    }
    if (layer == 1 && FN_INDEX(keycode) < FN_ACTIONS_1_SIZE) {
        action.code = pgm_read_word(&fn_actions_1[FN_INDEX(keycode)]);
    }
    if (layer == 2 && FN_INDEX(keycode) < FN_ACTIONS_2_SIZE) {
        action.code = pgm_read_word(&fn_actions_2[FN_INDEX(keycode)]);
    }
    if (layer == 3 && FN_INDEX(keycode) < FN_ACTIONS_3_SIZE) {
        action.code = pgm_read_word(&fn_actions_3[FN_INDEX(keycode)]);
    }
    if (layer == 4 && FN_INDEX(keycode) < FN_ACTIONS_4_SIZE) {
        action.code = pgm_read_word(&fn_actions_4[FN_INDEX(keycode)]);
    }
    if (layer == 5 && FN_INDEX(keycode) < FN_ACTIONS_5_SIZE) {
        action.code = pgm_read_word(&fn_actions_5[FN_INDEX(keycode)]);
    }

    // by default, use fn_actions from default layer 0
    // this is needed to get mapping for same key, that was used switch to some layer,
    // to have possibility to switch layers back
    if (action.code == ACTION_NO && FN_INDEX(keycode) < FN_ACTIONS_SIZE) {
        action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
    }

    return action;
}

