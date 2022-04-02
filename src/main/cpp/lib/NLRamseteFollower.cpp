
#include <float.h>
#include "lib/N/NMemory.h"
#include "lib/N/NMath.h"
#include "lib/N/NErrorHandling.h"

#include "lib/NL/MotionControl/NLOdometry.h"
#include "lib/NL/MotionControl/NLRamseteFollower.h"

// Si a E [-2PI,2PI] alors _pipi(a) E [-PI,PI]
static Nf32 _pipi(Nf32 a)
{
	NErrorIf(a > NF32_2PI, NERROR_VALUE_OUTOFRANGE);
	NErrorIf(a < -NF32_2PI, NERROR_VALUE_OUTOFRANGE);

	if (a > NF32_PI)
		return a - NF32_2PI;
	else if (a < -NF32_PI)
		return a + NF32_2PI;
	else
		return a;
}

static Nf32 _angleDiffa_b(const Nf32 a, const Nf32 b)
{
	Nf32 r = a - b;
	if (r > NF32_PI)
		return r - NF32_2PI;
	else if (r < -NF32_PI)
		return r + NF32_2PI;
	else
		return r;
}
NLRAMSETEOUTPUT *NLRAMSETEFOLLOWER::update(NLRAMSETEOUTPUT *pout, const NLDRIVETRAINSPECS *pspecs, const NLTRAJECTORY_STATE *ptargetstate, const NLROBOTPOSE *pcurrentposture)
{
	// ------------------------------------------------------------------------------------------------------------------------------
	// RAMSETE
	// On calcule la position ref par rapport � cette matrice, c'est � dire la position du robot de ref par rapport � la position du robot ...
	// ...estim�e par odom�trie + gyro
	NVEC2 p, errp, ntgt, ortho_ntgt;

	// Calcul de la matrice de transformation � la mano:
	Nf32 co, si;
	NCosSin(pcurrentposture->m_angle, &co, &si);
	NVEC2f32 i, j;

	i.x = co;
	j.x = -si; // k.x = 0
	i.y = si;
	j.y = co; // k.y = 0
	//	i.z = 0			j.z =  0	// k.z = 1

	p.x = ptargetstate->m_position.x - pcurrentposture->m_position.x;
	p.y = ptargetstate->m_position.y - pcurrentposture->m_position.y;

	errp.x = p.x * i.x + p.y * i.y; // = NVec2DotProduct(&p, &i);
	errp.y = p.x * j.x + p.y * j.y; // = NVec2DotProduct(&p, &j);

	ntgt = ptargetstate->m_tangent;
	NVec2Normalize(&ntgt);

	Nf32 cos_erra = NVec2DotProduct(&ntgt, &i);
	cos_erra = NCLAMP(-1.0f, cos_erra, 1.0f);
	Nf32 erra = acosf(cos_erra);
	Nf32 d2 = NVec2DotProduct(&ntgt, &j);
	if (d2 < 0.0f)
		erra = -erra;

	// V�rification de "l'erreur"( errp.x, errp.y, erra ) par rapport � la "tol�rance"( tol.x, tol.y, tola ) fix�e.

	Nf32 vref = ptargetstate->m_kin.m_v;
	Nf32 wref = ptargetstate->m_kin.m_v * ptargetstate->m_localCurvature;

	// Et c'est pa'ti pou' la fo'mu'e incomp'�hensib' mais que tou' l' monde dit quelle est supey'
	Nf32 _k = 2.0f * m_zeta * sqrt(NPOW2(wref) + m_b * NPOW2(vref));

	Nf32 _v = vref * cos_erra + _k * (errp.x);
	Nf32 _omega = wref + _k * erra + m_b * vref * NSinc(erra) * (errp.y);

	pout->m_leftVelocity = NLODOMETRY_L_WHEEL_FROM_DRIVETRAIN(_omega, _v, pspecs->m_axleTrack);
	pout->m_rightVelocity = NLODOMETRY_R_WHEEL_FROM_DRIVETRAIN(_omega, _v, pspecs->m_axleTrack);

	// ramsete
	// ------------------------------------------------------------------------------------------------------------------------------

	// 2) avec k on a R = 1/k et avec R on a la distribution gauche droite
	if (ptargetstate->m_localCurvature == 0.0f)
	{
		pout->m_leftAcceleration = ptargetstate->m_kin.m_a;
		pout->m_rightAcceleration = ptargetstate->m_kin.m_a;
	}
	else
	{
		Nf32 r = 1.0f / ptargetstate->m_localCurvature;
		pout->m_leftAcceleration = (r - pspecs->m_axleTrack * 0.5f) * ptargetstate->m_localCurvature * ptargetstate->m_kin.m_a;
		pout->m_rightAcceleration = (r + pspecs->m_axleTrack * 0.5f) * ptargetstate->m_localCurvature * ptargetstate->m_kin.m_a;
	}

	return pout;
}
#ifdef _NEDITOR
Nu32 NLRAMSETEFOLLOWER::read(NLPATH_WORKBENCH *pwb)
{
	if (pwb)
	{
		if (ISFLAG_ON(pwb->m_flags, FLAG_NLPATH_WORKBENCH_USE_SPECIFIC_RAMSETEPARAMS))
		{
			m_b = pwb->m_specificRamseteParams.m_b;
			m_zeta = pwb->m_specificRamseteParams.m_zeta;
		}
		else
		{
			m_b = Project.m_ramseteParams.m_b;		 // |_A�e, acc�s � une globale direct,..., sale mais bon...
			m_zeta = Project.m_ramseteParams.m_zeta; // |
		}
		return 1;
	}
	else
		return 0;
}
#endif
Nu32 NLRAMSETEFOLLOWER::read(FILE *pfile)
{
	if (fread(&m_b, sizeof(Nf32), 1, pfile) != 1)
		return 0;
	if (fread(&m_zeta, sizeof(Nf32), 1, pfile) != 1)
		return 0;
	return 1;
}
Nu32 NLRAMSETEFOLLOWER::write(FILE *pfile)
{
	if (fwrite(&m_b, sizeof(Nf32), 1, pfile) != 1)
		return 0;
	if (fwrite(&m_zeta, sizeof(Nf32), 1, pfile) != 1)
		return 0;
	return 1;
}
/*
version initiale avec decalage de +PI/2 de l'orientation du robot

void NLRAMSETEFOLLOWER::update(const NLDRIVETRAINSPECS* pspecs, const NLTRAJECTORY_STATE* ptargetstate, const NLROBOTPOSE* pcurrentposture)
{
// ------------------------------------------------------------------------------------------------------------------------------
// ramsete
// D'abord on calcul l'erreur '� la First' mais en mieux quand m�me c'est � dire sans 17 appels de fonctions pour faire une addition.
// La matrice du robot ( orientation estim�e...) avec l'axe Y pointant vers l'avant du robot et l'axe x pointant vers la droite
	NMATRIX3x3	mx;

	Nf32 ramsete_ang = _pipi(pcurrentposture->m_angle);

	NRotationMatrix3x3_AxisZ(&mx, ramsete_ang - NF32_PI_2);
	//NRotationMatrix3x3_AxisZ(&mx, pcurrentposture->m_angle + NF32_PI_2);

	// on calcule la position ref par rapport � cette matrice, c'est � dire la position du robot de ref par rapport au robot
	NVEC2	p,errp,ntgt;
	p.x			= ptargetstate->m_position.x - pcurrentposture->m_position.x;
	p.y			= ptargetstate->m_position.y - pcurrentposture->m_position.y;

	errp.x		= p.x * mx.XAxis.x + p.y * mx.XAxis.y; // = NVec2DotProduct(&p, (NVEC2*)&mx.XAxis);
	errp.y		= p.x * mx.YAxis.x + p.y * mx.YAxis.y; // = NVec2DotProduct(&p, (NVEC2*)&mx.YAxis);

	ntgt		= ptargetstate->m_tangent;
	NVec2Normalize(&ntgt);
	Nf32 at		= atan2f(ntgt.y, ntgt.x);
	Nf32 erra	= _angleDiffa_b(at, ramsete_ang );

	Nf32 vref	= ptargetstate->m_kin.m_v;
	Nf32 wref	= ptargetstate->m_kin.m_v * ptargetstate->m_localCurvature;

	// Et c'est pa'ti pou' la fo'mu'e incomp'�hensib' mais que tou' l' monde dit quelle est supey'
	Nf32 _k		= 2.0f * m_zeta * sqrt(NPOW2(vref) + m_b * NPOW2(wref));
	Nf32 _v		= vref * cos(erra) + _k * errp.y;
	Nf32 _omega = wref + _k * erra + m_b * vref * NSinc(erra) * (-errp.x);

	m_leftV = NLODOMETRY_L_WHEEL_FROM_DRIVETRAIN(_omega, _v,  pspecs->m_axleTrack);
	m_rightV = NLODOMETRY_R_WHEEL_FROM_DRIVETRAIN(_omega, _v, pspecs->m_axleTrack);

	// ramsete
	// ------------------------------------------------------------------------------------------------------------------------------

	// 2) avec k on a R = 1/k et avec R on a la distribution gauche droite
	if (ptargetstate->m_localCurvature == 0.0f)
	{
		m_leftA		= ptargetstate->m_kin.m_a;
		m_rightA	= ptargetstate->m_kin.m_a;
	}
	else
	{
		Nf32 r		= 1.0f / ptargetstate->m_localCurvature;
		m_leftA		= (r - pspecs->m_axleTrack * 0.5f) * ptargetstate->m_localCurvature * ptargetstate->m_kin.m_a;
		m_rightA	= (r + pspecs->m_axleTrack * 0.5f) * ptargetstate->m_localCurvature * ptargetstate->m_kin.m_a;
	}
}
*/