void
changebarpos(const Arg *arg)
{
	selmon->topbar = !selmon->topbar;
	updatebarpos(selmon);
	XMoveResizeWindow(dpy, selmon->barwin, selmon->wx, selmon->by, selmon->ww, bh);
	arrange(selmon);
}