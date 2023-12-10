/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;		/* 0 means bottom bar */
static const int user_bh            = 25;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static int smartgaps                = 0;        /* 1 means no outer gap when there is only one window */
static const int decorhints			= 1;	   /* 1 means respect decoration hints */

static const char *fonts[]          = { "Hack Nerd Font:size=11:style=Bold" };  /*{ "monospace:size=10" };*/
static const char dmenufont[]       = "Source Code Pro:size=11:style=Bold"; /*"monospace:size=10";*/

static const char red[]       = "#f28fad";
static const char orange[]    = "#f8bd96";
static const char yellow[]    = "#fae3b0";
static const char green[]     = "#abe9b3";
static const char cyan[]      = "#89dceb";
static const char blue[]	  = "#7aa2f7";
static const char pink[]	  = "#bb9af7";
static const char white[]	  = "#d9e0ee";
static const char cream[]	  = "#c3bac6";
static const char indigo[]	  = "#575268";
static const char dark[]	  = "#302d41";
/*static const char black[]	  = "#1a1823";*/
static const char black[]	  = "#000000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { white, black, black },
	[SchemeSel]  = { black, white,  white },
};

/* tagging */
static const char *tags[] = { "", "󰍳", "󰇥", "󱢢", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	//{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Eww",	  NULL,       NULL,       0,			1,			 -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
#include <X11/XF86keysym.h>

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ " ",      tile },    /* first entry is default */
	{ "󰧱",      NULL },    /* no layout function means floating behavior */
	//{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, NULL };
//static const char *termcmd[]  = { "alacritty", NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *browser[]	 = { "chromium-browser", NULL };
static const char *filemanager[] = { "pcmanfm", NULL };
static const char *wallpaper[]   = { "nitrogen", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	//{ MODKEY,                       XK_r,      spawn,		   SHCMD("~/scripts/menu.sh") },
	{ MODKEY,		                XK_Return, spawn,          {.v = termcmd } },
	//{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_Right,  focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Left,   focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,	            XK_Left,   incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,	            XK_Right,  incnmaster,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_Left,   setmfact,       {.f = -0.05} },
	{ MODKEY|ControlMask,           XK_Right,  setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Up,	   zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,						XK_q,      killclient,     {0} },
	//{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	//{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	//{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	//{ MODKEY,                       XK_space,  setlayout,      {0} },
	//{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask|ShiftMask, XK_End, 				 quit,         {0} },
	{ MODKEY|ControlMask,           XK_Up,     				 setcfact,     {.f = +0.25} },
	{ MODKEY|ControlMask,           XK_Down,   				 setcfact,	   {.f = -0.25} },
	{ MODKEY,						XK_b,	   				 spawn,		   {.v = browser } },
	{ MODKEY,						XK_f,	   				 spawn,		   {.v = filemanager } },
	{ MODKEY,						XK_w,					 spawn,		   {.v = wallpaper } },
	{0,								XF86XK_AudioLowerVolume, spawn,		   SHCMD("amixer -q sset Master 5%-") },
	{0,								XF86XK_AudioRaiseVolume, spawn,		   SHCMD("amixer -q sset Master 5%+") },
	{0,								XF86XK_AudioMute,		 spawn,		   SHCMD("amixer -q sset Master toggle") },
	{ MODKEY,						XK_Print,				 spawn,		   SHCMD("flameshot full -p ~/Pictures/screenshots") },
	{ MODKEY,						XK_t,					 spawn,		   SHCMD("$HOME/dwm-kiefciman/trayer.sh") },
	{0,								XF86XK_MonBrightnessDown,spawn,		   SHCMD("brightnessctl set 5%-") },	
	{0,								XF86XK_MonBrightnessUp,  spawn,		   SHCMD("brightnessctl set +5%") },	
	{ MODKEY,						XK_d,					 spawn,		   SHCMD("~/scripts/dashboard.sh") },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

