//
//  PauseResumeMenu.hpp
//  SpaceGame-mobile
//
//  Created by Madji on 20.06.18.
//

#ifndef PauseResumeMenu_hpp
#define PauseResumeMenu_hpp

#include <stdio.h>

using namespace cocos2d;

class PauseResumeMenu : public::Layer
{
private:
    
    Sprite          *bg1, *bg2, *bg3;
    Size            visibleSize;
    Vec2            origin;
    
public:
    static Scene* createScene();
    
    virtual bool init();
    
    void Resume (Ref *pSender);
    void Highscores(Ref *pSender);
    void Settings(Ref *pSender);
    void ExitGame(Ref *pSender);
    
    void update(float dt);
    
    CREATE_FUNC(PauseResumeMenu);
    
};

#endif /* PauseResumeMenu_hpp */
