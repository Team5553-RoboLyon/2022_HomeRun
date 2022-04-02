#include "lib/N/File/NFile.h"
#include "lib/N/NString.h"
#include "lib/N/Core/NLimits.h"

#include "lib/NL/MotionControl/Characterization/NLCharacterizationTable.h"

NLCHARACTERIZATION_TABLE::NLCHARACTERIZATION_TABLE()
{
	NSetupArray(&m_table, 4, sizeof(NLCHARACTERIZATION_TABLE_ROW));
}

NLCHARACTERIZATION_TABLE::NLCHARACTERIZATION_TABLE(const Nu8 capacity)
{
	NSetupArray(&m_table, capacity, sizeof(NLCHARACTERIZATION_TABLE_ROW));
}

NLCHARACTERIZATION_TABLE::~NLCHARACTERIZATION_TABLE()
{
	NClearArray(&m_table, NULL);
}

void NLCHARACTERIZATION_TABLE::load(const Nchar *pfilename, const Nbool bclear_table_before_loading)
{
	NErrorIf(!NCheckFileType(pfilename, EXTENSION_NLCHARACTERIZATION_TABLE_TXT), NERROR_FILE_INVALID_EXTENSION);

	NFILE *pfile;
	Nchar tempstring[1024];
	Nchar name[32];
	Nchar *pstr;
	Ns32 gearbox_nb = 0;
	Ns32 motor_nb = 0;
	Ns32 inverted = 0;
	Nf32 gb_ratio = 1.0f;
	Nf32 wscale = 0.0f;
	Nu8 g, m;
	NLCHARACTERIZATION_TABLE_ROW row;

	// Reset de la table avant chargement ?
	if (bclear_table_before_loading)
		NEraseArray(&m_table, NULL);

	pfile = NFileOpen(pfilename, FLAG_NFILE_READ); // ouverture du fichier
	NFileSeek(pfile, 0, NFILE_SEEK_SET);		   // on se place au d�but du fichier

	// recup�rer le nombre de gearbox d�crites dans le fichier
	pstr = NFileGetString(tempstring, 1024, pfile);
	pstr = NStrGet_Ns32_AfterLabel(pstr, "gearbox = ", &gearbox_nb);
	// Si le nombre de gearbox d�crites dans le fichier est superieur au nombre MAX de gearbox  on g�n�re une erreur !
	// Si cela produit, il faut, augmenter la valeur static du nombre max de moteurs .. ou v�rifier qu'il n'y a pas une erreur dans le fichier entrant.
	NErrorIf((gearbox_nb <= 0) || (gearbox_nb > NU8_MAX), NERROR_INDEX_OUTOFRANGE);

	for (g = 0; g < gearbox_nb; g++)
	{
		pstr = NFileGetString(tempstring, 1024, pfile);
		pstr = NStrGet_Ns32_AfterLabel(pstr, "motors= ", &motor_nb);

		pstr = NStrGet_Nf32_AfterLabel(pstr, "ratio= ", &row.m_gearRatio);
		pstr = NStrGet_Nf32_AfterLabel(pstr, "wscale= ", &row.m_angularVelocityScaleFactor);
		pstr = NStrGet_Nf32_AfterLabel(pstr, "vmax+= ", &row.m_forwardVelocityMax);
		pstr = NStrGet_Nf32_AfterLabel(pstr, "amax+= ", &row.m_forwardAccelerationMax);
		pstr = NStrGet_Nf32_AfterLabel(pstr, "vmax-= ", &row.m_backwardVelocityMax);
		pstr = NStrGet_Nf32_AfterLabel(pstr, "amax-= ", &row.m_backwardAccelerationMax);

		// Si le nombre de moteurs d�crit dans le fichier est superieur au nombre MAX de moteurs  on g�n�re une erreur !
		// Si cela produit, il faut, augmenter la valeur static du nombre max de moteurs .. ou v�rifier qu'il n'y a pas une erreur dans le fichier entrant.
		NErrorIf((motor_nb <= 0) || (motor_nb > NU8_MAX), NERROR_INDEX_OUTOFRANGE);
		// On charge autant de lignes que de moteurs
		for (m = 0; m < motor_nb; m++)
		{
			pstr = NFileGetString(tempstring, 1024, pfile);

			row.m_flags = 0;
			pstr = NStrGet_Ns32_AfterLabel(pstr, "inv= ", &inverted);
			if (inverted)
				FLAG_ON(row.m_flags, FLAG_NLCHARACTERIZATION_TABLE_ROW_IS_INVERTED);

			row.m_gearboxId = g;
			row.m_motorId = m;

			pstr = NStrGet_String_BetweenLabels(pstr, "name= ", " ", name);
			NStrCopy(row.m_motorName, name, 8);

			// Forward Kv, Ka, et intercept
			pstr = NStrGet_Nf32_AfterLabel(pstr, "kv+= ", &row.m_characterization.m_forwardKv);
			pstr = NStrGet_Nf32_AfterLabel(pstr, "ka+= ", &row.m_characterization.m_forwardKa);
			pstr = NStrGet_Nf32_AfterLabel(pstr, "intercept+= ", &row.m_characterization.m_forwardIntercept);

			// Backward Kv, Ka, et intercept
			pstr = NStrGet_Nf32_AfterLabel(pstr, "kv-= ", &row.m_characterization.m_backwardKv);
			pstr = NStrGet_Nf32_AfterLabel(pstr, "ka-= ", &row.m_characterization.m_backwardKa);
			pstr = NStrGet_Nf32_AfterLabel(pstr, "intercept-= ", &row.m_characterization.m_backwardIntercept);

			NArrayPushBack(&m_table, (NBYTE *)&row);
		}
	}
	NFileClose(pfile);
}
// ------------------------------------------------------------------------------------------
/**
 *	@brief	Extrait une characterization specifique de la table des characterizations. La characterization extraite peut �tre modul�e
 *			pour travailler avec des m�tres/secondes en sortie de boite (apr�s r�duction), o� des rad/sec en entr�e de boite ( avant r�duction ).
 *			Le coefficient utilis� pour moduler d�pend directement du rayon des roues et de la r�duction des boites de vitesse lors des tests de
 *			characterization. ( coef = traction Wheel Radius / GearBox_fact)
 *	@param		pdst est un pointeur sur la structure charaterization � remplir avec les donn�es extraites de la table.
 *	@param		table_index est l'index de la characterization qu'on veut extraire de la table
 *	@param		angular_velocity_scaled_coef est un bool�en qui, si il est � TRUE indique que la characterization attendue est celle travaillant avec des rad/s ( entr�e de boite ) et si il est � FALSE des valeurs sortie de boite en m/s
 *	@return		Si table_index est valide alors la fonction rempli la structure point�e par pdst et retourne pdst en sortie.
 *				Sinon la fonction retourne le pointeur null et la structure point�e par pdst demeure inchang�e.
 */
