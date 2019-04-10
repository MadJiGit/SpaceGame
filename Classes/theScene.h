#pragma once

USING_NS_CC;

#include "cocos2d.h"
#include "Ranger.hpp"
#include "Enemy.hpp"
#include "Shooting.hpp"
#include "DEFINITIONS.h"
#include "PhysicsCategory.hpp"


class Ranger;
class Enemy;
class Shooting;

using namespace cocos2d;

class theScene : public Layer
{

private:
    
    Sprite          *bg1, *bg2, *bg3, *rr1, *rr2, *rr3;
    Size            visibleSize;
    Vec2            origin;
    Ranger          *ranger;
    Enemy           *enemy;
    Shooting        *shoot;
    PhysicsBody     *rangerBody;
    Enemy           *enemyBody;
    Shooting        *shootBody;
    PhysicsWorld    *sceneWorld;
    static int      score;
    static int      countRanger;
    static int      countEnemy;
    static int      countEnemyToPrint;
    static int      countScoreToPrint;
    
    void SetPhysicsWorld( PhysicsWorld *world) { sceneWorld = world; };
    
public:
    
    // тук е променено заради physic world -> theScene* to Scene*
    static Scene* createScene();
    
    virtual bool init();

    CREATE_FUNC(theScene);

    void pushEnemy(float dt);
    
    void update(float dt);
    
    bool onContactBegan(PhysicsContact &contact);
    
    static int GetScore() { return score; }
    static int GetCountRanger() { return countRanger; }
    static int GetCountEnemy() { return countEnemy; }
    static int GetCountEnemyPrint() { return countEnemyToPrint; }
    static int GetCountScorePrint() { return countScoreToPrint; }
    
    void extraRangers();
    void pauseButton();
    void printScore();

    Label *scoreLabel;
    
};

