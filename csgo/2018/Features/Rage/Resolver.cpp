#include "Resolver.hpp"
#include "../../SDK/CVariables.hpp"
#include "../Visuals/CChams.hpp"
#include "../Rage/AntiAim.hpp"
#include "../Rage/Ragebot.hpp"
#include "../Rage/Autowall.h"
#include "../Visuals/EventLogger.hpp"

bool bLBYIsFlicking = false;

namespace Engine {
	CResolver g_Resolver;
	CResolverData g_ResolverData[65];

	void CResolver::FindBestAngle(C_CSPlayer* player) {
		auto pLocal = C_CSPlayer::GetLocalPlayer();
		if (!pLocal)
			return;

		// constants.
		constexpr float STEP{ 4.f };
		constexpr float RANGE{ 32.f };

		// best target.
		struct AutoTarget_t { float fov; C_CSPlayer* player; };
		AutoTarget_t target{ 180.f + 1.f, nullptr };

		if (!player || player->IsDead())
			return;

		if (player->IsDormant())
			return;

		bool is_team = player->IsTeammate(player);
		if (is_team)
			return;

		auto lag_data = Engine::LagCompensation::Get()->GetLagData(player->m_entIndex);
		if (!lag_data.IsValid())
			return;

		auto AngleDistance = [&](QAngle& angles, const Vector& start, const Vector& end) -> float {
			auto direction = end - start;
			auto aimAngles = direction.ToEulerAngles();
			auto delta = aimAngles - angles;
			delta.Normalize();

			return sqrtf(delta.x * delta.x + delta.y * delta.y);
		};

		float fov = AngleDistance(g_Vars.globals.m_pCmd->viewangles, g_Vars.globals.m_vecFixedEyePosition, player->WorldSpaceCenter());

		if (fov < target.fov) {
			target.fov = fov;
			target.player = player;
		}

		// get best origin based on target.
		auto m_vecOrigin = player->m_vecOrigin();

		// get predicted away angle for the player.
		Vector angAway;
		Math::VectorAngles(pLocal->m_vecOrigin() - m_vecOrigin, angAway);

		if (!target.player) {
			// set angle to backwards.
			g_ResolverData[player->EntIndex()].m_flBestYaw = angAway.y + 180.f;
			g_ResolverData[player->EntIndex()].m_flBestDistance = -1.f;
			g_ResolverData[player->EntIndex()].m_bCollectedFreestandData = false;
			return;
		}

		// construct vector of angles to test.
		std::vector< AdaptiveAngle > angles{ };
		angles.emplace_back(angAway.y - 90.f);
		angles.emplace_back(angAway.y + 90.f);

		// start the trace at the enemy shoot pos.
		Vector start = g_Vars.globals.m_vecFixedEyePosition;

		Vector end = target.player->GetEyePosition();

		// see if we got any valid result.
		// if this is false the path was not obstructed with anything.
		bool valid{ false };

		// iterate vector of angles.
		for (auto it = angles.begin(); it != angles.end(); ++it) {

			// compute the 'rough' estimation of where our head will be.
			Vector end{ end.x + std::cos(DEG2RAD(it->m_yaw)) * RANGE,
				end.y + std::sin(DEG2RAD(it->m_yaw)) * RANGE,
				end.z };

			// compute the direction.
			Vector dir = end - start;
			float len = dir.Normalize();

			// should never happen.
			if (len <= 0.f)
				continue;

			// step thru the total distance, 4 units per step.
			for (float i{ 0.f }; i < len; i += STEP) {
				// get the current step position.
				Vector point = start + (dir * i);

				// get the contents at this point.
				int contents = Interfaces::m_pEngineTrace->GetPointContents(point, MASK_SHOT_HULL);

				// contains nothing that can stop a bullet.
				if (!(contents & MASK_SHOT_HULL))
					continue;

				float mult = 1.f;

				// over 50% of the total length, prioritize this shit.
				if (i > (len * 0.5f))
					mult = 1.25f;

				// over 90% of the total length, prioritize this shit.
				if (i > (len * 0.75f))
					mult = 1.25f;

				// over 90% of the total length, prioritize this shit.
				if (i > (len * 0.9f))
					mult = 2.f;

				// append 'penetrated distance'.
				it->m_dist += (STEP * mult);

				// mark that we found anything.
				valid = true;
			}
		}

		if (!valid) {
			// set angle to backwards.
			g_ResolverData[player->EntIndex()].m_flBestYaw = angAway.y;
			g_ResolverData[player->EntIndex()].m_flBestDistance = -1.f;
			g_ResolverData[player->EntIndex()].m_bCollectedFreestandData = false;
			return;
		}

		// put the most distance at the front of the container.
		std::sort(angles.begin(), angles.end(),
			[](const AdaptiveAngle& a, const AdaptiveAngle& b) {
				return a.m_dist > b.m_dist;
			});

		// the best angle should be at the front now.
		AdaptiveAngle* best = &angles.front();

		// check if we are not doing a useless change.
		if (best->m_dist != g_ResolverData[player->EntIndex()].m_flBestDistance) {
			// set yaw to the best result.
			g_ResolverData[player->EntIndex()].m_flBestYaw = Math::AngleNormalize(best->m_yaw);
			g_ResolverData[player->EntIndex()].m_flBestDistance = best->m_dist;

			// for later use.
			g_ResolverData[player->EntIndex()].m_bCollectedFreestandData = true;
		}
	}

	void CResolver::ResolveAngles(C_CSPlayer* player, C_AnimationRecord* record) {
		FindBestAngle(player);

		// we arrived here we can do the acutal resolve.
		if (record->m_iResolverMode == EResolverModes::RESOLVE_WALK)
			ResolveWalk(player, record);

		else if (record->m_iResolverMode == EResolverModes::RESOLVE_STAND)
			ResolveStand(player, record);

		else if (record->m_iResolverMode == EResolverModes::RESOLVE_AIR)
			ResolveAir(player, record);
	}

