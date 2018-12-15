
#include "scenes_handler.hpp"

#include "start_screen.hpp"
#include "HelloWorldScene.h"
#include "library/library_scene.hpp"

USING_NS_CC;

scenes_handler::~scenes_handler(){}

scenes_handler::scenes_handler(): start_game_scene(nullptr),main_menu_scene(nullptr), library_scene(nullptr) {
    director = cocos2d::Director::getInstance();
}

scenes_handler &scenes_handler::instance()
{
    // Not thread safe in vs2013
    static scenes_handler fk;
    return fk;
}

cocos2d::Scene *scenes_handler::get_start_game_scene(){
//    if (nullptr == start_game_scene) {
        start_game_scene = HelloWorld::create();
//    }
    return start_game_scene;
}

cocos2d::Scene *scenes_handler::get_main_menu_scene(){
//    if (nullptr == main_menu_scene) {
        main_menu_scene = start_screen::create();
//    }
    return main_menu_scene;
}

cocos2d::Scene *scenes_handler::get_library_scene(){
//    if (nullptr == library_scene) {
        library_scene = library_scene::create();
//    }
    return library_scene;
}

void scenes_handler::return_to_main_screen(){
//    director->popScene();
//    director->resume();
    director->replaceScene(get_main_menu_scene());
}

void scenes_handler::run_game_scene(){
//    director->pushScene(director->getRunningScene());
    director->replaceScene(get_start_game_scene());
}

void scenes_handler::enter_library_scene(){
//    director->pushScene(director->getRunningScene());
    director->replaceScene(get_library_scene());
}
