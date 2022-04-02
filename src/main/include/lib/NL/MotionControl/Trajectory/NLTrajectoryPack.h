#pragma once
#include "lib/N/NType.h"
#include "lib/N/NMatrix.h"
#include "lib/N/File/NFile.h"
#include "lib/N/Containers/NArray.h"
#include "lib/NL/MotionControl/Path/Geometry/NLPathGeometry.h"
#include "NLTrajectoryState.h"
#include "lib/NL/MotionControl/Trajectory/NLTrajectoryKeyState.h"

#ifdef _NEDITOR
#include "../../NL2DOrthogonalCoordinateSystem.h"
// forward declaration of NLPathWorkbench ( to include it into SPACK, which is also included into NLPathWorkbench )
class NLPATH_WORKBENCH;
#endif
class NLTRAJECTORY_PACK
{
public:
	NLTRAJECTORY_PACK();
	~NLTRAJECTORY_PACK();

	Nu32 read(FILE *pfile);
#ifdef _NEDITOR
	Nu32 read(NLPATH_WORKBENCH *pwb); // fonction read "sp�ciale" qui copie les donn�es du path workbench pass� en param�tre plutot
#endif								  // _NEDITOR
									  // ... tout en permettant de recup�rer directement les donn�es du path workbench.
	Nu32 write(FILE *pfile);

	NLTRAJECTORY_STATE *getState(NLTRAJECTORY_STATE *pstate, const Nf32 t);

#ifdef _NEDITOR
	void drawTrajectoryKeyStateArray(NL2DOCS *p2docs);
#endif

	NARRAY m_keyStatesArray;
	//	NARRAY					m_triggersArray;
	//	NARRAY					m_messagesArray;
	NLPATH_GEOMETRY m_pathGeometry;
	NMATRIX m_matrix;
	Nf32 m_dt; // Dur�e totale n�c�ssaire pour parcourir la trajectoire

	// persistent Data:
	// NLTRAJECTORY_STATE	m_previousReturnedState;
	// Nf32					m_tPrev;
	// Nf32					m_sPrev;
};

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + FILE
// +
#define VERSION_NLTRAJECTORY_STATE_PACK_HEADER NMAKEVERSION(0, 0, 0) // >>> 2021/04/05
typedef struct
{
	Nf32 m_dt;
	NMATRIX m_matrix;
	NARRAYBOUNDS m_keyStatesArrayBounds;
} NLTRAJECTORY_STATE_PACK_HEADER;
