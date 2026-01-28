/*$path.* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 20;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 26;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */
static const char *panel_str        = "tint2";
static const char *kb_str           = "svkbd";
static const char *fonts[]          = { "Hack Nerd Font Mono:size=13" };
static const char dmenufont[]       = "Hack Nerd Font Mono:size=12";
static const char svkbdfont[]       = "Hack Nerd Font Mono:size=22";
static const int kb_height_div      = 3;      /* height of the keyboard */
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_cyan_satu[]   = "#4C95B2";
static const char col_orange[]      = "#FF875F";
static const char col_orange_satu[] = "#C1883D";
static const char col_black[]       = "#000000";
static const char col_red[]         = "#ff0000";
static const char col_yellow[]      = "#ffff00";
static const char col_red_satu[]    = "#C34646";
static const char col_white[]       = "#ffffff";
static const char col_purple[]      = "#c70082";
static const char col_purple_satu[] = "#B55393";
static const char col_darkpurple[]  = "#8f005d";
static const char col_darkgray[]    = "#495057";
static const char col_gray_satu[]   = "#393939";
static const char col_green_satu[]  = "#50fa7b";

static const char theme_col_fg[] =  "#393939"; /* "#939393" "#393939" #939393 */
static const char theme_col_bg[] =  "#FF875F"; /* "#443166" "#bbbbbb"*/
static const char theme_col_text[] = "#393939"; /* "#bbbbbb" #393939*/

// Get display name
// xrandr -q | grep ' connected' | head -n 1 | cut -d ' ' -f1
static const char mon_name[]        = "eDP-1";

#ifndef _LIGHT_MODE_
#  define _HEAVY_MODE_

