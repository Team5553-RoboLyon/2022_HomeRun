#pragma once
#include "lib/N/NType.h"
#include "lib/N/Maths/NMatrix3x3.h"

#include "NLRobotPose.h"
#include "lib/NL/MotionControl/Trajectory/NLTrajectoryState.h"

typedef struct NLRAMSETEOUTPUT NLRAMSETEOUTPUT;
struct NLRAMSETEOUTPUT
{
	void null()
	{
		m_leftVelocity = 0.0f;
		m_leftAcceleration = 0.0f;
		m_rightVelocity = 0.0f;
		m_rightAcceleration = 0.0f;
	}
	Nf32 m_leftVelocity;	  // Vitesse � appliquer � gauche
	Nf32 m_leftAcceleration;  // Acceleration � appliquer � gauche
	Nf32 m_rightVelocity;	  // Vitesse � appliquer � droite
	Nf32 m_rightAcceleration; // Acceleration � appliquer � droite
};

#define DEFAULT_NLRAMSETEPARAMS_B 2.0f
#define DEFAULT_NLRAMSETEPARAMS_ZETA 0.7f

#ifdef _NEDITOR
// forward declaration of NLPathWorkbench ( NLRAMSETEFOLLOWER is also included into NLPathWorkbench )
class NLPATH_WORKBENCH;
#endif

class NLRAMSETEFOLLOWER
{
public:
	NLRAMSETEFOLLOWER() : m_b(DEFAULT_NLRAMSETEPARAMS_B), m_zeta(DEFAULT_NLRAMSETEPARAMS_ZETA) {}
	NLRAMSETEFOLLOWER(const Nf32 b, const Nf32 zeta) : m_b(b), m_zeta(zeta) {}
	NLRAMSETEOUTPUT *update(NLRAMSETEOUTPUT *pout, const NLDRIVETRAINSPECS *pspecs, const NLTRAJECTORY_STATE *ptargetstate, const NLROBOTPOSE *pcurrentposture);

#ifdef _NEDITOR
	Nu32 read(NLPATH_WORKBENCH *pwb); // fonction read "sp�ciale" qui copie les donn�es du path workbench pass� en param�tre plutot
#endif								  // _NEDITOR
									  // ... tout en permettant de recup�rer directement les donn�es du path workbench.
	Nu32 read(FILE *pfile);
	Nu32 write(FILE *pfile);
	/*
	#ifdef _NEDITOR
		void draw();
	#endif
	*/
	// A propos de m_b et m_zeta:
	//
	// Controls Engineering in the FIRST Robotics Competition
	//	 Graduate - level control theory for high schoolers
	//					Tyler Veness
	// page 90:
	//		b and zeta are tuning parameters where b > 0 and zeta element of (0, 1).Larger values of b make convergence
	//		more aggressive(like a proportional term), and larger values of zeta provide more damping "
	//
	Nf32 m_b;	 // m_b > 0
	Nf32 m_zeta; // 0 <= m_zeta <= 1

	// DBG
	NMATRIX3x3 dbg_mx;
	NVEC2f32 dbg_errp;
	NVEC2f32 dbg_currentposture;
};
