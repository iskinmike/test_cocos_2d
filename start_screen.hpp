#ifndef __START_SCREEN_SCENE_H__
#define __START_SCREEN_SCENE_H__

#include "cocos/base/CCVector.h"
#include "cocos2d.h"
#include "menu_items/main_menu_items.hpp"

class start_screen : public cocos2d::Scene
{
    cocos2d::EventListenerMouse* _mouseListener;

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;


    cocos2d::MenuItem* get_start_game_item();
    cocos2d::MenuItem* get_close_item();
    cocos2d::MenuItem* get_enter_library_item();
    void create_menu_items();
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void update(float delta) override;

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menu_select_start_game(cocos2d::Ref* pSender);
    void menu_select_library(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(start_screen);

    cocos2d::Vector<cocos2d::MenuItem*> menu_items;

    const cocos2d::Vector<cocos2d::MenuItem*>& get_menu_items();


};


#endif // __START_SCREEN_SCENE_H__
