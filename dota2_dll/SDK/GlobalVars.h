#pragma once

class CGlobalVars
{
public:
	float realtime; //0x0000 
	int32_t framecount; //0x0004 
	float absoluteframetime; //0x0008 
	float absoluteframestarttimestddev; //0x000C 
	int32_t maxClients; //0x0010 
	int32_t tickcount; //0x0014 
	float interval_per_tick; //0x0018 
	float interpolation_amount; //0x001C 
private:
	std::byte pad_0x0020[0x8]; //0x0020
public:
	void* warningFunc; //0x0028 
private:
	std::byte pad_0x0030[0x4]; //0x0030
public:
	float curtime; //0x0034 
private:
	std::byte pad_0x0038[0x10]; //0x0038
public:
	void* m_pNetChan; //0x0048 
private:
	std::byte pad_0x0050[0x128]; //0x0050
public:
	char* mapname; //0x0178 
	char* mapGroupName; //0x0180 

}; //Size=0x0188

#define TICK_INTERVAL			((*G::pGlobals)->interval_per_tick)

#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )
#define TICKS_TO_TIME( t )		( TICK_INTERVAL *( t ) )
#define ROUND_TO_TICKS( t )		( TICK_INTERVAL * TIME_TO_TICKS( t ) )
#define TICK_NEVER_THINK		(-1)