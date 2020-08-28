#pragma once

#include "Definitions.hpp"

#include "CInput.hpp"
#include "IClientMode.hpp"
#include "CGlobalVarsBase.hpp"
#include "ClientClass.hpp"
#include "ButtonCode.h"

namespace SDK
{
    enum CStrike15_User_Message_t 
    {
        CS_UM_VGUIMenu = 1,
        CS_UM_Geiger = 2,
        CS_UM_Train = 3,
        CS_UM_HudText = 4,
        CS_UM_SayText = 5,
        CS_UM_SayText2 = 6,
        CS_UM_TextMsg = 7,
        CS_UM_HudMsg = 8,
        CS_UM_ResetHud = 9,
        CS_UM_GameTitle = 10,
        CS_UM_Shake = 12,
        CS_UM_Fade = 13, // Fade HUD in/out
        CS_UM_Rumble = 14,
        CS_UM_CloseCaption = 15,
        CS_UM_CloseCaptionDirect = 16,
        CS_UM_SendAudio = 17,
        CS_UM_RawAudio = 18,
        CS_UM_VoiceMask = 19,
        CS_UM_RequestState = 20,
        CS_UM_Damage = 21,
        CS_UM_RadioText = 22,
        CS_UM_HintText = 23,
        CS_UM_KeyHintText = 24,
        CS_UM_ProcessSpottedEntityUpdate = 25,
        CS_UM_ReloadEffect = 26,
        CS_UM_AdjustMoney = 27,
        CS_UM_UpdateTeamMoney = 28,
        CS_UM_StopSpectatorMode = 29,
        CS_UM_KillCam = 30,
        CS_UM_DesiredTimescale = 31,
        CS_UM_CurrentTimescale = 32,
        CS_UM_AchievementEvent = 33,
        CS_UM_MatchEndConditions = 34,
        CS_UM_DisconnectToLobby = 35,
        CS_UM_PlayerStatsUpdate = 36,
        CS_UM_DisplayInventory = 37,
        CS_UM_WarmupHasEnded = 38,
        CS_UM_ClientInfo = 39,
        CS_UM_XRankGet = 40, // Get ELO Rank Value from Client
        CS_UM_XRankUpd = 41, // Update ELO Rank Value on Client
        CS_UM_CallVoteFailed = 45,
        CS_UM_VoteStart = 46,
        CS_UM_VotePass = 47,
        CS_UM_VoteFailed = 48,
        CS_UM_VoteSetup = 49,
        CS_UM_ServerRankRevealAll = 50,
        CS_UM_SendLastKillerDamageToClient = 51,
        CS_UM_ServerRankUpdate = 52,
        CS_UM_ItemPickup = 53,
        CS_UM_ShowMenu = 54, // Show hud menu
        CS_UM_BarTime = 55, // For the C4 progress bar.
        CS_UM_AmmoDenied = 56,
        CS_UM_MarkAchievement = 57,
        CS_UM_MatchStatsUpdate = 58,
        CS_UM_ItemDrop = 59,
        CS_UM_GlowPropTurnOff = 60,
        CS_UM_SendPlayerItemDrops = 61
    };

    enum ClientFrameStage_t
    {
        FRAME_UNDEFINED = -1,
        FRAME_START,
        FRAME_NET_UPDATE_START,
        FRAME_NET_UPDATE_POSTDATAUPDATE_START,
        FRAME_NET_UPDATE_POSTDATAUPDATE_END,
        FRAME_NET_UPDATE_END,
        FRAME_RENDER_START,
        FRAME_RENDER_END
    };

    // Used by RenderView
    enum RenderViewInfo_t
    {
        RENDERVIEW_UNSPECIFIED = 0,
        RENDERVIEW_DRAWVIEWMODEL = (1 << 0),
        RENDERVIEW_DRAWHUD = (1 << 1),
        RENDERVIEW_SUPPRESSMONITORRENDERING = (1 << 2),
    };

    class IBaseClientDLL
    {
    public:
        virtual int              Connect(CreateInterfaceFn appSystemFactory, CGlobalVarsBase* pGlobals) = 0;
        virtual int              Disconnect(void) = 0;
        virtual int              Init(CreateInterfaceFn appSystemFactory, CGlobalVarsBase* pGlobals) = 0;
        virtual void             PostInit() = 0;
        virtual void             Shutdown(void) = 0;
        virtual void             LevelInitPreEntity(char const* pMapName) = 0;
        virtual void             LevelInitPostEntity() = 0;
        virtual void             LevelShutdown(void) = 0;
        virtual ClientClass*     GetAllClasses(void) = 0;

