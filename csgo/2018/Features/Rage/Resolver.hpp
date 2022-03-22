#pragma once
#include "LagCompensation.hpp"
#include <vector>
#include <deque>

namespace Engine {
	// taken from supremacy
	enum EResolverModes : size_t {
		RESOLVE_NONE = 0,
		RESOLVE_WALK,
		RESOLVE_STAND,
		RESOLVE_STAND1,
		RESOLVE_STAND2,
		RESOLVE_AIR,
		RESOLVE_PRED,
		RESOLVE_EDGE,
	};

	struct CResolverData {
		struct LastMoveData_t {
			float m_flLowerBodyYawTarget;
			float m_flSimulationTime;
			float m_flAnimTime;
			Vector m_vecOrigin;
		};

		bool m_bCollectedValidMoveData;
		bool m_bWentDormant;
		bool m_bPredictingUpdates;

		Vector m_vecSavedOrigin;
		LastMoveData_t m_sMoveData;
		int m_StandIndex;
		int m_unknown_move;
		float m_flBestYaw;
		float m_flBestDistance;
		bool  m_bCollectedFreestandData;
		int m_air_index;
		float m_flNextBodyUpdate;
		bool gotserverside = false;
		float serversideangle;
		float m_flFinalResolverYaw;
		float m_flOldLowerBodyYawTarget;
		std::string m_sResolverMode;

		float m_body, m_old_body;

		float flNextBodyUpdate = 9999999999;
		// this being like that will prevent it from trying to predict people we dont have the timing of
	};

	class CResolver {
	private:
		void IsFreestanding(C_AnimationRecord* record);

		void ResolveAngles(C_CSPlayer* player, C_AnimationRecord* record);
		Engine::C_LagRecord* FindIdealRecord(C_CSPlayer* data);
		void ResolveWalk(C_CSPlayer* player, C_AnimationRecord* record);
		void ResolveStand(C_CSPlayer* player, C_AnimationRecord* record);
		void yaw_bruteforce(C_AnimationRecord* record, C_CSPlayer* player);
		void ResolveAir(C_CSPlayer* player, C_AnimationRecord* record);
	public:
		void OnBodyUpdate(C_CSPlayer* player, float value);

		void ResolveManual(C_CSPlayer* player, C_AnimationRecord* record, bool bDisallow = false);
		void ResolveYaw(C_CSPlayer* player, C_AnimationRecord* record);
		void ResetBruteforce(C_CSPlayer* player);
		void PredictBodyUpdates(C_CSPlayer* player, C_AnimationRecord* record, C_AnimationRecord* prev);

	public:

		// check if the players yaw is sideways.
		bool IsLastMoveValid(C_AnimationRecord* record, float m_yaw) {
			auto local = C_CSPlayer::GetLocalPlayer();
			if (!local)
				return false;
			Vector angAway;
			Math::VectorAngles(local->m_vecOrigin() - record->m_vecOrigin, angAway);
			const float delta = fabs(Math::AngleNormalize(angAway.y - m_yaw));
			return delta > 20.f && delta < 160.f;
		}

		// freestanding.
		class AdaptiveAngle {
		public:
			float m_yaw;
			float m_dist;

		public:
			// ctor.
			__forceinline AdaptiveAngle() :
				m_yaw{ },
				m_dist{ }
			{ };

			__forceinline AdaptiveAngle(float yaw, float penalty = 0.f) {
				// set yaw.
				m_yaw = Math::AngleNormalize(yaw);

				// init distance.
				m_dist = 0.f;

				// remove penalty.
				m_dist -= penalty;
			}
		};
		void FindBestAngle(C_CSPlayer* player);
	};

	extern CResolver g_Resolver;
	extern CResolverData g_ResolverData[65];
}

/*#pragma once
#include "LagCompensation.hpp"
#include <vector>
#include <deque>

namespace Engine {
	// taken from supremacy
	enum EResolverModes : size_t {
		RESOLVE_NONE = 0,
		RESOLVE_WALK,
		RESOLVE_STAND,
		RESOLVE_STAND1,
		RESOLVE_STAND2,
		RESOLVE_AIR,
		RESOLVE_PRED,
		RESOLVE_EDGE,
		RESOLVE_MANUAL
	};

	enum EFreestandingSides : size_t {
		NO_SIDE = 0,
		RIGHT_SIDE,
		LEFT_SIDE
	};

	struct CResolverData {
		struct LastMoveData_t {
			float m_flLowerBodyYawTarget;
			float m_flSimulationTime;
			float m_flAnimTime;
			Vector m_vecOrigin;
		};

		bool m_bCollectedValidMoveData;
		bool m_bWentDormant;
		bool m_bPredictingUpdates;

		Vector m_vecSavedOrigin;
		LastMoveData_t m_sMoveData;

		float m_flBestYaw;
		float m_flBestDistance;
		bool  m_bCollectedFreestandData;

		float m_flNextBodyUpdate;
		float m_flFinalResolverYaw;
		float m_flOldLowerBodyYawTarget;

		// initialize this at 0 so we don't have any problems
		int m_iFreestandingSide = 0;

		std::string m_sResolverMode;
	};

	class CResolver {
	private:
		void ResolveAngles(C_CSPlayer* player, C_AnimationRecord* record, C_AnimationRecord* prev);
		Engine::C_LagRecord* FindIdealRecord(C_CSPlayer* data);
		void ResolveWalk(C_CSPlayer* player, C_AnimationRecord* record);
		void ResolveStand(C_CSPlayer* player, C_AnimationRecord* record, C_AnimationRecord* prev);
		void ResolveAir(C_CSPlayer* player, C_AnimationRecord* record, C_AnimationRecord* prev);
	public:
		void ResolveManual(C_CSPlayer* player, C_AnimationRecord* record, bool bDisallow = false);
		void ResolveYaw(C_CSPlayer* player, C_AnimationRecord* record, C_AnimationRecord* prev);
		void PredictBodyUpdates(C_CSPlayer* player, C_AnimationRecord* record, C_AnimationRecord* prev);

	public:
		// check if the players yaw is sideways.
		bool IsLastMoveValid(C_AnimationRecord* record, float m_yaw) {
			auto local = C_CSPlayer::GetLocalPlayer();
			if (!local)
				return false;
			Vector angAway;
			Math::VectorAngles(local->m_vecOrigin() - record->m_vecOrigin, angAway);
			const float delta = fabs(Math::AngleNormalize(angAway.y - m_yaw));
			return delta > 20.f && delta < 160.f;
		}

		// freestanding.
		class AdaptiveAngle {
		public:
			float m_yaw;
			float m_dist;

		public:
			// ctor.
			__forceinline AdaptiveAngle() :
				m_yaw{ },
				m_dist{ }
			{ };

			__forceinline AdaptiveAngle(float yaw, float penalty = 0.f) {
				// set yaw.
				m_yaw = Math::AngleNormalize(yaw);

				// init distance.
				m_dist = 0.f;

				// remove penalty.
				m_dist -= penalty;
			}
		};
		void FindBestAngle(C_CSPlayer* player);
	};

	extern CResolver g_Resolver;
	extern CResolverData g_ResolverData[65];
} */