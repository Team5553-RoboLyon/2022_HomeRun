#pragma once
#include "lib/N/NType.h"
#include "lib/N/Maths/NVec2f32.h"
#include "lib/NL/MotionControl/NLKin.h"

// FULL STATE :

typedef struct NLTRAJECTORY_STATE NLTRAJECTORY_STATE;
struct NLTRAJECTORY_STATE
{
	void set(NLKIN *pkin, const Nf32 curvature, NVEC2f32 *ppos, NVEC2f32 *ptgt)
	{
		m_localCurvature = curvature;
		m_kin = *pkin;
		m_position = *ppos;
		m_tangent = *ptgt;
	}
	inline void null() { Nmem0(this, NLTRAJECTORY_STATE); }

	NLKIN m_kin;		   // kin repr�sentant le robot ( son centre d'inertie )
	Nf32 m_localCurvature; // courbure � l'abscisse curviligne m_kin.m_s

	NVEC2f32 m_position; // position (x,y) sur la trajectoire.
	NVEC2f32 m_tangent;	 // tangente � la trajectoire en cette position ( pour l'instant n'est pas garanti unitaire � cause de l'appel � la fonction NLTRAJECTORY_PACK::getState )
};
