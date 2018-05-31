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
// Copyright (c) 2016-2018 NVIDIA Corporation. All rights reserved.


#include "NvBlastAsset.h"
#include "NvBlastIndexFns.h"
#include "NvBlastAssert.h"
#include "NvBlastMemory.h"
#include "NvBlastMath.h"
#include "NvBlastPreprocessorInternal.h"

#include <algorithm>


namespace Nv
{
namespace Blast
{

/**
Class to hold chunk descriptor and annotation context for sorting a list of indices
*/
class ChunksOrdered
{
public:
	ChunksOrdered(const NvBlastChunkDesc* descs, const char* annotation) : m_descs(descs), m_annotation(annotation) {}

	bool	operator () (uint32_t i0, uint32_t i1) const
	{
		const bool upperSupport0 = (m_annotation[i0] & Asset::ChunkAnnotation::UpperSupport) != 0;
		const bool upperSupport1 = (m_annotation[i1] & Asset::ChunkAnnotation::UpperSupport) != 0;

		if (upperSupport0 != upperSupport1)
		{
			return upperSupport0;	// If one is uppersupport and one is subsupport, uppersupport should come first
		}

		// Parent chunk index (+1 so that UINT32_MAX becomes the lowest value)
		const uint32_t p0 = m_descs[i0].parentChunkIndex + 1;
		const uint32_t p1 = m_descs[i1].parentChunkIndex + 1;

		return p0 < p1;	// With the same support relationship, order by parent index
	}

private:
	const NvBlastChunkDesc*	m_descs;
	const char*				m_annotation;
};

} // namespace Blast
} // namespace Nv


using namespace Nv::Blast;

