#ifndef CCPOINTINSTANCEINFO_H
#define CCPOINTINSTANCEINFO_H

#include "../SpriterPlusPlus/spriterengine/objectinfo/pointinstanceinfo.h"
#include "axmol.h"
//namespace cocos2d {
//	class Node;
//}

namespace Spriter2dX
{

	class CCPointInstanceInfo : public SpriterEngine::PointInstanceInfo
	{
	public:
		CCPointInstanceInfo(ax::Node* parent);

		void render() override;

	private:
        ax::Node* parent;

	};

}

#endif // CCPOINTINSTANCEINFO_H
