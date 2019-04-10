//
//  MainMenuScene.hpp
//  SpaceGame-mobile
//
//  Created by Madji on 17.06.18.
//

#ifndef MainMenuScene_hpp
#define MainMenuScene_hpp

#include <stdio.h>
using namespace cocos2d;

class MainMenuScene : public::Layer
{
private:
    
    Sprite          *bg1, *bg2, *bg3;
    Size            visibleSize;
    Vec2            origin;
    
public:
    static Scene* createScene();
    
    virtual bool init();
    
    void GoToTheScene (Ref *pSender);
    void Highscores(Ref *pSender);
    void Settings(Ref *pSender);
    void ExitGame(Ref *pSender);
    
    void update(float dt);
    
    CREATE_FUNC(MainMenuScene);
    
};

#endif /* MainMenuScene_hpp */
