#include "lib/NL/MotionControl/NLKin.h"
#include "lib/NL/MotionControl/Trajectory/NLTrajectoryPack.h"

NLTRAJECTORY_PACK::NLTRAJECTORY_PACK()
{
	NSetupArray(&m_keyStatesArray, 0, sizeof(NLTRAJECTORY_KEY_STATE));
}

NLTRAJECTORY_PACK::~NLTRAJECTORY_PACK()
{
	NClearArray(&m_keyStatesArray, NULL);
}

Nu32 NLTRAJECTORY_PACK::read(FILE *pfile)
{
	// 1) lecture Version
	Nu32 version_u32;
	if (fread(&version_u32, sizeof(Nu32), 1, pfile) != 1)
		return 0;
	// 2) lecture Header
	NLTRAJECTORY_STATE_PACK_HEADER header;

	switch (NGETVERSION_MAIN(version_u32))
	{
		// all versions 0.0.x
	case NGETVERSION_MAIN(VERSION_NLTRAJECTORY_STATE_PACK_HEADER):
		if (fread(&header, sizeof(NLTRAJECTORY_STATE_PACK_HEADER), 1, pfile) != 1)
			return 0;
		m_dt = header.m_dt;
		m_matrix = header.m_matrix;
		// Recherche de potentiels pbs sur les arrays.
		// ('NIsArrayCorruptedOrInconsistent' se charge de faire un setup auto en cas de array full of ZEROS)
		if (NIsArrayCorruptedOrInconsistent(&m_keyStatesArray, &header.m_keyStatesArrayBounds, NTRUE)) // signifie qu'il y a un pb ( NARRAYCHK_INCONSISTENCY ou NARRAYCHK_CORRUPTED )
			return 0;

		NResizeArray(&m_keyStatesArray, header.m_keyStatesArrayBounds.Size, NULL, NULL);

		if (m_keyStatesArray.Size)
		{
			if (fread(m_keyStatesArray.pFirst, m_keyStatesArray.ElementSize, m_keyStatesArray.Size, pfile) != m_keyStatesArray.Size)
				return 0;
		}
		if (!m_pathGeometry.read(pfile))
			return 0;

		return 1;

	default:
		break;
	}
	return 0;
}
#ifdef _NEDITOR
Nu32 NLTRAJECTORY_PACK::read(NLPATH_WORKBENCH *pwb)
{
	// 'operator =' n'est pas d�fini pour NLTRAJECTORY_PACK donc on doit faire une partie du JOB � la main
	if (pwb)
	{
		NARRAYBOUNDS bounds;
		NGetArrayBounds(&bounds, &pwb->m_pTrajectoryStatePack->m_keyStatesArray);
		// Recherche de potentiels pbs sur les arrays.
		// ('NIsArrayCorruptedOrInconsistent' se charge de faire un setup auto en cas de array full of ZEROS)
		if (NIsArrayCorruptedOrInconsistent(&m_keyStatesArray, &bounds, NTRUE))
		{
			NErrorIf(1, NERROR_ARRAY_CORRUPTED);
			return 0;
		}
		else
		{
			NCopyArray(&m_keyStatesArray, &pwb->m_pTrajectoryStatePack->m_keyStatesArray);
		}

		// 'operator =' est d�fini pour NLPATHGEOMETRY
		m_pathGeometry = pwb->m_pTrajectoryStatePack->m_pathGeometry;
		m_matrix = pwb->m_pTrajectoryStatePack->m_matrix;
		m_dt = pwb->m_pTrajectoryStatePack->m_dt;

		return 1;
	}
	return 0;
}
#endif
Nu32 NLTRAJECTORY_PACK::write(FILE *pfile)
{
	// 1) �criture Version
	Nu32 version_u32 = VERSION_NLTRAJECTORY_STATE_PACK_HEADER;
	if (fwrite(&version_u32, sizeof(Nu32), 1, pfile) != 1)
		return 0;

	// 2) �criture Header
	NLTRAJECTORY_STATE_PACK_HEADER header;
	header.m_dt = m_dt;
	header.m_matrix = m_matrix;
	// header.m_keyStatesArraySize = m_keyStatesArray.Size;
	NGetArrayBounds(&header.m_keyStatesArrayBounds, &m_keyStatesArray);
	if (fwrite(&header, sizeof(NLTRAJECTORY_STATE_PACK_HEADER), 1, pfile) != 1)
		return 0;

	// 3) �criture m_keyStatesArray � la main et en une fois
	if (m_keyStatesArray.Size)
	{
		if (fwrite(m_keyStatesArray.pFirst, m_keyStatesArray.ElementSize, m_keyStatesArray.Size, pfile) != m_keyStatesArray.Size)
			return 0;
	}

	return m_pathGeometry.write(pfile);
}

