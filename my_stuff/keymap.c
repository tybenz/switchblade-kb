#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] =
    KEYMAP(PGUP, GRV ,  1   , 2   , 3   , 4     , 5       , NO   , NO     , 6      , 7      , 8   , 9   , 0   , MINS, EQL , GRV , BSPC, \
           PGDN, TAB ,  Q   , W   , E   , R     , T       , NO   , NO     , Y      , U      , I   , O   , P   , LBRC, RBRC, BSLS, NO  , \
           HOME, LCTL,  A   , S   , D   , F     , G       , NO   , NO     , H      , J      , K   , L   , SCLN, QUOT, NO  , ENT , NO  , \
           END , LSFT,  Z   , X   , C   , V     , NO      , NO   , NO     , B      , N      , M   , COMM, DOT , SLSH, UP  , RSFT, NO  , \
           INS , FN0 ,  LALT, LGUI, SPC , _VOLUP, _VOLDOWN, _MUTE, MS_BTN1, MS_BTN3, MS_BTN2, NO  , SPC , RGUI, LEFT, DOWN, RGHT, NO  ),

    [1] =
    KEYMAP(TRNS, ESC , F1   , F2  , F3  , F4    , F5      , TRNS , TRNS   , F6     , F7     , F8  , F9  , F10 , F11 , F12 , F13 , DEL , \
           TRNS, TRNS, TRNS , TRNS, TRNS, TRNS  , TRNS    , TRNS , TRNS   , TRNS   , TRNS   , TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
           TRNS, TRNS, TRNS , TRNS, TRNS, TRNS  , TRNS    , TRNS , TRNS   , TRNS   , TRNS   , TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
           TRNS, TRNS, MPRV , MPLY, MNXT, TRNS  , TRNS    , TRNS , TRNS   , TRNS   , TRNS   , TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
           TRNS, TRNS, TRNS , TRNS, TRNS, TRNS  , TRNS    , TRNS , TRNS   , TRNS   , TRNS   , TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),
};

