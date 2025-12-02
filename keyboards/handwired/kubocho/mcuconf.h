// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

// Enable UART0 for serial communication
#undef RP_SERIAL_USE_UART0
#define RP_SERIAL_USE_UART0 TRUE