// Autostart information
static unsigned int child_pid = 0;
# if defined(_LIVE_MODE_)
static const char *(stup_prgs[17][7])    = {   // [Number_programs][Number_args]
# else
static const char *(stup_prgs[16][7])    = {   // [Number_programs][Number_args]
# endif
	/* prog path            arg1           arg2                          arg... */
	{ "picom",              NULL,          NULL,                         NULL,   NULL,    NULL, NULL },
	{ "blueman-applet",     NULL,          NULL,                         NULL,   NULL,    NULL, NULL },
	{ "bash",               "-c",          "bash /etc/p3ng0s/display.sh",     NULL,   NULL,    NULL, NULL },
	{ "bash",               "-c",          "feh --bg-fill $HOME/.wallpaper.png", NULL,   NULL,    NULL, NULL },
	{ "setxkbmap",          "-option",     "caps:escape",                NULL,   NULL,    NULL, NULL },
	{ "bash",               "-c",          "bash /etc/p3ng0s/bar.sh",     NULL,   NULL,    NULL, NULL },
	{ "/usr/bin/xautolock", "-locker",     "/etc/p3ng0s/locker.sh",      "-time", "15",  NULL },
	{ "/usr/lib/notification-daemon-1.0/notification-daemon",       NULL, NULL, NULL, NULL, NULL, NULL },
	{ "/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1",  NULL, NULL, NULL, NULL, NULL, NULL },
	{ "/usr/bin/flameshot", NULL,          NULL,                         NULL,   NULL,    NULL, NULL },
	{ "bash",               "-c",          "/usr/bin/conky -c /etc/p3ng0s/conkyconf",   NULL,   NULL,    NULL, NULL },
	{ "bash",               "-c",          "/usr/bin/tint2 -c /etc/p3ng0s/tint2conf", NULL,   NULL,    NULL, NULL },
	{ "bash",               "-c",          "sleep 30 && /usr/bin/kdeconnect-indicator", NULL,   NULL,    NULL, NULL }, // This needs a sleep since it bugs out with tint2 if you dont give it time to load
	{ "/usr/bin/redshift-gtk",  "-l48.856613:2.352222", "-b",               "1.0:0.6", NULL,  NULL, NULL },
	{ "/usr/bin/kdeconnectd",       NULL,          NULL,                    NULL, NULL,  NULL, NULL },
# if defined(_LIVE_MODE_)
	{ "bash",               "-c",          "sleep 5; sudo /usr/bin/calamares", NULL,   NULL,   NULL, NULL },
# endif
	{ NULL,                 NULL,          NULL,                         NULL,   NULL,    NULL, NULL }
};

#  include "startup.c"
#endif

//static const unsigned int baralpha  = 0xd0;
//static const unsigned int borderalpha = OPAQUE;

#define baralpha (0xff)
#define borderalpha (OPAQUE)

// The status bar colors
static const char *colors[][3]      = {
	/*                    fg              bg             border   */
	[SchemeNorm]     = { theme_col_text,    theme_col_bg,    theme_col_bg },    // \01
	[SchemeSel]      = { theme_col_bg,   theme_col_fg,       theme_col_fg },  // \02
	[SchemeWarn]     = { col_gray4,    col_orange_satu,  col_orange_satu },  // \03
	[SchemeUrgent]   = { col_red,    col_gray_satu,     col_gray_satu },     // \04
	[SchemeCustom]   = { col_gray4,    col_cyan_satu,    col_cyan_satu },    // \05
	[SchemeOk]       = { col_gray4,    col_green_satu,   col_green_satu},    // \06
};
static const unsigned int alphas[][3] = {
	/*                 fg      bg        border     */
	[SchemeNorm]   = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]    = { OPAQUE, baralpha, borderalpha },
	[SchemeWarn]   = { OPAQUE, baralpha, borderalpha },
	[SchemeUrgent] = { OPAQUE, baralpha, borderalpha },
	[SchemeCustom] = { OPAQUE, baralpha, borderalpha },
	[SchemeOk]     = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tagsalt[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	*	WM_CLASS(STRING) = instance, class
	*	WM_NAME(STRING) = title
	*/
	/* class      instance    title       tags mask  iscentered isfloating monitor */
	// Floating windows
	{ "conky",     NULL,       NULL,          0,        0,        1,         -1 },
	{ "ripdrag",    NULL,     NULL,          0,        0,        1,         -1 },
	{ "zenity",       NULL,     NULL,          0,      1,        1,         -1 },
	{ "Tint2",       NULL,     NULL,          511,      0,        1,         -1 },
	{ "svkbd",       NULL,     NULL,          511,      0,        1,         -1 },
	// Swalow windows
	{ "st",       NULL,     NULL,             0,        0,        0,         -1 },
	{ NULL,       NULL,     "tmux",           0,        0,        0,         -1 },
	{ "vivaldi-stable",        NULL, NULL,    0,        0,        0,         -1 },
	// Special tabs windows
	//{ "firefox",  NULL,        NULL,          1 << 7,   0,        0,         -1 },
	// floating centered windows
	{ NULL,        NULL,       "ranger",      0,        1,        1,         -1 },
	{ NULL,        NULL,       "newsboat",    0,        1,        1,         -1 },
	{ NULL,        NULL,       "neomutt",     0,        1,        1,         -1 },
	{ "gvim",      NULL,       NULL,          0,        1,        1,         -1 },
	{ "mpv",       NULL,       NULL,          0,        1,        1,         -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",        tile },  /* first entry is default */
	{ "[D]",        deck },    /* no layout function means floating behavior */
	{ "[M]",        monocle },
	{ "|M|",        centeredfloatingmaster },
	{ "|@|",        spiral },
};

/* key definitions Mod1 -> Alt */
//#define MODKEY Mod4Mask
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *svkbdcmd[] = { "svkbd-p3ng0s", "-fn", svkbdfont, "-r", "20", "-g", "\n", NULL };
static const char *roficmd[] = { "rofi", "-show", "drun", "-show-icons", "-theme",
	"/etc/p3ng0s/rofi.rasi", NULL };
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont,
	"-nb", theme_col_fg, "-nf", theme_col_bg, "-sb", theme_col_bg, "-sf", theme_col_fg,
	"-h", "27", "-bw", "0", NULL };
static const char *dmenushut[] = { "dmenu_shut", "-fn", dmenufont,
	"-nb", theme_col_fg, "-nf", theme_col_bg, "-sb", theme_col_bg, "-sf", theme_col_fg,
	"-h", "25", "-bw", "5", "-l", "5", "-c", NULL };
static const char *dmenusplain[] = { "dmenu_splain", "-fn", dmenufont,
	"-nb", theme_col_fg, "-nf", theme_col_bg, "-sb", theme_col_bg, "-sf", theme_col_fg,
	"-h", "25", "-bw", "p", "-l", "15", "-p", "$", "-b", NULL };
static const char *dmenuwin[] = { "dmenu_win", "-fn", dmenufont,
	"-nb", theme_col_fg, "-nf", theme_col_bg, "-sb", theme_col_bg, "-sf", theme_col_fg,
	"-h", "25", "-bw", "p", "-l", "15", "-p", "$", "-b", NULL };
static const char *dmenukeyb[] = { "dmenu_keyboard", "-fn", dmenufont,
	"-nb", theme_col_fg, "-nf", theme_col_bg, "-sb", theme_col_bg, "-sf", theme_col_fg,
	"-h", "25", "-bw", "p", "-l", "15", "-p", "$", "-b", NULL };
static const char *dmenuovpn[] = { "dmenu_ovpn", "-fn", dmenufont,
	"-nb", theme_col_fg, "-nf", theme_col_bg, "-sb", theme_col_bg, "-sf", theme_col_fg,
	"-h", "25", "-bw", "p", "-l", "15", "-p", "$", "-b", NULL };
static const char *dmenuemoji[] = { "dmenu_emoji", "-nb", theme_col_fg, "-nf",
	theme_col_bg, "-sb", theme_col_bg, "-sf", theme_col_fg, "-h", "25", "-bw",
	"p", "-l", "15", "-p", "$", "-b", NULL };

static const char *graphicalmenu[] = { "skippy-xd", NULL };

static const char *xmenucmd[]  = { "xmenu_run","-fn", dmenufont, "-nb", theme_col_fg,
	"-nf", theme_col_bg, "-sb", theme_col_bg, "-sf", theme_col_fg,
	"-bc", theme_col_bg, NULL };

static const char *termcmd[]  = { "st", NULL };
static const char *termcmd_tmux[]  = { "st", "tmux", NULL };
static const char *termcmd_tmuxer[]  = { "st", "/etc/p3ng0s/tmuxer.sh", NULL };
static const char *file_manager[]  = { "st", "ranger", NULL };
static const char *news_feed[]  = { "st", "newsboat", NULL };
static const char *display_manager[]  = { "/etc/p3ng0s/display.sh", NULL };
static const char *file_manager_gui[]  = { "nautilus", NULL };
static const char *networkMange[]  = { "st", "nmtui", NULL };
static const char *music[]  = { "st", "mocp", NULL };

static const char *browser[]  = { "qutebrowser", NULL };

static const char *wireshark[] = { "wireshark", NULL };
static const char *burp_suite[] = { "BurpSuitePro", NULL };
static const char *keepass[] = { "keepass", NULL };

static const char *kdeconnect[] = { "kdeconnect-app", NULL };

static const char *soundManage[] = { "pavucontrol", NULL };

static const char *lockscreen[]  = { "i3lock-fancy", "-p", "-t", "Oh hell no!", NULL };

static const char *mutecmd[] = { "/home/p4p1/.local/share/pipx/venvs/status/bin/sound.sh", "=", NULL };
static const char *volupcmd[] = { "/home/p4p1/.local/share/pipx/venvs/status/bin/sound.sh", "+", NULL };
static const char *voldowncmd[] = { "/home/p4p1/.local/share/pipx/venvs/status/bin/sound.sh", "-", NULL };

static const char *monMin[] = { "/home/p4p1/.local/share/pipx/venvs/status/bin/brightness.sh", "-", NULL };
static const char *monMax[] = { "/home/p4p1/.local/share/pipx/venvs/status/bin/brightness.sh", "+", NULL };

static const char *prtscrcmd[] = { "bash", "-c", "scrot $HOME/Pictures/screenshots/%Y-%m-%d-%H-%M-%S-1920x1080.png", NULL };
static const char *flameshot[] = { "flameshot", "gui", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd_tmux } },
	{ MODKEY|ControlMask,           XK_Return, spawn,          {.v = termcmd_tmuxer } },
	{ MODKEY|ControlMask|ShiftMask, XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = browser } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = lockscreen} },
	{ MODKEY,                       XK_w,      spawn,          {.v = networkMange} },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = wireshark } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = soundManage} },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = dmenushut} },
	{ MODKEY,                       XK_r,      spawn,          {.v = file_manager } },
	{ MODKEY|ShiftMask,             XK_r,      spawn,          {.v = file_manager_gui } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = display_manager } },
	{ MODKEY,                       XK_f,      spawn,          {.v = news_feed } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = keepass } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = dmenusplain } },
	{ MODKEY,                       XK_o,      spawn,          {.v = dmenuemoji } },
	{ MODKEY,                       XK_a,      spawn,          {.v = music } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenukeyb } },
	{ MODKEY|ShiftMask,             XK_o,      spawn,          {.v = dmenuovpn } },
	{ MODKEY,                       XK_x,      spawn,          {.v = flameshot } },
	{ MODKEY,                       XK_v,      spawn,          {.v = dmenuwin } },
	{ MODKEY,                       XK_Tab,    spawn,          {.v = graphicalmenu } },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = burp_suite } },
	{ MODKEY|ShiftMask,             XK_k,      spawn,          {.v = kdeconnect } },
	{ MODKEY,                       XK_b,      togglebar,      { 0 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_space,  zoom,           {0} },
	{ MODKEY|ShiftMask,             XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_d,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_u,      togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY,                       XK_n,      togglealttag,   {0} },
	{ MODKEY|ShiftMask,             XK_Up,     spawn,          {.v = volupcmd} },
	{ MODKEY|ShiftMask,             XK_Down,   spawn,          {.v = voldowncmd} },
	{ MODKEY|ShiftMask,             XK_Left,   spawn,          {.v = monMin } },
	{ MODKEY|ShiftMask,             XK_Right,  spawn,          {.v = monMax } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
	{ 0, XK_Print, spawn, {.v = prtscrcmd } },
	{ 0, XK_Menu, spawn, {.v = xmenucmd } },
	{ 0, XK_Super_L, spawn, {.v = roficmd } },
	{ 0, XF86XK_AudioMute, spawn, {.v = mutecmd } },

	/***** Stealing these keys for the pine phone port ****/
	{ 0, XF86XK_AudioLowerVolume, openkeyboard, {0} },
	{ 0, XF86XK_AudioRaiseVolume, spawn, {.v = roficmd } },
	{ 0, XF86XK_PowerOff, spawn, { .v =  termcmd_tmux  } },
	/***** Stealing these keys for the pine phone port ****/

	{ 0, XF86XK_MonBrightnessUp, spawn, {.v = monMax} },
	{ 0, XF86XK_MonBrightnessDown, spawn, {.v = monMin} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask        button          function        argument */
	{ ClkLtSymbol,          0,                Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                Button3,        setlayout,      {.v = &layouts[3]} },
	{ ClkWinTitle,          0,                Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                Button1,        spawn,          {.v = dmenushut } },
	{ ClkStatusText,        0,                Button2,        spawn,          {.v = graphicalmenu } },
	{ ClkRootWin,           0,                Button3,        spawn,          {.v = xmenucmd } },
	{ ClkClientWin,         MODKEY,           Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,           Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,                Button1,        view,           {0} },
	{ ClkTagBar,            0,                Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,           Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,           Button3,        toggletag,      {0} },
};

