#include "start_screen.hpp"

#include "SimpleAudioEngine.h"
#include <iostream>

#include "cocos/ui/CocosGUI.h"

#include "engine_helper/scenes_handler.hpp"

USING_NS_CC;


namespace  {
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

} // namespace


cocos2d::Scene *start_screen::createScene(){
    return start_screen::create();
}


void start_screen::update(float delta) {
    // implement update code
    delta++;
}

void start_screen::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void start_screen::menu_select_start_game(Ref *pSender){
//    auto director = Director::getInstance();
//    director->pushScene(this);
    scenes_handler::instance().run_game_scene();
}

void start_screen::menu_select_library(Ref *pSender){
//    auto director = Director::getInstance();
     scenes_handler::instance().enter_library_scene();
}


MenuItem *start_screen::get_close_item(){
    auto closeItem = cocos2d::MenuItemImage::create(
                "CloseNormal.png",
                "CloseSelected.png",
                CC_CALLBACK_1(start_screen::menuCloseCallback, this));

    if (closeItem == nullptr ||
            closeItem->getContentSize().width <= 0 ||
            closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(cocos2d::Vec2(x,y));
    }
    return closeItem;
}

MenuItem *start_screen::get_start_game_item(){
    auto start_game_item = cocos2d::MenuItemImage::create(
                // menu_tem_1.png  menu_tem_2.png
                "res/menu_items/menu_tem_1.png",
                "res/menu_items/menu_tem_2.png",
                CC_CALLBACK_1(start_screen::menu_select_start_game, this));

    if (nullptr != start_game_item) {
        const float start_item_offset = 60;
        float x = origin.x + visibleSize.width/2 - start_game_item->getContentSize().width/2;
        float y = origin.y + visibleSize.height/2 + start_game_item->getContentSize().height/2 + start_item_offset;
        start_game_item->setPosition(cocos2d::Vec2(x,y));
    }

    auto label = Label::createWithTTF("Start", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        const float up_offset = 5;
        label->setPosition(Vec2(origin.x + start_game_item->getContentSize().width/2,
                                origin.y + start_game_item->getContentSize().height - label->getContentSize().height + up_offset));

        // add the label as a child to this layer
        start_game_item->addChild(label, 1);
    }

    return start_game_item;
}

MenuItem *start_screen::get_enter_library_item(){
    auto start_game_item = cocos2d::MenuItemImage::create(
                // menu_tem_1.png  menu_tem_2.png
                "res/menu_items/menu_tem_1.png",
                "res/menu_items/menu_tem_2.png",
                CC_CALLBACK_1(start_screen::menu_select_library, this));

    if (nullptr != start_game_item) {
        const float start_item_offset = 0;
        float x = origin.x + visibleSize.width/2 - start_game_item->getContentSize().width/2;
        float y = origin.y + visibleSize.height/2 + start_game_item->getContentSize().height/2 + start_item_offset;
        start_game_item->setPosition(cocos2d::Vec2(x,y));
    }

    auto label = cocos2d::Label::createWithTTF("Enter Library", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        const float up_offset = 5;
        label->setPosition(Vec2(origin.x + start_game_item->getContentSize().width/2,
                                origin.y + start_game_item->getContentSize().height - label->getContentSize().height + up_offset));

        // add the label as a child to this layer
        start_game_item->addChild(label, 1);
    }

    return start_game_item;
}


void start_screen::create_menu_items() {
    menu_items.pushBack(get_close_item());
    menu_items.pushBack(get_start_game_item());
    menu_items.pushBack(get_enter_library_item());
}

const cocos2d::Vector<MenuItem *> &start_screen::get_menu_items(){
    if (!menu_items.size()) {
        create_menu_items();
    }

    return menu_items;
}


bool start_screen::init() {
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }


    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    // add a "close" icon to exit the progress. it's an autorelease object

    // create menu, it's an autorelease object
    auto menu = Menu::createWithArray(get_menu_items());
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add menu images

    return true;
}
