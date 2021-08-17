void relativemove(const Arg *arg) {
  if (selmon->sel && arg->i) {
    int endtag = selmon->selectedtag + arg->i;
    if (endtag < 0 || endtag > LENGTH(tags) - 1)
      return;
    selmon->sel->tags = 1 << endtag;
    focus(NULL);
    arrange(selmon);
  }
}

void relativeview(const Arg *arg) {
  int newmon = selmon->selectedtag + arg->i;
  if (newmon < 0 || newmon > LENGTH(tags) - 1)
    return;
  int endtag = 1 << newmon;
  if ((endtag & TAGMASK) == selmon->tagset[selmon->seltags])
    return;
  selmon->seltags ^= 1;
  if (endtag & TAGMASK)
    selmon->tagset[selmon->seltags] = endtag & TAGMASK;
  selmon->selectedtag = newmon;
  focus(NULL);
  arrange(selmon);
}

void relativemoveview(const Arg *arg) {
  if (selmon->sel && arg->i) {
    int endtag = selmon->selectedtag + arg->i;
    if (endtag < 0 || endtag > LENGTH(tags) - 1)
      return;
    selmon->sel->tags = 1 << endtag;
  }
  int newmon = selmon->selectedtag + arg->i;
  int endtag = 1 << newmon;
  if (endtag & TAGMASK)
    selmon->tagset[selmon->seltags] = endtag & TAGMASK;
  selmon->selectedtag = newmon;
  focus(NULL);
  arrange(selmon);
}

void viewtag(const Arg *arg) {
  int endtag = 1 << arg->ui;
  if (selmon->sel && endtag) {
    selmon->sel->tags = endtag & TAGMASK;
    selmon->selectedtag = arg->ui;
    focus(NULL);
    view(arg);
    arrange(selmon);
  }
}