// ------------------------------------------------------------------------------------------
NLMOTOR_CHARACTERIZATION *NLCHARACTERIZATION_TABLE::get(NLMOTOR_CHARACTERIZATION *pdst, const Nu8 table_index, const Nbool angular_velocity_scaled_coef)
{
	NLCHARACTERIZATION_TABLE_ROW *pcz;

	NErrorIf(table_index >= m_table.Size, NERROR_ARRAY_INDEX_BEYOND_LIMITS);
	if (table_index < m_table.Size)
	{
		if (angular_velocity_scaled_coef)
		{
			pcz = (NLCHARACTERIZATION_TABLE_ROW *)NGetArrayIndexPtr(&m_table, table_index);
			pdst->setFrom(&pcz->m_characterization, pcz->m_angularVelocityScaleFactor);
		}
		else
		{
			*pdst = ((NLCHARACTERIZATION_TABLE_ROW *)NGetArrayIndexPtr(&m_table, table_index))->m_characterization;
		}
		return pdst;
	}
	return NULL;
}

NLMOTOR_CHARACTERIZATION *NLCHARACTERIZATION_TABLE::get(NLMOTOR_CHARACTERIZATION *pdst, const Nu8 gearboxid, const Nu8 motorid, const Nbool angular_velocity_scaled_coef)
{
	Nu8 i;
	NLCHARACTERIZATION_TABLE_ROW *pcz = (NLCHARACTERIZATION_TABLE_ROW *)m_table.pFirst;
	for (i = 0; i < m_table.Size; i++, pcz++)
	{
		if ((pcz->m_gearboxId == gearboxid) && (pcz->m_motorId == motorid))
		{
			if (angular_velocity_scaled_coef)
			{
				pdst->setFrom(&pcz->m_characterization, pcz->m_angularVelocityScaleFactor);
			}
			else
			{
				*pdst = pcz->m_characterization;
			}
			return pdst;
		}
	}
	return NULL;
}

NLMOTOR_CHARACTERIZATION *NLCHARACTERIZATION_TABLE::get(NLMOTOR_CHARACTERIZATION *pdst, const Nchar *pmotorname, const Nbool angular_velocity_scaled_coef)
{
	Nu8 i;
	NLCHARACTERIZATION_TABLE_ROW *pcz = (NLCHARACTERIZATION_TABLE_ROW *)m_table.pFirst;
	for (i = 0; i < m_table.Size; i++, pcz++)
	{
		if (strcmp(pmotorname, pcz->m_motorName) == 0)
		{
			if (angular_velocity_scaled_coef)
			{
				pdst->setFrom(&pcz->m_characterization, pcz->m_angularVelocityScaleFactor);
			}
			else
			{
				*pdst = pcz->m_characterization;
			}
			return pdst;
		}
	}
	return NULL;
}
