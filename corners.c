// Works corrently only in tiling mode
#include <X11/Xlib.h>
void roundcorners(Client *c) {
  Window w = c->win;
  XWindowAttributes wa;
  XGetWindowAttributes(dpy, w, &wa);

  // Borders
  if (c->mon->cornerrad > 0) {
    c->mon->borderpx = borderpx;
  }
  else {
    c->mon->borderpx = borderpx;
  }

  // If this returns null, the window is invalid.
  if (!XGetWindowAttributes(dpy, w, &wa))
    return;

  int width = c->mon->borderpx * 2 + wa.width;
  int height = c->mon->borderpx * 2 + wa.height;
  /* int width = win_attr.border_width * 2 + win_attr.width; */
  /* int height = win_attr.border_width * 2 + win_attr.height; */
  int rad = c->mon->cornerrad;
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

  XSetForeground(dpy, shape_gc, 0);
  XFillRectangle(dpy, mask, shape_gc, 0, 0, width, height);
  XSetForeground(dpy, shape_gc, 1);

  if (c->mon->cornerrad > 0 && &tile == c->mon->lt[c->mon->sellt]->arrange) {
    // Rounded corners - X Y W H
    XFillArc(dpy, mask, shape_gc, 0, 0, dia, dia, 0, 23040);
    XFillArc(dpy, mask, shape_gc, width - dia, 0, dia, dia, 0,23040);
    XFillArc(dpy, mask, shape_gc, 0, height - dia, dia, dia, 0,23040);
    XFillArc(dpy, mask, shape_gc, width - dia, height - dia, dia, dia, 0, 23040);

    //XFillArc(dpy, mask, shape_gc, 0, 0, dia, dia, 0, 23040);
    //XFillArc(dpy, mask, shape_gc, width - dia - borderpx, 0, dia, dia, 0,23040);
    //XFillArc(dpy, mask, shape_gc, 0, height - dia, dia, dia, 0,23040);
    //XFillArc(dpy, mask, shape_gc, width - dia - borderpx, height - dia, dia, dia, 0, 23040);
  } else {
    // Square (normal) corners - X Y W H
    XFillRectangle(dpy, mask, shape_gc, 0, 0, dia, dia);
    XFillRectangle(dpy, mask, shape_gc, width - dia, 0, dia, dia);
    XFillRectangle(dpy, mask, shape_gc, 0, height - dia, dia, dia);
    XFillRectangle(dpy, mask, shape_gc, width - dia, height - dia, dia, dia);

    //XFillRectangle(dpy, mask, shape_gc, 0, 0, dia, dia);
    //XFillRectangle(dpy, mask, shape_gc, width - dia - 1 - borderpx, 0, dia, dia);
    //XFillRectangle(dpy, mask, shape_gc, 0, height - dia - 1, dia, dia);
    //XFillRectangle(dpy, mask, shape_gc, width - dia - 1 - borderpx, height - dia - 1 - 3, dia, dia);
  }

  // Fill everything else
  XFillRectangle(dpy, mask, shape_gc, rad, 0, width - dia, height);
  XFillRectangle(dpy, mask, shape_gc, 0, rad, width, height - dia);
  XShapeCombineMask(dpy, w, ShapeBounding, 0 - wa.border_width,
                    0 - wa.border_width, mask, ShapeSet);
  XFreePixmap(dpy, mask);
  XFreeGC(dpy, shape_gc);
}

// Doesn't play nicely with previously opened windows
// Has no effect when cornerrad = 0
void togglecorners(const Arg *arg) {
  if (selmon->cornerrad > 0) {
    selmon->cornerrad = 0;
    selmon->borderpx = 0;
  } else {
    selmon->cornerrad = cornerrad;
    selmon->borderpx = borderpx;
  }
  arrange(selmon);
}