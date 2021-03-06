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
     *   | App  | LGui |      |      |  L3  |                                       |   L4 |      |  ESC | RGui |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |  L6  |  L5  |       |  L5  |  L1  |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      | LAlt |       | RAlt |      |      |
     *                                 |  L2  |LShift|------|       |------|RShift| Space|
     *                                 |      |      | LCtrl|       | RCtrl|      |      |
     *                                 `--------------------'       `--------------------'
     */
    KEYMAP(
        // left hand
          NO,   1,   2,   3,   4,   5, GRV,
          NO,   X,   V,   L,   C,   W,PGUP,
         TAB,   U,   I,   A,   E,   O,
          NO,LBRC,SCLN,QUOT,   P,   Y,PGDN,
         APP,LGUI,  NO,  NO, FN3,
                                       FN6, FN5,
                                           LALT,
                                  FN2,LSFT,LCTL,
        // right hand
              EQL,   6,   7,   8,   9,   0, FN0,
              ENT,   K,   H,   G,   F,   Q,MINS,
                     S,   N,   R,   T,   D,   Z,
              DEL,   B,   M,COMM, DOT,   J,BSPC,
                        FN4,  NO, ESC,RGUI,  NO,
         FN5, FN1,
        RALT,
        RCTL,RSFT, SPC
    ),
    /*
     * Keymap: Layer 1: Neo2 when PC is set to Neo2
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |   1  |   2  |   3  |   4  |   5  |  ê   |           |   é  |   6  |   7  |   8  |   9  |   0  |   è    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |   Q  |   W  |   E  |   R  |   T  | PgUp |           | Enter|   Y  |   U  |   I  |   O  |   P  |   [    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |  Tab   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
     * |--------+------+------+------+------+------| PgDn |           |  Del |------+------+------+------+------+--------|
     * |        |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | Backsp |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | App  | LGui |      |      | L3   |                                       | L4   |      |  ESC | RGui |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |  L5  |       |  L5  |  L0  |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      | LAlt |       | LAlt |      |      |
     *                                 |CAPS  |LShift|------|       |------|RShift| Space|
     *                                 |      |      | LCtrl|       | RCtrl|      |      |
     *                                 `--------------------'       `--------------------'
     */
    KEYMAP(
        // left hand
          NO,   1,   2,   3,   4,   5, GRV,
          NO,   Q,   W,   E,   R,   T,PGUP,
         TAB,   A,   S,   D,   F,   G,
          NO,   Z,   X,   C,   V,   B,PGDN,
         APP,LGUI,  NO,  NO, FN3,
                                        NO, FN5,
                                           LALT,
                                 CAPS,LSFT,LCTL,
        // right hand
             RBRC,   6,   7,   8,   9,   0, EQL,
              ENT,   Y,   U,   I,   O,   P,LBRC,
                     H,   J,   K,   L,SCLN,QUOT,
              DEL,   N,   M,COMM, DOT,SLSH,BSPC,
                        FN4,  NO, ESC,RGUI,  NO,
         FN5, FN0,
        LALT,
        RCTL,RSFT, SPC
    ),
    /*
     * Keymap: Layer 2: Symbols and function keys
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
     * Keymap: Layer 3: Numbers
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
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
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,
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
             TRNS,TRNS,  P1,  P2,  P3, FN1,TRNS,
                         P0,TRNS,TRNS,TRNS,TRNS,
        TRNS,TRNS,
        TRNS,
        TRNS,TRNS,TRNS
    ),
    /*
     * Keymap: Layer 4: Keyboard functions
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
     * Keymap: Layer 5: F1-F12
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * | Teensy |   F1 |   F2 |   F3 |   F4 |   F5 |  F6  |           |  F7  |  F8  |  F9  | F10  |  F11 |  F12 |        |
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
         FN1,  F1,  F2,  F3,  F4,  F5,  F6,
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
     * Keymap: Layer 6: Plover
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |   Q  |   W  |   E  |   R  |   T  |------|           |------|   Y  |   U  |   I  |   O  |   P  |   [    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |   A  |   S  |   D  |   F  |   G  |      |           |      |   H  |   J  |   K  |   L  |   ;  |   '    |
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
               NO,   H,   J,   K,   L,SCLN,QUOT,
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
    LEFT_BRACKET,
    RIGHT_BRACKET,
    BACKSLASH,
    LEFT_BRACE,
    RIGHT_BRACE,
    PIPE,
    TILDE,
    AT,
    DEAD_GRAVE,
    UNDERSCORE,
    SLASH,
    STAR,
    DOLLAR,
    EXCL_MARK,
    EQUALS,
    AMPERSAND,
    QUESTION_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    PERCENT,
    DOUBLE_QUOTE,
    SINGLE_QUOTE,
    SEMI_COLON,
    NEO_SEMI_COLON,
};

/*
 * Fn action definition
 */
