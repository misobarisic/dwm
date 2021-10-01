/* See LICENSE file for copyright and license details. */

#include <X11/X.h>

/* appearance */
static const unsigned int arrowpx   = 12;       /* arrow size in px */
static const unsigned int s_arrowpx = 12;       /* arrow size in px */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 2;        /* gap pixel between windows */
static const unsigned int sidegappx = 8;        /* gap pixel between layout and sides */
static const unsigned int cornerrad = 0;		/* corner radius */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "size=11", "FontAwesome:size=12" };
static const char dmenufont[]       = "monospace:size=11";
static const char col_bg_n[]        = "#1F2937"; /* tailwind gray 800 */
static const char col_bg_s[]        = "#3f51b5"; /* indigo 500 */
static const char col_fg_n[]        = "#eeeeee";
static const char col_fg_s[]        = "#eeeeee";
static const char col_wb_s[] 	    = "#536dfe"; /* indigo a200 */
static const char col_wb_n[]	    = "#444444";
static const char col_active[]	    = "#d81b60"; /* pink 600 */
static const char *colors[][3]      = {
	/*                      fg        bg        border   */
	[SchemeNorm] 		= { col_fg_n, col_bg_n, col_wb_n },
	[SchemeSel]  		= { col_fg_s, col_bg_s, col_wb_s },
	[SchemeInfoNorm] 	= { col_fg_n, col_bg_n, col_wb_n },
	[SchemeInfoSel]  	= { col_fg_s, col_bg_s, col_wb_s },
	[SchemeStatus] 		= { col_fg_n, col_bg_n, col_wb_n },
	[SchemeActive]		= { col_fg_n, col_active, col_wb_s },
	[ArrowNorm]	    	= { col_bg_s, col_bg_n, col_wb_s },
	[ArrowNormWhite]	= { col_fg_s, col_bg_n, col_wb_s },
	[ArrowNormAlt]		= { col_bg_s, col_active, col_wb_s },
	[ArrowSel] 	    	= { col_bg_n, col_bg_s, col_wb_s },
	[ArrowSelWhite] 	= { col_fg_s, col_bg_s, col_wb_s },
	[ArrowSelAlt] 		= { col_active, col_bg_s, col_wb_s },
	[ArrowBg] 	    	= { col_bg_n, col_bg_n, col_wb_s },
	[ArrowActive]   	= { col_active, col_bg_n, col_wb_s },
	[ArrowActiveAlt]	= { col_bg_n, col_active, col_wb_s },
	[ArrowFullActive]	= { col_active, col_active, col_wb_s },
};

/* bar height */
static const int user_bh = 28; /* 0 means that dwm will calculate bar height */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "--firefox", NULL,       NULL,       1 << 8,       0,           -1 },
	{ "--Brave-browser",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Galculator",  NULL,       NULL,       0,       1,           -1 },
	{ "Yad",  NULL,       NULL,       0,       1,           -1 },
	{ "discord",  NULL,       NULL,       0,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "barpos.c"
#include "corners.c"
#include "fibonacci.c"
#include "gaps.c"
#include "layouts.c"
#include "movestack.c"
#include "tags.c"
#include "volume.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tilegaps },    /* first entry is default */
	{ "[t]",      tile },   
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[G]",      grid },
	{ "[@]",      spiral },
 	{ "[\\]",     dwindle },
	{ NULL, NULL}
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = TAG} }, \
	{ MODKEY|ControlMask,           KEY,      viewtag,        {.ui = TAG} }, \
	/*{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, */
	
