#ifndef SPRITER2DX_IMAGEFILE_H
#define SPRITER2DX_IMAGEFILE_H

#include <vector>
#include <functional>
#include "../SpriterPlusPlus/spriterengine/override/imagefile.h"
#include "axmol.h"

//namespace cocos2d {
//    class Node;
//    class Sprite;
//}

namespace Spriter2dX
{
    typedef std::vector<ax::Sprite*> SpriteList;
    typedef std::function<ax::Sprite*(const std::string&)> SpriteLoader;

	class CCImageFile : public SpriterEngine::ImageFile
	{
	public:
        CCImageFile(std::string initialFilePath
                   ,SpriterEngine::point initialDefaultPivot
				   ,ax::Node* parent
                   ,SpriteLoader loader);
        ~CCImageFile();

		void renderSprite(SpriterEngine::UniversalObjectInterface *spriteInfo) override;
        void resetSprites();


	private:
        SpriteLoader loader;
        ax::Sprite* nextSprite();

        ax::Node* parent;
        SpriteList avail;
        SpriteList used;
	};

}

#endif // SPRITER2DX_IMAGEFILE_H
