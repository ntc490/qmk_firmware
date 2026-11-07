// Copyright 2026 Nathan Crapo
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Keeper (keep-awake) mode, shared by the Kubocho keymaps.
//
// KEEPER_TOGG cycles: Off -> Manual (blue LED) -> PIR-gated (red LED) -> Off
//   Off:    LED off, no tickle
//   Manual: tap Shift after 60s with no key presses
//   PIR:    tap Shift every 60s, but only if the PIR sensor (GP29) saw motion
//
// To use from a keymap:
//   rules.mk:            SRC += keeper.c
//   keymap.c:            #include "keeper.h"
//   process_record_user: if (!keeper_process_record(keycode, record)) return false;
//   matrix_scan_user:    keeper_task();
//   keyboard_post_init_user: keeper_init();
// Keymap custom keycodes should start at KEEPER_SAFE_RANGE.

#pragma once

#include "quantum.h"

enum keeper_keycodes {
    KEEPER_TOGG = SAFE_RANGE,  // Cycle keeper modes
    KEEPER_SAFE_RANGE,         // First keycode free for keymap use
};

// Returns false if the key was handled (KEEPER_TOGG), true otherwise.
bool keeper_process_record(uint16_t keycode, keyrecord_t *record);

// Call every scan: sends the keep-awake tickle when due.
void keeper_task(void);

// Call once at startup: sets up the PIR pin and turns the LED off.
void keeper_init(void);
