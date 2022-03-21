#include "../Hooked.hpp"
#include "../../SDK/Displacement.hpp"
#include "../../SDK/sdk.hpp"
#include "../../SDK/Classes/Player.hpp"
#include "../../SDK/Valve/CBaseHandle.hpp"
#include "../../Features/Rage/LagCompensation.hpp"
#include "../../Features/Rage/Resolver.hpp"

namespace Hooked
{
	void m_nSmokeEffectTickBegin( CRecvProxyData* pData, void* pStruct, void* pOut ) 
	{
		g_Vars.globals.szLastHookCalled = XorStr( "28" );

		if( !pData || !pStruct || !pOut )
			return;

		Interfaces::m_pDidSmokeEffectSwap->GetOriginalFunction( )( pData, pStruct, pOut );
		if( g_Vars.esp.remove_smoke ) 
		{
			*reinterpret_cast< bool* >( reinterpret_cast< uintptr_t >( pOut ) + 0x1 ) = true;
		}
	}

	void RecvProxy_m_flAbsYaw( CRecvProxyData* pData, void* pStruct, void* pOut ) 
	{
		g_Vars.globals.szLastHookCalled = XorStr( "29" );

		if( !pData || !pStruct || !pOut )
			return;

		Interfaces::m_pFlAbsYawSwap->GetOriginalFunction( )( pData, pStruct, pOut );

		if( Interfaces::m_pEngine->IsConnected( ) && Interfaces::m_pEngine->IsInGame( ) ) 
		{
			CBaseHandle handle = *( CBaseHandle* )( ( uintptr_t )pStruct + Engine::Displacement.DT_CSRagdoll.m_hPlayer );
			if( handle.IsValid( ) ) 
			{
				auto player = ( C_CSPlayer* )handle.Get( );
				if( player ) 
				{
					auto lag_data = Engine::LagCompensation::Get( )->GetLagData( player->EntIndex( ) ).Xor( );
					if( lag_data && lag_data->m_History.size( ) )
					{
						lag_data->m_bGotAbsYaw = true;
						lag_data->m_flAbsYawHandled = pData->m_Value.m_Float;
					}
				}
			}

			Interfaces::m_pFlAbsYawSwap->GetOriginalFunction( )( pData, pStruct, pOut );
		}
	}

	// attempts to restore (64 tick servers) simulation time to the exact value it was on the server before it got compressed
	float ExtractLostPrecisionForSimulationTime(float val) 
	{
		char Str1[50];
		char Str2[50];

		// convert float to string
		int n = sprintf(Str1, "%f", val);

		// find the index of the decimal point in the string
		int pointLoc = strchr(Str1, '.') - Str1;

		// remove leading zeroes from the end of the string (Very fast, 5 iterations at max)
		int c = n - 1;
		for (; c > pointLoc + 1 && Str1[c] == '0' && Str1[c - 1] == '0'; c--) 
		{
			Str1[c] = 0;
		}

		// remove the decimal point from the string
		memcpy(Str2, Str1, pointLoc);
		memcpy(Str2 + pointLoc, Str1 + pointLoc + 1, n - (pointLoc + 1) - ((n - 1) - c) + 1);

		// convert the string to an int
		long long NewLL = atoll(Str2);

		// round the last digit to the nearest multiple of 25
		long long num25s = round((double)NewLL / 25.0);
		long long nigNew = num25s * 25;

		// convert the newly rounded int in nigNew to a string
		n = sprintf(Str1, "%lld", nigNew);

		// add the decimal point back into the int string
		Str2[pointLoc] = '.';

		// convert the int string back to a floating point string
		memcpy(Str2, Str1, pointLoc);
		memcpy(Str2 + pointLoc + 1, Str1 + pointLoc, n - pointLoc + 1);

		// store the result in nig ( Due the the limitations of floating point format, I was unable to see a difference for some values =/,
		// step through the code in the debugger and you will see how the string version of the float is perfectly rounded, but when it
		// is converted back to a floating point value, it loses that rounding >:( )
		return atof(Str2);
	}

	//void RecvProxy_m_flSimulationTime(CRecvProxyData* pData, void* pStruct, void* pOut) 
	//{
	//	g_Vars.globals.szLastHookCalled = XorStr("29");

	//	if (!pData || !pStruct || !pOut)
	//		return;

	//	Interfaces::m_pFlSimulationTime->GetOriginalFunction()(pData, pStruct, pOut);

	//	C_CSPlayer* pEntity = (C_CSPlayer*)pEntity;
	//	float returnTime = pData->m_Value.m_Float;

	//	if (Interfaces::m_pEngine->IsInGame() && Interfaces::m_pEngine->IsConnected() && C_CSPlayer::GetLocalPlayer() && pEntity && pEntity->IsPlayer() && pEntity != C_CSPlayer::GetLocalPlayer())
	//	{
	//		auto lagData = Engine::LagCompensation::Get()->GetLagData(pEntity->EntIndex()).Xor();
	//		if (lagData && lagData->m_History.size()) 
	//		{
	//			// just to make sure this variable isn't always set to true.
	//			lagData->m_sProxyData.m_bRecievedSimTime = false;

	//			if (Interfaces::m_pGlobalVars->interval_per_tick == (1.0f / 64.0f))
	//				returnTime = ExtractLostPrecisionForSimulationTime(returnTime);

