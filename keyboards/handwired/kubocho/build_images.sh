#!/usr/bin/env bash
# Build all Kubocho firmware images without flashing, and archive them.
#
# Produces:
#   kubocho_left.uf2         - default keymap, writes LEFT handedness to EEPROM on boot
#   kubocho_right.uf2        - default keymap, writes RIGHT handedness to EEPROM on boot
#   kubocho_generic.uf2      - default keymap, uses whatever handedness is in EEPROM
#   kubocho_eeprom_clear.uf2 - EEPROM reset keymap
#
# Usage: keyboards/handwired/kubocho/build_images.sh [archive_dir]
#   archive_dir defaults to ~/kubocho_firmware
# Images land in <archive_dir>/<date>-<git-sha>/ and <archive_dir>/latest -> that dir.

set -euo pipefail

KB=handwired/kubocho
ROOT="$(git -C "$(dirname "$0")" rev-parse --show-toplevel)"
ARCHIVE_ROOT="${1:-$HOME/kubocho_firmware}"

cd "$ROOT"
if [[ -z "${VIRTUAL_ENV:-}" && -f venv/bin/activate ]]; then
    # shellcheck disable=SC1091
    source venv/bin/activate
fi

sha="$(git rev-parse --short HEAD)"
git diff --quiet HEAD -- "keyboards/$KB" || sha="${sha}-dirty"
dest="$ARCHIVE_ROOT/$(date +%Y%m%d-%H%M%S)-$sha"
mkdir -p "$dest"

# TARGET gives each variant its own output name and object dir, so builds
# don't clobber each other. EXTRAFLAGS adds the same define the
# uf2-split-{left,right} flash targets would, without their wait-for-mount step.
build() {  # build <keymap> <target-name> [extra-cflags]
    echo "==> $2"
    make "$KB:$1" TARGET="$2" ${3:+EXTRAFLAGS="$3"}
    cp ".build/$2.uf2" "$dest/"
}

build default      kubocho_left         -DINIT_EE_HANDS_LEFT
build default      kubocho_right        -DINIT_EE_HANDS_RIGHT
build default      kubocho_generic
build eeprom_clear kubocho_eeprom_clear

ln -sfn "$dest" "$ARCHIVE_ROOT/latest"
echo
echo "Images archived in $dest:"
ls -l "$dest"
