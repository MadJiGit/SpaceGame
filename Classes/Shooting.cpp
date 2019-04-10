//
//  Shooting.cpp
//  SpaceGame-mobile
//
//  Created by Madji on 19.05.18.
//

#include "Shooting.hpp"

Shooting *Shooting::createShooting(theScene *scene, Ranger *ranger, int start, int end)
{
    Shooting            *sprite;
    sprite =        new Shooting();
    
    if(sprite && sprite->initWithFile("shoot.png"))
    {
        sprite->setInitParams(scene, ranger);
        sprite->initShooting(start, end);
        
        return sprite;
    }
 
    
    CC_SAFE_DELETE(sprite);
    
    return sprite = nullptr;
}

void Shooting::setInitParams(theScene *scene, Ranger *ranger)
{
    this->scene = scene;
    this->ranger = ranger;
    rangerPos = ranger->getPosition();
    
}

void Shooting::initShooting(int offsetShootingStart, int offsetShootingEnd)
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    auto shootBody = PhysicsBody::createCircle( this->getContentSize().width / 3, PhysicsMaterial(0, 1, 0));
    /////////
    shootBody->setDynamic(true);
    shootBody->setCategoryBitmask((int)PhysicsCategory::ShootPC);
    shootBody->setCollisionBitmask((int)PhysicsCategory::None);
    shootBody->setContactTestBitmask((int)PhysicsCategory::EnemyPC);
    this->setPhysicsBody( shootBody );
    this->setTag(3);
    /////////


//    this->setPosition(rangerPos);

    this->setPosition(Vec2((rangerPos.x + offsetShootingStart), rangerPos.y));
    scene->addChild(this, 3);
    auto shootDirection = MoveTo::create(4, Vec2(ranger->getPositionX() + offsetShootingEnd, (visibleSize.height * 1.2)));
    auto removeShoot = CallFunc::create([&] () {Shooting::cleanShoot(); });
    auto shoot = Sequence::create(shootDirection, removeShoot, nullptr);
    this->runAction(shoot);
    
    
}

void Shooting::cleanShoot()
{
    this->removeFromParentAndCleanup(true);
}



