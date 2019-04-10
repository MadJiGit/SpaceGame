//
//  Enemy.hpp
//  SpaceGame-mobile
//
//  Created by Madji on 19.05.18.
//

#pragma once
#include "theScene.h"
#include "DEFINITIONS.h"
#include "PhysicsCategory.hpp"

class theScene;

using namespace cocos2d;

class Enemy : public Sprite
{
    
private:
    theScene        *scene;
    Size            visibleSize;
    Vec2            origin;
    Enemy           *enemy;
    
public:
    
    static double   delayEnemy;
    static int countCleanEnemy;
    
    void setScene(theScene *e);
    
    static Enemy *createEnemy(theScene *e);
    
    void initEnemy();
    
    void cleanEnemy();
    
//    static double delayEnemy;
  
};


