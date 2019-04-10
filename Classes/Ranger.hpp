//
//  Ranger.hpp
//  SpaceGame-mobile
//
//  Created by Madji on 19.05.18.
//

#pragma once
#include "theScene.h"
#include "Shooting.hpp"
#include "DEFINITIONS.h"
#include "PhysicsCategory.hpp"

class theScene;
class Shooting;

using namespace cocos2d;

class Ranger : public Sprite
{
    
private:
    theScene        *scene;
    Size            visibleSize;
    Vec2            origin;
    Ranger          *ranger;
    Shooting        *shoot;
    
public:

    void setScene(theScene *scene);
    
    static Ranger *createRanger(theScene *scene);
    
    void positionToShoot();
    
    void initRanger();

    bool onTouchBegan(Touch *touch, Event *event);
    
    void cleanRanger();
    void listenersOn();
    
    static double   speedRanger;
    
    static double   pauseShoot;
    static double   GetPauseShoot() { return pauseShoot; }
    
};