static const uint16_t PROGMEM fn_actions[] = {
};

static const uint16_t PROGMEM fn_actions_0[] = {
    [ 0] = ACTION_MACRO(DEAD_GRAVE),                        // FN0  = dead `
    [ 1] = ACTION_LAYER_SET(1, ON_RELEASE),                 // FN1  = set Layer 1
    [ 2] = ACTION_LAYER_ON(2, ON_PRESS),                    // FN2  = set Layer 2
    [ 3] = ACTION_LAYER_ON(3, ON_PRESS),                    // FN3  = set Layer 3
    [ 4] = ACTION_LAYER_ON(4, ON_PRESS),                    // FN4  = set Layer 4
    [ 5] = ACTION_LAYER_ON(5, ON_PRESS),                    // FN5  = set Layer 5
    [ 6] = ACTION_LAYER_ON(6, ON_RELEASE),                  // FN6  = set Layer 6
};

static const uint16_t PROGMEM fn_actions_1[] = {
    [ 0] = ACTION_LAYER_SET(0, ON_RELEASE),                 // FN0  = Back to layer 0
    [ 3] = ACTION_LAYER_ON(3, ON_PRESS),                    // FN3  = set Layer 3
    [ 4] = ACTION_LAYER_ON(4, ON_PRESS),                    // FN4  = set Layer 4
    [ 5] = ACTION_LAYER_ON(5, ON_PRESS),                    // FN5  = set Layer 5
};

