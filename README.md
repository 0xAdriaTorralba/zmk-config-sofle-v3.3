# ZMK config — Eyelash Sofle (v3.3)

Personal ZMK configuration for the **Eyelash Sofle** split keyboard.

## What’s in this repo

- **Keymap**: `config/eyelash_sofle.keymap`
- **Board definitions**: `boards/arm/eyelash_sofle/`
- **ZMK manifest**: `config/west.yml`
- **Build matrix (CI)**: `build.yaml`
- **Keymap diagram inputs/outputs**:
  - Source YAML: `keymap-drawer/eyelash_sofle.yaml`
  - Rendered SVG: `keymap-drawer/eyelash_sofle.svg`
  - Drawer config: `keymap_drawer.config.yaml`

## Features / notes

- **ZMK Studio (left half)**: enabled in `build.yaml` via the `studio-rpc-usb-uart` snippet + CMake args.
- **Pointing/mouse keys**: enabled (`CONFIG_ZMK_POINTING=y`) and used in the keymap.
- **Soft-Off combo**: on ADJUST (hold the SYM and RAISE thumbs), press **Q + S + Z** and hold **2s** to enter deep sleep (wake via reset button). The combo only exists on ADJUST so it never delays `S`, a home-row mod, on the base layer.
- **Idle sleep**: each half enters deep sleep after **15 min** without a keypress on that half (each half counts only its own keys). The backlight stays on until then.
- **Displays**: both halves use the `nice_view_sofle` shield in `boards/shields/nice_view_sofle/`, customised from [nice-view-gem](https://github.com/M165437/nice-view-gem) `v0.3.0`. Each half shows its own battery as an icon plus `xx%`; the left (central) screen shows the selected Bluetooth profile number in large type (or `USB`) and the active layer, with no WPM widget.

## SYM layer, accents and home-row mods (Spanish ISO on macOS)

- **SYM (`lower`, layer 1)**: hold the left inner thumb (`cmd_space`). `A` stays transparent (⇧), so holding it still gives Shift.

  ```
  ! @ # $ %     \ { } ? +
  ⇧ | = & '     / ( ) ` "
  < > _ ^ *     ~ [ ] · -
  ```

  `^`, `~` and `` ` `` type literally (no dead key).
- **Accents**: dead keys at their Spanish positions. The key right of `P` types `` ` `` on tap (Shift: `^`) and `+` when held. The key right of `L` is `´` (Shift: `¨`). For example, `´` then `e` = é, Shift+`´` then `u` = ü. Hold `N` for ñ and `C` for ç.
- **Home-row mods**: hold `A S D F` for ⇧ ⌃ ⌥ ⌘ and `U I O P` for ⌘ ⌥ ⌃ ⇧. `G`, `Y` and `T` are plain letters.

## Build firmware (GitHub Actions)

This repo is compatible with ZMK’s standard *user config* workflow. The `build.yaml` file defines what gets built:

- `eyelash_sofle_right` + `nice_view_sofle`
- `eyelash_sofle_left` + `nice_view_sofle` (+ ZMK Studio variant for left)
- `nice_nano_v2` + `settings_reset`

If you already have a workflow configured, pushing changes to this repo should produce updated `.uf2` artifacts.

## Build locally (West)

From the repository root:

```bash
west init -l config
west update
west zephyr-export

# Right half
west build -s zmk/app -d build/right -b eyelash_sofle_right -- -DSHIELD=nice_view_sofle

# Left half
west build -s zmk/app -d build/left -b eyelash_sofle_left -- -DSHIELD=nice_view_sofle
```

## Update the keymap

Edit:

- `config/eyelash_sofle.keymap`

Then rebuild (CI or local) and flash the resulting `.uf2` to each half.

## Keymap diagram

Current layout diagram:

![Eyelash Sofle keymap](keymap-drawer/eyelash_sofle.svg)

To regenerate the diagram, use *keymap-drawer* with:

- `keymap_drawer.config.yaml`
- `keymap-drawer/eyelash_sofle.yaml` (or re-parse from the `.keymap`)
