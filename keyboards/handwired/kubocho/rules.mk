# MCU name
MCU = RP2040

# Bootloader selection
BOOTLOADER = rp2040

# Build Options
# Disable LTO to avoid compiler warnings with newer GCC
LTO_ENABLE = no

# Allow compiler warnings (needed for newer GCC with RP2040)
ALLOW_WARNINGS = yes

# Serial/UART driver for RP2040
SERIAL_DRIVER = vendor      # Use RP2040 PIO-based serial driver

# RGB LED support (WS2812/Neopixel on GP23)
RGBLIGHT_ENABLE = yes       # Enable RGB lighting
WS2812_DRIVER = vendor      # Use RP2040 PIO-based WS2812 driver
