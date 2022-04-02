#pragma once
#include "lib/N/NType.h"
#include "lib/N/Maths/NVec2f32.h"

typedef struct
{
	// friend class NLTRAJECTORY;
	// --------------------------------------------------------------------
	// Membres définis à la création du Path par la méthode NLPATH::Build()
	NVEC2f32 p; // Position
	Nf32 k;		// Courbure en ce point
	NVEC2f32 u; // Direction ( tangente en p orientée dans le sens du chemin, du début vers la fin )
	Nf32 s;		// Abscisse curviligne

	// --------------------------------------------------------------------
	// Membre(s) mis à jour/utilisés lors de la construction d'une "Trajectory" à partir du "Path" possèdant ce KeyPoint ( mise à jour par la méthode NLTRAJECTORY::Build(...)
	// private:
	//	Nf32			m_localVelocityLimit;
} NLPATH_POINT;

// Version simplifiée et minimaliste d'un point de path.
// Utilisée exclusivement comme structure de résultat en retour de fonction de calcul/estimation de path point
//
typedef struct
{
	NVEC2f32 p; // Position
	Nf32 k;		// Courbure en ce point
} NLPATH_POINT_S;