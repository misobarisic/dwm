void grid(Monitor *m) {
  unsigned int i, n, cx, cy, cw, ch, aw, ah, cols, rows;
  Client *c;

  for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next))
    n++;

  /* grid dimensions */
  for (rows = 0; rows <= n / 2; rows++)
    if (rows * rows >= n)
      break;
  cols = (rows && (rows - 1) * rows >= n) ? rows - 1 : rows;

  /* window geoms (cell height/width) */
  ch = m->wh / (rows ? rows : 1);
  cw = m->ww / (cols ? cols : 1);
  for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next)) {
    cx = m->wx + (i / rows) * cw;
    cy = m->wy + (i % rows) * ch;
    /* adjust height/width of last row/column's windows */
    ah = ((i + 1) % rows == 0) ? m->wh - ch * rows : 0;
    aw = (i >= rows * (cols - 1)) ? m->ww - cw * cols : 0;
    resize(c, cx, cy, cw - 2 * c->bw + aw, ch - 2 * c->bw + ah, False);
    i++;
  }
}

void tilegaps(Monitor *m) {
  unsigned int i, n, h, r, g = 0, mw, my, ty;
  Client *c;

  for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++)
    ;
  if (n == 0)
    return;

  if (n > m->nmaster) {
    mw = m->nmaster ? (m->ww - (g = m->gappx)) * m->mfact : 0;
  } else {
    mw = m->ww;
  }

  for (i = 0, my = ty = m->sidegappx * 2, c = nexttiled(m->clients); c;
       c = nexttiled(c->next), i++)
    if (i < m->nmaster) {
      r = MIN(n, m->nmaster) - i;
      h = ((m->wh - my - m->gappx * (r - 1)) / r);
      resize(c, m->wx + m->sidegappx, m->wy + my - m->sidegappx,
             mw - (2 * c->bw) - m->sidegappx -
                 (nexttiled(c->next) != NULL
                      ? 0
                      : m->sidegappx), // Check if there's only 1 window
                                       // present. If true, add right padding
             h - (2 * c->bw), 0);
      if (my + HEIGHT(c) < m->wh)
        my += HEIGHT(c) + m->gappx;
    } else {
      r = n - i;
      h = (m->wh - ty - m->gappx * (r - 1)) / r;
      resize(c, m->wx + mw + g, m->wy + ty - m->sidegappx,
             m->ww - mw - g - (2 * c->bw) - m->sidegappx, h - (2 * c->bw),
             False);
      if (ty + HEIGHT(c) < m->wh)
        ty += HEIGHT(c) + m->gappx;
    }
}
