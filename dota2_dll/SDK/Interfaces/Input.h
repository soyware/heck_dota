#pragma once

enum ButtonCode_t
{
	BUTTON_CODE_INVALID = -1,
	BUTTON_CODE_NONE = 0,

	KEY_FIRST = 0,

	KEY_NONE = KEY_FIRST,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_PAD_0,
	KEY_PAD_1,
	KEY_PAD_2,
	KEY_PAD_3,
	KEY_PAD_4,
	KEY_PAD_5,
	KEY_PAD_6,
	KEY_PAD_7,
	KEY_PAD_8,
	KEY_PAD_9,
	KEY_PAD_DIVIDE,
	KEY_PAD_MULTIPLY,
	KEY_PAD_MINUS,
	KEY_PAD_PLUS,
	KEY_PAD_ENTER,
	KEY_PAD_DECIMAL,
	KEY_LESSTHAN,
	KEY_LBRACKET,
	KEY_RBRACKET,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_BACKQUOTE,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_BACKSLASH,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_ENTER,
	KEY_SPACE,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_CAPSLOCK,
	KEY_NUMLOCK,
	KEY_ESCAPE,
	KEY_SCROLLLOCK,
	KEY_INSERT,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_BREAK,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LALT,
	KEY_RALT,
	KEY_LCONTROL,
	KEY_RCONTROL,
	KEY_LWIN,
	KEY_RWIN,
	KEY_APP,
	KEY_UP,
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_CAPSLOCKTOGGLE,
	KEY_NUMLOCKTOGGLE,
	KEY_SCROLLLOCKTOGGLE,
	KEY_AC_BACK,
	KEY_AC_BOOKMARKS,
	KEY_AC_FORWARD,
	KEY_AC_HOME,
	KEY_AC_REFRESH,
	KEY_AC_SEARCH,
	KEY_AC_STOP,
	KEY_AGAIN,
	KEY_ALTERASE,
	KEY_AMPERSAND,
	KEY_ASTERISK,
	KEY_AT,
	KEY_AUDIOMUTE,
	KEY_AUDIONEXT,
	KEY_AUDIOPLAY,
	KEY_AUDIOPREV,
	KEY_AUDIOSTOP,
	KEY_BRIGHTNESSDOWN,
	KEY_BRIGHTNESSUP,
	KEY_CALCULATOR,
	KEY_CANCEL,
	KEY_CARET,
	KEY_CLEAR,
	KEY_CLEARAGAIN,
	KEY_COLON,
	KEY_COMPUTER,
	KEY_COPY,
	KEY_CRSEL,
	KEY_CURRENCYSUBUNIT,
	KEY_CURRENCYUNIT,
	KEY_CUT,
	KEY_DECIMALSEPARATOR,
	KEY_DISPLAYSWITCH,
	KEY_DOLLAR,
	KEY_EJECT,
	KEY_EXCLAIM,
	KEY_EXECUTE_,
	KEY_EXSEL,
	KEY_F13,
	KEY_F14,
	KEY_F15,
	KEY_F16,
	KEY_F17,
	KEY_F18,
	KEY_F19,
	KEY_F20,
	KEY_F21,
	KEY_F22,
	KEY_F23,
	KEY_F24,
	KEY_FIND,
	KEY_GREATER,
	KEY_HASH,
	KEY_HELP,
	KEY_KBDILLUMDOWN,
	KEY_KBDILLUMTOGGLE,
	KEY_KBDILLUMUP,
	KEY_KP_00,
	KEY_KP_000,
	KEY_KP_A,
	KEY_KP_AMPERSAND,
	KEY_KP_AT,
	KEY_KP_B,
	KEY_KP_BACKSPACE,
	KEY_KP_BINARY,
	KEY_KP_C,
	KEY_KP_CLEAR,
	KEY_KP_CLEARENTRY,
	KEY_KP_COLON,
	KEY_KP_COMMA,
	KEY_KP_D,
	KEY_KP_DBLAMPERSAND,
	KEY_KP_DBLVERTICALBAR,
	KEY_KP_DECIMAL,
	KEY_KP_E,
	KEY_KP_EQUALS,
	KEY_KP_EQUALSAS400,
	KEY_KP_EXCLAM,
	KEY_KP_F,
	KEY_KP_GREATER,
	KEY_KP_HASH,
	KEY_KP_HEXADECIMAL,
	KEY_KP_LEFTBRACE,
	KEY_KP_LEFTPAREN,
	KEY_KP_LESS,
	KEY_KP_MEMADD,
	KEY_KP_MEMCLEAR,
	KEY_KP_MEMDIVIDE,
	KEY_KP_MEMMULTIPLY,
	KEY_KP_MEMRECALL,
	KEY_KP_MEMSTORE,
	KEY_KP_MEMSUBTRACT,
	KEY_KP_OCTAL,
	KEY_KP_PERCENT,
	KEY_KP_PLUSMINUS,
	KEY_KP_POWER,
	KEY_KP_RIGHTBRACE,
	KEY_KP_RIGHTPAREN,
	KEY_KP_SPACE,
	KEY_KP_TAB,
	KEY_KP_VERTICALBAR,
	KEY_KP_XOR,
	KEY_LEFTPAREN,
	KEY_MAIL,
	KEY_MEDIASELECT,
	KEY_MODE,
	KEY_MUTE,
	KEY_OPER,
	KEY_OUT,
	KEY_PASTE,
	KEY_PERCENT,
	KEY_PLUS,
	KEY_POWER,
	KEY_PRINTSCREEN,
	KEY_PRIOR,
	KEY_QUESTION,
	KEY_QUOTEDBL,
	KEY_RETURN2,
	KEY_RIGHTPAREN,
	KEY_SELECT,
	KEY_SEPARATOR,
	KEY_SLEEP,
	KEY_STOP,
	KEY_SYSREQ,
	KEY_THOUSANDSSEPARATOR,
	KEY_UNDERSCORE,
	KEY_UNDO,
	KEY_VOLUMEDOWN,
	KEY_VOLUMEUP,
	KEY_WWW,
	KEY_INVERTED_EXCLAMATION_MARK,
	KEY_CENT_SIGN,
	KEY_POUND_SIGN,
	KEY_CURRENCY_SIGN,
	KEY_YEN_SIGN,
	KEY_BROKEN_BAR,
	KEY_SECTION_SIGN,
	KEY_DIAERESIS,
	KEY_COPYRIGHT_SIGN,
	KEY_FEMININE_ORDINAL_INDICATOR,
	KEY_LEFT_POINTING_DOUBLE_ANGLE_QUOTATION_MARK,
	KEY_NOT_SIGN,
	KEY_REGISTERED_SIGN,
	KEY_MACRON,
	KEY_DEGREE_SIGN,
	KEY_DEGREE_SYMBOL,
	KEY_PLUS_MINUS_SIGN,
	KEY_SUPERSCRIPT_TWO,
	KEY_SUPERSCRIPT_THREE,
	KEY_ACUTE_ACCENT,
	KEY_MICRO_SIGN,
	KEY_PILCROW_SIGN,
	KEY_MIDDLE_DOT,
	KEY_CEDILLA,
	KEY_SUPERSCRIPT_ONE,
	KEY_MASCULINE_ORDINAL_INDICATOR,
	KEY_RIGHT_POINTING_DOUBLE_ANGLE_QUOTATION_MARK,
	KEY_VULGAR_FRACTION_ONE_QUARTER,
	KEY_VULGAR_FRACTION_ONE_HALF,
	KEY_VULGAR_FRACTION_THREE_QUARTERS,
	KEY_INVERTED_QUESTION_MARK,
	KEY_MULTIPLICATION_SIGN,
	KEY_SHARP_S,
	KEY_A_WITH_GRAVE,
	KEY_A_WITH_ACUTE,
	KEY_A_WITH_CIRCUMFLEX,
	KEY_A_WITH_TILDE,
	KEY_A_WITH_DIAERESIS,
	KEY_A_WITH_RING_ABOVE,
	KEY_AE,
	KEY_C_WITH_CEDILLA,
	KEY_E_WITH_GRAVE,
	KEY_E_WITH_ACUTE,
	KEY_E_WITH_CIRCUMFLEX,
	KEY_E_WITH_DIAERESIS,
	KEY_I_WITH_GRAVE,
	KEY_I_WITH_ACUTE,
	KEY_I_WITH_CIRCUMFLEX,
	KEY_I_WITH_DIAERESIS,
	KEY_ETH,
	KEY_N_WITH_TILDE,
	KEY_O_WITH_GRAVE,
	KEY_O_WITH_ACUTE,
	KEY_O_WITH_CIRCUMFLEX,
	KEY_O_WITH_TILDE,
	KEY_O_WITH_DIAERESIS,
	KEY_DIVISION_SIGN,
	KEY_O_WITH_STROKE,
	KEY_U_WITH_GRAVE,
	KEY_U_WITH_ACUTE,
	KEY_U_WITH_CIRCUMFLEX,
	KEY_U_WITH_DIAERESIS,
	KEY_Y_WITH_ACUTE,
	KEY_THORN,
	KEY_Y_WITH_DIAERESIS,
	KEY_EURO_SIGN,
	KEY_TILDE,
	KEY_LEFT_CURLY_BRACKET,
	KEY_RIGHT_CURLY_BRACKET,
	KEY_VERTICAL_BAR,
	KEY_KEY_CYRILLIC_YU,
	KEY_KEY_CYRILLIC_E,
	KEY_KEY_CYRILLIC_HARD_SIGN,
	KEY_KEY_CYRILLIC_HA,
	KEY_KEY_CYRILLIC_IO,
	KEY_KEY_CYRILLIC_ZHE,
	KEY_KEY_CYRILLIC_BE,

	KEY_LAST = KEY_KEY_CYRILLIC_BE,
	KEY_COUNT = KEY_LAST - KEY_FIRST + 1,

	// Mouse
	MOUSE_FIRST = KEY_LAST + 1,

	MOUSE_LEFT = MOUSE_FIRST,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	MOUSE_4,
	MOUSE_5,
	MOUSE_WHEEL_UP,		// A fake button which is 'pressed' and 'released' when the wheel is moved up 
	MOUSE_WHEEL_DOWN,	// A fake button which is 'pressed' and 'released' when the wheel is moved down

	MOUSE_LAST = MOUSE_WHEEL_DOWN,
	MOUSE_COUNT = MOUSE_LAST - MOUSE_FIRST + 1
};

class CInputSystem
{
public:
	inline bool IsButtonDown(ButtonCode_t code)
	{
		typedef bool(__thiscall* Fn) (CInputSystem*, ButtonCode_t);
		return GetVF<Fn>(this, 17)(this, code);
	}

	inline const char* CodeToString(ButtonCode_t code)
	{
		typedef const char*(__thiscall* Fn) (CInputSystem*, ButtonCode_t);
		return GetVF<Fn>(this, 37)(this, code);
	}
};