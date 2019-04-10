//
//  Enemy.cpp
//  SpaceGame-mobile
//
//  Created by Madji on 19.05.18.
//

#include <iostream>
#include "Enemy.hpp"
int Enemy::countCleanEnemy = 0;

//double Enemy::delayEnemy = 1.5;

Enemy* Enemy::createEnemy(theScene *e)
{
    
    auto sprite = new Enemy();

    if(sprite && sprite->initWithFile("blue_enemy.png"))
    {
        sprite->setScene(e);
        sprite->initEnemy();
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

void Enemy::setScene(theScene *scene)
{
    this->scene = scene;
}

void Enemy::initEnemy()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    // add physic to enemy
    auto enemyBody = PhysicsBody::createCircle( this->getContentSize().width / 2, PhysicsMaterial(0, 1, 0));
    enemyBody->setDynamic(true);
    /////////
    enemyBody->setCategoryBitmask((int)PhysicsCategory::EnemyPC);
    enemyBody->setCollisionBitmask((int)PhysicsCategory::None);
    enemyBody->setContactTestBitmask((int)PhysicsCategory::RangerPC);
    this->setPhysicsBody( enemyBody );
    this->setTag(2);
    ////////
    

    scene->addChild(this, 3);
    
    auto startX = RandomHelper::random_int(0 + (int)(getContentSize().width), (int)visibleSize.width);
    this->setPosition(Vec2(startX, visibleSize.height + origin.y + ((int)(getContentSize().height * 1.5))));
    
    auto flightDirection = MoveTo::create(7, Vec2(startX, -30 ));
    auto removeEnemy = CallFunc::create([&] () {Enemy::cleanEnemy(); });
    auto flightEnemy = Sequence::create(flightDirection, removeEnemy, nullptr);
    this->runAction(flightEnemy);
    
    this->scheduleUpdate();
}

void Enemy::cleanEnemy()
{
    countCleanEnemy++;
    CCLOG("cleanEnemy %d", countCleanEnemy);
    this->removeFromParentAndCleanup(true);
}