// symbol-layer
static const uint16_t PROGMEM fn_actions_2[] = {
    [ 0] = ACTION_LAYER_OFF(2, ON_RELEASE),                 // FN0  = Back to layer 0

    [ 1] = ACTION_MACRO(UNDERSCORE),                        // FN1  = _
    [ 2] = ACTION_MACRO(LEFT_BRACKET),                      // FN2  = [
    [ 3] = ACTION_MACRO(RIGHT_BRACKET),                     // FN3  = ]
    [ 4] = ACTION_MACRO(CARET),                             // FN4  = ^

    [ 5] = ACTION_MACRO(BACKSLASH),                         // FN5  = Backslash
    [ 6] = ACTION_MACRO(SLASH),                             // FN6  = /
    [ 7] = ACTION_MACRO(LEFT_BRACE),                        // FN7  = {
    [ 8] = ACTION_MACRO(RIGHT_BRACE),                       // FN8  = }
    [ 9] = ACTION_MACRO(STAR),                              // FN9  = *

    [10] = ACTION_KEY(KC_BSLS),                             // FN10 = #
    [11] = ACTION_MACRO(DOLLAR),                            // FN11 = $
    [12] = ACTION_MACRO(PIPE),                              // FN12 = |
    [13] = ACTION_MACRO(TILDE),                             // FN13 = ~
    [14] = ACTION_MACRO(GRAVE),                             // FN14 = `

    [15] = ACTION_MACRO(EXCL_MARK),                         // FN15 = !
    [16] = ACTION_MACRO(LEFT_ANGLE_BRACKET),                // FN16 = <
    [17] = ACTION_MACRO(RIGHT_ANGLE_BRACKET),               // FN17 = >
    [18] = ACTION_MACRO(EQUALS),                            // FN18 = =
    [19] = ACTION_MACRO(AMPERSAND),                         // FN19 = &

    [20] = ACTION_MACRO(QUESTION_MARK),                     // FN20 = ?
    [21] = ACTION_MACRO(LEFT_PAREN),                        // FN21 = (
    [22] = ACTION_MACRO(RIGHT_PAREN),                       // FN22 = )
    [23] = ACTION_KEY(KC_SLSH),                             // FN23 = -
    [24] = ACTION_MACRO(COLON),                             // FN24 = :
    [25] = ACTION_MACRO(AT),                                // FN25 = @

    [26] = ACTION_KEY(KC_RBRC),                             // FN26 = +
    [27] = ACTION_MACRO(PERCENT),                           // FN27 = %
    [28] = ACTION_MACRO(DOUBLE_QUOTE),                      // FN28 = "
    [29] = ACTION_MACRO(SINGLE_QUOTE),                      // FN29 = '
    [30] = ACTION_MACRO(SEMI_COLON),                        // FN30 = ;
};
static const uint16_t PROGMEM fn_actions_3[] = {
    [ 0] = ACTION_LAYER_OFF(3, ON_RELEASE),                 // FN0  = Back to layer 0
    [ 1] = ACTION_MACRO(NEO_SEMI_COLON),                    // FN2  = Shift+,           // ; in Neo2
};
static const uint16_t PROGMEM fn_actions_4[] = {
    [ 0] = ACTION_LAYER_OFF(4, ON_RELEASE),                 // FN0  = Back to layer 0
};
static const uint16_t PROGMEM fn_actions_5[] = {
    [ 0] = ACTION_LAYER_OFF(5, ON_RELEASE),
    [ 1] = ACTION_FUNCTION(TEENSY_KEY),
};
// Plover layer
static const uint16_t PROGMEM fn_actions_6[] = {
    [ 0] = ACTION_LAYER_OFF(6, ON_RELEASE),
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
            case LEFT_BRACKET: return MACRO(I(15), D(RALT), T(8), U(RALT), END);
            case RIGHT_BRACKET: return MACRO(I(15), D(RALT), T(9), U(RALT), END);
            case BACKSLASH: return MACRO(I(15), D(RALT), T(MINS), U(RALT), END);
            case LEFT_BRACE: return MACRO(I(15), D(RALT), T(7), U(RALT), END);
            case RIGHT_BRACE: return MACRO(I(15), D(RALT), T(0), U(RALT), END);
            case PIPE: return MACRO(I(15), D(RALT), T(NUBS), U(RALT), END);
            case TILDE: return MACRO(I(15), D(RALT), T(RBRC), U(RALT), END);
            case AT: return MACRO(I(15), D(RALT), T(Q), U(RALT), END);
            case DEAD_GRAVE: return MACRO(I(15), D(LSFT), T(EQL), U(LSFT), END);
            case UNDERSCORE: return MACRO(I(15), D(LSFT), T(SLSH), U(LSFT), END);
            case SLASH: return MACRO(I(15), D(LSFT), T(7), U(LSFT), END);
            case STAR: return MACRO(I(15), D(LSFT), T(RBRC), U(LSFT), END);
            case DOLLAR: return MACRO(I(15), D(LSFT), T(4), U(LSFT), END);
            case EXCL_MARK: return MACRO(I(15), D(LSFT), T(1), U(LSFT), END);
            case EQUALS: return MACRO(I(15), D(LSFT), T(0), U(LSFT), END);
            case AMPERSAND: return MACRO(I(15), D(LSFT), T(6), U(LSFT), END);
            case QUESTION_MARK: return MACRO(I(15), D(LSFT), T(MINS), U(LSFT), END);
            case LEFT_PAREN: return MACRO(I(15), D(LSFT), T(8), U(LSFT), END);
            case RIGHT_PAREN: return MACRO(I(15), D(LSFT), T(9), U(LSFT), END);
            case COLON: return MACRO(I(15), D(LSFT), T(DOT), U(LSFT), END);
            case PERCENT: return MACRO(I(15), D(LSFT), T(5), U(LSFT), END);
            case DOUBLE_QUOTE: return MACRO(I(15), D(LSFT), T(2), U(LSFT), END);
            case SINGLE_QUOTE: return MACRO(I(15), D(LSFT), T(BSLS), U(LSFT), END);
            case SEMI_COLON: return MACRO(I(15), D(LSFT), T(COMM), U(LSFT), END);
            case NEO_SEMI_COLON: return MACRO(I(15), D(LSFT), T(COMM), U(LSFT), END);
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
#define FN_ACTIONS_6_SIZE   (sizeof(fn_actions_6) / sizeof(fn_actions_6[0]))

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
    if (layer == 6 && FN_INDEX(keycode) < FN_ACTIONS_6_SIZE) {
        action.code = pgm_read_word(&fn_actions_6[FN_INDEX(keycode)]);
    }

    // by default, use fn_actions from default layer 0
    // this is needed to get mapping for same key, that was used switch to some layer,
    // to have possibility to switch layers back
    if (action.code == ACTION_NO && FN_INDEX(keycode) < FN_ACTIONS_SIZE) {
        action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
    }

    return action;
}
