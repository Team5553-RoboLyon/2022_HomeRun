
#include <float.h>
#include "lib/N/NMemory.h"
#include "lib/N/NMath.h"
#include "lib/N/NErrorHandling.h"

#include "lib/NL/MotionControl/NLOdometry.h"
#include "lib/NL/MotionControl/NLRobotPose.h"

/*
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
*/
/*
static Nf32 modulo2PI(Nf32 a)
{
	if (a > NF32_2PI)
		return a - NF32_2PI;
	else if (a < -NF32_2PI)
		return a + NF32_2PI;
	else
		return a;
}
*/
static Nf32 modulo2PI(Nf32 a)
{
	Nu32 _continue;
	do
	{
		_continue = 0;

		if (a > NF32_2PI)
		{
			a -= NF32_2PI;
			_continue = 1;
		}
		else if (a < 0.0f)
		{
			a += NF32_2PI;
			_continue = 1;
		}
	} while (_continue);

	NErrorIf(_isnan(a), NERROR_VALUE_OUTOFRANGE);
	NErrorIf(a > NF32_2PI, NERROR_VALUE_OUTOFRANGE);
	NErrorIf(a < 0.0f, NERROR_VALUE_OUTOFRANGE);

	return a;
}

void NLROBOTPOSE::odometryUpdate(const NLDRIVETRAINSPECS *pspecs, const Nf32 left_mov, const Nf32 right_mov)
{
	// mise � jour de la position et de l'angle "estim�s" du robot.
	Nf32 v = NLODOMETRY_DRIVETRAIN_V_FROM_WHEELS(left_mov, right_mov);
	Nf32 w = NLODOMETRY_DRIVETRAIN_W_FROM_WHEELS(left_mov, right_mov, pspecs->m_axleTrack);

	// m�thode simplifi�e pour de petites valeurs de w o� on consid�re que le d�placement du robot est un petit segment de droite
	m_angle = modulo2PI(m_angle + w);

	// m_angle = _pipi(m_angle); //modulo2PI(m_estimatedAngle);
	m_position.x += cos(m_angle) * v;
	m_position.y += sin(m_angle) * v;
}

void NLROBOTPOSE::odometryUpdate(const NLDRIVETRAINSPECS *pspecs, const Nf32 left_mov, const Nf32 right_mov, const Nf32 external_angle)
{
	// mise � jour de la position et de l'angle "estim�s" du robot.
	Nf32 v = NLODOMETRY_DRIVETRAIN_V_FROM_WHEELS(left_mov, right_mov);
	// Nf32 w = NLODOMETRY_DRIVETRAIN_W_FROM_WHEELS(left_mov, right_mov, pspecs->m_axleTrack);

	// m�thode simplifi�e pour de petites valeurs de w o� on consid�re que le d�placement du robot est un petit segment de droite
	// m_angle = _pipi(external_angle); //modulo2PI(m_estimatedAngle);
	m_angle = modulo2PI(external_angle);

	m_position.x += cos(m_angle) * v;
	m_position.y += sin(m_angle) * v;
}
