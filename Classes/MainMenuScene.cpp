//
//  MainMenuScene.cpp
//  SpaceGame-mobile
//
//  Created by Madji on 17.06.18.
//

#include "MainMenuScene.hpp"
#include "theScene.h"
#include "DEFINITIONS.h"
#include "Highscores.hpp"

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
    
    this->scheduleUpdate();
    
    auto playItem = MenuItemFont::create( "Play", CC_CALLBACK_1( MainMenuScene::GoToTheScene, this ) );
    auto highscoresItem = MenuItemFont::create("Highscores", CC_CALLBACK_1( MainMenuScene::Highscores, this ) );
    auto settingsItem = MenuItemFont::create("Settings", CC_CALLBACK_1( MainMenuScene::Settings, this ) );
    auto exitGame = MenuItemFont::create("Exit", CC_CALLBACK_1(MainMenuScene::ExitGame, this) );
    playItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 80 ) );
    playItem->setColor(Color3B::YELLOW);
    highscoresItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 20 ) );
    settingsItem->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 40) );
    exitGame->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 100) );
    exitGame->setColor(Color3B::RED);
    
    auto menu = Menu::create( playItem, highscoresItem, settingsItem, exitGame, nullptr );
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
    auto scene = Highscores::createScene();
    
    Director::getInstance( )->pushScene( TransitionFade::create( TRANSITION_TIME, scene ) );
    
    CCLOG("HIGHSCORES");
}

void MainMenuScene::Settings( Ref *sender )
{
    //    auto scene = theScene::createScene();
    //
    //    Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
    CCLOG("SETTINGS");
}

void MainMenuScene::ExitGame( Ref *sender )
{
    Director::getInstance()->end();
    exit(TRANSITION_TIME * 3);
}

void MainMenuScene::update(float dt)
{
    bg1->setPositionY(bg1->getPositionY()-1);
    if ((bg1->getPositionY() + bg1->getContentSize().height/2) < 0){
        bg1->setPositionY(bg3->getPositionY() + bg3->getContentSize().height-1);
    }
    
    bg2->setPositionY(bg2->getPositionY()-1);
    if ((bg2->getPositionY() + bg2->getContentSize().height/2) < 0){
        bg2->setPositionY(bg1->getPositionY() + bg1->getContentSize().height-1);
    }
    
    bg3->setPositionY(bg3->getPositionY()-1);
    if ((bg3->getPositionY() + bg3->getContentSize().height/2) < 0){
        bg3->setPositionY(bg2->getPositionY() + bg2->getContentSize().height-1);
    }
}
