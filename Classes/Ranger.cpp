//
//  Ranger.cpp
//  SpaceGame-mobile
//
//  Created by Madji on 19.05.18.
//

#include <iostream>
#include "Ranger.hpp"
#include "theScene.h"

double Ranger::pauseShoot = 0.0;
double Ranger::speedRanger = 1.0;
double Enemy::delayEnemy = 1.5;

Ranger *Ranger::createRanger(theScene *scene)
{
    Ranger               *sprite;
    sprite          = new Ranger();
    
    if(sprite && sprite->initWithFile("ranger.png"))
    {
        sprite->setScene(scene);
        sprite->initRanger();
        return sprite;
    }
    
    CC_SAFE_DELETE(sprite);
    
    return sprite = nullptr;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void Ranger::setScene(theScene *scene)
{
    this->scene = scene;
}

void Ranger::initRanger()
{
    pauseShoot = 0.0;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    this->setPosition(Vec2(visibleSize.width/2 + origin.x, origin.y - 20));
    
    auto rangerBody = PhysicsBody::createCircle( this->getContentSize().width / 2, PhysicsMaterial(0, 1, 0));
    rangerBody->setDynamic(true);
    /////////
    rangerBody->setCategoryBitmask((int)PhysicsCategory::RangerPC);
    rangerBody->setCollisionBitmask((int)PhysicsCategory::None);
    rangerBody->setContactTestBitmask((int)PhysicsCategory::EnemyPC);
    this->setPhysicsBody( rangerBody );
    this->setTag(1);
    /////////
    
    _eventDispatcher->removeEventListenersForTarget(this);
    auto listener = EventListenerTouchOneByOne::create();
    
    auto moveForward = MoveTo::create(2, Vec2(visibleSize.width/2  + origin.x, visibleSize.height/9 + origin.y));
    auto moveOnTheGamePosition = Sequence::create(moveForward, nullptr);
    this->runAction(moveOnTheGamePosition);
    
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(Ranger::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


bool Ranger::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    this->stopAllActions();
    auto whereToGo = (touch->getLocation().x - this->getPositionX());
    auto timeToGo = ( abs(whereToGo)/ (visibleSize.width/3) * speedRanger );
    auto moveToPositionX = MoveTo::create(timeToGo, Vec2((touch->getLocation().x + origin.x),
                                                         (visibleSize.height/9 + origin.y)));
    
    
//    if (theScene::GetScore() > 15) {
//        //        int offsetShootingLeftStart = -10;
//        //        int offsetShootingRightStart = 10;
//        //        int offsetShootingLeftEnd = -50;
//        //        int offsetShootingRightEnd = 50;
//        // TODO: fix delayEnemy
//        Enemy::delayEnemy = 0.5;
//        pauseShoot = 0.001;
//        DelayTime *pause2 = DelayTime::create(pauseShoot);
//        auto move = Sequence::create(moveToPositionX,
//                                     CallFunc::create([&] (){ Shooting::createShooting(scene, this, -10, -150);}),
//                                     pause2,
//                                     CallFunc::create([&] (){ Shooting::createShooting(scene, this, 10, 150);}),
//                                     pause2,
//                                     CallFunc::create([&] (){ Shooting::createShooting(scene, this, 0, 0);}),
//                                     nullptr);
//        this->runAction(move);
//    }
        if (theScene::GetScore() >= 0) {
//        int offsetShootingLeft = -10;
//        int offsetShootingRight = 10;
        pauseShoot = 0.001;
        DelayTime *pause2 = DelayTime::create(pauseShoot);
        auto move = Sequence::create(moveToPositionX,
                                     CallFunc::create([&] (){ Shooting::createShooting(scene, this, -10, -10);}),
                                     pause2,
                                     CallFunc::create([&] (){ Shooting::createShooting(scene, this, 10, 10);}),
                                     nullptr);
        this->runAction(move);
    }
//    else if (theScene::GetScore() > 4) {
////        int offsetShootingUp = 0;
//        Enemy::delayEnemy = 0.5;
//        pauseShoot = 0.5;
//        DelayTime *pause2 = DelayTime::create(pauseShoot);
//        auto move = Sequence::create(moveToPositionX,
//                                     CallFunc::create([&] (){ Shooting::createShooting(scene, this, 0, 0);}),
//                                     pause2,
//                                     CallFunc::create([&] (){ Shooting::createShooting(scene, this, 0, 0);})
//                                     , nullptr);
//        this->runAction(move);
//    }
//    else if (theScene::GetScore() < 5) {
////        int offsetShootingUp = 0;
//        Enemy::delayEnemy = 0.5;
//        auto move = Sequence::create(moveToPositionX,
//                                     CallFunc::create([&] (){ Shooting::createShooting(scene, this, 0, 0);}),
//                                     nullptr);
//        this->runAction(move);
//    }

    return true;
}

void Ranger::cleanRanger()
{
    this->removeFromParentAndCleanup(true);
}
