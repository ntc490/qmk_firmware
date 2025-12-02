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

## Layout

```
QWERTY (Base Layer)
┌─────┬─────┬─────┬─────┬─────┬─────┐     ┌─────┬─────┬─────┬─────┬─────┬─────┐
│ ESC │  Q  │  W  │  E  │  R  │  T  │     │  Y  │  U  │  I  │  O  │  P  │ BSPC│
├─────┼─────┼─────┼─────┼─────┼─────┤     ├─────┼─────┼─────┼─────┼─────┼─────┤
│ TAB │  A  │  S  │  D  │  F  │  G  │     │  H  │  J  │  K  │  L  │  ;  │  '  │
├─────┼─────┼─────┼─────┼─────┼─────┤     ├─────┼─────┼─────┼─────┼─────┼─────┤
│LSHFT│  Z  │  X  │  C  │  V  │  B  │     │  N  │  M  │  ,  │  .  │  /  │RSHFT│
└─────┴─────┴─────┼─────┼─────┼─────┤     ├─────┼─────┼─────┼─────┴─────┴─────┘
                  │LCTRL│LOWER│ SPC │     │ ENT │RAISE│RALT │
                  └─────┴─────┴─────┘     └─────┴─────┴─────┘
```

The default keymap includes:
- Base layer (QWERTY)
- Lower layer (numbers & symbols)
- Raise layer (function keys & navigation)
- Adjust layer (activated when both Lower and Raise are held)

## Notes

- The original KMK configuration includes haptic feedback via I2C (GP26/GP27), which is not implemented in this QMK port
- Modify `keymaps/default/keymap.c` to customize your layout
- The baud rate can be adjusted in `config.h` if needed
