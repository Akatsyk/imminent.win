#pragma once

// little include hack
#include "SDK/Valve/UtlBuffer.hpp"
#include "SDK/Valve/UtlMemory.hpp"
#include "SDK/Valve/UtlVector.hpp"
#include "SDK/Classes/INetworkStringTable.h"

#include "SDK/sdk.hpp"
#include "SDK/Valve/recv_swap.hpp"
#include <windows.h>
#include <shlobj.h>

template <typename T>
inline T WordSwapAsm(T w)
{
	__asm
	{
		mov ax, w
		xchg al, ah
	}
}

//Little endian things
#define LittleDWord( val )			( val )

//Floating point
#define LittleFloat( pOut, pIn )	( *pOut = *pIn )

#define WordSwap  WordSwapAsm
#pragma warning(push)
#pragma warning (disable:4035) // no return value

template <typename T>
inline T DWordSwapAsm(T dw)
{
	__asm
	{
		mov eax, dw
		bswap eax
	}
}

#define DWordSwap DWordSwapAsm
#define BigLong( val )				DWordSwap( val )
#define BigShort( val )				WordSwap( val )

extern DWORD* ClientCount;
extern DWORD ClientList;

inline DWORD GetServerClientEntity(int i)
{
	DWORD EAX = *(DWORD*)ClientList;
	DWORD EBX = *(DWORD*)((i * 4) + EAX);

#if 1
	if (!EBX)
		return NULL;

	return (EBX + 4);
#endif

#if 0
	DWORD val = *(DWORD*)(*(DWORD*)ClientList + (4 * i));
	if (!val)
		return NULL;

	return (val + 4);
#endif
}

//CBaseEntity::Instance(edict_t*)
inline C_BaseEntity* ServerClientToEntity(DWORD cl)
{
	cl -= 4;

	DWORD edict = *(DWORD*)(cl + 0x494); //0x48C

	DWORD ecx = *(DWORD*)(edict + 0x0C);
	if (ecx)
	{
		DWORD EAX = *(DWORD*)ecx;
		return ((C_BaseEntity * (__thiscall*)(DWORD))(*(DWORD*)(EAX + 0x14)))(ecx);
	}

	return nullptr;
}

inline int GetServerClientCount()
{
	return *ClientCount;
}

inline int GetClientCount()
{
	return 64;
	//return ActualNumPlayers;
}

class IClientMode {
public:
   virtual ~IClientMode( ) { }
   virtual int ClientModeCSNormal( void* ) = 0;
   virtual void Init( ) = 0;
   virtual void InitViewport( ) = 0;
   virtual void Shutdown( ) = 0;
   virtual void Enable( ) = 0;
   virtual void Disable( ) = 0;
   virtual void Layout( ) = 0;
   virtual IPanel* GetViewport( ) = 0;
   virtual void* GetViewportAnimationController( ) = 0;
   virtual void ProcessInput( bool bActive ) = 0;
   virtual bool ShouldDrawDetailObjects( ) = 0;
   virtual bool ShouldDrawEntity( C_BaseEntity* pEnt ) = 0;
   virtual bool ShouldDrawLocalPlayer( C_BaseEntity* pPlayer ) = 0;
   virtual bool ShouldDrawParticles( ) = 0;
   virtual bool ShouldDrawFog( void ) = 0;
   virtual void OverrideView( CViewSetup* pSetup ) = 0;
   virtual int KeyInput( int down, int keynum, const char* pszCurrentBinding ) = 0;
   virtual void StartMessageMode( int iMessageModeType ) = 0;
   virtual IPanel* GetMessagePanel( ) = 0;
   virtual void OverrideMouseInput( float* x, float* y ) = 0;
   virtual bool CreateMove( float flInputSampleTime, void* usercmd ) = 0;
   virtual void LevelInit( const char* newmap ) = 0;
   virtual void LevelShutdown( void ) = 0;
};

struct LagCompensationRecord
{
	float flSimulationTime;
	BOOLEAN bAlive;
	QAngle absangles;
	Vector absorigin;
	float body_yaw;
	float body_pitch;
	float goalfeetyaw;
	float curfeetyaw;
	int tickschoked;
	CUserCmd currentusercmd;
	CUserCmd lastusercmd;
};

