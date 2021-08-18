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
  int i;
	unsigned int tmptag;

  int newmon = selmon->selectedtag + arg->i;
  if (newmon < 0 || newmon > LENGTH(tags) - 1)
    return;
  int endtag = 1 << newmon;
  if ((endtag & TAGMASK) == selmon->tagset[selmon->seltags])
    return;
  selmon->seltags ^= 1;
  if (endtag & TAGMASK) {
    selmon->tagset[selmon->seltags] = endtag & TAGMASK;
    selmon->tagdata->prevtag = selmon->tagdata->curtag;

		if (endtag == ~0)
			selmon->tagdata->curtag = 0;
		else {
			for (i = 0; !(endtag& 1 << i); i++) ;
			selmon->tagdata->curtag = i + 1;
		}
	} else {
		tmptag = selmon->tagdata->prevtag;
		selmon->tagdata->prevtag = selmon->tagdata->curtag;
		selmon->tagdata->curtag = tmptag;
	}

	selmon->nmaster = selmon->tagdata->nmasters[selmon->tagdata->curtag];
	selmon->mfact = selmon->tagdata->mfacts[selmon->tagdata->curtag];
	selmon->sellt = selmon->tagdata->sellts[selmon->tagdata->curtag];
	selmon->lt[selmon->sellt] = selmon->tagdata->ltidxs[selmon->tagdata->curtag][selmon->sellt];
	selmon->lt[selmon->sellt^1] = selmon->tagdata->ltidxs[selmon->tagdata->curtag][selmon->sellt^1];

	if (selmon->showbar != selmon->tagdata->showbars[selmon->tagdata->curtag])
		togglebar(NULL);

  selmon->selectedtag = newmon;
  focus(NULL);
  arrange(selmon);
}

void relativemoveview(const Arg *arg) {
  int i;
	unsigned int tmptag;

  if (selmon->sel && arg->i) {
    int endtag = selmon->selectedtag + arg->i;
    if (endtag < 0 || endtag > LENGTH(tags) - 1)
      return;
    selmon->sel->tags = 1 << endtag;
  }
  int newmon = selmon->selectedtag + arg->i;
  int endtag = 1 << newmon;
  if (endtag & TAGMASK) {
    selmon->tagset[selmon->seltags] = endtag & TAGMASK;
    selmon->tagdata->prevtag = selmon->tagdata->curtag;

		if (endtag == ~0)
			selmon->tagdata->curtag = 0;
		else {
			for (i = 0; !(endtag& 1 << i); i++) ;
			selmon->tagdata->curtag = i + 1;
		}
	} else {
		tmptag = selmon->tagdata->prevtag;
		selmon->tagdata->prevtag = selmon->tagdata->curtag;
		selmon->tagdata->curtag = tmptag;
	}

	selmon->nmaster = selmon->tagdata->nmasters[selmon->tagdata->curtag];
	selmon->mfact = selmon->tagdata->mfacts[selmon->tagdata->curtag];
	selmon->sellt = selmon->tagdata->sellts[selmon->tagdata->curtag];
	selmon->lt[selmon->sellt] = selmon->tagdata->ltidxs[selmon->tagdata->curtag][selmon->sellt];
	selmon->lt[selmon->sellt^1] = selmon->tagdata->ltidxs[selmon->tagdata->curtag][selmon->sellt^1];

	if (selmon->showbar != selmon->tagdata->showbars[selmon->tagdata->curtag])
		togglebar(NULL);
    
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