	void CResolver::ResolveYaw(C_CSPlayer* player, C_AnimationRecord* record) {
		float speed = record->m_vecAnimationVelocity.Length();

		// improved this check & commented it out for when i fix it;
		// i was thinking this could be the reason we dump sometimes so i commented it out.
		//if (g_ResolverData[player->EntIndex()].gotserverside) 
		//{
		//	record->m_iResolverMode = EResolverModes::RESOLVE_STAND1;
		//	record->m_bResolved = true;
		//	g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = g_ResolverData[player->EntIndex()].serversideangle;

		//	// write potentially resolved angles.
		//	record->m_angEyeAngles.y = player->m_angEyeAngles().y = g_ResolverData[player->EntIndex()].m_flFinalResolverYaw;
		//	return;
		//}

		if ((record->m_fFlags & FL_ONGROUND) && (record->m_bFakeWalking || speed > 2.f) && !record->m_bUnsafeVelocityTransition)
			record->m_iResolverMode = EResolverModes::RESOLVE_WALK;

		if ((record->m_fFlags & FL_ONGROUND) && (speed <= 0.1f && !record->m_bFakeWalking || record->m_bUnsafeVelocityTransition))
			record->m_iResolverMode = EResolverModes::RESOLVE_STAND;

		else if (!(record->m_fFlags & FL_ONGROUND))
			record->m_iResolverMode = EResolverModes::RESOLVE_AIR;

		// attempt to resolve the player.
		ResolveAngles(player, record);

		// write potentially resolved angles.
		record->m_angEyeAngles.y = player->m_angEyeAngles().y = g_ResolverData[player->EntIndex()].m_flFinalResolverYaw;
	}

	void CResolver::ResolveWalk(C_CSPlayer* player, C_AnimationRecord* record) {
		// this guy aint tricking us bro
		if (record->m_bFakeWalking) {
			Encrypted_t<Engine::C_EntityLagData> pLagData = Engine::LagCompensation::Get()->GetLagData(player->EntIndex());
			if (pLagData.IsValid()) {
				g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("FW");
				switch (pLagData->m_iMissedShots % 6) { // left some comments of possible things i can do to improve this in the future if it isn't the greatest.
				case 0: /*g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = record->m_angDirWhenFirstStartedMoving.y; break;*/
				case 1:
					g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = Math::ClampYaw(record->m_angDirWhenFirstStartedMoving.y + 180.0f);
					break;
				case 2: // possibly a freestanding check here
				case 3: {
					QAngle dir;
					Math::VectorAngles(record->m_vecVelocity, dir);
					g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = Math::ClampYaw(dir.y + 180.0f);
					break;
				}
				case 4: // check if lby == old lby and if so then use lby here, if not do lby difference + angle when they first started moving
				case 5: // fuck it just fall back to this
					g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = record->m_angDirWhenFirstStartedMoving.y;
					break;
				default: { // we cannot stop fucking missing can we... redo angle estimates via veldir
					QAngle dir;
					Math::VectorAngles(record->m_vecVelocity, dir);
					g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = dir.y;
					break;
				}
				}
			}
		}

		// run the normal running resolver
		else {
			g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("R");

			// apply lby to eyeangles.
			g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = record->m_flLowerBodyYawTarget;

			// get lag data.
			Encrypted_t<Engine::C_EntityLagData> pLagData = Engine::LagCompensation::Get()->GetLagData(player->EntIndex());
			if (pLagData.IsValid()) {
				// predict the next time if they stop moving.
				pLagData->m_iMissedShotsLBY = 0;

				// reset missed shots counter as their angle has changed.
				pLagData->m_iMissedShots = 0;
			}

			// haven't checked this yet, do it in CResolver::ResolveStand( ... )
			g_ResolverData[player->EntIndex()].m_bCollectedValidMoveData = false;

			// set this to true so that way it pushes back a record of this.
			//record->m_bResolved = true;

			// store the data about the moving player, we need to because it contains crucial info
			// that we will have to later on use in our resolver.
			g_ResolverData[player->EntIndex()].m_sMoveData.m_flAnimTime = player->m_flAnimationTime();
			g_ResolverData[player->EntIndex()].m_sMoveData.m_vecOrigin = record->m_vecOrigin;
			g_ResolverData[player->EntIndex()].m_sMoveData.m_flLowerBodyYawTarget = record->m_flLowerBodyYawTarget;
			g_ResolverData[player->EntIndex()].m_sMoveData.m_flSimulationTime = record->m_flSimulationTime;
			return;
		}
	}

