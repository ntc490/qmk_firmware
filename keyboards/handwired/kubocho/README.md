# Kubocho Split Keyboard

A 42-key split keyboard using Raspberry Pi Pico (RP2040) MCUs with direct pin wiring.

## Hardware

- **MCU**: Raspberry Pi Pico (RP2040)
- **Layout**: 3x6 + 3 thumb keys per side (42 keys total)
- **Scanning**: Direct pin (one GPIO per key)
- **Split Communication**: UART on GP0/GP1
- **Master Side**: Right

## Pin Mapping

### Left Side
```
Row 0: GP7,  GP6,  GP5,  GP4,  GP3,  GP2
Row 1: GP13, GP12, GP11, GP10, GP9,  GP8
Row 2: GP19, GP18, GP17, GP16, GP15, GP14
Row 3: -,    -,    -,    GP22, GP21, GP20
```

### Right Side
Uses the same pins (mirrored layout)

### Communication
- **UART TX**: GP1
- **UART RX**: GP0
- **Baud Rate**: 38400

## Building

```bash
qmk compile -kb handwired/kubocho -km default
```

Or with make:
```bash
make handwired/kubocho:default
```

## Flashing

1. Build the firmware (creates `.uf2` file)
2. Put the Pico into bootloader mode (hold BOOTSEL while plugging in)
3. Drag and drop the `.uf2` file to the RPI-RP2 drive
4. Repeat for both sides

## Handedness Configuration

This keyboard uses `EE_HANDS` for handedness detection. You must set the handedness in EEPROM for each side:

### Option 1: Using QMK CLI (Recommended)
```bash
# For the left side
qmk flash -kb handwired/kubocho -km default -bl uf2-split-left

# For the right side
qmk flash -kb handwired/kubocho -km default -bl uf2-split-right
```

### Option 2: Using avrdude after flashing
After flashing the firmware to each side, run:
```bash
# Left side (while connected)
echo -e ":0100000001FE\n:00000001FF" | avrdude -c avrisp2 -p atmega32u4 -U eeprom:w:-:i

# Right side (while connected)
echo -e ":0100000000FF\n:00000001FF" | avrdude -c avrisp2 -p atmega32u4 -U eeprom:w:-:i
```

### Option 3: Hardcode handedness
If you prefer to hardcode the master side instead of using EEPROM:
1. Edit `config.h`
2. Comment out `#define EE_HANDS`
3. Uncomment `#define MASTER_RIGHT`

## Keymap

This keymap is ported from the original KMK configuration with home row mods and multiple layers.

### Layers

The default keymap includes 4 layers:
1. **QWERTY** - Base typing layer with home row mods
2. **NUMS** - Numbers and symbols
3. **FKEYS** - Function keys
4. **POWER** - Navigation (arrows, page up/down, next window)

### Home Row Mods

The keyboard uses **GASC** order (GUI, ALT, SHIFT, CTRL) for home row modifiers:

**Left hand:**
- A = GUI (tap A, hold for GUI/Cmd/Win)
- S = ALT
- D = SHIFT
- F = CTRL

**Right hand:** (mirrored)
- J = CTRL
- K = SHIFT
- L = ALT
- ; = GUI

**Tapping behavior:**
- Tap time: 200ms (matches original KMK config)
- `prefer_hold: False` - Won't activate mod if another key is pressed during hold

### Special Keys

- **TAB** (hold) - Activates POWER layer
- **Bottom-right corner key** - Momentary FKEYS layer
- **Both thumb NUMS keys** - Momentary NUMS layer

### Layer Details

```
QWERTY Layer
+-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
| ESC |  Q  |  W  |  E  |  R  |  T  |     |  Y  |  U  |  I  |  O  |  P  |  \  |
+-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
|TAB^P| A^G | S^A | D^S | F^C |  G  |     |  H  | J^C | K^S | L^A | ;^G |  '  |
+-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
|LSHFT|  Z  |  X  |  C  |  V  |  B  |     |  N  |  M  |  ,  |  .  |  /  |FKEYS|
+-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
                  |BKSP |LCTRL| NUMS|     | NUMS| ENT | SPC |
                  +-----+-----+-----+     +-----+-----+-----+
^G=GUI ^A=ALT ^S=SHIFT ^C=CTRL ^P=POWER(hold)

NUMS Layer
+-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
|     |  `  |     |     |  (  |  )  |     |  =  |  7  |  8  |  9  |  [  |  ]  |
+-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
|CAPS |     |     |     | {^C |  }  |     |  -  | 4^C | 5^S | 6^A | '^G |     |
+-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
|     |     |     | ESC |  [  |  ]  |     |  .  |  1  |  2  |  3  |     |     |
+-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
                  |     |     |     |     |     |     |  0  |
                  +-----+-----+-----+     +-----+-----+-----+
Home row mods on 4, 5, 6, and quote

FKEYS Layer
+-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
|     |     |     |     |     |     |     | F10 | F7  | F8  | F9  | F13 |     |
+-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
|     |     |     |     |     |     |     | F11 | F4  | F5  | F6  | F14 |     |
+-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
|     |     |     |     |     |     |     | F12 | F1  | F2  | F3  | F15 |     |
+-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
                  |     |     |     |     |     |     |     |
                  +-----+-----+-----+     +-----+-----+-----+

POWER Layer (accessed by holding TAB)
+-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
|     |     |     |     |     |     |     |PGDN |PGUP |     |     |     |     |
+-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
|     |     |     |     |     |     |     |LEFT |DOWN | UP  |RIGHT|     |     |
+-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
|     |     |     |     |     |     |     |NXTW |     |     |     |     |     |
+-----+-----+-----+-----+-----+-----+     +-----+-----+-----+-----+-----+-----+
                  |     |     |     |     |     |     |     |
                  +-----+-----+-----+     +-----+-----+-----+
NXTW = Next Window (Cmd+Grave)
```

## Notes

- Ported from KMK configuration with home row mods
- Haptic feedback (DRV2605 on I2C GP26/GP27) not implemented in QMK port
- KEEP key from KMK not implemented (was used for KMK's Keeper module)
- Home row mod timing matches original KMK config (200ms tap time)
- Modify `keymaps/default/keymap.c` to customize your layout
- The baud rate can be adjusted in `config.h` if needed
