#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include "card.hpp"
#include "game_field.hpp"

typedef cocos2d::Vec2 cube_position;
typedef cocos2d::Sprite cube;

typedef std::vector<card*> card_deck;
typedef std::vector<card*> card_hand;

class controled_objects{
    std::vector<cube*> cubes;
public:
    controled_objects();
    ~controled_objects();
    void create_cube(const cube_position& pos, const std::string& filename, const std::string& name, int z_order = 1);
    std::vector<cube *> getCubes() const;
};


class HelloWorld : public cocos2d::Scene
{
    controled_objects objects;

    card_deck deck;
    std::vector<card*> hand;
    game_field field;
    cocos2d::EventListenerMouse* _mouseListener;
    cube* cursor;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void update(float delta) override;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    void setup_objects();
};


//class cube : public cocos2d::Sprite {
//    int z_order;
//    int id;
//public:
//    cube(const std::string& filename) : cocos2d::Sprite(filename){}
//    void set_z_order(int order){
//        z_order = order;
//    }
//    int get_z_order(){
//        return z_order;
//    }

//    int getId() const;
//    void setId(int value);
//};







#endif // __HELLOWORLD_SCENE_H__
