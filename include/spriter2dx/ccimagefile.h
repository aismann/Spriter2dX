#ifndef SPRITER2DX_IMAGEFILE_H
#define SPRITER2DX_IMAGEFILE_H

#include <functional>
#include <map>
#include <string>
#include <vector>
#include "spriterengine/override/imagefile.h"

namespace cocos2d {
    class Node;
    class Sprite;
}

namespace Spriter2dX
{
    typedef std::vector<cocos2d::Sprite*> SpriteList;
    typedef std::function<cocos2d::Sprite*(const std::string&)> SpriteLoader;

	class CCImageFile : public SpriterEngine::ImageFile
	{
	public:
        CCImageFile(std::string initialFilePath
                   ,SpriterEngine::point initialDefaultPivot
				   ,cocos2d::Node* parent
                   ,SpriteLoader loader);
        ~CCImageFile();
        
		void renderSprite(SpriterEngine::UniversalObjectInterface *spriteInfo) override;
        void resetSprites();

	private:
        void setNextSprite();

        SpriteLoader loader;

        cocos2d::Node* parent;
        cocos2d::Node* nextSprite;

        std::map<std::string, cocos2d::Node*> sprites;
	};

}

#endif // SPRITER2DX_IMAGEFILE_H
