//
//  Highscores.cpp
//  SpaceGame-mobile
//
//  Created by Madji on 18.06.18.
//

#include "Highscores.hpp"
#include "theScene.h"
#include "DEFINITIONS.h"

USING_NS_CC;

Scene* Highscores::createScene()
{
    auto scene = Scene::create();
    
    auto layer = Highscores::create();
    
    scene->addChild(layer);
    
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Highscores::init()
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
    
    // TODO: to fix total point counter (all pushed enemy - all clean enemy)
    
    this->scheduleUpdate();
    
    int scorePrint = (int)(theScene::GetCountScorePrint());
    int enemyPrint = (int)(theScene::GetCountEnemyPrint());
    double successRate = (scorePrint / (enemyPrint * 0.1)) * 10;

    __String *tempScore = __String::createWithFormat("Current Score %05d", scorePrint);
    scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf" , visibleSize.height * SCORE_FONT_SIZE);
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100));

    this->addChild( scoreLabel, 1000 );
    
    __String *tempSuccessRate = __String::createWithFormat("Shooting Sccuracy %.0f %%", successRate);
    scoreLabe2 = Label::createWithTTF(tempSuccessRate->getCString(), "fonts/Marker Felt.ttf" , visibleSize.height * SCORE_FONT_SIZE);
    scoreLabe2->setColor(Color3B::WHITE);
    scoreLabe2->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 30));

    this->addChild( scoreLabe2, 1000 );
   
    auto goBack = MenuItemFont::create("Go Back", CC_CALLBACK_1( Highscores::GoBack, this ));
    goBack->setFontSize(visibleSize.height * SCORE_FONT_SIZE);
    goBack->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 40) );
    
    auto menu = Menu::create( goBack, nullptr );
    menu->setPosition( Point(0, 0) );
    
    this->addChild( menu, 2 );
    
    return true;
}


void Highscores::GoBack( Ref *sender )
{
    Director::getInstance( )->popScene(  );
}

void Highscores::update(float dt)
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

