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
     *   | App  | LGui |      |      | ~L2  |                                       |  ~L2 |      |  ESC | RGui |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        | ~L1  | ~L3  |       | ~L3  | ~L1  |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      | LAlt |       | RAlt |      |      |
     *                                 | ~L1  |LShift|------|       |------|RShift| Space|
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
                                       FN1, FN3,
                                           LALT,
                                  FN1,LSFT,LCTL,
        // right hand
              EQL,   6,   7,   8,   9,   0, FN0,
              ENT,   K,   H,   G,   F,   Q,MINS,
                     S,   N,   R,   T,   D,   Z,
              DEL,   B,   M,COMM, DOT,   J,BSPC,
                        FN2,  NO, ESC,RGUI,  NO,
         FN3, FN1,
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
        TRNS,TRNS, FN0, FN1, FN2, FN3,TRNS,
        TRNS, FN8, FN9,FN10,FN11,FN12,
        TRNS,BSLS,FN18,FN19,FN20,FN21,TRNS,
        TRNS,TRNS,TRNS,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
             TRNS, FN4,NUBS, FN5, FN6, FN7,TRNS,
                  FN13,FN14,FN15,FN16,FN17,TRNS,
             TRNS,RBRC,FN22,FN23,FN24,FN25,TRNS,
                       TRNS,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),
    /*
     * Keymap: Layer 2: Keyboard functions
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * | Teensy |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        | PgUp | Backs|  Up  |  Del | PgDn |      |           |      |      |  KP7 |  KP8 |  KP9 |   +  |    -   |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        | Home | Left | Down | Right|  End |------|           |------|      |  KP4 |  KP5 |  KP6 |   ,  |    .   |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |      |  Tab |      | Enter|      |      |           |      |      |  KP1 |  KP2 |  KP3 |   ;  |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |      |      |      |      |                                       |  KP0 |      |      |      |      |
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
        TRNS,NO,  NO,  NO,  NO,  PAUS,PSCR,
        TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
        TRNS,NO,  NO,  NO,  TRNS,NO,
        TRNS,NO,  NO,  NO,  TRNS,NO,  TRNS,
        TRNS,TRNS,FN17,TRNS,TRNS,
                                      TRNS,TRNS,
                                           TRNS,
                                 TRNS,TRNS,TRNS,
        // right hand
             SLCK,NLCK,PSLS,PAST,PAST,PMNS,BSPC,
             TRNS,NO,  P7,  P8,  P9,  PMNS,PGUP,
                  NO,  P4,  P5,  P6,  PPLS,PGDN,
             TRNS,NO,  P1,  P2,  P3,  PPLS,PENT,
                       P0,  PDOT,SLSH,PENT,PENT,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),
    /*
     * Keymap: Layer 3: F1-F12
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |   +L4  |   F1 |   F2 |   F3 |   F4 |   F5 |  F6  |           |  F7  |  F8  |  F9  | F10  |  F11 |  F12 |        |
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
    KEYMAP(
        // left hand
        TRNS,NO,  NO,  NO,  NO,  NO,  NO,
        TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
        TRNS,NO,  TRNS,NO,  NO,  NO,
        TRNS,NO,  TRNS,NO,  NO,  NO,  TRNS,
        TRNS,TRNS,TRNS,LALT,LGUI,
                                      TRNS,TRNS,
                                           TRNS,
                                 LCTL,LSFT,TRNS,
        // right hand
             NO,  NO,  NO,  NO,  NO,  NO,  TRNS,
             TRNS,NO,  F1,  F2,  F3,  F4,  PGUP,
                  NO,  F5,  F6,  F7,  F8,  PGDN,
             TRNS,NO,  F9,  F10, F11, F12, APP,
                       RGUI,RALT,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,RSFT,RCTL
    ),
    /*
     * Keymap: Layer 4: Plover
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |   +L0  |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
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
        TRNS,TRNS,TRNS,LALT,LGUI,
                                      TRNS,TRNS,
                                           TRNS,
                                 LCTL,LSFT,TRNS,
        // right hand
             NO,  NO,  NO,  NO,  NO,  NO,  TRNS,
             TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
                  NO,  NO,  NO,  NO,  NO,  TRNS,
             TRNS,NO,  NO,  NO,  NO,  NO,  TRNS,
                       RGUI,RALT,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,RSFT,RCTL
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
};

/*
 * Fn action definition
 */
static const uint16_t PROGMEM fn_actions[] = {
    [0] =   ACTION_MODS_KEY(MOD_LSFT, KC_EQL),              // FN0  = dead `

    [1] =   ACTION_LAYER_MOMENTARY(1),                      // FN1  = momentary Layer 1
    [2] =   ACTION_LAYER_MOMENTARY(2),                      // FN2  = momentary Layer 2
    [3] =   ACTION_LAYER_MOMENTARY(3),                      // FN3  = momentary Layer 3
};