extern std::deque<LagCompensationRecord*> gLagCompensationRecords[65];

typedef struct netpacket_s netpacket_t;
extern double* net_time;
static bool bNetchanIsHooked, bMessageHandlerHooked;

namespace Interfaces
{
   extern Encrypted_t<IBaseClientDLL> m_pClient;
   extern Encrypted_t<IClientEntityList> m_pEntList;
   extern Encrypted_t<IGameMovement> m_pGameMovement;
   extern Encrypted_t<IPrediction> m_pPrediction;
   extern Encrypted_t<IMoveHelper> m_pMoveHelper;
   extern Encrypted_t<IInput> m_pInput;
   extern Encrypted_t< CGlobalVars >  m_pGlobalVars;
   extern Encrypted_t<ISurface> m_pSurface;
   extern Encrypted_t<IVEngineClient> m_pEngine;
   extern Encrypted_t<IClientMode> m_pClientMode;
   extern Encrypted_t<ICVar> m_pCvar;
   extern Encrypted_t<IPanel> m_pPanel;
   extern Encrypted_t<IGameEventManager> m_pGameEvent;
   extern Encrypted_t<IVModelRender> m_pModelRender;
   extern Encrypted_t<IMaterialSystem> m_pMatSystem;
   extern Encrypted_t<ISteamClient> g_pSteamClient;
   extern Encrypted_t<ISteamGameCoordinator> g_pSteamGameCoordinator;
   extern Encrypted_t<ISteamMatchmaking> g_pSteamMatchmaking;
   extern Encrypted_t<ISteamUser> g_pSteamUser;
   extern Encrypted_t<ISteamFriends> g_pSteamFriends;
   extern Encrypted_t<IPhysicsSurfaceProps> m_pPhysSurface;
   extern Encrypted_t<IEngineTrace> m_pEngineTrace;
   extern Encrypted_t<CGlowObjectManager> m_pGlowObjManager;
   extern Encrypted_t<IVModelInfo> m_pModelInfo;
   extern Encrypted_t< CClientState >  m_pClientState;
   extern Encrypted_t<IVDebugOverlay> m_pDebugOverlay;
   extern Encrypted_t<IEngineSound> m_pEngineSound;
   extern Encrypted_t<IMemAlloc> m_pMemAlloc;
   extern Encrypted_t<IViewRenderBeams> m_pRenderBeams;
   extern Encrypted_t<ILocalize> m_pLocalize;
   extern Encrypted_t<IStudioRender> m_pStudioRender;
   extern Encrypted_t<CSPlayerResource*>  m_pPlayerResource;
   extern Encrypted_t<ICenterPrint> m_pCenterPrint;
   extern Encrypted_t<IVRenderView> m_pRenderView;
   extern Encrypted_t<IClientLeafSystem> m_pClientLeafSystem;
   extern Encrypted_t<IMDLCache> m_pMDLCache;
   extern Encrypted_t<IViewRender> m_pViewRender;
   extern Encrypted_t<IInputSystem> m_pInputSystem;
   extern Encrypted_t<INetGraphPanel> m_pNetGraphPanel;
   extern Encrypted_t<CHud> m_pHud;
   extern Encrypted_t<SFHudDeathNoticeAndBotStatus> g_pDeathNotices;
   extern Encrypted_t<CNetworkStringTableContainer> g_pClientStringTableContainer;
   extern WNDPROC oldWindowProc;
   extern HWND hWindow;

   // netvar proxies
   extern RecvPropHook::Shared m_pDidSmokeEffectSwap;
   extern RecvPropHook::Shared m_pFlAbsYawSwap;
   extern RecvPropHook::Shared m_pPlaybackRateSwap;
   extern RecvPropHook::Shared m_bClientSideAnimationSwap;

   bool Create( void* reserved );
   void Destroy( );

   void* CreateInterface( const std::string& image_name, const std::string& name );
}

__forceinline std::string GetDocumentsDirectory( ) {
    char my_documents[ MAX_PATH ];
    HRESULT result = SHGetFolderPath( NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents );

    return std::string( my_documents );
}