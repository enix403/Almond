#pragma once

// clang-format off

#define AD_KEY_UNKNOWN            -1

/* Printable keys */
#define AD_KEY_SPACE              32
#define AD_KEY_APOSTROPHE         39  /* ' */
#define AD_KEY_COMMA              44  /* , */
#define AD_KEY_MINUS              45  /* - */
#define AD_KEY_PERIOD             46  /* . */
#define AD_KEY_SLASH              47  /* / */
#define AD_KEY_0                  48
#define AD_KEY_1                  49
#define AD_KEY_2                  50
#define AD_KEY_3                  51
#define AD_KEY_4                  52
#define AD_KEY_5                  53
#define AD_KEY_6                  54
#define AD_KEY_7                  55
#define AD_KEY_8                  56
#define AD_KEY_9                  57
#define AD_KEY_SEMICOLON          59  /* ; */
#define AD_KEY_EQUAL              61  /* = */
#define AD_KEY_A                  65
#define AD_KEY_B                  66
#define AD_KEY_C                  67
#define AD_KEY_D                  68
#define AD_KEY_E                  69
#define AD_KEY_F                  70
#define AD_KEY_G                  71
#define AD_KEY_H                  72
#define AD_KEY_I                  73
#define AD_KEY_J                  74
#define AD_KEY_K                  75
#define AD_KEY_L                  76
#define AD_KEY_M                  77
#define AD_KEY_N                  78
#define AD_KEY_O                  79
#define AD_KEY_P                  80
#define AD_KEY_Q                  81
#define AD_KEY_R                  82
#define AD_KEY_S                  83
#define AD_KEY_T                  84
#define AD_KEY_U                  85
#define AD_KEY_V                  86
#define AD_KEY_W                  87
#define AD_KEY_X                  88
#define AD_KEY_Y                  89
#define AD_KEY_Z                  90
#define AD_KEY_LEFT_BRACKET       91  /* [ */
#define AD_KEY_BACKSLASH          92  /* \ */
#define AD_KEY_RIGHT_BRACKET      93  /* ] */
#define AD_KEY_GRAVE_ACCENT       96  /* ` */
#define AD_KEY_WORLD_1            161 /* non-US #1 */
#define AD_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define AD_KEY_ESCAPE             256
#define AD_KEY_ENTER              257
#define AD_KEY_TAB                258
#define AD_KEY_BACKSPACE          259
#define AD_KEY_INSERT             260
#define AD_KEY_DELETE             261
#define AD_KEY_RIGHT              262
#define AD_KEY_LEFT               263
#define AD_KEY_DOWN               264
#define AD_KEY_UP                 265
#define AD_KEY_PAGE_UP            266
#define AD_KEY_PAGE_DOWN          267
#define AD_KEY_HOME               268
#define AD_KEY_END                269
#define AD_KEY_CAPS_LOCK          280
#define AD_KEY_SCROLL_LOCK        281
#define AD_KEY_NUM_LOCK           282
#define AD_KEY_PRINT_SCREEN       283
#define AD_KEY_PAUSE              284
#define AD_KEY_F1                 290
#define AD_KEY_F2                 291
#define AD_KEY_F3                 292
#define AD_KEY_F4                 293
#define AD_KEY_F5                 294
#define AD_KEY_F6                 295
#define AD_KEY_F7                 296
#define AD_KEY_F8                 297
#define AD_KEY_F9                 298
#define AD_KEY_F10                299
#define AD_KEY_F11                300
#define AD_KEY_F12                301
#define AD_KEY_F13                302
#define AD_KEY_F14                303
#define AD_KEY_F15                304
#define AD_KEY_F16                305
#define AD_KEY_F17                306
#define AD_KEY_F18                307
#define AD_KEY_F19                308
#define AD_KEY_F20                309
#define AD_KEY_F21                310
#define AD_KEY_F22                311
#define AD_KEY_F23                312
#define AD_KEY_F24                313
#define AD_KEY_F25                314
#define AD_KEY_KP_0               320
#define AD_KEY_KP_1               321
#define AD_KEY_KP_2               322
#define AD_KEY_KP_3               323
#define AD_KEY_KP_4               324
#define AD_KEY_KP_5               325
#define AD_KEY_KP_6               326
#define AD_KEY_KP_7               327
#define AD_KEY_KP_8               328
#define AD_KEY_KP_9               329
#define AD_KEY_KP_DECIMAL         330
#define AD_KEY_KP_DIVIDE          331
#define AD_KEY_KP_MULTIPLY        332
#define AD_KEY_KP_SUBTRACT        333
#define AD_KEY_KP_ADD             334
#define AD_KEY_KP_ENTER           335
#define AD_KEY_KP_EQUAL           336
#define AD_KEY_LEFT_SHIFT         340
#define AD_KEY_LEFT_CONTROL       341
#define AD_KEY_LEFT_ALT           342
#define AD_KEY_LEFT_SUPER         343
#define AD_KEY_RIGHT_SHIFT        344
#define AD_KEY_RIGHT_CONTROL      345
#define AD_KEY_RIGHT_ALT          346
#define AD_KEY_RIGHT_SUPER        347
#define AD_KEY_MENU               348