#define Prnt	    0x0000ff61

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run","-m", dmenumon, "-fn", dmenufont, "-nb", col_bg_n, "-nf", col_fg_n, "-sb", col_bg_s, "-sf", col_fg_s, NULL };
static const char *alacrittycmd[]  = { "alacritty", NULL };
static const char *flameshotgui[]  = { "flameshot", "gui", NULL };
static const char *flameshotfull[]  = { "flameshot", "full", "-p", "/home/mb/", NULL };
static const char *kittycmd[]  = { "kitty", NULL };
static const char *stcmd[]  = { "st", NULL };
static const char *browsercmd[]  = { "firefox", NULL };
static const char *browserpcmd[]  = { "firefox","--private-window", NULL };
static const char *filecmd[]  = { "nemo", NULL };
static const char *rangercmd[]  = { "alacritty", "-e", "ranger", NULL };
static const char *nitrogencmd[]  = { "nitrogen", NULL };
static const char *officecmd[]  = { "libreoffice", NULL };
static const char *gimpcmd[]  = { "gimp", NULL };
static const char *emailcmd[]  = { "thunderbird", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = alacrittycmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = stcmd } },
	{ MODKEY|ControlMask,           XK_Return, spawn,          {.v = kittycmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = browsercmd } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = browserpcmd } },
	{ MODKEY,                       XK_f,      spawn,          {.v = rangercmd } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = filecmd } },
	{ MODKEY,                       XK_e,      spawn,          {.v = emailcmd } },
	{ MODKEY,                       XK_r,      spawn,          {.v = officecmd } },
	{ MODKEY,                       XK_g,      spawn,          {.v = gimpcmd } },
	{ MODKEY,                       XK_t,      spawn,          {.v = nitrogencmd } },

	// Flameshot
	{ 0,                            Prnt,      spawn,          {.v = flameshotgui } },
	{ MODKEY,                       Prnt,      spawn,          {.v = flameshotfull } },

	// Picom control
	{ MODKEY|ShiftMask,             XK_o,      spawn,          SHCMD("kill $(pidof picom)") },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("picom") },

	// dwmblocks
	{ MODKEY|ShiftMask,             XK_l,      spawn,          SHCMD("killall dwmblocks; notify-send -t 2000 -u low 'Restarted dwmblocks'; dwmblocks") },

	// backlight controls (acpilight)
	{ MODKEY|ShiftMask,             XK_t,      spawn,          SHCMD("xbacklight -5") },
	{ MODKEY|ShiftMask,             XK_z,      spawn,          SHCMD("xbacklight +5") },

	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} }, /* kill dwm */
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} }, /* restart dwm */

	{ MODKEY,                       XK_q,      killclient,     {0} }, // Close window
	{ MODKEY,                       XK_b,      togglebar,      {0} }, // Switch bar on/off
	{ MODKEY|ShiftMask,             XK_b,      changebarpos,   {0} }, // Move between up and down

	// Volume controls
	{ MODKEY|ShiftMask,             XK_i,      increaseVolume, {0} },
	{ MODKEY|ShiftMask,             XK_u,      decreaseVolume, {0} },
	{ MODKEY|ShiftMask,             XK_m,      muteVolume,     {0} },

	// Stack controls
	{ MODKEY,                       XK_k,      focusstack,     {.i = +1 } }, 
	{ MODKEY,                       XK_j,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = +1} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = -1} },

	// Relative controls
	{ MODKEY,                       XK_s,      relativeview,   {.i = +1} },
	{ MODKEY,                       XK_a,      relativeview,   {.i = -1} },
	{ MODKEY|ShiftMask,             XK_s,      relativemoveview,   {.i = +1} },
	{ MODKEY|ShiftMask,             XK_a,      relativemoveview,   {.i = -1} },
	{ MODKEY|ShiftMask,             XK_x,      relativemove,   {.i = +1} },
	{ MODKEY|ShiftMask,             XK_y,      relativemove,   {.i = -1} },

        // Corner controls
	{ MODKEY|ShiftMask,             XK_e,      togglecorners,  {0} },

	{ MODKEY,			XK_m,      cyclelayout,    {.i = +1 } },
	{ MODKEY,             	        XK_n,      cyclelayout,    {.i = -1 } },
	
        // Inner gaps
	{ MODKEY|ControlMask,   	XK_k,      modifygaps,     {.i = +12} },
	{ MODKEY|ControlMask,           XK_j,      modifygaps,     {.i = -12} },
	{ MODKEY|ControlMask,           XK_n,      setgaps,        {.i = gappx} },

    	// Outer gaps
	{ MODKEY|ControlMask,   	XK_i,      modifysidegaps, {.i = +12} },
	{ MODKEY|ControlMask,           XK_u,      modifysidegaps, {.i = -12} },
	{ MODKEY|ControlMask,           XK_m,      setsidegaps,    {.i = sidegappx} },

	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_d,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_x,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	// { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	// { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	// { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	// { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	// { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	// { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	//TAGKEYS(                        XK_9,                      8)
	};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = alacrittycmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
