/* See LICENSE file for copyright and license details. */
/* Constants */
#define TERMINAL "alacritty"
#define TERMCLASS "Alacritty"

/* appearance */
static const unsigned int borderpx  = 1;
static const unsigned int snap      = 10;
static const unsigned int gappih    = 0;
static const unsigned int gappiv    = 0;
static const unsigned int gappoh    = 0;
static const unsigned int gappov    = 0;
static const int swallowfloating    = 0;
static const int smartgaps          = 1;
static const int showbar            = 1;
static const int topbar             = 1;
#define ICONSIZE 17   /* icon size */
#define ICONSPACING 7 /* space between icon and title */
static const char *fonts[]          = {"dina:size=10" , "Font Awesome 6 Free:pixelsize=12"  }; 
static char dmenufont[]             = "monospace:size=13";
static char normbgcolor[]           = "#282828"; 
static char normbordercolor[]       = "#000000"; 
static char normfgcolor[]           = "#d5c4a1"; 
static char selfgcolor[]            = "#ffb52a"; 
static char selbordercolor[]        = "#ffef00"; 
static char selbgcolor[]            = "#282828"; 
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class    instance      title       	 tags mask    isfloating   isterminal  noswallow  monitor */
//{ "Gimp",     NULL,       NULL,       	    1 << 8,       0,           0,         0,        -1 },
	{ TERMCLASS,   NULL,       NULL,       	    0,            0,           1,         0,        -1 },
	{ NULL,       NULL,       "Event Tester",   0,            0,           0,         1,        -1 },
	{ NULL,      "spterm",    NULL,       	    SPTAG(0),     1,           1,         0,        -1 },
	{ NULL,      "spcalc",    NULL,       	    SPTAG(1),     1,           1,         0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "[]=",	tile },			 /* Default: Master on left, slaves on right */
	{ "=",	bstack },		 /* Master on top, slaves on bottom */

	{ "[@]",	spiral },		 /* Fibonacci spiral */
	{ "[\\]",	dwindle },		 /* Decreasing in size right and leftward */

	{ "H[]",	deck },			 /* Master on left, slaves in monocle-like mode on right */
 	{ "[M]",	monocle },		 /* All windows on top of eachother */

	{ "|M|",	centeredmaster },		/* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster },	/* Same but master floats */

	{ "><>",	NULL },			 /* no layout function means floating behavior */
	{ NULL,		NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"
static Key keys[] = {
	/* modifier         key        function    argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	TAGKEYS(			XK_1,		0)
	TAGKEYS(			XK_2,		1)
	TAGKEYS(			XK_3,		2)
	TAGKEYS(			XK_4,		3)
	TAGKEYS(			XK_5,		4)
	TAGKEYS(			XK_6,		5)
	TAGKEYS(			XK_7,		6)
	TAGKEYS(			XK_8,		7)
	TAGKEYS(			XK_9,		8)
	{ MODKEY,			XK_0,		view,		{.ui = ~0 } },
	{ MODKEY,			XK_Tab,		view,		{0} },
	{ MODKEY|ShiftMask,	XK_0,		tag,		{.ui = ~0 } },
	{ MODKEY,			XK_q,		killclient,	{0} },
	{ MODKEY,			XK_t,		setlayout,	{.v = &layouts[0]} }, /* tile */
	{ MODKEY|ShiftMask,	XK_t,		setlayout,	{.v = &layouts[1]} }, /* bstack */
	{ MODKEY,			XK_y,		setlayout,	{.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,	XK_y,		setlayout,	{.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,			XK_u,		setlayout,	{.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,	XK_u,		setlayout,	{.v = &layouts[5]} }, /* monocle */
	{ MODKEY,			XK_i,		setlayout,	{.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,	XK_i,		setlayout,	{.v = &layouts[7]} }, /* centeredfloatingmaster */
	{ MODKEY,			XK_a,		togglegaps,	{0} },
	{ MODKEY|ShiftMask,	XK_a,		defaultgaps,{0} },
	{ MODKEY,			XK_s,		togglesticky,{0} },
	//{ MODKEY,			XK_d,		spawn,      {.v = dmenucmd } },
	{ MODKEY,	        XK_d,		spawn,		SHCMD("dmenu_run") },
	{ MODKEY,			XK_f,		togglefullscr,	{0} },
	{ MODKEY,			XK_h,		setmfact,	{.f = -0.05} },
	{ MODKEY,			XK_l,		setmfact,   {.f = +0.05} },
	{ MODKEY,			XK_Return,	spawn,		{.v = termcmd } },
	{ MODKEY,			XK_z,		incrgaps,	{.i = +3 } },
	{ MODKEY,			XK_x,		incrgaps,	{.i = -3 } },
	{ MODKEY,			XK_b,		togglebar,	{0} },
	{ MODKEY|ControlMask,XK_j,		focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask,	XK_j,		tagmon,		{.i = -1 } },
	{ MODKEY|ControlMask,XK_k,		focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask,	XK_k,		tagmon,		{.i = +1 } },
	{ MODKEY,			XK_space,	zoom,		{0} },
	{ MODKEY|ShiftMask,	XK_space,	togglefloating,	{0} },
	{ MODKEY,			XK_r,		spawn,		SHCMD(TERMINAL " -e ranger") },
	{ MODKEY,			XK_w,		spawn,		SHCMD("$BROWSER") },
	{ MODKEY,			XK_c,		spawn,		SHCMD("chatterino") },
	{ MODKEY,	        XK_v,		spawn,		SHCMD("noti") },
	{ MODKEY|ShiftMask,	XK_p,		spawn,		SHCMD("maimpick") },
	{ MODKEY,			XK_p,		spawn,		SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ MODKEY,			XK_F11,		spawn,		SHCMD("mpv --no-cache --no-osc --no-input-default-bindings --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
	{ 0, XF86XK_AudioMute,      	spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_PowerOff,	    	spawn,		SHCMD("sysact") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("light -A 5") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("light -U 5") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
#endif
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,	{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin, 		MODKEY, 		Button4,    	incrgaps,	{.i = +1} },
	{ ClkClientWin, 		MODKEY, 		Button5,    	incrgaps,	{.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,    		0,        		Button4,    	shiftview,	{.i = -1} },
	{ ClkTagBar,    		0,      		Button5,    	shiftview,	{.i = 1} },
	{ ClkRootWin,   		0,		        Button2,    	togglebar,	{0} },
};
