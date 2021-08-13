void increaseVolume(const Arg *arg) {
  system("cd ~/.config/dwm; ./volume_increase.sh");
}

void decreaseVolume(const Arg *arg) {
  system("cd ~/.config/dwm; ./volume_decrease.sh");
}

void muteVolume(const Arg *arg) {
  system("cd ~/.config/dwm; ./volume_mute.sh");
}
