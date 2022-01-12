void brightUp(const Arg *arg) {
  char buffer[100];
  sprintf(buffer, "cd ~/.scripts/dwm; ./bright_up.sh %d &", arg->i);
  system(buffer);
}

void brightDown(const Arg *arg) {
  char buffer[100];
  sprintf(buffer, "cd ~/.scripts/dwm; ./bright_down.sh %d &", arg->i);
  system(buffer);
}
