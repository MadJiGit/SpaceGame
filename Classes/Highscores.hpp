//
//  Highscores.hpp
//  SpaceGame-mobile
//
//  Created by Madji on 18.06.18.
//

#ifndef Highscores_hpp
#define Highscores_hpp

#include <stdio.h>
#include "Enemy.hpp"
#include "theScene.h"

class theScene;

using namespace cocos2d;

class Highscores : public::Layer
{
private:
    
    Sprite          *bg1, *bg2, *bg3;
    Size            visibleSize;
    Vec2            origin;
    
public:
    static Scene* createScene();
    virtual bool init();
    
    void GoBack (Ref *sender);

    Label *scoreLabel;
    Label *scoreLabe2;
    
    void update(float dt);
    
    CREATE_FUNC(Highscores);
    
};
#endif /* Highscores_hpp */
