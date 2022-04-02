#include "lib/N/NMemory.h"
#include "lib/N/NMath.h"
#include "lib/N/NErrorHandling.h"
#include "lib/N/Core/NLimits.h"

#include "lib/NL/MotionControl/NLKinLimits.h"

// ------------------------------------------------------------------------------------------
/**
 *	@brief	Constructeur par defaut de la classe. Ne fait rien.
 */
// ------------------------------------------------------------------------------------------
NLKINLIMITS::NLKINLIMITS()
{
	Nmem0(this, NLKINLIMITS);
}

// ------------------------------------------------------------------------------------------
/**
 *	@brief	Utilise les valeurs 'par defaut' de vitesse max, acceleration max et jerk max pour
 *			calculer toutes les autres constantes de la classe.
 */
// ------------------------------------------------------------------------------------------
/*
void NLKINLIMITS::default()
{
	m_v = DEFAULT_NLKINLIMITS_VELOCITY_MAX;
	m_a = DEFAULT_NLKINLIMITS_ACCELERATION_MAX;
	m_j = DEFAULT_NLKINLIMITS_JERK_MAX;

	compute();
}
*/

// ------------------------------------------------------------------------------------------
/**
 *	@brief	Constructeur specifique de la classe.
 *
 *	A partir des valeurs de velocite, acceleration et jerk maximum, plusieurs constantes, utilisees regulierement, sont precalculees et stockees.
 *  Le nom de ces constantes se compose de la maniere suivante: \n
 *	D'abord le prefixe "m_" suivit d'un ensemble de lettres et de chiffres. \n
 *	@li "2v" se lit "2 * v"		( 2 fois la vitesse max )
 *  @li "v2" se lit "v^2 "		( la vitesse max au carre )
 *  @li "2v2" se lit "2*v^2 "	( 2 fois la vitesse max au carre )
 *  @li "aooj" se lit "a/j "	( l'acceleration max divise par  (out of) le jerk max )
 *  @li "vmvx" se lit "v-vx "	( la vitesse max moins la vitesse 'vx' ) \n
 *	\n
 *	Certaines de ces constantes sont accessibles par 2 noms differents. Le premier nom est le nom 'standard' qui d�crit le calcul dont la constante est le resultat.
 *	Le second nom est plus "explicite" quand � ce que represente la constante ( tx, vx ... ).\n
 *	\n
 *	@li \e a, \e v et \e j represente respectivement l'acceleration max, la vitesse max et le jerk max. \n
 *	@li \e tx est le temps necessaire pour passe d'une acceleration nulle a l'acceleration max, ( tx = a/j ). \n
 *	@li \e 2tx est simplement le double de tx, ( 2tx = 2a/j ). \n
 *  @li \e vx est la vitesse acquise au temps tx, depuis v0 = 0, a0 = 0, s=0 et t=0 ( vx = a^2/2j ). \n
 *  @li \e 2vx est simplement le double de vx. C'est la vitesse maximum depuis a=0,v=0 en passant par l'acceleration maximum (sans la maintenir!) et en revenant a une acceleration nulle.\n
 *  @li \e sx est la distance parcourue au temps \e tx, depuis v0 = 0, a0 = 0, s=0 et t=0 ( sx =  a^3/(6j^2) ). Dans ces conditions, la vitesse en \e sx vaut \e vx.\n
 *	@li \e sxx  est la portion de distance g�n�r�e par \e vx pendant une dur�e \e tx. \n
 *	@li \e sxxx  est la portion de distance generee par la variation d'acceleration quand elle evolue de l'acceleration max � une valeur nulle. \n
 *	@li \e ss est la distance parcourue depuis v0 = 0, a0 = 0, s0=0 et t0=0 et jusqu'� v = 2vx, a = 0, s=ss et t=2tx .( Avec a = acceleration max et v = vx au temps tx ). \n
 *	@li \e 2ss est le double de ss et represente la distance parcourue depuis v0 = 0, a0 = 0 et jusqu'� v = 0, a = 0  en passant par une vitesse max de 2vx au temps 2tx. \n
 *
 *	\n
 *  <img src="kinlimits_detail.png" align="left"/>
 *  <div style="clear: both"></div>
 *	@param	velocity_max	est la velocite ( vitesse ) maximum possible.
 *	@param	accel_max		est l'acceleration maximum possible.
 *	@param	jerk_max		est le jerk maximum appliquable.
 */
// ------------------------------------------------------------------------------------------
NLKINLIMITS::NLKINLIMITS(const Nf32 velocity_max, const Nf32 accel_max, const Nf32 jerk_max)
{
	m_v = velocity_max;
	m_a = accel_max;
	m_j = jerk_max;

	compute();
}

