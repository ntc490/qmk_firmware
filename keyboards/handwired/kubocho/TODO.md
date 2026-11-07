# Kubocho TODO

## Keymap consistency (default vs 34key)

- [ ] **Repeat key on 34key.** default has QK_REP on the right inner thumb.
      If it earns its place, move it to 34key too: Repeat replaces Enter on a
      thumb, and Enter moves to a combo (e.g. comma + period; avoid M + comma,
      "m," is common). Gate an Enter combo on prior idle so it can't misfire
      mid-word (QMK: `within_flow_tap_term()` in `combo_should_trigger()`).

## Cleanup

- [ ] Remove the handedness write in each keymap's `keyboard_post_init_user()`:
      current QMK already applies INIT_EE_HANDS_LEFT/RIGHT in `split_pre_init()`
      (quantum/split_common/split_util.c), before the value is read.
- [ ] README: the "handedness requires two boots" note is out of date (one boot
      is enough now); document Caps Word, Shift+Backspace = Delete, Layer Lock,
      autocorrect, the scrollback key, and `KEYMAP=` for build_images.sh.

## Laptop (kanata, /etc/kanata-common.kbd)

- [ ] Upgrade kanata to 1.12.0 (AUR) for `defhands` / `tap-hold-opposite-hand`
      (= Chordal Hold) and `tap-hold-require-prior-idle` (= Flow Tap).
- [ ] New kanata-common.kbd to match the Kubocho: opposite-hand home row mods,
      C+V = Backspace chord, numbers on G/H, F-keys on T, Caps = Tab tap /
      Power hold. Tab (Caps) and Enter stay on their own keys.
