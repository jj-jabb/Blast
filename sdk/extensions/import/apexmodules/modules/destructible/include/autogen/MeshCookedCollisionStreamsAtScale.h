// This code contains NVIDIA Confidential Information and is disclosed to you
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and
// any modifications thereto. Any use, reproduction, disclosure, or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA Corporation is strictly prohibited.
//
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2008-2017 NVIDIA Corporation. All rights reserved.

// This file was generated by NvParameterized/scripts/GenParameterized.pl


#ifndef HEADER_MeshCookedCollisionStreamsAtScale_h
#define HEADER_MeshCookedCollisionStreamsAtScale_h

#include "NvParametersTypes.h"

#ifndef NV_PARAMETERIZED_ONLY_LAYOUTS
#include "nvparameterized/NvParameterized.h"
#include "nvparameterized/NvParameterizedTraits.h"
#include "NvParameters.h"
#include "NvTraitsInternal.h"
#endif

namespace nvidia
{
namespace destructible
{

#if PX_VC
#pragma warning(push)
#pragma warning(disable: 4324) // structure was padded due to __declspec(align())
#endif

namespace MeshCookedCollisionStreamsAtScaleNS
{


struct REF_DynamicArray1D_Type
{
	NvParameterized::Interface** buf;
	bool isAllocated;
	int32_t elementSize;
	int32_t arraySizes[1];
};


struct ParametersStruct
{

	REF_DynamicArray1D_Type meshCookedCollisionStreams;

};

static const uint32_t checksum[] = { 0xf356e0c1, 0xf4812209, 0x4cf28347, 0xc18b1923, };

} // namespace MeshCookedCollisionStreamsAtScaleNS

#ifndef NV_PARAMETERIZED_ONLY_LAYOUTS
class MeshCookedCollisionStreamsAtScale : public NvParameterized::NvParameters, public MeshCookedCollisionStreamsAtScaleNS::ParametersStruct
{
public:
	MeshCookedCollisionStreamsAtScale(NvParameterized::Traits* traits, void* buf = 0, int32_t* refCount = 0);

	virtual ~MeshCookedCollisionStreamsAtScale();

	virtual void destroy();

	static const char* staticClassName(void)
	{
		return("MeshCookedCollisionStreamsAtScale");
	}

	const char* className(void) const
	{
		return(staticClassName());
	}

	static const uint32_t ClassVersion = ((uint32_t)0 << 16) + (uint32_t)0;

	static uint32_t staticVersion(void)
	{
		return ClassVersion;
	}

	uint32_t version(void) const
	{
		return(staticVersion());
	}

	static const uint32_t ClassAlignment = 8;

	static const uint32_t* staticChecksum(uint32_t& bits)
	{
		bits = 8 * sizeof(MeshCookedCollisionStreamsAtScaleNS::checksum);
		return MeshCookedCollisionStreamsAtScaleNS::checksum;
	}

	static void freeParameterDefinitionTable(NvParameterized::Traits* traits);

	const uint32_t* checksum(uint32_t& bits) const
	{
		return staticChecksum(bits);
	}

	const MeshCookedCollisionStreamsAtScaleNS::ParametersStruct& parameters(void) const
	{
		MeshCookedCollisionStreamsAtScale* tmpThis = const_cast<MeshCookedCollisionStreamsAtScale*>(this);
		return *(static_cast<MeshCookedCollisionStreamsAtScaleNS::ParametersStruct*>(tmpThis));
	}

	MeshCookedCollisionStreamsAtScaleNS::ParametersStruct& parameters(void)
	{
		return *(static_cast<MeshCookedCollisionStreamsAtScaleNS::ParametersStruct*>(this));
	}

	virtual NvParameterized::ErrorType getParameterHandle(const char* long_name, NvParameterized::Handle& handle) const;
	virtual NvParameterized::ErrorType getParameterHandle(const char* long_name, NvParameterized::Handle& handle);

	void initDefaults(void);

protected:

	virtual const NvParameterized::DefinitionImpl* getParameterDefinitionTree(void);
	virtual const NvParameterized::DefinitionImpl* getParameterDefinitionTree(void) const;


	virtual void getVarPtr(const NvParameterized::Handle& handle, void*& ptr, size_t& offset) const;

private:

	void buildTree(void);
	void initDynamicArrays(void);
	void initStrings(void);
	void initReferences(void);
	void freeDynamicArrays(void);
	void freeStrings(void);
	void freeReferences(void);

	static bool mBuiltFlag;
	static NvParameterized::MutexType mBuiltFlagMutex;
};

class MeshCookedCollisionStreamsAtScaleFactory : public NvParameterized::Factory
{
	static const char* const vptr;

public:

	virtual void freeParameterDefinitionTable(NvParameterized::Traits* traits)
	{
		MeshCookedCollisionStreamsAtScale::freeParameterDefinitionTable(traits);
	}

	virtual NvParameterized::Interface* create(NvParameterized::Traits* paramTraits)
	{
		// placement new on this class using mParameterizedTraits

		void* newPtr = paramTraits->alloc(sizeof(MeshCookedCollisionStreamsAtScale), MeshCookedCollisionStreamsAtScale::ClassAlignment);
		if (!NvParameterized::IsAligned(newPtr, MeshCookedCollisionStreamsAtScale::ClassAlignment))
		{
			NV_PARAM_TRAITS_WARNING(paramTraits, "Unaligned memory allocation for class MeshCookedCollisionStreamsAtScale");
			paramTraits->free(newPtr);
			return 0;
		}

		memset(newPtr, 0, sizeof(MeshCookedCollisionStreamsAtScale)); // always initialize memory allocated to zero for default values
		return NV_PARAM_PLACEMENT_NEW(newPtr, MeshCookedCollisionStreamsAtScale)(paramTraits);
	}

	virtual NvParameterized::Interface* finish(NvParameterized::Traits* paramTraits, void* bufObj, void* bufStart, int32_t* refCount)
	{
		if (!NvParameterized::IsAligned(bufObj, MeshCookedCollisionStreamsAtScale::ClassAlignment)
		        || !NvParameterized::IsAligned(bufStart, MeshCookedCollisionStreamsAtScale::ClassAlignment))
		{
			NV_PARAM_TRAITS_WARNING(paramTraits, "Unaligned memory allocation for class MeshCookedCollisionStreamsAtScale");
			return 0;
		}

		// Init NvParameters-part
		// We used to call empty constructor of MeshCookedCollisionStreamsAtScale here
		// but it may call default constructors of members and spoil the data
		NV_PARAM_PLACEMENT_NEW(bufObj, NvParameterized::NvParameters)(paramTraits, bufStart, refCount);

		// Init vtable (everything else is already initialized)
		*(const char**)bufObj = vptr;

		return (MeshCookedCollisionStreamsAtScale*)bufObj;
	}

	virtual const char* getClassName()
	{
		return (MeshCookedCollisionStreamsAtScale::staticClassName());
	}

	virtual uint32_t getVersion()
	{
		return (MeshCookedCollisionStreamsAtScale::staticVersion());
	}

	virtual uint32_t getAlignment()
	{
		return (MeshCookedCollisionStreamsAtScale::ClassAlignment);
	}

	virtual const uint32_t* getChecksum(uint32_t& bits)
	{
		return (MeshCookedCollisionStreamsAtScale::staticChecksum(bits));
	}
};
#endif // NV_PARAMETERIZED_ONLY_LAYOUTS

} // namespace destructible
} // namespace nvidia

#if PX_VC
#pragma warning(pop)
#endif

#endif
