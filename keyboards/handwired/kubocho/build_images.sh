#!/usr/bin/env bash
# Build all Kubocho firmware images without flashing, and archive them.
#
# Produces:
#   kubocho_left.uf2         - default keymap, writes LEFT handedness to EEPROM on boot
#   kubocho_right.uf2        - default keymap, writes RIGHT handedness to EEPROM on boot
#   kubocho_generic.uf2      - default keymap, uses whatever handedness is in EEPROM
#   kubocho_eeprom_clear.uf2 - EEPROM reset keymap
#
# Usage: [KEYMAP=34key] keyboards/handwired/kubocho/build_images.sh [archive_dir]
#   KEYMAP      defaults to "default"; other keymaps get it in their file names
#               (e.g. kubocho_34key_left.uf2)
#   archive_dir defaults to ~/kubocho_firmware
# Images land in <archive_dir>/<date>-<git-sha>[-<keymap>]/ and
# <archive_dir>/latest[-<keymap>] -> that dir.

set -euo pipefail

KB=handwired/kubocho
ROOT="$(git -C "$(dirname "$0")" rev-parse --show-toplevel)"
ARCHIVE_ROOT="${1:-$HOME/kubocho_firmware}"
KEYMAP="${KEYMAP:-default}"

cd "$ROOT"
if [[ -z "${VIRTUAL_ENV:-}" && -f venv/bin/activate ]]; then
    # shellcheck disable=SC1091
    source venv/bin/activate
fi

sha="$(git rev-parse --short HEAD)"
git diff --quiet HEAD -- "keyboards/$KB" || sha="${sha}-dirty"
if [[ "$KEYMAP" == default ]]; then name=kubocho; suffix=""; else name="kubocho_$KEYMAP"; suffix="-$KEYMAP"; fi
[[ -d "keyboards/$KB/keymaps/$KEYMAP" ]] || { echo "No such keymap: $KEYMAP" >&2; exit 1; }
dest="$ARCHIVE_ROOT/$(date +%Y%m%d-%H%M%S)-$sha$suffix"
mkdir -p "$dest"

# Regenerate autocorrect data from the shared dictionary for keymaps that use it
dict="keyboards/$KB/autocorrect_dictionary.txt"
if [[ -f "$dict" ]] && grep -qs '^AUTOCORRECT_ENABLE *= *yes' "keyboards/$KB/keymaps/$KEYMAP/rules.mk"; then
    qmk generate-autocorrect-data -kb "$KB" -km "$KEYMAP" "$dict" -q
fi

# TARGET gives each variant its own output name and object dir, so builds
# don't clobber each other. EXTRAFLAGS adds the same define the
# uf2-split-{left,right} flash targets would, without their wait-for-mount step.
build() {  # build <keymap> <target-name> [extra-cflags]
    echo "==> $2"
    make "$KB:$1" TARGET="$2" ${3:+EXTRAFLAGS="$3"}
    cp ".build/$2.uf2" "$dest/"
}

build "$KEYMAP"    "${name}_left"       -DINIT_EE_HANDS_LEFT
build "$KEYMAP"    "${name}_right"      -DINIT_EE_HANDS_RIGHT
build "$KEYMAP"    "${name}_generic"
build eeprom_clear kubocho_eeprom_clear

ln -sfn "$dest" "$ARCHIVE_ROOT/latest$suffix"
echo
echo "Images archived in $dest:"
ls -l "$dest"
