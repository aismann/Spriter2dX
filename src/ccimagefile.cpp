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
        this->sprites = std::map<std::string, cc::Node*>();
		this->nextSprite = nullptr;
	}

	CCImageFile::~CCImageFile()
	{
		for (auto sprite : this->sprites)
		{
			sprite.second->removeFromParentAndCleanup(true);
		}

		this->sprites.clear();
	}

	void CCImageFile::renderSprite(se::UniversalObjectInterface* spriteInfo)
	{
		if (this->nextSprite != nullptr)
		{
			this->nextSprite->setVisible(false);
		}

		this->setNextSprite();

		if (this->nextSprite == nullptr)
		{
			return;
		}

		this->nextSprite->setVisible(true);

		const cc::Vec2 pos = cc::Vec2(float(spriteInfo->getPosition().x), -float(spriteInfo->getPosition().y));
		const cc::Vec2 anchor = cc::Vec2(float(spriteInfo->getPivot().x), 1.0f - float(spriteInfo->getPivot().y));
		const float rotation = float(se::toDegrees(spriteInfo->getAngle()));
		const float scaleX = float(spriteInfo->getScale().x);
		const float scaleY = float(spriteInfo->getScale().y);

		if (pos != nextSprite->getPosition())
		{
			this->nextSprite->setPosition(pos);
		}

		if (anchor != nextSprite->getAnchorPoint())
		{
			this->nextSprite->setAnchorPoint(anchor);
		}

		if (rotation != nextSprite->getRotation())
		{
			this->nextSprite->setRotation(rotation);
		}

		if (scaleX != nextSprite->getScaleX())
		{
			this->nextSprite->setScaleX(scaleX);
		}

		if (scaleY != nextSprite->getScaleY())
		{
			this->nextSprite->setScaleY(scaleY);
		}

		if (this->nextSprite->getChildrenCount() > 0)
		{
			cc::Sprite* innerSpriteHack = dynamic_cast<cc::Sprite*>(this->nextSprite->getChildren().at(0));

			if (innerSpriteHack != nullptr)
			{
				const GLubyte opacity = GLubyte((spriteInfo->getAlpha()) * 255);

				if (this->nextSprite->getContentSize().width != innerSpriteHack->getContentSize().width ||
					this->nextSprite->getContentSize().height != innerSpriteHack->getContentSize().height)
				{
					this->nextSprite->setContentSize(innerSpriteHack->getContentSize());
				}

				if (innerSpriteHack->getAnchorPoint() != cc::Vec2::ZERO)
				{
					innerSpriteHack->setAnchorPoint(cc::Vec2::ZERO);
				}

				if (innerSpriteHack->getOpacity() != opacity)
				{
					innerSpriteHack->setOpacity(opacity);
				}

				const cc::Vec2 innerPos = cc::Vec2(float(spriteInfo->getOffset().y), float(spriteInfo->getOffset().x));

				if (innerPos != innerSpriteHack->getPosition())
				{
					innerSpriteHack->setPosition(innerPos);
				}
			}
		}
	}

	void CCImageFile::setNextSprite()
	{
		auto createInnerSprite = [=]()
		{
			cc::Sprite* spriteInnerHack = loader(filePath);

			if (!spriteInnerHack)
			{
				CCLOGERROR("CCImageFile() - cocos sprite unable to load file from path %s", filePath.c_str());
			}

			return spriteInnerHack;
		};

		auto createSprite = [=]()
		{
			cc::Node* newSprite = cc::Node::create();
			cc::Sprite* spriteInnerHack = createInnerSprite();

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

		if (this->sprites.find(filePath) == this->sprites.end())
		{
			this->sprites[filePath] = createSprite();
		}
		
		this->nextSprite = this->sprites[filePath];
	}
}
