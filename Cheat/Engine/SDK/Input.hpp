#pragma once
#include "CUserCmd.hpp"

#define MULTIPLAYER_BACKUP 150

namespace SDK
{
	class CInput
	{
	public:
		char				chillout[0x0C];               //0x00
		bool                m_fTrackIRAvailable;          //0x08
		bool                m_fMouseInitialized;          //0x09
		bool                m_fMouseActive;               //0x0A
		bool                m_fJoystickAdvancedInit;      //0x0B
		char                pad_0x08[0x2C];               //0x0C
		void* m_pKeys;                      //0x38
		char                pad_0x38[0x6C];               //0x3C
		bool                m_fCameraInterceptingMouse;   //0xA8
		bool                m_fCameraInThirdPerson;       //0xA9
		bool                m_fCameraMovingWithMouse;     //0xAA
		Vector              m_vecCameraOffset;			  //0xAB
		float               m_fCameraDistanceMove;		  //0xBD
		int                 m_nOldCameraX;                //0xC1
		int                 m_nOldCameraY;                //0xC5
		int                 m_nCameraX;                   //0xC9
		int                 m_nCameraY;                   //0xCD
		bool                m_CameraIsOrthographic;       //0xD1
		Vector              m_angPreviousViewAngles;      //0xD2
		Vector              m_angPreviousViewAnglesTilt;  //0xE4
		float               m_flLastForwardMove;          //0xF6
		int                 m_nClearInputState;           //0xFA
		char                pad_0xE4[0x8];                //0xFE

		CInput() {};

		void GetClicked();
		bool Holding(int, int, int, int);
		bool Hovering(int, int, int, int);
		bool Clicked(int, int, int, int);
	private:
		bool bClicked, bMouseD;
	};
}