# nice_view_sofle

Status screen for the nice!view displays on the Eyelash Sofle.

This shield is a vendored copy of `boards/shields/nice_view_gem/` from
[M165437/nice-view-gem](https://github.com/M165437/nice-view-gem) at tag `v0.3.0`
(commit `7794ebf7f75d7e16cb05240bcffe6c5a45ef5b44`), MIT licensed (see `LICENSE`).

## Changes from upstream

- Renamed the shield to `nice_view_sofle` (`SHIELD_NICE_VIEW_SOFLE`) and the
  `NICE_VIEW_GEM_*` Kconfig options to `NICE_VIEW_SOFLE_*`.
- Removed the WPM gauge and graph (and `CONFIG_ZMK_WPM`) from the central screen.
- Replaced the `BAT` label on both halves with a battery icon whose fill grows
  with the charge (20 px fill, 5 % per pixel), next to the `NN%` text. The
  charging bolt stays right of the text while USB powers the half.
- The central screen shows the selected Bluetooth profile (1-5) in Montserrat 48
  where the WPM widget was, or `USB` in Montserrat 28 when USB is the selected
  output. The 5-dot profile row is gone; the layer name stays at the bottom.