#define AD_KEY_LAST               AD_KEY_MENU

/*! @} */

/*! @defgroup mods Modifier key flags
 *  @brief Modifier key flags.
 *
 *  See [key input](@ref input_key) for how these are used.
 *
 *  @ingroup input
 *  @{ */

/*! @brief If this bit is set one or more Shift keys were held down.
 *
 *  If this bit is set one or more Shift keys were held down.
 */
#define AD_MOD_SHIFT           0x0001
/*! @brief If this bit is set one or more Control keys were held down.
 *
 *  If this bit is set one or more Control keys were held down.
 */
#define AD_MOD_CONTROL         0x0002
/*! @brief If this bit is set one or more Alt keys were held down.
 *
 *  If this bit is set one or more Alt keys were held down.
 */
#define AD_MOD_ALT             0x0004
/*! @brief If this bit is set one or more Super keys were held down.
 *
 *  If this bit is set one or more Super keys were held down.
 */
#define AD_MOD_SUPER           0x0008
/*! @brief If this bit is set the Caps Lock key is enabled.
 *
 *  If this bit is set the Caps Lock key is enabled and the @ref
 *  AD_LOCK_KEY_MODS input mode is set.
 */
#define AD_MOD_CAPS_LOCK       0x0010
/*! @brief If this bit is set the Num Lock key is enabled.
 *
 *  If this bit is set the Num Lock key is enabled and the @ref
 *  AD_LOCK_KEY_MODS input mode is set.
 */
#define AD_MOD_NUM_LOCK        0x0020

/*! @} */

/*! @defgroup buttons Mouse buttons
 *  @brief Mouse button IDs.
 *
 *  See [mouse button input](@ref input_mouse_button) for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define AD_MOUSE_BUTTON_1         0
#define AD_MOUSE_BUTTON_2         1
#define AD_MOUSE_BUTTON_3         2
#define AD_MOUSE_BUTTON_4         3
#define AD_MOUSE_BUTTON_5         4
#define AD_MOUSE_BUTTON_6         5
#define AD_MOUSE_BUTTON_7         6
#define AD_MOUSE_BUTTON_8         7
#define AD_MOUSE_BUTTON_LAST      AD_MOUSE_BUTTON_8
#define AD_MOUSE_BUTTON_LEFT      AD_MOUSE_BUTTON_1
#define AD_MOUSE_BUTTON_RIGHT     AD_MOUSE_BUTTON_2
#define AD_MOUSE_BUTTON_MIDDLE    AD_MOUSE_BUTTON_3

// clang-format on
