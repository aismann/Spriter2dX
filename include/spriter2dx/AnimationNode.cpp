//
// Created by jeremy on 12/12/15.
//
#include <2d/CCSprite.h>
#include <sstream>

#include "AnimationNode.h"
#include "ccobjectfactory.h"

using namespace cocos2d;

namespace Spriter2dX
{
    AnimationNode::AnimationNode(const std::string& scmlFile, SpriteLoader loader)
            : files(new CCFileFactory(this, loader)),
            model(scmlFile, files, new CCObjectFactory(this)),
            renderDisabled(false),
            isFlippedX(false),
            isFlippedY(false)
    {
    }

    AnimationNode::~AnimationNode()
    {
    }

    void doNothing(SpriterEngine::EntityInstance*)
    {
    }

    void AnimationNode::update(float dt)
    {
        for (auto it = this->entities.begin(); it != this->entities.end(); it++)
        {
            const EntityCommand& cmd = *it;
            
            if (cmd.entity != nullptr)
            {
                auto pre_ratio = cmd.entity->getTimeRatio();
                cmd.entity->setTimeElapsed(dt * 1000.0f);
                
                if (cmd.type == PlayOnce && (pre_ratio > .99f || pre_ratio > cmd.entity->getTimeRatio()))
                {
                    cmd.onComplete(cmd.entity.get());
                }

                cmd.entity->playAllTriggers();

                if (!this->renderDisabled)
                {
                    cmd.entity->render();
                }
            }
        }
    }

    SpriterEngine::EntityInstance* AnimationNode::createEntity(const std::string &name, CommandType type ,EntityEvent onComplete)
    {
        SpriterEngine::EntityInstance* entity = model.getNewEntityInstance(name);
        entities.emplace_back(type, entity, onComplete);

        return entity;
    }

    void AnimationNode::deleteEntity(SpriterEngine::EntityInstance*& remove)
    {
        auto removed = std::remove_if(entities.begin(), entities.end(), [=](const EntityCommand& cmd)
        {
            return cmd.entity.get() == remove;
        });

        entities.erase(removed, entities.end());
        remove = nullptr;
    }

    void AnimationNode::updateFlipped(bool isFlippedX, bool isFlippedY)
    {
        for (auto it = this->entities.begin(); it != this->entities.end(); *it++)
        {
            if (it->entity != nullptr)
            {
                it->entity->setScale(SpriterEngine::point(isFlippedX ? -1.0f : 1.0f, isFlippedY ? -1.0f : 1.0f));
            }
        }
    }

    void AnimationNode::setFlippedX(bool flippedX)
    {
        this->isFlippedX = flippedX;
        this->updateFlipped(this->isFlippedX, this->isFlippedY);
    }

    void AnimationNode::setFlippedY(bool flippedY)
    {
        this->isFlippedY = flippedY;
        this->updateFlipped(this->isFlippedX, this->isFlippedY);
    }

    SpriterEngine::EntityInstance* AnimationNode::playOnce(const std::string &name)
    {
        SpriterEngine::EntityInstance* instance = this->createEntity(name, PlayOnce, doNothing);
        this->updateFlipped(this->isFlippedX, this->isFlippedY);

        return instance;
    }

    SpriterEngine::EntityInstance* AnimationNode::playOnce(const std::string &name, EntityEvent onComplete)
    {
        SpriterEngine::EntityInstance* instance = this->createEntity(name, PlayOnce, onComplete);
        this->updateFlipped(this->isFlippedX, this->isFlippedY);

        return instance;
    }

    SpriterEngine::EntityInstance *AnimationNode::play(const std::string &name)
    {
        SpriterEngine::EntityInstance* instance = this->createEntity(name, PlayRepeat, doNothing);
        this->updateFlipped(this->isFlippedX, this->isFlippedY);

        return instance;
    }

    AnimationNode* AnimationNode::create(const std::string& scmlFile, SpriteLoader loader)
    {
        AnimationNode* ret = new (std::nothrow) AnimationNode(scmlFile, loader);

        if (ret && ret->init())
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(ret);
        }

        return ret;
    }

    SpriteLoader AnimationNode::fileLoader()
    {
        return [](const std::string& name)
        {
            return Sprite::create(name);
        };
    }

    std::vector<std::string> split(const std::string& s, char delim)
    {
        std::stringstream ss(s);
        std::string item;
        std::vector<std::string> elems;

        while (std::getline(ss, item, delim))
        {
            elems.push_back(item);
        }

        return elems;
    }

    SpriteLoader AnimationNode::cacheLoader()
    {
        return [](const std::string& name)
        {
            auto fullpath = split(name, '/');
            return Sprite::createWithSpriteFrameName(fullpath.back());
        };
    }

    void AnimationNode::onEnter()
    {
        Node::onEnter();
        this->scheduleUpdate();
    }

    void AnimationNode::onExit()
    {
        Node::onExit();
        this->unscheduleUpdate();
    }

	void AnimationNode::disableRender()
    {
        this->renderDisabled = true;
    }

	void AnimationNode::enableRender()
    {
        this->renderDisabled = false;
    }
}
