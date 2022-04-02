#pragma once

#include "lib/N/NType.h"
#include "lib/N/Containers/NArray.h"
#include "lib/N/Maths/NVec3f32.h"
#include "lib/NL/MotionControl/Characterization/NLMotorCharacterization.h"

#ifdef _NEDITOR
#endif

#define EXTENSION_NLCHARACTERIZATION_TABLE_TXT ".txt" // extention des noms de fichiers de characterization (format texte)
#define EXTENSION_NLCHARACTERIZATION_TABLE_BIN ".czt" // extention des noms de fichiers de characterization (format binaire)

#define FLAG_NLCHARACTERIZATION_TABLE_ROW_IS_INVERTED BIT_0
typedef struct NLCHARACTERIZATION_TABLE_ROW NLCHARACTERIZATION_TABLE_ROW;
struct NLCHARACTERIZATION_TABLE_ROW
{
	Nu16 m_flags;
	Nu8 m_gearboxId;							 // de 0 � n
	Nu8 m_motorId;								 // 'gearbox relative' c'est � dire que pour chaque Gearbox les moteurs sont num�rot�s de 0 � n
	Nchar m_motorName[8];						 // nom du moteur 7 lettres max (+ caractere null de fin ).
	NLMOTOR_CHARACTERIZATION m_characterization; // Kv, Ka, Intercept en forward et backward.
	Nf32 m_gearRatio;							 // Gearbox ratio = Driven / Drive
	Nf32 m_angularVelocityScaleFactor;			 // = traction wheel radius ! Kangv = kv*m_angularVelocityScaleFactor Kanga = ka*m_angularVelocityScaleFactor
	Nf32 m_forwardVelocityMax;					 // m/s
	Nf32 m_forwardAccelerationMax;				 // m/s�
	Nf32 m_backwardVelocityMax;					 // m/s
	Nf32 m_backwardAccelerationMax;				 // m/s�
};

typedef struct NLCHARACTERIZATION_TABLE NLCHARACTERIZATION_TABLE;
struct NLCHARACTERIZATION_TABLE
{
	NLCHARACTERIZATION_TABLE();
	NLCHARACTERIZATION_TABLE(const Nu8 capacity);

	~NLCHARACTERIZATION_TABLE();

	void load(const Nchar *pfilename, const Nbool bclear_table_before_loading = NFALSE);
	NLMOTOR_CHARACTERIZATION *get(NLMOTOR_CHARACTERIZATION *pdst, const Nu8 table_index, const Nbool angular_velocity_scaled_coef);
	NLMOTOR_CHARACTERIZATION *get(NLMOTOR_CHARACTERIZATION *pdst, const Nu8 gearboxid, const Nu8 motorid, const Nbool angular_velocity_scaled_coef);
	NLMOTOR_CHARACTERIZATION *get(NLMOTOR_CHARACTERIZATION *pdst, const Nchar *pmotorname, const Nbool angular_velocity_scaled_coef);

	NARRAY m_table;
};
