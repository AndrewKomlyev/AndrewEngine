#pragma once

#include "Common.h"

namespace AndrewEngine::Graphics
{
	struct Bone
	{
		std::string name;
		int index = -1;

		Bone* parent = nullptr;
		int parentIndex = -1;

		std::vector<Bone*> children;
		std::vector<int> childrenIndices;

		AEMath::Matrix4 toParentTransform;
		AEMath::Matrix4 offsetTransform;

	};
}
