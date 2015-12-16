#ifndef CCFILEFACTORY_H
#define CCFILEFACTORY_H

#include <memory>
#include "../SpriterPlusPlus/spriterengine/override/filefactory.h"
#include "../SpriterPlusPlus/spriterengine/override/imagefile.h"

namespace cocos2d {
	class Node;
}

namespace Spriter2dX
{

	class CCFileFactory : public SpriterEngine::FileFactory
	{
	public:
		CCFileFactory(cocos2d::Node* parent);
		~CCFileFactory();
		
		SpriterEngine::ImageFile *newImageFile(const std::string& initialFilePath, SpriterEngine::point initialDefaultPivot) override;

		SpriterEngine::SoundFile *newSoundFile(const std::string& initialFilePath) override;

		SpriterEngine::SpriterFileDocumentWrapper *newScmlDocumentWrapper() override;

		/**
         * After each render cycle, this method must be called to hide
         * all the Cocos2d Sprites in use and mark them available in the pools
         * maintained in each CCImageFile.
         * @memberof CCFileFactory
         */
		void resetSprites();

	private:
		class impl;
		std::unique_ptr<impl> self;
	};

}

#endif // CCFILEFACTORY_H
