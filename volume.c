void increaseVolume(const Arg *arg) {
  system("cd ~/.scripts/dwm; ./volume_increase.sh &");
}

void decreaseVolume(const Arg *arg) {
  system("cd ~/.scripts/dwm; ./volume_decrease.sh &");
}

void muteVolume(const Arg *arg) {
  system("cd ~/.scripts/dwm; ./volume_mute.sh &");
}
