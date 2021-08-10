<h1 align="center">Welcome to dwm</h1>
<p>
  <a href="https://github.com/misobarisic/dwm/blob/master/LICENSE" target="_blank">
    <img alt="License: MIT" src="https://img.shields.io/badge/License-MIT-blue.svg" />
  </a>
</p>

## About
This is my personal lightly patched build of [dwm](https://dwm.suckless.org/).

## Patches
- autostart
- bar-height
- gaps
- movestack
- restartsig
- custom status bar patches (no .diff files)

## Expected packages
- alacritty
- dmenu
- firefox
- ranger
- nautilus

These are the packages which need to be installed on your system for the default keybindings to function properly. All bindings can easily be changed by modifying `config.h`.

## Keybindings

By default `MOD` refers to the `SUPER` key.

### Programs
| Keybinding |  Action|
|:-----|------:|
| MOD + RETURN  | launch alacritty |
| MOD + W  | launch firefox |
| MOD + SHIFT + W  | launch firefox (private) |
| MOD + F  | launch ranger |
| MOD + SHIFT + F  | launch nautilus |

### General keybindings
| Keybinding |  Action|
|:-----|------:|
| MOD + Q | close window with focus |
| MOD + SHIFT + Q  | kill dwm |
| MOD + SHIFT + R  | restart dwm |
| MOD + B | toggle status bar |
| MOD + [1-9]  | go to tag [1-9]  |
| MOD + SHIFT + [1-9]  | push window to tag [1-9] |
| MOD + J  | change stack focus by +1 |
| MOD + K  | change stack focus by -1 |
| MOD + SHIFT + J  | move window up by one in stack |
| MOD + SHIFT + K  | move window down by one in stack  |
| MOD + H  | change master factor by -0.05 |
| MOD + L  | change master factor by +0.05|

### Layout keybindings
| Keybinding |  Action|
|:-----|------:|
| MOD + C | tiling layout |
| MOD + D | floating layout |
| MOD + X | monocle (fullscreen) layout |
| MOD + SPACE | toggle floating mode for window |
| MOD + CONTROL + J | increase gap between windows |
| MOD + CONTROL + K | decrease gap between windows |
| MOD + CONTROL + N | reset gap between windows |

### Mouse controls
| Keybinding |  Action|
|:-----|------:|
| L_CLICK + DRAG | move window (floating mode)|
| R_CLICK + DRAG | resize window (floating mode) |


## Author

**Mišo Barišić**

* Website: https://www.misobarisic.com
* GitHub: [@misobarisic](https://github.com/misobarisic)