	//			lagData->m_sProxyData.m_flSimulationTime = returnTime;
	//			lagData->m_sProxyData.m_bRecievedSimTime = true;
	//		}
	//	}
	//	
	//	Interfaces::m_pFlSimulationTime->GetOriginalFunction()(pData, pStruct, pOut);
	//}

	//void RecvProxy_m_flLowerBodyYawTarget(CRecvProxyData* pData, void* pStruct, void* pOut) 
	//{
	//	g_Vars.globals.szLastHookCalled = XorStr("29");

	//	if (!pData || !pStruct || !pOut)
	//		return;

	//	Interfaces::m_pFlLowerBodyYaw->GetOriginalFunction()(pData, pStruct, pOut);

	//	C_CSPlayer* pEntity = (C_CSPlayer*)pEntity;
	//	if (Interfaces::m_pEngine->IsInGame() && Interfaces::m_pEngine->IsConnected() && C_CSPlayer::GetLocalPlayer() && pEntity && pEntity->IsPlayer() && pEntity != C_CSPlayer::GetLocalPlayer())
	//	{
	//		auto lagData = Engine::LagCompensation::Get()->GetLagData(pEntity->EntIndex()).Xor();
	//		if (lagData && lagData->m_History.size())
	//		{
	//			// just to make sure this variable isn't always set to true.
	//			lagData->m_sProxyData.m_bRecievedLBY = false;
	//			lagData->m_sProxyData.m_iTickRecievedLBYUpdate = Interfaces::m_pGlobalVars->tickcount;
	//			lagData->m_sProxyData.m_flLowerBodyYaw = pData->m_Value.m_Float;

	//			auto animationRecord = Engine::AnimationSystem::Get()->GetAnimationData(pEntity->EntIndex())->m_AnimationRecord;
	//			if (!animationRecord.empty() && animationRecord.size() >= 2 && animationRecord.front().m_flLowerBodyYawTarget != lagData->m_sProxyData.m_flLowerBodyYaw)
	//				lagData->m_sProxyData.m_bLBYUpdated = true;

	//			lagData->m_sProxyData.m_bRecievedLBY = true;
	//		}
	//	}

	//	Interfaces::m_pFlLowerBodyYaw->GetOriginalFunction()(pData, pStruct, pOut);
	//}

	//void RecvProxy_m_angEyeAnglesY(CRecvProxyData* pData, void* pStruct, void* pOut) 
	//{
	//	g_Vars.globals.szLastHookCalled = XorStr("29");

	//	if (!pData || !pStruct || !pOut)
	//		return;

	//	Interfaces::m_pEyeAnglesY->GetOriginalFunction()(pData, pStruct, pOut);

	//	C_CSPlayer* pEntity = (C_CSPlayer*)pEntity;
	//	if (Interfaces::m_pEngine->IsInGame() && Interfaces::m_pEngine->IsConnected() && C_CSPlayer::GetLocalPlayer() && pEntity && pEntity->IsPlayer() && pEntity != C_CSPlayer::GetLocalPlayer())
	//	{
	//		auto lagData = Engine::LagCompensation::Get()->GetLagData(pEntity->EntIndex()).Xor();
	//		if (lagData && lagData->m_History.size())
	//		{
	//			// just to make sure this variable isn't always set to true.
	//			lagData->m_sProxyData.m_bRecievedYawAngle = false;
	//			lagData->m_sProxyData.m_flEyeYawAngle = pData->m_Value.m_Float;
	//			lagData->m_sProxyData.m_bRecievedYawAngle = true;
	//		}
	//	}

	//	Interfaces::m_pEyeAnglesY->GetOriginalFunction()(pData, pStruct, pOut);
	//}

	void m_bClientSideAnimation( CRecvProxyData* pData, void* pStruct, void* pOut ) 
	{
		auto local = C_CSPlayer::GetLocalPlayer( );
		if( !local || local->IsDead( ) )
			return Interfaces::m_bClientSideAnimationSwap->GetOriginalFunction( )( pData, pStruct, pOut );

		auto player = ( C_CSPlayer* )pStruct;

		if( player && player->IsPlayer( ) && !player->IsTeammate( local ) )
			*( int* )pOut = ( g_Vars.globals.m_bUpdatingAnimations ? 1 : 0 );
	}

	void RecvProxy_PlaybackRate( CRecvProxyData* pData, void* pStruct, void* pOut ) 
	{
		g_Vars.globals.szLastHookCalled = XorStr( "47" );
		// PlaybackRate
		Interfaces::m_pPlaybackRateSwap->GetOriginalFunction( )( pData, pStruct, pOut );

		C_CSPlayer* LocalPlayer = C_CSPlayer::GetLocalPlayer( );

		if( !LocalPlayer )
			return;

		auto pAnimOverlay = ( C_AnimationLayer* )pStruct;
		if( pAnimOverlay ) 
		{
			auto player = ( C_BasePlayer* )pAnimOverlay->m_pOwner;
			if( !player || player == LocalPlayer )
				return;

			auto& lag_data = Engine::LagCompensation::Get( )->GetLagData( player->EntIndex( ) );
			if( lag_data.Xor( ) ) 
			{
				lag_data->m_flRate = pAnimOverlay->m_flPlaybackRate;
				lag_data->m_bRateCheck = true;
			}
		}
	}
}