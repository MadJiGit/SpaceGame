//
//  MainMenuScene.cpp
//  SpaceGame-mobile
//
//  Created by Madji on 15.06.18.
//

#include "MainMenuScene.hpp"
#include "theScene.h"
#include "DEFINITIONS.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = MainMenuScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MainMenuScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    bg1 = Sprite::create("spacebg1.png");
    
    if (bg1 == nullptr)
    {
        problemLoading("'bg1'");
    }
    else
    {
        bg1->setPosition(Vec2(visibleSize.width/2 + origin.x, bg1->getContentSize().height/2));
        this->addChild(bg1, 1);
        
        bg2 = Sprite::create("spacebg2.png");
        if (bg2 == nullptr) {
            problemLoading("'bg2'");
        }
        else
        {
            bg2->setPosition(Vec2(visibleSize.width/2 + origin.x, bg1->getContentSize().height + bg2->getContentSize().height/2));
            this->addChild(bg2, 1);
            
            bg3 = Sprite::create("spacebg3.png");
            if (bg3 == nullptr) {
                problemLoading("'bg3'");
            }
            else
            {
                bg3->setPosition(Vec2(visibleSize.width/2 + origin.x, bg2->getPositionY() + bg3->getContentSize().height));
                this->addChild(bg3, 1);
            }
        }
    }
    
    auto playItem = MenuItemFont::create( "Play", CC_CALLBACK_1( MainMenuScene::GoToTheScene, this ) );
    auto highscoresItem = MenuItemFont::create("Highscores", CC_CALLBACK_1( MainMenuScene::GoToTheScene, this ) );
    auto settingsItem = MenuItemFont::create("Settings", CC_CALLBACK_1( MainMenuScene::GoToTheScene, this ) );
    playItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 50 ) );
    highscoresItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 10 ) );
    settingsItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 40) );
    
    auto menu = Menu::create( playItem, highscoresItem, settingsItem, nullptr );
    menu->setPosition( Point(0, 0) );
    
    this->addChild( menu, 2 );
    
    return true;
}

void MainMenuScene::GoToTheScene( Ref *sender )
{
    auto scene = theScene::createScene();
    
    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
}

void MainMenuScene::Highscores( Ref *sender )
{
//    auto scene = theScene::createScene();
//
//    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
    
    CCLOG("HIGHSCORES");
}

void MainMenuScene::Settings( Ref *sender )
{
//    auto scene = theScene::createScene();
//
//    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
    CCLOG("SETTINGS");
}












