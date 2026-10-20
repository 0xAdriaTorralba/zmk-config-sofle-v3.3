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
- **Soft-Off combo**: press **Q + S + Z** and hold **2s** to enter deep sleep (wake via reset button).

## ACC and SYM layers (Spanish ISO on macOS)

- **ACC (layer 6)**: tap an Alt thumb, then one key. Holding the thumb is still Alt.
  - Acute: `A` á, `E` é, `I` í, `O` ó, `U` ú
  - Grave and diaeresis: `Z` à, `D` è, `L` ò, `8` ï, `7` ü
  - Other: `C` ç, `N` ñ, `.` l·l, `/` ¿, `1` ¡
  - Capitals: hold Shift first, then tap Alt, then the letter.
  - Any other key types normally and closes ACC.
- **SYM (`lower`, layer 1)**: hold the left inner thumb (`cmd_space`). Home-row mods don't apply inside SYM.

  ```
  ! @ # $ %     ^ & * ~ `
  \ | = + -     < ( ) > "
  € · _ / ?     { [ ] } '
  ```

  `^`, `~` and `` ` `` type literally (no dead key).
- **Dead keys on base**: the key right of `P` is `` ` `` and the key right of `L` is `´`, as on a Spanish keyboard.

## Build firmware (GitHub Actions)

This repo is compatible with ZMK’s standard *user config* workflow. The `build.yaml` file defines what gets built:

- `eyelash_sofle_right` + `nice_view`
- `eyelash_sofle_left` + `nice_view` (+ ZMK Studio variant for left)
- `nice_nano_v2` + `settings_reset`

If you already have a workflow configured, pushing changes to this repo should produce updated `.uf2` artifacts.

## Build locally (West)

From the repository root:

```bash
west init -l config
west update
west zephyr-export

# Right half
west build -s zmk/app -d build/right -b eyelash_sofle_right -- -DSHIELD=nice_view

# Left half
west build -s zmk/app -d build/left -b eyelash_sofle_left -- -DSHIELD=nice_view
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
