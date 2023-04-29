#ifndef CCBONEINSTANCEINFO_H
#define CCBONEINSTANCEINFO_H

#include "../SpriterPlusPlus/spriterengine/objectinfo/boneinstanceinfo.h"
#include "axmol.h"
//namespace ax {
//	class Node;
//}
namespace Spriter2dX
{

	class CCBoneInstanceInfo : public SpriterEngine::BoneInstanceInfo
	{
	public:
		CCBoneInstanceInfo(SpriterEngine::point initialSize, ax::Node* parent);

		void render() override;
	};

}

#endif // CCBONEINSTANCEINFO_H
