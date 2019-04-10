#pragma once
#include "theScene.h"
#include "Ranger.hpp"
#include "DEFINITIONS.h"
#include "PhysicsCategory.hpp"

class theScene;
class Ranger;

using namespace cocos2d;

class Shooting : public Sprite
{
    
private:
    theScene        *scene;
    Size            visibleSize;
    Vec2            origin;
    Ranger          *ranger;
    Shooting        *shoot;
    Vec2            rangerPos;
    
public:
    
//    static int offsetShooting;
    
    static Shooting* createShooting(theScene *scene, Ranger *ranger, int offsetShootingFromRangerStart, int offsetShootingFromRangerEnd);
    
    void setInitParams(theScene *scene, Ranger *ranger);
    
    void initShooting(int offsetShootingStart, int offsetShootingEnd);
    
    void cleanShoot();
    
};

