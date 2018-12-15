#ifndef __LIBRARY_SCENE_H__
#define __LIBRARY_SCENE_H__

#include "cocos/base/CCVector.h"
#include "cocos2d.h"
#include "menu_items/main_menu_items.hpp"

#include "table_view.hpp"
#include "scroll_view.hpp"

class library_scene : public cocos2d::Scene
{
    cocos2d::EventListenerMouse* _mouseListener;
    cocos2d::Vector<cocos2d::MenuItem*> menu_items;

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    cocos2d::MenuItem* get_return_to_main_menu_item();
    void create_menu_items();
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void update(float delta) override;

    // a selector callback
    void return_to_main_menu(cocos2d::Ref* pSender);
//    void menu_select_start_game(cocos2d::Ref* pSender);
    void menu_select_library(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(library_scene);


    const cocos2d::Vector<cocos2d::MenuItem*>& get_menu_items();


};


#endif // __LIBRARY_SCENE_H__
