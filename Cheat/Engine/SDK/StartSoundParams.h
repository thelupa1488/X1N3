#pragma once
#include "SDK.h"

struct StartSoundParams_t // apparently outdated thank sen66 for pointing it out.
{
	bool		 staticsound;
	int			 userdata;
	int			 soundsource;
	int			 entchannel;
	void*        pSfx;
	Vector		 origin;
	Vector		 direction;
	bool		 bUpdatePositions;
	float		 fvol;
	soundlevel_t soundlevel;
	int			 flags;
	int			 pitch;
	bool		 fromserver;
	float	     delay;
	int			 speakerentity;
	bool		 suppressrecording;
	int			 initialStreamPosition;
};