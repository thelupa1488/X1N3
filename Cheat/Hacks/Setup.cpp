#include "Setup.h"

CRender::IRender*	GP_Render = nullptr;
CSetup::ISetup*		GP_Setup = nullptr;
CEntityPlayers*		GP_EntPlayers = nullptr;
CEsp*				GP_Esp = nullptr;
CMisc*				GP_Misc = nullptr;
CLegitAim*			GP_LegitAim = nullptr;
CRadar*				GP_Radar = nullptr;
CSkins*				GP_Skins = nullptr;
#ifdef YOUGAMEBIZ
#else
CInventory*         GP_Inventory = nullptr;
#endif
CGHelper*			GP_GHelper = nullptr;