extern "C"
{

bool NvBlastBuildAssetDescChunkReorderMap(uint32_t* chunkReorderMap, const NvBlastChunkDesc* chunkDescs, uint32_t chunkCount, void* scratch, NvBlastLog logFn)
{
	NVBLASTLL_CHECK(chunkCount == 0 || chunkDescs != nullptr, logFn, "NvBlastBuildAssetDescChunkReorderMap: NULL chunkDescs input with non-zero chunkCount", return false);
	NVBLASTLL_CHECK(chunkReorderMap == nullptr || chunkCount != 0, logFn, "NvBlastBuildAssetDescChunkReorderMap: NULL chunkReorderMap input with non-zero chunkCount", return false);
	NVBLASTLL_CHECK(chunkCount == 0 || scratch != nullptr, logFn, "NvBlastBuildAssetDescChunkReorderMap: NULL scratch input with non-zero chunkCount", return false);

	uint32_t* chunkMap = static_cast<uint32_t*>(scratch);	scratch = pointerOffset(scratch, chunkCount * sizeof(uint32_t));
	char* chunkAnnotation = static_cast<char*>(scratch);	scratch = pointerOffset(scratch, chunkCount * sizeof(char));

	uint32_t supportChunkCount;
	uint32_t leafChunkCount;
	if (!Asset::ensureExactSupportCoverage(supportChunkCount, leafChunkCount, chunkAnnotation, chunkCount, const_cast<NvBlastChunkDesc*>(chunkDescs), true, logFn))
	{
		NVBLASTLL_LOG_ERROR(logFn, "NvBlastBuildAssetDescChunkReorderMap: chunk descriptors did not have exact coverage, map could not be built.  Use NvBlastEnsureAssetExactSupportCoverage to fix descriptors.");
		return false;
	}

	// check order for fast out (identity map)
	if (Asset::testForValidChunkOrder(chunkCount, chunkDescs, chunkAnnotation, scratch))
	{
		for (uint32_t i = 0; i < chunkCount; ++i)
		{
			chunkReorderMap[i] = i;
		}

		return true;
	}
	
	for (uint32_t i = 0; i < chunkCount; ++i)
	{
		chunkMap[i] = i;
	}
	std::sort(chunkMap, chunkMap + chunkCount, ChunksOrdered(chunkDescs, chunkAnnotation));

	invertMap(chunkReorderMap, chunkMap, chunkCount);

	return false;
}


void NvBlastApplyAssetDescChunkReorderMap
(
	NvBlastChunkDesc* reorderedChunkDescs,
	const NvBlastChunkDesc* chunkDescs,
	uint32_t chunkCount,
	NvBlastBondDesc* bondDescs,
	uint32_t bondCount,
	const uint32_t* chunkReorderMap,
	bool keepBondNormalChunkOrder, 
	NvBlastLog logFn
)
{
	NVBLASTLL_CHECK(chunkCount == 0 || chunkDescs != nullptr, logFn, "NvBlastApplyAssetDescChunkReorderMap: NULL chunkDescs input with non-zero chunkCount", return);
	NVBLASTLL_CHECK(reorderedChunkDescs == nullptr || chunkCount != 0, logFn, "NvBlastApplyAssetDescChunkReorderMap: NULL reorderedChunkDescs input with non-zero chunkCount", return);
	NVBLASTLL_CHECK(chunkReorderMap == nullptr || chunkCount != 0, logFn, "NvBlastApplyAssetDescChunkReorderMap: NULL chunkReorderMap input with non-zero chunkCount", return);
	NVBLASTLL_CHECK(bondCount == 0 || bondDescs != nullptr, logFn, "NvBlastApplyAssetDescChunkReorderMap: NULL bondDescs input with non-zero bondCount", return);
	NVBLASTLL_CHECK(bondDescs == nullptr || chunkReorderMap != nullptr, logFn, "NvBlastApplyAssetDescChunkReorderMap: NULL bondDescs input with NULL chunkReorderMap", return);

	// Copy chunk descs 
	if (reorderedChunkDescs)
	{
		for (uint32_t i = 0; i < chunkCount; ++i)
		{
			reorderedChunkDescs[chunkReorderMap[i]] = chunkDescs[i];
			uint32_t& parentIndex = reorderedChunkDescs[chunkReorderMap[i]].parentChunkIndex;
			if (parentIndex < chunkCount)
			{
				parentIndex = chunkReorderMap[parentIndex];	// If the parent index is valid, remap it too to reflect the new order
			}
		}
	}

	if (bondDescs)
	{
		for (uint32_t i = 0; i < bondCount; ++i)
		{
			NvBlastBondDesc& bondDesc = bondDescs[i];
			uint32_t& index0 = bondDesc.chunkIndices[0];
			uint32_t& index1 = bondDesc.chunkIndices[1];
			const uint32_t newIndex0 = index0 < chunkCount ? chunkReorderMap[index0] : index0;
			const uint32_t newIndex1 = index1 < chunkCount ? chunkReorderMap[index1] : index1;
			if (keepBondNormalChunkOrder && (index0 < index1) != (newIndex0 < newIndex1))
			{
				VecMath::mul(bondDesc.bond.normal, -1);
			}
			index0 = newIndex0;
			index1 = newIndex1;
		}
	}
}


void NvBlastApplyAssetDescChunkReorderMapInPlace
(
	NvBlastChunkDesc* chunkDescs,
	uint32_t chunkCount,
	NvBlastBondDesc* bondDescs,
	uint32_t bondCount,
	const uint32_t* chunkReorderMap,
	bool keepBondNormalChunkOrder,
	void* scratch,
	NvBlastLog logFn
)
{
	NVBLASTLL_CHECK(chunkCount == 0 || chunkDescs != nullptr, logFn, "NvBlastApplyAssetDescChunkReorderMapInPlace: NULL chunkDescs input with non-zero chunkCount", return);
	NVBLASTLL_CHECK(chunkCount == 0 || scratch != nullptr, logFn, "NvBlastApplyAssetDescChunkReorderMapInPlace: NULL scratch input with non-zero chunkCount", return);

	NvBlastChunkDesc* chunksTemp = static_cast<NvBlastChunkDesc*>(scratch);
	memcpy(chunksTemp, chunkDescs, sizeof(NvBlastChunkDesc) * chunkCount);
	NvBlastApplyAssetDescChunkReorderMap(chunkDescs, chunksTemp, chunkCount, bondDescs, bondCount, chunkReorderMap, keepBondNormalChunkOrder, logFn);
}


bool NvBlastReorderAssetDescChunks
(
	NvBlastChunkDesc* chunkDescs,
	uint32_t chunkCount,
	NvBlastBondDesc* bondDescs,
	uint32_t bondCount,
	uint32_t* chunkReorderMap,
	bool keepBondNormalChunkOrder,
	void* scratch,
	NvBlastLog logFn
)
{
	if (!NvBlastBuildAssetDescChunkReorderMap(chunkReorderMap, chunkDescs, chunkCount, scratch, logFn))
	{
		NvBlastApplyAssetDescChunkReorderMapInPlace(chunkDescs, chunkCount, bondDescs, bondCount, chunkReorderMap, keepBondNormalChunkOrder, scratch, logFn);
		return false;
	}
	return true;
}


bool NvBlastEnsureAssetExactSupportCoverage(NvBlastChunkDesc* chunkDescs, uint32_t chunkCount, void* scratch, NvBlastLog logFn)
{
	NVBLASTLL_CHECK(chunkCount == 0 || chunkDescs != nullptr, logFn, "NvBlastEnsureAssetExactSupportCoverage: NULL chunkDescs input with non-zero chunkCount", return false);
	NVBLASTLL_CHECK(chunkCount == 0 || scratch != nullptr, logFn, "NvBlastEnsureAssetExactSupportCoverage: NULL scratch input with non-zero chunkCount", return false);

	uint32_t supportChunkCount;
	uint32_t leafChunkCount;
	return Asset::ensureExactSupportCoverage(supportChunkCount, leafChunkCount, static_cast<char*>(scratch), chunkCount, chunkDescs, false, logFn);
}

} // extern "C"
