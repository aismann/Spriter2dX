#include "ccimagefile.h"
#include "spriterengine/objectinfo/universalobjectinterface.h"
#include <2d/CCSprite.h>
#include <platform/CCFileUtils.h>
#include <sstream>

namespace se = SpriterEngine;
namespace cc = cocos2d;

namespace Spriter2dX
{

	CCImageFile::CCImageFile(std::string initialFilePath
		, se::point initialDefaultPivot
		, cc::Node* parent
		, SpriteLoader loader) :
		se::ImageFile(initialFilePath, initialDefaultPivot), parent(parent), loader(loader)
	{
	}

	CCImageFile::~CCImageFile()
	{
		for (auto sprite : avail) {
			sprite->removeFromParentAndCleanup(true);
		}
		for (auto sprite : used) {
			sprite->removeFromParentAndCleanup(true);
		}
	}

	void CCImageFile::renderSprite(se::UniversalObjectInterface* spriteInfo)
	{
		auto sprite = nextSprite();

		sprite->setPosition(float(spriteInfo->getPosition().x), -float(spriteInfo->getPosition().y));
		sprite->setAnchorPoint(cc::Vec2(float(spriteInfo->getPivot().x), 1.0f - float(spriteInfo->getPivot().y)));
		sprite->setRotation(float(se::toDegrees(spriteInfo->getAngle())));
		sprite->setScale(float(spriteInfo->getScale().x), float(spriteInfo->getScale().y));
		sprite->setVisible(true);

		if (sprite->getChildrenCount() > 0)
		{
			cc::Sprite* innerSpriteHack = dynamic_cast<cc::Sprite*>(sprite->getChildren().at(0));

			if (innerSpriteHack != nullptr)
			{
				sprite->setContentSize(innerSpriteHack->getContentSize());
				innerSpriteHack->setAnchorPoint(cc::Vec2::ZERO);
				innerSpriteHack->setOpacity((spriteInfo->getAlpha()) * 255);
				innerSpriteHack->setPosition(float(spriteInfo->getOffset().y), float(spriteInfo->getOffset().x));
				innerSpriteHack->setVisible(true);
			}
		}
	}

	cc::Sprite* CCImageFile::nextSprite()
	{
		cc::Sprite* sprite{ nullptr };

		auto createSprite = [=]()
		{
			cc::Sprite* newSprite = cc::Sprite::create();
			cc::Sprite* spriteInnerHack = loader(path());

			newSprite->addChild(spriteInnerHack);

			if (newSprite && spriteInnerHack)
			{
				parent->addChild(newSprite);
			}
			else
			{
				CCLOGERROR("CCImageFile() - cocos sprite unable to load file from path %s", path().c_str());
			}

			return newSprite;
		};

		if (avail.size() > 0)
		{
			sprite = avail.back();
			avail.pop_back();
		}
		else
		{
			sprite = createSprite();
		}

		// Recreate sprite if the image path changes
		if (sprite->getChildrenCount() > 0)
		{
			cc::Sprite* innerSpriteHack = dynamic_cast<cc::Sprite*>(sprite->getChildren().at(0));
			
			if (innerSpriteHack->getResourceName() != path())
			{
				sprite = createSprite();
			}
		}

        used.push_back(sprite);
        return sprite;
    }

    void CCImageFile::resetSprites()
    {
        for (auto sprite: used) {
            sprite->setVisible(false);
            avail.push_back(sprite);
        }
        used.clear();
    }

}
