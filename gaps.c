void
setgaps(const Arg *arg) {
	if (arg->i == 0)
		selmon->gappx = gappx;
	else
		selmon->gappx = arg->i;
	arrange(selmon);
}

void
modifygaps(const Arg *arg) {
	if ((arg->i == 0) || (selmon->gappx + arg->i < 0))
		selmon->gappx = 0;
	else
		selmon->gappx += arg->i;
	arrange(selmon);
}
