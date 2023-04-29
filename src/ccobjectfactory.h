#ifndef CCOBJECTFACTORY_H
#define CCOBJECTFACTORY_H


#include "../SpriterPlusPlus/spriterengine/override/objectfactory.h"
#include "axmol.h"
//namespace axmol {
//	class ax::Node;
//}

namespace Spriter2dX
{

	class CCObjectFactory : public SpriterEngine::ObjectFactory
	{
	public:
		CCObjectFactory(ax::Node* parent);
		
		SpriterEngine::PointInstanceInfo *newPointInstanceInfo() override;

		SpriterEngine::BoxInstanceInfo *newBoxInstanceInfo(SpriterEngine::point size) override;

		SpriterEngine::BoneInstanceInfo *newBoneInstanceInfo(SpriterEngine::point size) override;

		SpriterEngine::TriggerObjectInfo *newTriggerObjectInfo(std::string triggerName) override;
	private:
		ax::Node* parent;
	};

}

#endif // CCOBJECTFACTORY_H