	void CResolver::ResolveStand(C_CSPlayer* player, C_AnimationRecord* record) {
		auto local = C_CSPlayer::GetLocalPlayer();
		if (!local)
			return;

		// get resolver data.
		auto& data = g_ResolverData[player->EntIndex()];

		// get predicted away angle for the player.
		Vector angAway;
		Math::VectorAngles(local->m_vecOrigin() - record->m_vecOrigin, angAway);

		// get lag data.
		Encrypted_t<Engine::C_EntityLagData> pLagData = Engine::LagCompensation::Get()->GetLagData(player->EntIndex());
		if (!pLagData.IsValid()) {
			return;
		}

		bool bDetectingDistortion = false;
		const int nMisses = pLagData->m_iMissedShots;

		// we have a valid moving record.
		static Vector vDormantOrigin;
		if (player->IsDormant()) {
			data.m_bCollectedValidMoveData = false;
			vDormantOrigin = record->m_vecOrigin;
		}
		else {
			Vector delta = vDormantOrigin - record->m_vecOrigin;
			if (delta.Length() > 16.f) {
				data.m_bCollectedValidMoveData = true;
				vDormantOrigin = Vector();
			}

			// improved logic on lby check
			static float flLBYDifference = record->m_flLowerBodyYawTarget - g_ResolverData[player->EntIndex()].m_flOldLowerBodyYawTarget;
			if ((flLBYDifference > 56.f && nMisses >= 3 || flLBYDifference > 36.f) && !bLBYIsFlicking && !record->m_bUnsafeVelocityTransition) // funny number
				bDetectingDistortion = true;
		}

		bool bModulatingLBY = bDetectingDistortion || bLBYIsFlicking || record->m_flLowerBodyYawTarget != g_ResolverData[player->EntIndex()].m_flOldLowerBodyYawTarget || record->m_bUnsafeVelocityTransition;

		// the logic behind this should work.
		// this could also be the reason everything is broken.
		bool bInvalidatedLastMovingLBY = false;
		if (!bInvalidatedLastMovingLBY)
		{
			if (data.m_bCollectedValidMoveData && IsLastMoveValid(record, g_ResolverData[player->EntIndex()].m_sMoveData.m_flLowerBodyYawTarget) && bModulatingLBY)
				bInvalidatedLastMovingLBY = true;
		}
		else if (data.m_bCollectedValidMoveData && !IsLastMoveValid(record, g_ResolverData[player->EntIndex()].m_sMoveData.m_flLowerBodyYawTarget) && bInvalidatedLastMovingLBY)
			bInvalidatedLastMovingLBY = false;

		// possibly proxy our targeted entities yaw & lby and use them here so we always have the most pristine angles.

		// we have valid move data but we can't freestand them.
		// there's a possibility that our last moving will be invalid if the target starts distorting, see if that is the case eventually.
		if (data.m_bCollectedValidMoveData && IsLastMoveValid(record, g_ResolverData[player->EntIndex()].m_sMoveData.m_flLowerBodyYawTarget) && !bInvalidatedLastMovingLBY && nMisses < 1) {
			g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("LM");
			g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = g_ResolverData[player->EntIndex()].m_sMoveData.m_flLowerBodyYawTarget;
			record->m_bResolved = true;
			return;
		}

		// no lby modulation; force this bitch
		else if (!bModulatingLBY)
		{
			g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("LBY");
			g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = record->m_flLowerBodyYawTarget;
			record->m_bResolved = true;
			return;
		}

		// distortion resolver; or at least hopefully a distortion resolver.
		// the last move check possibly might not needed
		// removed the last moving check as distortion should invalidate last moving as it updates the lby.
		else if (bDetectingDistortion ) //&& g_Vars.rage.distortion_resolver.enabled
		{
			g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("D");
			switch (nMisses % 2) {
			case 0: // lby difference
				g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = record->m_flLowerBodyYawTarget - g_ResolverData[player->EntIndex()].m_flOldLowerBodyYawTarget;
				break;

			case 1: // distortion estimate
			{
				g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = Math::ClampYr(Math::ClampYr(record->m_angEyeAngles.y) - (record->m_flLowerBodyYawTarget - g_ResolverData[player->EntIndex()].m_flOldLowerBodyYawTarget));
				break;
			}
			}
		}

		// only force this if we don't have a valid last move or if our lby is being modulated.
		// commented for now.
		//else if (data.m_bCollectedFreestandData && pLagData->DetectAutoDirerction(pLagData, player) && (bModulatingLBY || data.m_bCollectedValidMoveData && !IsLastMoveValid(record, g_ResolverData[player->EntIndex()].m_sMoveData.m_flLowerBodyYawTarget))) {
		//	g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("FB");
		//	switch (nMisses % 4) {
		//	case 0:
		//		g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = pLagData->m_flDirection;
		//		break;

		//	case 1:
		//		g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = g_ResolverData[player->EntIndex()].m_flBestYaw;
		//		break;

		//	case 2:
		//		g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = angAway.y + 70.f;
		//		break;

		//	case 3:
		//		g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = angAway.y - 70.f;
		//		break;

		//	case 4:
		//		g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = angAway.y + 180.f;
		//		break;
		//	}
		//}
	}

	void CResolver::ResolveAir(C_CSPlayer* player, C_AnimationRecord* record) {
		// we have barely any speed. 
		// either we jumped in place or we just left the ground.
		// or someone is trying to fool our resolver.
		if (record->m_vecAnimationVelocity.Length2D() < 60.f) {
			// set this for completion.
			// so the shot parsing wont pick the hits / misses up.
			// and process them wrongly.
			record->m_iResolverMode = EResolverModes::RESOLVE_STAND;

			// invoke our stand resolver.
			ResolveStand(player, record);

			// we are done.
			return;
		}

		// get lag data.
		Encrypted_t<Engine::C_EntityLagData> pLagData = Engine::LagCompensation::Get()->GetLagData(player->m_entIndex);
		if (!pLagData.IsValid())
			return;

		// try to predict the direction of the player based on his velocity direction.
		// this should be a rough estimation of where he is looking.
		float velyaw = RAD2DEG(std::atan2(record->m_vecAnimationVelocity.y, record->m_vecAnimationVelocity.x));

		// this is not really fully resolved yet so don't set resolved to true here.

		g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("A");

		switch (pLagData->m_iMissedShots % 4) {
		case 0:
			g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = velyaw + 180.f;
			break;

		case 1:
			g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = velyaw - 90.f;
			break;

		case 2:
			g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = velyaw + 90.f;
			break;

		case 3:
			g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = velyaw;
			break;
		}
	}

	void CResolver::ResolveManual(C_CSPlayer* player, C_AnimationRecord* record, bool bDisallow) {
		auto local = C_CSPlayer::GetLocalPlayer();
		if (!local)
			return;

		static auto bHasTarget = false;
		if (!g_Vars.rage.override_reoslver.enabled) {
			bHasTarget = false;
			return;
		}

		static std::vector<C_CSPlayer*> pTargets;
		static auto bLastChecked = 0.f;

		// check if we have a player?
		if (bLastChecked != Interfaces::m_pGlobalVars->curtime) {
			// update this.
			bLastChecked = Interfaces::m_pGlobalVars->curtime;
			pTargets.clear();

			// get viewangles.
			QAngle m_vecLocalViewAngles;
			Interfaces::m_pEngine->GetViewAngles(m_vecLocalViewAngles);

			// loop through all entitys.
			const auto m_flNeededFOV = 20.f;
			for (int i{ 1 }; i <= Interfaces::m_pGlobalVars->maxClients; ++i) {
				auto entity = reinterpret_cast<C_CSPlayer*>(Interfaces::m_pEntList->GetClientEntity(i));
				if (!entity || entity->IsDead() || !entity->IsTeammate(local))
					continue;

				auto AngleDistance = [&](QAngle& angles, const Vector& start, const Vector& end) -> float {
					auto direction = end - start;
					auto aimAngles = direction.ToEulerAngles();
					auto delta = aimAngles - angles;
					delta.Normalize();

					return sqrtf(delta.x * delta.x + delta.y * delta.y);
				};
				// get distance based FOV.
				float m_flBaseFOV = AngleDistance(m_vecLocalViewAngles, local->GetEyePosition(), entity->GetEyePosition());

				// we have a valid target in our FOV.
				if (m_flBaseFOV < m_flNeededFOV) {
					// push back our target.
					pTargets.push_back(entity);
				}
			}
		}

		// we dont have any targets.
		if (pTargets.empty()) {
			bHasTarget = false;
			return;
		}

		auto bFoundPlayer = false;
		// iterate through our targets.
		for (auto& t : pTargets) {
			if (player == t) {
				bFoundPlayer = true;
				break;
			}
		}

		// we dont have one lets exit.
		if (!bFoundPlayer)
			return;

		// get lag data.
		Encrypted_t<Engine::C_EntityLagData> pLagData = Engine::LagCompensation::Get()->GetLagData(player->EntIndex());
		if (!pLagData.IsValid()) {
			return;
		}

		// get current viewangles.
		QAngle m_vecViewAngles;
		Interfaces::m_pEngine->GetViewAngles(m_vecViewAngles);

		static auto m_flLastDelta = 0.f;
		static auto m_flLastAngle = 0.f;

		const auto angAway = Math::CalcAngle(local->GetEyePosition(), player->GetEyePosition()).y;
		auto m_flDelta = Math::AngleNormalize(m_vecViewAngles.y - angAway);

		if (bHasTarget && fabsf(m_vecViewAngles.y - m_flLastAngle) < 0.1f) {
			m_vecViewAngles.y = m_flLastAngle;
			m_flDelta = m_flLastDelta;
		}

		bHasTarget = true;

		if (g_Vars.rage.override_reoslver.enabled) {
			if (m_flDelta > 1.2f)
				record->m_angEyeAngles.y = angAway + 90.f;
			else if (m_flDelta < -1.2f)
				record->m_angEyeAngles.y = angAway - 90.f;
			else
				record->m_angEyeAngles.y = angAway;
		}

		m_flLastAngle = m_vecViewAngles.y;
		m_flLastDelta = m_flDelta;
	}

