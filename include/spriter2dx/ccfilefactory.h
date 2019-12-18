#ifndef CCFILEFACTORY_H
#define CCFILEFACTORY_H

#include <memory>
#include "spriterengine/override/filefactory.h"
#include "ccimagefile.h"

namespace Spriter2dX
{
	class CCFileFactory : public SpriterEngine::FileFactory
	{
	public:
		CCFileFactory(cocos2d::Node* parent, SpriteLoader loader);
		~CCFileFactory();
		
		SpriterEngine::ImageFile *newImageFile(const std::string& initialFilePath, SpriterEngine::point initialDefaultPivot, SpriterEngine::atlasdata atlasData) override;

		SpriterEngine::SoundFile *newSoundFile(const std::string& initialFilePath) override;

		SpriterEngine::SpriterFileDocumentWrapper *newScmlDocumentWrapper() override;

	private:
		class impl;
		std::unique_ptr<impl> self;
	};

}

#endif // CCFILEFACTORY_H
