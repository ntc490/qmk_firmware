#ifndef KINESIS_NTCMOD_H
#define KINESIS_NTCMOD_H

#include "../kinesis.h"

#define ERGODOX_KEYMAP(                   \
        k80,k70,k60,k50,k40,k30,na1,      \
        k81,k71,k61,k51,k41,k31,na2,      \
        k82,k72,k62,k52,k42,k32,          \
        k83,k73,k63,k53,k43,k33,na3,      \
            k74,k64,k54,k34,na4,          \
                              k36,k35,    \
                                  k55,    \
                          k56,k46,k75,    \
        na5,k94,kA4,kB4,kD4,kE4,kF4,      \
        na6,k95,kA5,kB5,kD5,kE5,kF5,      \
            k96,kA6,kB6,kD6,kE6,kF6,      \
        na7,k97,kA7,kB7,kD7,kE7,kF7,      \
            na8,k93,kB3,kD3,kE3,          \
      k47,k66,                            \
      k67,                                \
      k87,k76,k86                         \
) {                                       \
        { KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO   }, \
        { KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO   }, \
        { KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO   }, \
        { k30,    k31,    k32,    k33,    k34,    k35,    k36,     KC_NO   }, \
        { k40,    k41,    k42,    k43,    KC_NO,  KC_NO,  k46,     k47     }, \
        { k50,    k51,    k52,    k53,    k54,    k55,    k56,     KC_NO   }, \
        { k60,    k61,    k62,    k63,    k64,    KC_NO,  k66,     k67     }, \
        { k70,    k71,    k72,    k73,    k74,    k75,    k76,     KC_NO   }, \
        { k80,    k81,    k82,    k83,    KC_NO,  KC_NO,  k86,     k87}, \
        { KC_NO,  KC_NO  ,KC_NO  ,k93,    k94,    k95,    k96,     k97}, \
        { KC_NO,  KC_NO  ,KC_NO  ,KC_NO,  kA4,    kA5,    kA6,     kA7}, \
        { KC_NO,  KC_NO  ,KC_NO  ,kB3,    kB4,    kB5,    kB6,     kB7}, \
        { KC_NO,  KC_NO  ,KC_NO  ,KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO}, \
        { KC_NO,  KC_NO  ,KC_NO  ,kD3,    kD4,    kD5,    kD6,     kD7}, \
        { KC_NO,  KC_NO  ,KC_NO  ,kE3,    kE4,    kE5,    kE6,     kE7}, \
        { KC_NO,  KC_NO  ,KC_NO  ,KC_NO,  kF4,    kF5,    kF6,     kF7} \
}

/* 86 Keys */
#define KEYMAP(                           \
    k02,k22,k12,k01,k21,k11,k00,k20,k10,  \
    k80,k70,k60,k50,k40,k30,              \
    k81,k71,k61,k51,k41,k31,              \
    k82,k72,k62,k52,k42,k32,              \
    k83,k73,k63,k53,k43,k33,              \
        k74,k64,k54,k34,                  \
                        k36,k35,          \
                            k55,          \
                    k56,k46,k75,          \
    k03,k23,k13,k04,k24,k14,k05,k85,k84,  \
        k94,kA4,kB4,kD4,kE4,kF4,          \
        k95,kA5,kB5,kD5,kE5,kF5,          \
        k96,kA6,kB6,kD6,kE6,kF6,          \
        k97,kA7,kB7,kD7,kE7,kF7,          \
            k93,kB3,kD3,kE3,              \
    k47,k66,                              \
    k67,                                  \
    k87,k76,k86                           \
) {                                       \
        { k00,    k01,    k02,    k03,    k04,    k05,    KC_NO,   KC_NO   }, \
        { k10,    k11,    k12,    k13,    k14,    KC_NO,  KC_NO,   KC_NO   }, \
        { k20,    k21,    k22,    k23,    k24,    KC_NO,  KC_NO,   KC_NO   }, \
        { k30,    k31,    k32,    k33,    k34,    k35,    k36,     KC_NO   }, \
        { k40,    k41,    k42,    k43,    KC_NO,  KC_NO,  k46,     k47     }, \
        { k50,    k51,    k52,    k53,    k54,    k55,    k56,     KC_NO   }, \
        { k60,    k61,    k62,    k63,    k64,    KC_NO,  k66,     k67     }, \
        { k70,    k71,    k72,    k73,    k74,    k75,    k76,     KC_NO   }, \
        { k80,    k81,    k82,    k83,    k84,    k85,    k86,     k87}, \
        { KC_NO,  KC_NO  ,KC_NO  ,k93,    k94,    k95,    k96,     k97}, \
        { KC_NO,  KC_NO  ,KC_NO  ,KC_NO,  kA4,    kA5,    kA6,     kA7}, \
        { KC_NO,  KC_NO  ,KC_NO  ,kB3,    kB4,    kB5,    kB6,     kB7}, \
        { KC_NO,  KC_NO  ,KC_NO  ,KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO}, \
        { KC_NO,  KC_NO  ,KC_NO  ,kD3,    kD4,    kD5,    kD6,     kD7}, \
        { KC_NO,  KC_NO  ,KC_NO  ,kE3,    kE4,    kE5,    kE6,     kE7}, \
        { KC_NO,  KC_NO  ,KC_NO  ,KC_NO,  kF4,    kF5,    kF6,     kF7} \
}

#endif