	void CResolver::PredictBodyUpdates(C_CSPlayer* player, C_AnimationRecord* record, C_AnimationRecord* prev) {
		auto local = C_CSPlayer::GetLocalPlayer();
		if (!local)
			return;

		if (!(local->m_fFlags() & FL_ONGROUND) || !(player->m_fFlags() & FL_ONGROUND))
			return;

		// nah
		if (local->IsDead()) {
			Engine::g_ResolverData[player->EntIndex()].m_bPredictingUpdates = false;
			g_ResolverData[player->EntIndex()].m_bCollectedValidMoveData = false;
			bLBYIsFlicking = false;
			return;
		}

		// we have no reliable move data, we can't predict
		if (!Engine::g_ResolverData[player->EntIndex()].m_bCollectedValidMoveData) {
			Engine::g_ResolverData[player->EntIndex()].m_bPredictingUpdates = false;
			bLBYIsFlicking = false;
			return;
		}

		// get lag data about this player
		Encrypted_t<Engine::C_EntityLagData> pLagData = Engine::LagCompensation::Get()->GetLagData(player->m_entIndex);
		if (!pLagData.IsValid()) {
			Engine::g_ResolverData[player->EntIndex()].m_bPredictingUpdates = false;
			bLBYIsFlicking = false;
			return;
		}

		if (pLagData->m_iMissedShotsLBY >= 2) {
			Engine::g_ResolverData[player->EntIndex()].m_bPredictingUpdates = false;
			bLBYIsFlicking = false;
			return;
		}

		if (record->m_bUnsafeVelocityTransition || record->m_bFakeWalking) {
			Engine::g_ResolverData[player->EntIndex()].m_bPredictingUpdates = false;
			bLBYIsFlicking = false;
			return;
		}

		// inform esp that we're about to be the prediction process
		Engine::g_ResolverData[player->EntIndex()].m_bPredictingUpdates = true;

		//check if the player is walking
		// no need for the extra fakewalk check since we null velocity when they're fakewalking anyway
		if (record->m_vecAnimationVelocity.Length2D() > 0.1f) {
			g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("F");

			// predict the first flick they have to do after they stop moving
			Engine::g_ResolverData[player->EntIndex()].m_flNextBodyUpdate = player->m_flAnimationTime() + 0.22f;

			record->m_bResolved = true;
			bLBYIsFlicking = true;

			// since we are still not in the prediction process, inform the cheat that we arent predicting yet
			// this is only really used to determine if we should draw the lby timer bar on esp, no other real purpose
			Engine::g_ResolverData[player->EntIndex()].m_bPredictingUpdates = false;
		}

		// lby updated on this tick
		else if ((Engine::g_ResolverData[player->EntIndex()].m_flOldLowerBodyYawTarget && record->m_flLowerBodyYawTarget) || player->m_flAnimationTime() >= Engine::g_ResolverData[player->EntIndex()].m_flNextBodyUpdate) {
			// inform the cheat of the resolver method
			record->m_iResolverMode = EResolverModes::RESOLVE_PRED;

			g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("F");

			// predict the next body update
			Engine::g_ResolverData[player->EntIndex()].m_flNextBodyUpdate = player->m_flAnimationTime() + 1.1f;

			// set eyeangles to lby
			record->m_angEyeAngles.y = player->m_angEyeAngles().y = record->m_flLowerBodyYawTarget;

			// this is also only really used for esp flag
			record->m_bResolved = true;
			bLBYIsFlicking = true;

			// we're now in the prediction stage.
			Engine::g_ResolverData[player->EntIndex()].m_bPredictingUpdates = true;
		}
	}
}


