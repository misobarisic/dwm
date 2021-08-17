// Works corrently only in tiling mode
void roundcorners(Client *c) {
  Window w = c->win;
  XWindowAttributes wa;
  XGetWindowAttributes(dpy, w, &wa);

  // Borders
  if (c->mon->cornerrad > 0)
    c->mon->borderpx = 0;
  else {
    c->mon->borderpx = borderpx;
  }

  // If this returns null, the window is invalid.
  if (!XGetWindowAttributes(dpy, w, &wa))
    return;

  int width = borderpx * 2 + wa.width;
  int height = borderpx * 2 + wa.height;
  /* int width = win_attr.border_width * 2 + win_attr.width; */
  /* int height = win_attr.border_width * 2 + win_attr.height; */
  int rad = cornerrad;
  int dia = 2 * rad;

  // do not try to round if the window would be smaller than the corners
  if (width < dia || height < dia)
    return;

  Pixmap mask = XCreatePixmap(dpy, w, width, height, 1);
  // if this returns null, the mask is not drawable
  if (!mask)
    return;

  XGCValues xgcv;
  GC shape_gc = XCreateGC(dpy, mask, 0, &xgcv);
  if (!shape_gc) {
    XFreePixmap(dpy, mask);
    return;
  }

  if (c->mon->cornerrad > 0) {
    XSetForeground(dpy, shape_gc, 0);
    XFillRectangle(dpy, mask, shape_gc, 0, 0, width, height);
    XSetForeground(dpy, shape_gc, 1);
    XFillArc(dpy, mask, shape_gc, 0, 0, dia, dia, 0, 23040);
    XFillArc(dpy, mask, shape_gc, width - dia - 1 - borderpx, 0, dia, dia, 0,
             23040);
    XFillArc(dpy, mask, shape_gc, 0, height - dia - 1, dia, dia-borderpx, 0, 23040);
    XFillArc(dpy, mask, shape_gc, width - dia - 1 - borderpx,
             height - dia - 1 - 3, dia, dia, 0, 23040);
    XFillRectangle(dpy, mask, shape_gc, rad, 0, width - dia, height);
    XFillRectangle(dpy, mask, shape_gc, 0, rad, width, height - dia);
    XShapeCombineMask(dpy, w, ShapeBounding, 0 - wa.border_width,
                      0 - wa.border_width, mask, ShapeSet);
  }

  XFreePixmap(dpy, mask);
  XFreeGC(dpy, shape_gc);
}

// Doesn't play nicely with previously opened windows
// Has no effect when cornerrad = 0
void togglecorners(const Arg *arg) {
  if (selmon->cornerrad > 0)
    selmon->cornerrad = 0;
  else
    selmon->cornerrad = cornerrad;
  arrange(selmon);
}