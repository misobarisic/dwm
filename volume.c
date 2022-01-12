void increaseVolume(const Arg *arg) {
  char buffer[100];
  sprintf(buffer, "cd ~/.scripts/dwm; ./volume_increase.sh %d &", arg->i);
  system(buffer);
}

void decreaseVolume(const Arg *arg) {
  char buffer[100];
  sprintf(buffer, "cd ~/.scripts/dwm; ./volume_decrease.sh %d &", arg->i);
  system(buffer);
}

void muteVolume(const Arg *arg) {
  system("cd ~/.scripts/dwm; ./volume_mute.sh &");
}
