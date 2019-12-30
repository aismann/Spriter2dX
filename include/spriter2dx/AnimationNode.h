//
// Created by jeremy on 12/12/15.
//

#ifndef SPRITER2DX_SPRITERNODE_H
#define SPRITER2DX_SPRITERNODE_H

#include <memory>

#include "spriterengine/spriterengine.h"
#include "ccfilefactory.h"

#include <2d/CCNode.h>

namespace cocos2d
{
    class Sprite;
}

namespace Spriter2dX
{
    class EntityInstance;
    
    typedef std::function<void(SpriterEngine::EntityInstance*)> EntityEvent;

    class AnimationNode : public cocos2d::Node
    {
    public:
        AnimationNode(const std::string& scmlFile, SpriteLoader loader);
        virtual ~AnimationNode();
        void update (float dt) override;

        /**
         * Sets whether the sprite should be flipped horizontally or not.
         * @param flippedX true if the sprite should be flipped horizontally, false otherwise.
         */
        void setFlippedX(bool flippedX);

        /**
         * Sets whether the sprite should be flipped vertically or not.
         * @param flippedY true if the sprite should be flipped vertically, false otherwise.
         */
        void setFlippedY(bool flippedY);

        /**
         * Gets whether the sprite is flipped horizontally or not.
         * @return True if sprite is flipped horizontally
         */
        inline bool getFlippedX() const {
            return isFlippedX;
        }

        /**
         * Gets whether the sprite is flipped vertically or not.
         * @return True if sprite is flipped vertically
         */
        inline bool getFlippedY() const {
            return isFlippedY;
        }

        /**
         * Creates and schedules for maintenance a SpriterPlusPlus animation
         * entity. Once the animation completes once it will be deleted, even if it
         * is configured to loop. Use AnimationNode::play for looping animations.
         * @memberof AnimationNode
         * @param name Name of the Spriter Entity in the AnimationNode's model
         * @return a SpriterEngine::EntityInstance which can be manipulated
         * using the SpriterPlusPlus API.
         */
        SpriterEngine::EntityInstance* playOnce(const std::string &name);

        SpriterEngine::EntityInstance* playOnce(const std::string &name, EntityEvent onComplete);

        /**
         * Creates and schedules for maintenance a SpriterPlusPlus animation
         * entity. It will be maintained until deleted using AnimationNode::deleteEntity.
         * Note that the actual behavior depends on the Entity's looping configuration in Spriter;
         * if the animation loops it will play continuously. Otherwise you can use the EntityInstance
         * to resume playback when required.
         * When the animation is no longer needed, it should be cleaned up with AnimationNode::deleteEntity.
         * @memberof AnimationNode
         * @param name Name of the Spriter Entity in the AnimationNode's model
         * @return a SpriterEngine::EntityInstance which can be manipulated
         * using the SpriterPlusPlus API.
         */
        SpriterEngine::EntityInstance* play(const std::string &name);

        /**
         * Remove and destroy the EntityInstance. Takes a reference to an
         * EntityInstance* and will set it to nullptr after removing and deleting it.
         * @memberof AnimationNode
         * @param entity the EntityInstance to delete.
         */
        void deleteEntity(SpriterEngine::EntityInstance*& entity);

        void disableRender();
        void enableRender();

        static AnimationNode* create(const std::string& scmlFile, SpriteLoader loader = fileLoader());

        virtual void onEnter() override;
        virtual void onExit() override;

        static SpriteLoader fileLoader();
        static SpriteLoader cacheLoader();

        bool renderDisabled;

    private:
        enum CommandType
        {
            PlayOnce,
            PlayRepeat
        };

        struct EntityCommand
        {
            EntityCommand(CommandType type, SpriterEngine::EntityInstance* entity, EntityEvent onComplete) :
                type(type), entity(entity), onComplete(onComplete)
            {
            }

            CommandType type;
            std::unique_ptr<SpriterEngine::EntityInstance> entity;
            EntityEvent onComplete;
        };

        SpriterEngine::EntityInstance* createEntity(const std::string &name, CommandType type ,EntityEvent onComplete);
        void updateFlipped(bool isFlippedX, bool isFlippedY);

        bool isFlippedX;
        bool isFlippedY;

        CCFileFactory* files;
        std::vector<EntityCommand> entities;
        SpriterEngine::SpriterModel model;
    };
}



#endif //SPRITERNODE_H
