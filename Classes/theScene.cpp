#include "theScene.h"
#include "SimpleAudioEngine.h"
#include "DEFINITIONS.h"
#include "MainMenuScene.hpp"
#include "PauseResumeMenu.hpp"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace ui;

int theScene::score = 0;
int theScene::countRanger = 1;
int theScene::countEnemy = 0;
int theScene::countEnemyToPrint = 0;
int theScene::countScoreToPrint = 0;

Scene* theScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    scene->getPhysicsWorld()->setGravity(Vect(0,0));

    auto layer = theScene::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld() );

    scene->addChild(layer);

    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool theScene::init()
{
    // тук е променено заради physic world -> Scene to Layer
    if ( !Layer::init() )
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
    
    // create ranger
    ranger = Ranger::createRanger(this);
    this->addChild(ranger, 3);
    
    // create enemy
    this->schedule(schedule_selector(theScene::pushEnemy), Enemy::delayEnemy);
    
    // collision detector
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(theScene::onContactBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    // create extra rangers
    extraRangers();
    
    // print score
    printScore();
    
    // menu button
    pauseButton();
 
    return true;
}

void theScene::extraRangers()
{
    rr1 = Sprite::create("ranger.png");
    rr2 = Sprite::create("ranger.png");
    rr3 = Sprite::create("ranger.png");
    rr1->setPosition(Vec2(visibleSize.width + origin.x - visibleSize.width / 15, visibleSize.height + origin.y - visibleSize.height / 30));
    rr2->setPosition(Vec2(rr1->getPositionX() - (rr1->getContentSize().width / 1), visibleSize.height + origin.y - visibleSize.height / 30));
    rr3->setPosition(Vec2(rr2->getPositionX() - (rr2->getContentSize().width / 1), visibleSize.height + origin.y - visibleSize.height / 30));
    rr1->setScale(0.7);
    rr2->setScale(0.7);
    rr3->setScale(0.7);
    rr1->setVisible(true);
    rr2->setVisible(true);
    rr3->setVisible(true);
    this->addChild(rr1, 2);
    this->addChild(rr2, 2);
    this->addChild(rr3, 2);
    
}

void theScene::printScore()
{
    __String *tempScore = __String::createWithFormat("%05d", score);
    scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf" , visibleSize.height * SCORE_FONT_SIZE);
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(Point( origin.x + visibleSize.width / 10, visibleSize.height + origin.y - visibleSize.height / 30));
    
    this->addChild( scoreLabel, 10000 );
}

void theScene::pauseButton()
{
    auto menuButton = Button::create("pauseButton.png");
    menuButton->setScale(0.5);
    menuButton->setPosition(Point(origin.x + visibleSize.width / 20, visibleSize.height + origin.y - visibleSize.height / 15));
    menuButton->addTouchEventListener([&](Ref *pSender, Widget::TouchEventType type){
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                countEnemyToPrint = countEnemy;
                countScoreToPrint = score;
                auto scene = PauseResumeMenu::createScene();
                Director::getInstance( )->pushScene( TransitionFade::create( TRANSITION_TIME, scene ) );
                break;
//            case cocos2d::ui::Widget::TouchEventType::MOVED:
//                <#code#>
//                break;
//            case cocos2d::ui::Widget::TouchEventType::ENDED:
//                <#code#>
//                break;
//            case cocos2d::ui::Widget::TouchEventType::CANCELED:
//                <#code#>
//                break;
        }
    });
    
    this->addChild(menuButton, 4);
}

void theScene::update(float dt)
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

void theScene::pushEnemy(float dt)
{
    auto callEnemy = CallFunc::create([&] (){
        enemy = Enemy::createEnemy(this);
    });
    
    countEnemy++;
    
    this->runAction(callEnemy);
}

bool theScene::onContactBegan(PhysicsContact &contact)
{
    auto nodeA = (Sprite*)contact.getShapeA()->getBody()->getNode();
    auto nodeB = (Sprite*)contact.getShapeB()->getBody()->getNode();
    
    // TODO: change the way to calculate score when two shoot contact with same enemy
//    score++;
    score = countEnemy - Enemy::countCleanEnemy;
    
    if ((nodeA->getTag() == 2 && nodeB->getTag() == 1) ||
        (nodeA->getTag() == 1 && nodeB->getTag() == 2))
    {
        // Kill ranger
        nodeA->removeFromParent();
        nodeB->removeFromParent();
        
        countRanger--;
        
        if(GetCountRanger() == 2 ){
            rr1->setVisible(false);
            auto newRanger = Ranger::createRanger(this);
            this->addChild(newRanger, 3);
        }
        else if(GetCountRanger() == 1 ){
            rr2->setVisible(false);
            auto newRanger = Ranger::createRanger(this);
            this->addChild(newRanger, 3);
        }
        else if(GetCountRanger() == 0 ){
            rr3->setVisible(false);
            countRanger = 1;
            auto sceneTwo = MainMenuScene::createScene();
            Director::getInstance()->replaceScene( TransitionFade::create( TRANSITION_TIME, sceneTwo ));
            countEnemyToPrint = countEnemy;
            countScoreToPrint = score;
            score = 0;
            countEnemy = 0;
        }
        
        Enemy::countCleanEnemy = 0;
    }
    
    if ((nodeA->getTag() == 2 && nodeB->getTag() == 3) ||
        (nodeA->getTag() == 3 && nodeB->getTag() == 2))
    {
        // Kill enemy
        nodeA->removeFromParent();
        nodeB->removeFromParent();

        __String *tempScore = __String::createWithFormat("%05d", score);
        scoreLabel->setString(tempScore->getCString());
    }

    return true;
}
