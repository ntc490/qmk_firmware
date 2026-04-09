# Kubocho Split Keyboard

A 42-key split keyboard using Raspberry Pi Pico (RP2040) MCUs with direct pin wiring.

## Hardware

- **MCU**: Raspberry Pi Pico (RP2040) - both sides
- **Layout**: 3x6 + 3 thumb keys per side (42 keys total)
- **Scanning**: Direct pin (one GPIO per key)
- **Split Communication**: UART on GP0/GP1
- **Master Side**: Right

## Pin Mapping

### Right Side
```
Row 0: GP2,  GP3,  GP4,  GP5,  GP6,  GP7
Row 1: GP8,  GP9,  GP10, GP11, GP12, GP13
Row 2: GP14, GP15, GP16, GP17, GP18, GP19
Row 3: GP20, GP21, GP22, -,    -,    -
```

### Left Side
Uses the same pins (mirrored layout)

### Communication
- **UART TX**: GP1
- **UART RX**: GP0
- **Baud Rate**: 38400

## Building Firmware

This keyboard uses `EE_HANDS` for handedness detection, which stores left/right configuration in EEPROM (emulated in flash on RP2040).

### Initial Setup (First Time Only)

You need to flash hand-specific firmware once to each side to initialize EEPROM:

```bash
# Activate Python environment
source venv/bin/activate

# Build left-hand initialization firmware
make handwired/kubocho:default:uf2-split-left

# Save it
cp .build/handwired_kubocho_default.uf2 ~/kubocho_left.uf2

# Clean and build right-hand initialization firmware
rm -rf .build
make handwired/kubocho:default:uf2-split-right

# Save it
cp .build/handwired_kubocho_default.uf2 ~/kubocho_right.uf2
```

### Generic Firmware (After Initial Setup)

Once handedness is initialized, you can flash the same generic firmware to both sides:

```bash
make handwired/kubocho:default

# The resulting .build/handwired_kubocho_default.uf2 can be flashed to either side
```

### EEPROM Clear Firmware (Optional)

If you need to reset EEPROM (e.g., if a keyboard is mis-configured):

```bash
make handwired/kubocho:eeprom_clear
cp .build/handwired_kubocho_eeprom_clear.uf2 ~/kubocho_eeprom_clear.uf2
```

This creates a special firmware where pressing the F or J keys (index fingers) will clear EEPROM.

## Flashing Instructions

### Initial Setup (First Time)

**For the LEFT keyboard:**
1. Put left Pico into bootloader mode (hold BOOTSEL while plugging in USB)
2. Drag `kubocho_left.uf2` to the RPI-RP2 drive
3. Keyboard will reboot automatically
4. **Unplug and replug** the keyboard (or press reset) - handedness requires two boots to take effect
5. Left keyboard is now configured

**For the RIGHT keyboard:**
1. Put right Pico into bootloader mode (hold BOOTSEL while plugging in USB)
2. Drag `kubocho_right.uf2` to the RPI-RP2 drive
3. Keyboard will reboot automatically
4. **Unplug and replug** the keyboard (or press reset) - handedness requires two boots to take effect
5. Right keyboard is now configured

**Why two reboots?**
The first boot writes handedness to EEPROM, but reads the old value. The second boot reads the newly written value.

### Updating Firmware (After Initial Setup)

Once handedness is set, you can flash the same generic firmware to both sides:

1. Put Pico into bootloader mode
2. Drag generic `handwired_kubocho_default.uf2` to RPI-RP2 drive
3. Works immediately (no second reboot needed)

### Resetting EEPROM (If Needed)

If a keyboard gets mis-configured:

1. Flash `kubocho_eeprom_clear.uf2` to the problem keyboard
2. Press F or J key (index fingers) - keyboard will reset
3. Reflash the appropriate hand-specific firmware (`kubocho_left.uf2` or `kubocho_right.uf2`)
4. Reboot twice as described in Initial Setup

## How Handedness Works

- **Left/Right Init Firmware**: Contains code that writes handedness to EEPROM on every boot
- **Generic Firmware**: Only reads handedness from EEPROM (doesn't write it)
- **EEPROM Emulation**: RP2040 doesn't have real EEPROM, so QMK emulates it in flash
- **Persistence**: Once set, handedness survives firmware updates (unless EEPROM is explicitly cleared)

## Alternative: Hardcode Handedness

If you prefer to hardcode the master side instead of using EEPROM:

1. Edit `config.h`
2. Comment out `#define EE_HANDS`
3. Uncomment `#define MASTER_RIGHT`
4. Build separate left/right firmware and never mix them up

This avoids EEPROM entirely but requires maintaining two different firmware builds.

## Notes

- Ported from KMK configuration with home row mods
- Home row mod timing matches original KMK config (200ms tap time)
- Modify `keymaps/default/keymap.c` to customize your layout
- The `eeprom_clear` keymap is intentionally minimal (all keys are KC_NO except F/J)
- Keeper toggle feature (keep-awake) is available on the numbers layer