NLKINLIMITS::NLKINLIMITS(NLKINLIMITS const &tobecopied)
{
	*this = tobecopied;
}

NLKINLIMITS::NLKINLIMITS(const NLKINLIMITS *pklim)
{
	if (pklim)
		*this = *pklim;
	else
		Nmem0(this, NLKINLIMITS);
}

/*
NLKINLIMITS::~NLKINLIMITS()
{
}
*/

void NLKINLIMITS::compute()
{
	if (m_j)
	{
		// Pr�calcul constantes
		m_tx = m_a / m_j;								 // = a/j
		m_2tx = 2.0f * m_a / m_j;						 // = 2a/j
		m_vx = (m_a * m_a) / (2.0f * m_j);				 // = a�/2j
		m_2vx = (m_a * m_a) / m_j;						 // = a�/j
		m_sx = (m_a * m_a * m_a) / (6.0f * m_j * m_j);	 // = a^3/6j�
		m_sxx = (m_a * m_a * m_a) / (2.0f * m_j * m_j);	 // = a^3/2j�
		m_sxxx = (m_a * m_a * m_a) / (3.0f * m_j * m_j); // = a^3/3j�
		m_ss = (m_a * m_a * m_a) / (m_j * m_j);			 // = a^3/j�
		m_2ss = 2.0f * (m_a * m_a * m_a) / (m_j * m_j);	 // = 2a^3/j�

		m_2j = 2.0f * m_j;	 // = 2j
		m_vmvx = m_v - m_vx; // = v - a�/2j

		m_2a2ooj = (2.0f * m_a * m_a) / m_j;			  // = 2a�/j
		m_a4ooj2 = (m_a * m_a * m_a * m_a) / (m_j * m_j); // = a^4/j�
		m_4j2a = 4.0f * m_j * m_j * m_a;				  // = 4j�a

		// m_4a = 4.0f * m_a;								// = 4a
		// m_a2 = m_a * m_a;									// = a�
		// m_a4 = m_a * m_a * m_a * m_a;						// = a�
	}
	else
	{
		// setup constantes
		m_tx = NF32_MAX;   // = a/j		>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.
		m_2tx = NF32_MAX;  // = 2a/j		>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.
		m_vx = NF32_MAX;   // = a�/2j		>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.
		m_2vx = NF32_MAX;  // = a�/j		>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.
		m_sx = NF32_MAX;   // = a^3/6j�	>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.
		m_sxx = NF32_MAX;  // = a^3/2j�	>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.
		m_sxxx = NF32_MAX; // = a^3/3j�	>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.
		m_ss = NF32_MAX;   // = a^3/j�	>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.
		m_2ss = NF32_MAX;  // = 2a^3/j�	>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.

		m_2j = 0.0f;		// = 2j
		m_vmvx = -NF32_MAX; // = v - a�/2j	>>> = -NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.

		m_2a2ooj = NF32_MAX; // = 2a�/j		>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.
		m_a4ooj2 = NF32_MAX; // = a^4/j�		>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.
		m_4j2a = 0.0f;		 // = 4j�a

		// m_4a = 0.0f;				// = 4a
		// m_a2 = 0.0f;				// = a�
		// m_a4 = 0.0f;				// = a^4
	}

	m_a2 = m_a * m_a;			  // = a�
	m_4a = 4.0f * m_a;			  // = 4a
	m_a4 = m_a * m_a * m_a * m_a; // = a^4
}

void NLKINLIMITS::null()
{
	m_v = 0.0f;
	m_a = 0.0f;
	m_j = 0.0f;

	// setup constantes
	m_tx = NF32_MAX;   // = a/j		>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.
	m_2tx = NF32_MAX;  // = 2a/j		>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.
	m_vx = NF32_MAX;   // = a�/2j		>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.
	m_2vx = NF32_MAX;  // = a�/j		>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.
	m_sx = NF32_MAX;   // = a^3/6j�	>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.
	m_sxx = NF32_MAX;  // = a^3/2j�	>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.
	m_sxxx = NF32_MAX; // = a^3/3j�	>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.
	m_ss = NF32_MAX;   // = a^3/j�	>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.
	m_2ss = NF32_MAX;  // = 2a^3/j�	>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.

	m_2j = 0.0f;		// = 2j
	m_a2 = 0.0f;		// = a�
	m_vmvx = -NF32_MAX; // = v - a�/2j	>>> = -NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.

	m_2a2ooj = NF32_MAX; // = 2a�/j		>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.
	m_a4ooj2 = NF32_MAX; // = a^4/j�		>>> = NF32_MAX mais n'est pas d�fini car le r�sultat d'une division par ZERO n'est pas d�fini.
	m_4a = 0.0f;		 // = 4a

	m_a4 = 0.0f;   // = a^4
	m_4j2a = 0.0f; // = 4j�a
}
