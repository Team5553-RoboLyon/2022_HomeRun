#pragma once
#include "lib/N/NType.h"
#include "lib/N/NMemory.h"

#include "lib/NL/MotionControl/NLKin.h"
#include "lib/NL/MotionControl/Path/Geometry/NLPathGeometry.h"

typedef struct NLTRAJECTORY_KEY_STATE NLTRAJECTORY_KEY_STATE;
struct NLTRAJECTORY_KEY_STATE
{
	void set(NLKIN *pkin, NLPATH_POINT *pkp1, NLPATH_PRIMITIVE *ppr)
	{
		m_kin = *pkin;
		m_pKeyPoint1 = pkp1;
		m_pPrimitive = ppr;
	}
	inline void null() { Nmem0(this, NLTRAJECTORY_KEY_STATE); }

	NLKIN m_kin; // kin repr�sentant le robot ( son centre d'inertie )
	// Primitive ou se situe ce kin
	NLPATH_POINT *m_pKeyPoint1;		// |_ portion du path o� se trouve le key state
	NLPATH_PRIMITIVE *m_pPrimitive; // |
};