        bool DispatchUserMessage(int messageType, int arg, int arg1, void* data)
        {
            using DispatchUserMessage_t = bool* (__thiscall*)(void*, int, int, int, void*);
            return GetMethod<DispatchUserMessage_t>(this, 38)(this, messageType, arg, arg1, data);
        }
    };

    typedef size_t(*MemAllocFailHandler_t)(size_t);

    class IMemAlloc
    {
    public:
        virtual ~IMemAlloc();

        // Release versions
        virtual void* alloc(size_t nSize) = 0;
        virtual void* realloc(void* pMem, size_t nSize) = 0;
        virtual void free(void* pMem) = 0;
        virtual void* Expand_NoLongerSupported(void* pMem, size_t nSize) = 0;

        // Debug versions
            //virtual void *Alloc(size_t nSize, const char *pFileName, int nLine) = 0;
            //virtual void *Realloc(void *pMem, size_t nSize, const char *pFileName, int nLine) = 0;
            //virtual void  Free(void *pMem, const char *pFileName, int nLine) = 0;
            //virtual void *Expand_NoLongerSupported(void *pMem, size_t nSize, const char *pFileName, int nLine) = 0;

        // Returns size of a particular allocation
        virtual size_t GetSize(void* pMem) = 0;

        // Force file + line information for an allocation
        virtual void PushAllocDbgInfo(const char* pFileName, int nLine) = 0;
        virtual void PopAllocDbgInfo() = 0;

        // FIXME: Remove when we have our own allocator
        // these methods of the Crt debug code is used in our codebase currently
        virtual long CrtSetBreakAlloc(long lNewBreakAlloc) = 0;
        virtual	int CrtSetReportMode(int nReportType, int nReportMode) = 0;
        virtual int CrtIsValidHeapPointer(const void* pMem) = 0;
        virtual int CrtIsValidPointer(const void* pMem, unsigned int size, int access) = 0;
        virtual int CrtCheckMemory(void) = 0;
        virtual int CrtSetDbgFlag(int nNewFlag) = 0;
        virtual void CrtMemCheckpoint(_CrtMemState* pState) = 0;

        // FIXME: Make a better stats interface
        virtual void DumpStats() = 0;
        virtual void DumpStatsFileBase(char const* pchFileBase) = 0;

        // FIXME: Remove when we have our own allocator
        virtual void* CrtSetReportFile(int nRptType, void* hFile) = 0;
        virtual void* CrtSetReportHook(void* pfnNewHook) = 0;
        virtual int CrtDbgReport(int nRptType, const char* szFile,
            int nLine, const char* szModule, const char* pMsg) = 0;

        virtual int heapchk() = 0;

        virtual bool IsDebugHeap() = 0;

        virtual void GetActualDbgInfo(const char*& pFileName, int& nLine) = 0;
        virtual void RegisterAllocation(const char* pFileName, int nLine, int nLogicalSize, int nActualSize, unsigned nTime) = 0;
        virtual void RegisterDeallocation(const char* pFileName, int nLine, int nLogicalSize, int nActualSize, unsigned nTime) = 0;

        virtual int GetVersion() = 0;

        virtual void CompactHeap() = 0;

        // Function called when malloc fails or memory limits hit to attempt to free up memory (can come in any thread)
        virtual MemAllocFailHandler_t SetAllocFailHandler(MemAllocFailHandler_t pfnMemAllocFailHandler) = 0;

        virtual void DumpBlockStats(void*) = 0;

#if defined( _MEMTEST )	
        virtual void SetStatsExtraInfo(const char* pMapName, const char* pComment) = 0;
#endif

        // Returns 0 if no failure, otherwise the size_t of the last requested chunk
        //  "I'm sure this is completely thread safe!" Brian Deen 7/19/2012.
        virtual size_t MemoryAllocFailed() = 0;

        // handles storing allocation info for coroutines
        virtual int  GetDebugInfoSize() = 0;
        virtual void SaveDebugInfo(void* pvDebugInfo) = 0;
        virtual void RestoreDebugInfo(const void* pvDebugInfo) = 0;
        virtual void InitDebugInfo(void* pvDebugInfo, const char* pchRootFileName, int nLine) = 0;

        // Replacement for ::GlobalMemoryStatus which accounts for unused memory in our system
        virtual void GlobalMemoryStatus(size_t* pUsedMemory, size_t* pFreeMemory) = 0;
    };
}