/*#include "Resolver.hpp"
#include "../../SDK/CVariables.hpp"
#include "../Visuals/CChams.hpp"
#include "../Rage/AntiAim.hpp"
#include "../Rage/Ragebot.hpp"
#include "../Rage/Autowall.h"
#include "../Visuals/EventLogger.hpp"

namespace Engine {
	// well alpha took supremacy resolver, but supremacy resolver is actual dogshit
	// so this is going to be a hard test for viopastins (again this is referring to violations, the man who is responsible for selling immortal software source code!)

	//violations you should really watch your friend sean1!

	// vader.tech invite https://discord.gg/GV6JNW3nze

	//artens ip 67.162.21.17

	CResolver g_Resolver;
	CResolverData g_ResolverData[65];

	void CResolver::FindBestAngle(C_CSPlayer* player) {
		auto pLocal = C_CSPlayer::GetLocalPlayer();
		if (!pLocal)
			return;

		// constants.
		constexpr float STEP{ 4.f };
		constexpr float RANGE{ 32.f };

		// best target.
		struct AutoTarget_t { float fov; C_CSPlayer* player; };
		AutoTarget_t target{ 180.f + 1.f, nullptr };

		if (!player || player->IsDead())
			return;

		if (player->IsDormant())
			return;

		bool is_team = player->IsTeammate(player);
		if (is_team)
			return;

		auto lag_data = Engine::LagCompensation::Get()->GetLagData(player->m_entIndex);
		if (!lag_data.IsValid())
			return;

		auto AngleDistance = [&](QAngle& angles, const Vector& start, const Vector& end) -> float {
			auto direction = end - start;
			auto aimAngles = direction.ToEulerAngles();
			auto delta = aimAngles - angles;
			delta.Normalize();

			return sqrtf(delta.x * delta.x + delta.y * delta.y);
		};

		float fov = AngleDistance(g_Vars.globals.m_pCmd->viewangles, g_Vars.globals.m_vecFixedEyePosition, player->WorldSpaceCenter());

		if (fov < target.fov) {
			target.fov = fov;
			target.player = player;
		}

		// get best origin based on target.
		auto m_vecOrigin = player->m_vecOrigin();

		// get predicted away angle for the player.
		Vector angAway;
		Math::VectorAngles(pLocal->m_vecOrigin() - m_vecOrigin, angAway);

		if (!target.player) {
			// set angle to backwards.
			g_ResolverData[player->EntIndex()].m_flBestYaw = angAway.y + 180.f;
			g_ResolverData[player->EntIndex()].m_flBestDistance = -1.f;
			g_ResolverData[player->EntIndex()].m_bCollectedFreestandData = false;
			return;
		}

		// construct vector of angles to test.
		std::vector< AdaptiveAngle > angles{ };
		angles.emplace_back(angAway.y - 90.f);
		angles.emplace_back(angAway.y + 90.f);

		// start the trace at the enemy shoot pos.
		Vector start = g_Vars.globals.m_vecFixedEyePosition;

		Vector end = target.player->GetEyePosition();

		// see if we got any valid result.
		// if this is false the path was not obstructed with anything.
		bool valid{ false };

		// iterate vector of angles.
		for (auto it = angles.begin(); it != angles.end(); ++it) {

			// compute the 'rough' estimation of where our head will be.
			Vector end{ end.x + std::cos(DEG2RAD(it->m_yaw)) * RANGE,
				end.y + std::sin(DEG2RAD(it->m_yaw)) * RANGE,
				end.z };

			// compute the direction.
			Vector dir = end - start;
			float len = dir.Normalize();

			// should never happen.
			if (len <= 0.f)
				continue;

			// step thru the total distance, 4 units per step.
			for (float i{ 0.f }; i < len; i += STEP) {
				// get the current step position.
				Vector point = start + (dir * i);

				// get the contents at this point.
				int contents = Interfaces::m_pEngineTrace->GetPointContents(point, MASK_SHOT_HULL);

				// contains nothing that can stop a bullet.
				if (!(contents & MASK_SHOT_HULL))
					continue;

				float mult = 1.f;

				// over 50% of the total length, prioritize this shit.
				if (i > (len * 0.5f))
					mult = 1.25f;

				// over 90% of the total length, prioritize this shit.
				if (i > (len * 0.75f))
					mult = 1.25f;

				// over 90% of the total length, prioritize this shit.
				if (i > (len * 0.9f))
					mult = 2.f;

				// append 'penetrated distance'.
				it->m_dist += (STEP * mult);

				// mark that we found anything.
				valid = true;
			}
		}

		if (!valid) {
			// set angle to backwards.
			g_ResolverData[player->EntIndex()].m_flBestYaw = angAway.y;
			g_ResolverData[player->EntIndex()].m_flBestDistance = -1.f;
			g_ResolverData[player->EntIndex()].m_bCollectedFreestandData = false;
			return;
		}

		// put the most distance at the front of the container.
		std::sort(angles.begin(), angles.end(),
			[](const AdaptiveAngle& a, const AdaptiveAngle& b) {
				return a.m_dist > b.m_dist;
			});

		// the best angle should be at the front now.
		AdaptiveAngle* best = &angles.front();

		// check if we are not doing a useless change.
		if (best->m_dist != g_ResolverData[player->EntIndex()].m_flBestDistance) {
			// set yaw to the best result.
			g_ResolverData[player->EntIndex()].m_flBestYaw = Math::AngleNormalize(best->m_yaw);
			g_ResolverData[player->EntIndex()].m_flBestDistance = best->m_dist;

			// for later use.
			g_ResolverData[player->EntIndex()].m_bCollectedFreestandData = true;
		}
	}

	// runs a trace to see if the freestanding angle is valid.
	bool ShouldUseFreestand(C_CSPlayer* player) {
		auto pLocal = C_CSPlayer::GetLocalPlayer();
		if (!pLocal)
			return false;

		Vector src3D, dst3D, forward, right, up, src, dst;
		float back_two, right_two, left_two;
		CGameTrace tr;
		CTraceFilterSkipEntity filter(player);

		QAngle angAway;
		Math::VectorAngles(pLocal->m_vecOrigin() - player->m_vecOrigin(), angAway);

		Math::AngleVectors(QAngle(0, angAway.y, 0), forward, right, up);

		src3D = player->GetEyePosition();
		dst3D = src3D + (forward * 384);

		Interfaces::m_pEngineTrace->TraceRay(Ray_t(src3D, dst3D), MASK_SHOT_BRUSHONLY | MASK_OPAQUE_AND_NPCS, &filter, &tr);
		back_two = (tr.endpos - tr.startpos).Length();

		Interfaces::m_pEngineTrace->TraceRay(Ray_t(src3D + right * 35, dst3D + right * 35), MASK_SHOT_BRUSHONLY | MASK_OPAQUE_AND_NPCS, &filter, &tr);
		right_two = (tr.endpos - tr.startpos).Length();

		Interfaces::m_pEngineTrace->TraceRay(Ray_t(src3D - right * 35, dst3D - right * 35), MASK_SHOT_BRUSHONLY | MASK_OPAQUE_AND_NPCS, &filter, &tr);
		left_two = (tr.endpos - tr.startpos).Length();

		if (left_two > right_two) {
			g_ResolverData[player->EntIndex()].m_iFreestandingSide = EFreestandingSides::LEFT_SIDE;
			return true;
		}
		else if (right_two > left_two) {
			g_ResolverData[player->EntIndex()].m_iFreestandingSide = EFreestandingSides::RIGHT_SIDE;
			return true;
		}
		else {
			g_ResolverData[player->EntIndex()].m_iFreestandingSide = EFreestandingSides::NO_SIDE;
			return false;
		}
	}

	void CResolver::ResolveAngles(C_CSPlayer* player, C_AnimationRecord* record, C_AnimationRecord* prev) {
		if (!prev)
			return;

		FindBestAngle(player);

		// we arrived here we can do the acutal resolve.
		if (record->m_iResolverMode == EResolverModes::RESOLVE_WALK)
			ResolveWalk(player, record);

		else if (record->m_iResolverMode == EResolverModes::RESOLVE_STAND)
			ResolveStand(player, record, prev);

		else if (record->m_iResolverMode == EResolverModes::RESOLVE_AIR)
			ResolveAir(player, record, prev);

		else if (record->m_iResolverMode == EResolverModes::RESOLVE_MANUAL)
			ResolveManual(player, record);
	}

	void CResolver::ResolveYaw(C_CSPlayer* player, C_AnimationRecord* record, C_AnimationRecord* prev) {
		float speed = record->m_vecAnimationVelocity.Length();

		if ((record->m_fFlags & FL_ONGROUND) && (record->m_bFakeWalking || speed > 0.1f) && !record->m_bUnsafeVelocityTransition && !g_Vars.rage.override_reoslver.enabled)
			record->m_iResolverMode = EResolverModes::RESOLVE_WALK;

		if ((record->m_fFlags & FL_ONGROUND) && (speed <= 0.1f || record->m_bFakeWalking || record->m_bUnsafeVelocityTransition) && !g_Vars.rage.override_reoslver.enabled)
			record->m_iResolverMode = EResolverModes::RESOLVE_STAND;

		else if (!(record->m_fFlags & FL_ONGROUND) && !g_Vars.rage.override_reoslver.enabled)
			record->m_iResolverMode = EResolverModes::RESOLVE_AIR;

		else if ((record->m_fFlags & FL_ONGROUND) && (speed <= 0.1f || record->m_bFakeWalking || record->m_bUnsafeVelocityTransition) && g_Vars.rage.override_reoslver.enabled)
			record->m_iResolverMode = EResolverModes::RESOLVE_MANUAL;

		// attempt to resolve the player.
		ResolveAngles(player, record, prev);

		// write potentially resolved angles.
		record->m_angEyeAngles.y = player->m_angEyeAngles().y = g_ResolverData[player->EntIndex()].m_flFinalResolverYaw;
	}

	void CResolver::ResolveWalk(C_CSPlayer* player, C_AnimationRecord* record) {
		// this guy aint tricking us bro
		if (record->m_bFakeWalking) {
			Encrypted_t<Engine::C_EntityLagData> pLagData = Engine::LagCompensation::Get()->GetLagData(player->EntIndex());
			if (pLagData.IsValid()) {
				g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("FW");
				switch (pLagData->m_iMissedShots % 6) { // left some comments of possible things i can do to improve this in the future; i just know that u said it hit before.
				//case 0: g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = record->m_angDirWhenFirstStartedMoving.y; break;
				case 1:
					g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = Math::ClampYaw(record->m_angDirWhenFirstStartedMoving.y + 180.0f);
					break;
				case 2: // possibly a freestanding check here
				case 3: {
					QAngle dir;
					Math::VectorAngles(record->m_vecVelocity, dir);
					g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = Math::ClampYaw(dir.y + 180.0f);
					break;
				}
				case 4: // then maybe come up with another calculation here
				case 5: // fuck it just fall back to this
					g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = record->m_angDirWhenFirstStartedMoving.y;
					break;
				default: { // we cannot stop fucking missing can we... redo angle estimates via veldir
					QAngle dir;
					Math::VectorAngles(record->m_vecVelocity, dir);
					g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = dir.y;
					break;
				}
				}
			}
		}

		// run the normal running resolver
		else {
			// mark resolver mode.
			g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("MOVING");

			// apply lby to eyeangles.
			g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = record->m_flLowerBodyYawTarget;

			// get lag data.
			Encrypted_t<Engine::C_EntityLagData> pLagData = Engine::LagCompensation::Get()->GetLagData(player->EntIndex());
			if (pLagData.IsValid()) {
				// predict the next time if they stop moving.
				pLagData->m_iMissedShotsLBY = 0;
			}

			// haven't checked this yet, do it in CResolver::ResolveStand( ... )
			g_ResolverData[player->EntIndex()].m_bCollectedValidMoveData = false;

			// store the data about the moving player, we need to because it contains crucial info
			// that we will have to later on use in our resolver.
			g_ResolverData[player->EntIndex()].m_sMoveData.m_flAnimTime = player->m_flAnimationTime();
			g_ResolverData[player->EntIndex()].m_sMoveData.m_vecOrigin = record->m_vecOrigin;
			g_ResolverData[player->EntIndex()].m_sMoveData.m_flLowerBodyYawTarget = record->m_flLowerBodyYawTarget;
			g_ResolverData[player->EntIndex()].m_sMoveData.m_flSimulationTime = record->m_flSimulationTime;
		}
	}

	void CResolver::ResolveStand(C_CSPlayer* player, C_AnimationRecord* record, C_AnimationRecord* prev) {
		auto local = C_CSPlayer::GetLocalPlayer();
		if (!local)
			return;

		//NOTE: check act 979 or 980 for antifreestand
		// get resolver data.
		auto& data = g_ResolverData[player->EntIndex()];

		C_AnimationLayer* curr = &record->m_serverAnimOverlays[3], prevv = prev->m_serverAnimOverlays[3];
		int act = player->GetSequenceActivity(curr->m_nSequence);
		int prevAct = player->GetSequenceActivity(prevv.m_nSequence);

		// get predicted away angle for the player.
		Vector angAway;
		Math::VectorAngles(local->m_vecOrigin() - record->m_vecOrigin, angAway);

		// get lag data.
		Encrypted_t<Engine::C_EntityLagData> pLagData = Engine::LagCompensation::Get()->GetLagData(player->EntIndex());
		if (!pLagData.IsValid()) {
			return;
		}

		const int nMisses = pLagData->m_iMissedShots;

		// we have a valid moving record.
		static Vector vDormantOrigin;
		if (player->IsDormant()) {
			data.m_bCollectedValidMoveData = false;
			vDormantOrigin = record->m_vecOrigin;
		}
		else {
			Vector delta = vDormantOrigin - record->m_vecOrigin;
			if (delta.Length() > 16.f) {
				data.m_bCollectedValidMoveData = true;
				vDormantOrigin = Vector();
			}
		}

		if (data.m_bCollectedValidMoveData) {
			// we have a valid last moving, just force that.
			if (IsLastMoveValid(record, g_ResolverData[player->EntIndex()].m_sMoveData.m_flLowerBodyYawTarget)) {
				// check if our freestanding data is the same as our last moving lby
				if (data.m_bCollectedFreestandData) {
					// time to bruteforce!
					switch (nMisses % 3) {
					case 0:
						g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("MAB:LM");
						g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = g_ResolverData[player->EntIndex()].m_sMoveData.m_flLowerBodyYawTarget;
						break;
					case 1:
						if (ShouldUseFreestand) {
							switch (g_ResolverData[player->EntIndex()].m_iFreestandingSide) {
							case EFreestandingSides::LEFT_SIDE:
								g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("MAB:L");
								g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = g_ResolverData[player->EntIndex()].m_flBestYaw - 90;
								break;
							case EFreestandingSides::RIGHT_SIDE:
								g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("MAB:R");
								g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = g_ResolverData[player->EntIndex()].m_flBestYaw + 90;
								break;
							}
						}
						else { // ↓ this probably is not accurate if that trace returned false, so this part will need some work.
							g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("MAB:B");
							g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = g_ResolverData[player->EntIndex()].m_flBestYaw;
						}
						break;
					case 2:
						g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("MAB:LBY");
						g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = record->m_flLowerBodyYawTarget;
						break;
						// ↑ this could possibly use more cases.
					}
				}

				// if not just force our normal last moving angle
				else {
					g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("LM");
					g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = g_ResolverData[player->EntIndex()].m_sMoveData.m_flLowerBodyYawTarget;
					return;
				}
			}

			// we have a valid freestanding angle, just force that.
			else if (!IsLastMoveValid(record, g_ResolverData[player->EntIndex()].m_sMoveData.m_flLowerBodyYawTarget) && data.m_bCollectedFreestandData) {
				if (ShouldUseFreestand) {
					switch (g_ResolverData[player->EntIndex()].m_iFreestandingSide) {
					case EFreestandingSides::LEFT_SIDE:
						g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("FLM:L");
						g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = g_ResolverData[player->EntIndex()].m_flBestYaw - 90;
						break;
					case EFreestandingSides::RIGHT_SIDE:
						g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("FLM:R");
						g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = g_ResolverData[player->EntIndex()].m_flBestYaw + 90;
						break;
					}
				}
				else { // ↓ this probably is not accurate if that trace returned false, so this part will need some work.
					g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("FLM:B");
					g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = g_ResolverData[player->EntIndex()].m_flBestYaw;
				}
			}
		}

		// we don't have any moving data to work with so we are better off just forcing freestanding.
		else if (!data.m_bCollectedValidMoveData && data.m_bCollectedFreestandData) {
			if (ShouldUseFreestand) {
				switch (g_ResolverData[player->EntIndex()].m_iFreestandingSide) {
				case EFreestandingSides::LEFT_SIDE:
					g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("F:L");
					g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = g_ResolverData[player->EntIndex()].m_flBestYaw - 90;
					break;
				case EFreestandingSides::RIGHT_SIDE:
					g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("F:R");
					g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = g_ResolverData[player->EntIndex()].m_flBestYaw + 90;
					break;
				}
			}
			else { // ↓ this probably is not accurate if that trace returned false, so this part will need some work.
				g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("F:B");
				g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = g_ResolverData[player->EntIndex()].m_flBestYaw;
			}
		}

		else if (!data.m_bCollectedFreestandData && !data.m_bCollectedValidMoveData) {
			switch (nMisses % 6) {
			case 0:
				g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("B:LBY");
				g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = record->m_flLowerBodyYawTarget;
				break;
			case 1:
				g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("B:EXP");
				if (ShouldUseFreestand) {
					switch (g_ResolverData[player->EntIndex()].m_iFreestandingSide) {
					case EFreestandingSides::LEFT_SIDE:
						g_ResolverData[player->EntIndex()].m_sResolverMode += XorStr(":L");
						g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = angAway.y - 90;
						break;
					case EFreestandingSides::RIGHT_SIDE:
						g_ResolverData[player->EntIndex()].m_sResolverMode += XorStr(":R");
						g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = angAway.y + 90;
						break;
					}
				}
				else {
					g_ResolverData[player->EntIndex()].m_sResolverMode += XorStr(":A");
					g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = angAway.y;
				}
				break;
			case 2:
				g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("B:L");
				g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = angAway.y + 70.f;
				break;
			case 3:
				g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("B:R");
				g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = angAway.y - 70.f;
				break;
			case 4:
				g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("B:B");
				g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = angAway.y + 180.f;
				break;
			case 5:
				g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("B:LBYInv");
				g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = record->m_flLowerBodyYawTarget + 180.f;
				break;
			}
		}
	}

	void CResolver::ResolveAir(C_CSPlayer* player, C_AnimationRecord* record, C_AnimationRecord* prev) {
		// we have barely any speed. 
		// either we jumped in place or we just left the ground.
		// or someone is trying to fool our resolver.
		if (record->m_vecAnimationVelocity.Length2D() < 60.f) {
			// set this for completion.
			// so the shot parsing wont pick the hits / misses up.
			// and process them wrongly.
			record->m_iResolverMode = EResolverModes::RESOLVE_STAND;

			// invoke our stand resolver.
			ResolveStand(player, record, prev);

			// we are done.
			return;
		}

		// get lag data.
		Encrypted_t<Engine::C_EntityLagData> pLagData = Engine::LagCompensation::Get()->GetLagData(player->m_entIndex);
		if (!pLagData.IsValid())
			return;

		g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("AIR");

		// try to predict the direction of the player based on his velocity direction.
		// this should be a rough estimation of where he is looking.
		float velyaw = RAD2DEG(std::atan2(record->m_vecAnimationVelocity.y, record->m_vecAnimationVelocity.x));

		switch (pLagData->m_iMissedShots % 4) {
		case 0:
			g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = velyaw + 180.f;
			break;

		case 1:
			g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = velyaw - 90.f;
			break;

		case 2:
			g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = velyaw + 90.f;
			break;

		case 3:
			g_ResolverData[player->EntIndex()].m_flFinalResolverYaw = velyaw;
			break;
		}
	}

	void CResolver::ResolveManual(C_CSPlayer* player, C_AnimationRecord* record, bool bDisallow) {
		auto local = C_CSPlayer::GetLocalPlayer();
		if (!local)
			return;

		static auto bHasTarget = false;
		if (!g_Vars.rage.override_reoslver.enabled) {
			bHasTarget = false;
			return;
		}

		static std::vector<C_CSPlayer*> pTargets;
		static auto bLastChecked = 0.f;

		// check if we have a player?
		if (bLastChecked != Interfaces::m_pGlobalVars->curtime) {
			// mark resolver
			g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("MANUAL");
			// update this.
			bLastChecked = Interfaces::m_pGlobalVars->curtime;
			pTargets.clear();

			// get viewangles.
			QAngle m_vecLocalViewAngles;
			Interfaces::m_pEngine->GetViewAngles(m_vecLocalViewAngles);

			// loop through all entitys.
			const auto m_flNeededFOV = 20.f;
			for (int i{ 1 }; i <= Interfaces::m_pGlobalVars->maxClients; ++i) {
				auto entity = reinterpret_cast<C_CSPlayer*>(Interfaces::m_pEntList->GetClientEntity(i));
				if (!entity || entity->IsDead() || !entity->IsTeammate(local))
					continue;

				auto AngleDistance = [&](QAngle& angles, const Vector& start, const Vector& end) -> float {
					auto direction = end - start;
					auto aimAngles = direction.ToEulerAngles();
					auto delta = aimAngles - angles;
					delta.Normalize();

					return sqrtf(delta.x * delta.x + delta.y * delta.y);
				};
				// get distance based FOV.
				float m_flBaseFOV = AngleDistance(m_vecLocalViewAngles, local->GetEyePosition(), entity->GetEyePosition());

				// we have a valid target in our FOV.
				if (m_flBaseFOV < m_flNeededFOV) {
					// push back our target.
					pTargets.push_back(entity);
				}
			}
		}

		// we dont have any targets.
		if (pTargets.empty()) {
			bHasTarget = false;
			return;
		}

		auto bFoundPlayer = false;
		// iterate through our targets.
		for (auto& t : pTargets) {
			if (player == t) {
				bFoundPlayer = true;
				break;
			}
		}

		// we dont have one lets exit.
		if (!bFoundPlayer)
			return;

		// get lag data.
		Encrypted_t<Engine::C_EntityLagData> pLagData = Engine::LagCompensation::Get()->GetLagData(player->EntIndex());
		if (!pLagData.IsValid()) {
			return;
		}

		// get current viewangles.
		QAngle m_vecViewAngles;
		Interfaces::m_pEngine->GetViewAngles(m_vecViewAngles);

		static auto m_flLastDelta = 0.f;
		static auto m_flLastAngle = 0.f;

		const auto angAway = Math::CalcAngle(local->GetEyePosition(), player->GetEyePosition()).y;
		auto m_flDelta = Math::AngleNormalize(m_vecViewAngles.y - angAway);

		if (bHasTarget && fabsf(m_vecViewAngles.y - m_flLastAngle) < 0.1f) {
			m_vecViewAngles.y = m_flLastAngle;
			m_flDelta = m_flLastDelta;
		}

		bHasTarget = true;

		if (g_Vars.rage.override_reoslver.enabled) {
			if (m_flDelta > 1.2f)
				record->m_angEyeAngles.y = angAway + 90.f;
			else if (m_flDelta < -1.2f)
				record->m_angEyeAngles.y = angAway - 90.f;
			else
				record->m_angEyeAngles.y = angAway;
		}

		m_flLastAngle = m_vecViewAngles.y;
		m_flLastDelta = m_flDelta;
	}

	void CResolver::PredictBodyUpdates(C_CSPlayer* player, C_AnimationRecord* record, C_AnimationRecord* prev) {
		auto local = C_CSPlayer::GetLocalPlayer();
		if (!local)
			return;

		if (!(local->m_fFlags() & FL_ONGROUND))
			return;

		// nah
		if (local->IsDead()) {
			Engine::g_ResolverData[player->EntIndex()].m_bPredictingUpdates = false;
			g_ResolverData[player->EntIndex()].m_bCollectedValidMoveData = false;
			return;
		}

		// we have no reliable move data, we can't predict
		if (!Engine::g_ResolverData[player->EntIndex()].m_bCollectedValidMoveData) {
			Engine::g_ResolverData[player->EntIndex()].m_bPredictingUpdates = false;
			return;
		}

		// fake flick shit.
		if (!record->m_bUnsafeVelocityTransition) {
			Engine::g_ResolverData[player->EntIndex()].m_bPredictingUpdates = false;
			return;
		}

		// get lag data about this player
		Encrypted_t<Engine::C_EntityLagData> pLagData = Engine::LagCompensation::Get()->GetLagData(player->m_entIndex);
		if (!pLagData.IsValid()) {
			Engine::g_ResolverData[player->EntIndex()].m_bPredictingUpdates = false;
			return;
		}

		if (pLagData->m_iMissedShotsLBY >= 2) {
			Engine::g_ResolverData[player->EntIndex()].m_bPredictingUpdates = false;
			return;
		}

		// inform esp that we're about to be the prediction process
		Engine::g_ResolverData[player->EntIndex()].m_bPredictingUpdates = true;

		//check if the player is walking
		// no need for the extra fakewalk check since we null velocity when they're fakewalking anyway
		if ( record->m_vecAnimationVelocity.Length( ) > 0.1f && !record->m_bFakeWalking) { // switched this to AnimationVelocity as i can tell that it was one of their antipastes due to the comment above.
			g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("FLICK");

			// predict the first flick they have to do after they stop moving
			Engine::g_ResolverData[player->EntIndex()].m_flNextBodyUpdate = player->m_flAnimationTime() + 0.22f;

			// since we are still not in the prediction process, inform the cheat that we arent predicting yet
			// this is only really used to determine if we should draw the lby timer bar on esp, no other real purpose
			Engine::g_ResolverData[player->EntIndex()].m_bPredictingUpdates = false;
		}

		// lby updated on this tick
		else if (player->m_flAnimationTime() >= Engine::g_ResolverData[player->EntIndex()].m_flNextBodyUpdate) {
			g_ResolverData[player->EntIndex()].m_sResolverMode = XorStr("FLICK");

			// inform the cheat of the resolver method
			record->m_iResolverMode = EResolverModes::RESOLVE_PRED;

			// predict the next body update
			Engine::g_ResolverData[player->EntIndex()].m_flNextBodyUpdate = player->m_flAnimationTime() + 1.1f;

			// set eyeangles to lby
			record->m_angEyeAngles.y = player->m_angEyeAngles().y = record->m_flLowerBodyYawTarget;

			// this is also only really used for esp flag
			record->m_bResolved = true;

			// we're now in the prediction stage.
			Engine::g_ResolverData[player->EntIndex()].m_bPredictingUpdates = true;
		}
	}
} */