
#ifndef SCENES_HANDLER_HPP
#define SCENES_HANDLER_HPP

#include <memory>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <vector>

#include "cocos2d.h"

// Try to do it as Meyerce's Singletone [https://ru.stackoverflow.com/questions/327136/singleton-%D0%B8-%D1%80%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D1%8F]
class scenes_handler
{
    std::mutex cond_mtx;
    struct sync_waiter {
        std::atomic_bool flag;
        std::condition_variable cond;
    };

    std::mutex mtx;

    cocos2d::Scene* start_game_scene;
    cocos2d::Scene* main_menu_scene;
    cocos2d::Scene* library_scene;

    cocos2d::Director* director;

    std::vector<sync_waiter*> sync_array;
    ~scenes_handler();
    scenes_handler();
public:
    static scenes_handler& instance();
    scenes_handler(scenes_handler const&) = delete;
    scenes_handler& operator= (scenes_handler const&) = delete;

    // метод регистрации сцены начала игры
    cocos2d::Scene* get_start_game_scene();
    // метод регистрации сцены входа в библиотеку
    cocos2d::Scene* get_main_menu_scene();
    cocos2d::Scene* get_library_scene();

    void return_to_main_screen();
    void run_game_scene();
    void enter_library_scene();

};

#endif  /* SCENES_HANDLER_HPP */