// symbol-layer
static const uint16_t PROGMEM fn_actions_1[] = {
    [ 0] = ACTION_MODS_KEY(MOD_LSFT, KC_SLSH),              // FN0  = Shifted Slash     // _ in Neo2
    [ 1] = ACTION_MODS_KEY(MOD_LSFT, KC_8),                 // FN1  = Shift+8           // [ in Neo2
    [ 2] = ACTION_MODS_KEY(MOD_LSFT, KC_9),                 // FN2  = Shift+9           // ] in Neo2
    [ 3] = ACTION_MACRO(CARET),                             // FN3  = GRV,SPC           // ^ in Neo2
    [ 4] = ACTION_MODS_KEY(MOD_LSFT, KC_1),                 // FN4  = Shift+1           // ! in Neo2
    [ 5] = ACTION_MODS_KEY(MOD_LSFT, KC_NUBS),              // FN5  = Shift+\           // > in Neo2
    [ 6] = ACTION_MODS_KEY(MOD_LSFT, KC_0),                 // FN6  = Shift+0           // = in Neo2
    [ 7] = ACTION_MODS_KEY(MOD_LSFT, KC_6),                 // FN7  = Shitf+6           // & in Neo2
    [ 8] = ACTION_MODS_KEY(MOD_RALT, KC_MINS),              // FN8  = AltGr+-           // \ in Neo2
    [ 9] = ACTION_MODS_KEY(MOD_LSFT, KC_7),                 // FN9  = Shift+7           // / in Neo2
    [10] = ACTION_MODS_KEY(MOD_RALT, KC_7),                 // FN10 = AltGr+7           // { in Neo2
    [11] = ACTION_MODS_KEY(MOD_RALT, KC_0),                 // FN11 = AltGr+0           // } in Neo2
    [12] = ACTION_MODS_KEY(MOD_LSFT, KC_RBRC),              // FN12 = Shift+]           // * in Neo2
    [13] = ACTION_MODS_KEY(MOD_LSFT, KC_MINS),              // FN13 = Shift+-           // ? in Neo2
    [14] = ACTION_MODS_KEY(MOD_LSFT, KC_8),                 // FN14 = Shift+8           // ( in Neo2
    [15] = ACTION_MODS_KEY(MOD_LSFT, KC_9),                 // FN15 = Shift+9           // ) in Neo2
    [16] = ACTION_MODS_KEY(MOD_LSFT, KC_BSLS),              // FN16 = Shift+\           // : in Neo2
    [17] = ACTION_MODS_KEY(MOD_RALT, KC_Q),                 // FN17 = AltGr+Q           // @ in Neo2
    [18] = ACTION_MODS_KEY(MOD_LSFT, KC_4),                 // FN18 = Shift+4           // $ in Neo2
    [19] = ACTION_MODS_KEY(MOD_RALT, KC_NUBS),              // FN19 = Shift+4           // | in Neo2
    [20] = ACTION_MODS_KEY(MOD_RALT, KC_RBRC),              // FN20 = Shift+4           // ~ in Neo2
    [21] = ACTION_MACRO(GRAVE),                             // FN21 = Shift+=,SPC       // ` in Neo2
    [22] = ACTION_MODS_KEY(MOD_LSFT, KC_5),                 // FN22 = Shift+5           // % in Neo2
    [23] = ACTION_MODS_KEY(MOD_LSFT, KC_2),                 // FN23 = Shift+2           // " in Neo2
    [24] = ACTION_MODS_KEY(MOD_LSFT, KC_BSLS),              // FN24 = Shift+\           // ' in Neo2
    [25] = ACTION_MODS_KEY(MOD_LSFT, KC_COMM),              // FN25 = Shift+,           // ; in Neo2
};
// Plover layer
static const uint16_t PROGMEM fn_actions_2[] = {
    [ 0] = ACTION_FUNCTION(TEENSY_KEY),
}
static const uint16_t PROGMEM fn_actions_3[] = {
    [ 4] = ACTION_LAYER_SET(4),
}
static const uint16_t PROGMEM fn_actions_4[] = {
    [ 0] = ACTION_LAYER_SET(0),
}
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

#define FN_ACTIONS_4_SIZE   (sizeof(fn_actions_4) / sizeof(fn_actions_4[0]))
#define FN_ACTIONS_7_SIZE   (sizeof(fn_actions_7) / sizeof(fn_actions_7[0]))
#define FN_ACTIONS_9_SIZE   (sizeof(fn_actions_9) / sizeof(fn_actions_9[0]))

/*
 * translates Fn keycode to action
 * for some layers, use different translation table
 */
action_t keymap_fn_to_action(uint8_t keycode)
{
    uint8_t layer = biton32(layer_state);

    action_t action;
    action.code = ACTION_NO;

    if (layer == 1 && FN_INDEX(keycode) < FN_ACTIONS_1_SIZE) {
        action.code = pgm_read_word(&fn_actions_1[FN_INDEX(keycode)]);
    }

    // by default, use fn_actions from default layer 0
    // this is needed to get mapping for same key, that was used switch to some layer,
    // to have possibility to switch layers back
    if (action.code == ACTION_NO && FN_INDEX(keycode) < FN_ACTIONS_SIZE) {
        action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
    }

    return action;
}

