#pragma once

namespace Log
{
	//-----------------------------------------------------------------------------
	// Maximum length of a sprintf'ed logging message.
	//-----------------------------------------------------------------------------
	const int MAX_LOGGING_MESSAGE_LENGTH = 2048;

	//-----------------------------------------------------------------------------
	// An invalid color set on a channel to imply that it should use
	// a device-dependent default color where applicable.
	//-----------------------------------------------------------------------------
	const Color UNSPECIFIED_LOGGING_COLOR(0, 0, 0, 0);

	//-----------------------------------------------------------------------------
	// An ID returned by the logging system to refer to a logging channel.
	//-----------------------------------------------------------------------------
	typedef int LoggingChannelID_t;

	//-----------------------------------------------------------------------------
	// A sentinel value indicating an invalid logging channel ID.
	//-----------------------------------------------------------------------------
	const LoggingChannelID_t INVALID_LOGGING_CHANNEL_ID = -1;

	//-----------------------------------------------------------------------------
	// The severity of a logging operation.
	//-----------------------------------------------------------------------------
	enum LoggingSeverity_t
	{
		//-----------------------------------------------------------------------------
		// An informative logging message.
		//-----------------------------------------------------------------------------
		LS_MESSAGE = 0,

		//-----------------------------------------------------------------------------
		// A warning, typically non-fatal
		//-----------------------------------------------------------------------------
		LS_WARNING = 1,

		//-----------------------------------------------------------------------------
		// A message caused by an Assert**() operation.
		//-----------------------------------------------------------------------------
		LS_ASSERT = 2,

		//-----------------------------------------------------------------------------
		// An error, typically fatal/unrecoverable.
		//-----------------------------------------------------------------------------
		LS_ERROR = 3,

		//-----------------------------------------------------------------------------
		// A placeholder level, higher than any legal value.
		// Not a real severity value!
		//-----------------------------------------------------------------------------
		LS_HIGHEST_SEVERITY = 4,
	};

	//-----------------------------------------------------------------------------
	// Action which should be taken by logging system as a result of 
	// a given logged message.
	//
	// The logging system invokes ILoggingResponsePolicy::OnLog() on
	// the specified policy object, which returns a LoggingResponse_t.
	//-----------------------------------------------------------------------------
	enum LoggingResponse_t
	{
		LR_CONTINUE,
		LR_DEBUGGER,
		LR_ABORT,
	};

	//-----------------------------------------------------------------------------
	// Logging channel behavior flags, set on channel creation.
	//-----------------------------------------------------------------------------
	enum LoggingChannelFlags_t
	{
		//-----------------------------------------------------------------------------
		// Indicates that the spew is only relevant to interactive consoles.
		//-----------------------------------------------------------------------------
		LCF_CONSOLE_ONLY = 0x00000001,

		//-----------------------------------------------------------------------------
		// Indicates that spew should not be echoed to any output devices.
		// A suitable logging listener must be registered which respects this flag 
		// (e.g. a file logger).
		//-----------------------------------------------------------------------------
		LCF_DO_NOT_ECHO = 0x00000002,
	};

	//-----------------------------------------------------------------------------
	// A callback function used to register tags on a logging channel 
	// during initialization.
	//-----------------------------------------------------------------------------
	typedef void (*RegisterTagsFunc)();

	//-----------------------------------------------------------------------------
	// A context structure passed to logging listeners and response policy classes.
	//-----------------------------------------------------------------------------
	struct LoggingContext_t
	{
		// ID of the channel being logged to.
		LoggingChannelID_t m_ChannelID;
		// Flags associated with the channel.
		LoggingChannelFlags_t m_Flags;
		// Severity of the logging event.
		LoggingSeverity_t m_Severity;
		// Color of logging message if one was specified to Log_****() macro.
		// If not specified, falls back to channel color.
		// If channel color is not specified, this value is UNSPECIFIED_LOGGING_COLOR
		// and indicates that a suitable default should be chosen.
		Color m_Color;
	};

	//-----------------------------------------------------------------------------
	// Register a logging channel with the logging system.
	// The same channel can be registered multiple times, but the parameters
	// in each call to RegisterLoggingChannel must either match across all calls
	// or be set to defaults on any given call
	//
	// This function is not thread-safe and should generally only be called 
	// by a single thread. Using the logging channel definition macros ensures 
	// that this is called on the static initialization thread.
	//-----------------------------------------------------------------------------
	LoggingChannelID_t RegisterLoggingChannel(const char* pChannelName, RegisterTagsFunc registerTagsFunc = nullptr, int flags = 0, LoggingSeverity_t minimumSeverity = LS_MESSAGE, Color spewColor = UNSPECIFIED_LOGGING_COLOR)
	{
		typedef LoggingChannelID_t(*Fn)(const char*, RegisterTagsFunc, int, LoggingSeverity_t, Color);
		static const Fn func = reinterpret_cast<Fn>(GetProcAddress(GetModuleHandle("tier0.dll"), "LoggingSystem_RegisterLoggingChannel"));
		return func(pChannelName, registerTagsFunc, flags, minimumSeverity, spewColor);
	}

	//-----------------------------------------------------------------------------
	// Logs a variable-argument to a given channel with the specified severity.
	// NOTE: if adding overloads to this function, remember that the Log_***
	// macros simply pass their variadic parameters through to LoggingSystem_Log().
	// Therefore, you need to ensure that the parameters are in the same general 
	// order and that there are no ambiguities with the overload.
	//-----------------------------------------------------------------------------
	template<typename ... Args>
	LoggingResponse_t Log(LoggingChannelID_t channelID, LoggingSeverity_t severity, const char* pMessageFormat, Args ... args)
	{
		typedef LoggingResponse_t(*Fn)(LoggingChannelID_t, LoggingSeverity_t, const char*, ...);
		static const Fn func = reinterpret_cast<Fn>(GetProcAddress(GetModuleHandle("tier0.dll"), "LoggingSystem_Log"));
		return func(channelID, severity, pMessageFormat, args...);
	}

	template<typename ... Args>
	LoggingResponse_t Log(LoggingChannelID_t channelID, LoggingSeverity_t severity, Color spewColor, const char* pMessageFormat, Args ... args)
	{
		typedef LoggingResponse_t(*Fn)(LoggingChannelID_t, LoggingSeverity_t, Color, const char*, ...);
		static const Fn func = reinterpret_cast<Fn>(GetProcAddress(GetModuleHandle("tier0.dll"), "?LoggingSystem_Log@@YA?AW4LoggingResponse_t@@HW4LoggingSeverity_t@@VColor@@PBDZZ"));
		return func(channelID, severity, spewColor, pMessageFormat, args...);
	}

	LoggingChannelID_t LOG_HECK;

	void Init()
	{
		LOG_HECK = RegisterLoggingChannel("heck", nullptr, LCF_CONSOLE_ONLY, LS_MESSAGE, Color::Green());
	}

	template<typename ... Args>
	void Msg(const char* pMessageFormat, Args ... args)
	{
		Log(LOG_HECK, LS_MESSAGE, pMessageFormat, args...);
	}

	template<typename ... Args>
	void Msg(Color spewColor, const char* pMessageFormat, Args ... args)
	{
		Log(LOG_HECK, LS_MESSAGE, spewColor, pMessageFormat, args...);
	}
}