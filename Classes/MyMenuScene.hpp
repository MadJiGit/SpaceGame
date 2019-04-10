//
//  MyMenuScene.hpp
//  SpaceGame-mobile
//
//  Created by Madji on 15.06.18.
//

#ifndef MyMenuScene_hpp
#define MyMenuScene_hpp

#include <stdio.h>
using namespace cocos2d;

class MainMenuScene : public::Layer
{
private:
    
    Sprite          *bg1, *bg2, *bg3;
    Size            visibleSize;
    Vec2            origin;
    
//    void GoToTheScene (Ref *sender);
//    void Highscores(Ref *pSender);
//    void Settings(Ref *pSender);
    
public:
    static Scene* createScene();
    
    virtual bool init();
    
    void GoToTheScene (Ref *sender);
    void Highscores(Ref *pSender);
    void Settings(Ref *pSender);
    
    CREATE_FUNC(MainMenuScene);
    
};

#endif /* MyMenuScene_hpp */