NLTRAJECTORY_STATE *NLTRAJECTORY_PACK::getState(NLTRAJECTORY_STATE *pstate, const Nf32 t)
{
	NLTRAJECTORY_KEY_STATE *pks0, *pks1;

	if (t <= 0.0f)
	{
		pks0 = (NLTRAJECTORY_KEY_STATE *)m_keyStatesArray.pFirst;
		pstate->m_kin = pks0->m_kin;
		NLPATH_POINT *pkp0 = (pks0->m_pKeyPoint1 - 1);
		pstate->m_position = pkp0->p;
		pstate->m_tangent = pkp0->u;
		pstate->m_localCurvature = pkp0->k;
	}
	else if (t < m_dt)
	{
		pks1 = (NLTRAJECTORY_KEY_STATE *)m_keyStatesArray.pFirst;
		while (pks1->m_kin.m_t < t)
		{
			pks1++;
		}
		pks0 = pks1 - 1;
		pstate->m_kin.from(&pks0->m_kin, pks1->m_kin.m_j, t - pks0->m_kin.m_t);

		NLPATH_POINT p;
		m_pathGeometry.getPathPoint(&p, pks1->m_pKeyPoint1, pks1->m_pPrimitive, pstate->m_kin.m_s);
		pstate->m_position = p.p;
		pstate->m_tangent = p.u;
		pstate->m_localCurvature = p.k;
	}
	else // t >= m_dt
	{
		pks1 = (NLTRAJECTORY_KEY_STATE *)NGetLastArrayPtr(&m_keyStatesArray);
		pstate->m_kin = pks1->m_kin;
		NLPATH_POINT *pkp1 = pks1->m_pKeyPoint1;
		pstate->m_position = pkp1->p;
		pstate->m_tangent = pkp1->u;
		pstate->m_localCurvature = pkp1->k;
	}
	return pstate;
}

/*
#ifdef _NEDITOR
void NLTRAJECTORY_BASIC_PACK::drawTrajectoryStateSArray(NL2DOCS * p2docs)
{
	NLTRAJECTORY_BASIC_STATE	*pstate = (NLTRAJECTORY_BASIC_STATE*)m_basicKeyStatesArray.pFirst; pstate++;

	for (Nu32 i = 1; i < m_basicKeyStatesArray.Size; i++, pstate++)
	{
		pstate->m_kin.draw(p2docs, &(pstate - 1)->m_kin);
	}
}
#endif
*/

/*
void NLTRAJECTORY_TRACKER::build(NLPATH_GEOMETRY * ppath_geometry, const NLDRIVETRAINSPECS * pdtspecs)
{
	NLDIFFERENTIAL_DRIVETRAIN_POSE	d2tp;

	NLKIN	 kin;
	NLKIN	*pkin0 = (NLKIN*)m_kinsArray.pFirst;
	NLKIN	*pkin1 = pkin0;
	Nu32	 kin1_id = 0;

	NLPATH_POINT *pkp0 = (NLPATH_POINT*)ppath->m_geometry.m_keyPointsArray.pFirst;
	NLPATH_POINT *pkp1 = pkp0 + 1;
	NLPATH_PRIMITIVE *pprim = (NLPATH_PRIMITIVE*)ppath->m_geometry.m_primitivesArray.pFirst;

	Nf32	curvature;
	Nf32	slocal;

	NResizeArray(&m_differentialDriveTrainPosesArray, 0, NULL, NULL);

	for (Nu32 i = 0; i < ppath->m_geometry.m_primitivesArray.Size; i++, pkp0 = pkp1, pkp1++, pprim++)
	{
		while ((kin1_id < m_kinsArray.Size) && (pkin1->m_s < pkp1->s))
		{
			// on recup�re la courbure en pkin->m_s
					// ( on sait que pkin->m_s est situ� "entre" pkp0 et pkp1 sur la primitive pprim ...
			if (pprim->m_core.m_id == NLPATH_PRIMITIVE_ID_CLOTHOID)
			{
				slocal = pkin1->m_s - pkp0->s;
				curvature = ISFLAG_ON(pprim->m_core.m_flags, FLAG_NLPATH_CLOTHOID_SECOND) ? (pprim->m_core.m_l - slocal) * pkp0->k / pprim->m_core.m_l : slocal * pkp1->k / pprim->m_core.m_l;
			}
			else // pprim->m_core.m_id ==  NLPATH_PRIMITIVE_ID_SEGMENT ou pprim->m_core.m_id ==  NLPATH_PRIMITIVE_ID_ARC
			{
				curvature = pkp1->k;
			}
			d2tp.set(pkin1, curvature);
			NArrayPushBack(&m_differentialDriveTrainPosesArray, (NBYTE*)&d2tp);

			// Kin suivant
			// !!! ATTENTION !!! � la toute fin, "kin1_id = m_kinsArray.Size" et le pointeur pkin1 pointe en dehors de m_kinsArray !!!
			pkin0 = pkin1;
			pkin1++;
			kin1_id++;
		}

		// A partir d'ici nous savons:
		//  pkin1->m_s >= pkp1->s
		//		OU
		//  kin1_id == m_kinsArray.Size,
		//	ce qui signifie que l'abscisse curviligne du dernier Kin de m_kinsArray est inf�rieure � longueur totale du chemin...
		//	... et que le pointeur pkin1 courant est invalide ( hors array )
		if (kin1_id < m_kinsArray.Size)
		{
			// on calcule et on ins�re une pose issue de "pkp1"
			getKinAtS(&kin, pkin0, pkin1, pkp1->s);
			d2tp.set(&kin, pkp1->k);
			NArrayPushBack(&m_differentialDriveTrainPosesArray, (NBYTE*)&d2tp);
		}
		else
		{
			break;
		}
	}
	// Une derni�re chose,
	// il est possible que l'abscisse curviligne du dernier kin soit l�g�rement sup�rieure � la longueur totale du chemin.
	if (kin1_id < m_kinsArray.Size)
	{
		kin1_id++;
	}
}
*/