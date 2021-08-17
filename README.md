<h1 align="center">Welcome to dwm</h1>
<p>
  <a href="https://github.com/misobarisic/dwm/blob/master/LICENSE" target="_blank">
    <img alt="License: MIT" src="https://img.shields.io/badge/License-MIT-blue.svg" />
  </a>
</p>

## About
This is my personal build of [dwm](https://dwm.suckless.org/).

## Patches
- autostart
- bar-height
- fibonacci layout
- gaps
- movestack
- restartsig
- custom patches (no .diff files)

## Custom patches
- modified drawbar, tile and view functions
- barpos.c
- gaps.c
- tags.c
- volume.c
- more but I've forgotten

## Expected packages
- alacritty
- dmenu
- firefox
- ranger
- nemo

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
| MOD + SHIFT + F  | launch nemo |

### General keybindings
| Keybinding |  Action|
|:-----|------:|
| MOD + Q | close window with focus |
| MOD + SHIFT + Q  | kill dwm |
| MOD + SHIFT + R  | restart dwm |
| MOD + B | toggle status bar |
| MOD + SHIFT + B | change status bar position |
| MOD + [1-9]  | go to tag [1-9]  |
| MOD + SHIFT + [1-9]  | push window to tag [1-9] |
| MOD + J  | change stack focus by +1 |
| MOD + K  | change stack focus by -1 |
| MOD + SHIFT + J  | move window up by one in stack |
| MOD + SHIFT + K  | move window down by one in stack  |
| MOD + H  | change master factor by -0.05 |
| MOD + L  | change master factor by +0.05|

### Volume keybindings
| Keybinding |  Action|
|:-----|------:|
| MOD + SHIFT + M | toggle sound on/off |
| MOD + SHIFT + I  | increase volume by 5% |
| MOD + SHIFT + U  | decrease volume by 5% |

### Tag keybindings
| Keybinding |  Action|
|:-----|------:|
| MOD + [1-9]  | go to tag [1-9]  |
| MOD + SHIFT + [1-9]  | push window to tag [1-9] |
| MOD + CONTROL + [1-9]  | combination of the previous two |
| MOD + S  | go to next tag |
| MOD + A | go to previous tag |
| MOD + SHIFT + S  | move window to next tag and go there |
| MOD + SHIFT + A | move window to previous tag and go there |
| MOD + SHIFT + X  | move window to next tag |
| MOD + SHIFT + Y | move window to previous tag |

### Layout keybindings
| Keybinding |  Action|
|:-----|------:|
| MOD + C | tiling layout |
| MOD + D | floating layout |
| MOD + X | monocle (fullscreen) layout |
| MOD + SPACE | toggle floating mode for window |
| MOD + N | cycle layout +1 |
| MOD + M | cycle layout -1 |
| MOD + CONTROL + J | increase gap between windows |
| MOD + CONTROL + K | decrease gap between windows |
| MOD + CONTROL + N | reset gap between windows |
| MOD + CONTROL + U | increase gap between layout and sides |
| MOD + CONTROL + I | decrease gap between layout and sides |
| MOD + CONTROL + M | reset gap between layout and sides |

### Mouse controls
| Keybinding |  Action|
|:-----|------:|
| L_CLICK + DRAG | move window (floating mode)|
| R_CLICK + DRAG | resize window (floating mode) |


## Author

**Mišo Barišić**

* Website: https://www.misobarisic.com
* GitHub: [@misobarisic](https://github.com/misobarisic)
* GitLab: [@misobarisic](https://gitlab.com/misobarisic)
