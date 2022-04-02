#ifndef __NVEC4F32_H
#define __NVEC4F32_H

// ***************************************************************************************
// ***************************************************************************************
// **																					**
// **								   NVec4f32.h										**
// **																					**
// ***************************************************************************************
#include "lib/N/NCStandard.h"
#include "lib/N/NType.h"
#include "lib/N/NMath.h"
#include "lib/N/NVecLimits.h"
#ifdef __cplusplus
extern "C"
{
#endif
	// --------------------------------------------------------------------------------------------------------------------------------------------------------------
	// ***************************************************************************************
	// **								Structures											**
	// ***************************************************************************************
	typedef struct
	{
		union
		{
			struct
			{
				Nf32 x;
				Nf32 y;
				Nf32 z;
				Nf32 w;
			};
			Nf32 coord[4];
		};
	} NVEC4;
	typedef NVEC4 NVEC4f32;

	// ***************************************************************************************
	// **								 Functions											**
	// ***************************************************************************************
	inline void NVec4Set(NVEC4 *v, const Nf32 x, const Nf32 y, const Nf32 z, const Nf32 w)
	{
		v->x = x;
		v->y = y;
		v->z = z;
		v->w = w;
	}
	inline void NVec4Null(NVEC4 *v)
	{
		v->x = 0;
		v->y = 0;
		v->z = 0;
		v->w = 0;
	}
	inline void NVec4Lerp(NVEC4 *vr, const NVEC4 *vorigin, const NVEC4 *v, const Nf32 t)
	{
		vr->x = vorigin->x + (v->x - vorigin->x) * t;
		vr->y = vorigin->y + (v->y - vorigin->y) * t;
		vr->z = vorigin->z + (v->z - vorigin->z) * t;
		vr->w = vorigin->w + (v->w - vorigin->w) * t;
	}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif // __cpluplus
#endif // __NVECTOR_H
