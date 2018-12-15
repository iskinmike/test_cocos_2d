
#include "card.hpp"
#include <iostream>


using namespace cocos2d;


std::string card::getName() const
{
    return name;
}

void card::setName(const std::string &value)
{
    name = value;
}

std::string card::getDisplayed_text() const
{
    return displayed_text;
}

void card::setDisplayed_text(const std::string &value)
{
    displayed_text = value;
}

void card::setup_part(part_type type, card_position pos){
    card_part* part = this->get_part(type);
    if (nullptr == part) return;
    part->setPosition(pos);
    current_card_view->addChild(part, 0);
}

card::card(const std::string &name): name(name), current_card_view(nullptr) {


}

void card::test(){

    //    cocos2d::Sprite* test = cocos2d::Sprite::create();

    //    test->addChild();


}

void card::set_part(card_part *part, part_type type){
    switch (type){
    case part_type::border:              { sprites.border = part;              break; }
    case part_type::image:               { sprites.image = part;               break; }
    case part_type::name:                { sprites.name = part;                break; }
    case part_type::type:                { sprites.type = part;                break; }
    case part_type::symbol_left_top:     { sprites.symbol_left_top = part;     break; }
    case part_type::symbol_right_top:    { sprites.symbol_right_top = part;    break; }
    case part_type::symbol_left_bottom:  { sprites.symbol_left_bottom = part;  break; }
    case part_type::symbol_right_bottom: { sprites.symbol_right_bottom = part; break; }
    case part_type::background:          { sprites.background = part;          break; }
    case part_type::text_area:           { sprites.text_area = part;           break; }
    case part_type::keywords:            { sprites.keywords = part;            break; }
    }
}

card_part *card::get_part(part_type type){
    switch (type){
    case part_type::border:              { return sprites.border;              }
    case part_type::image:               { return sprites.image;               }
    case part_type::name:                { return sprites.name;                }
    case part_type::type:                { return sprites.type;                }
    case part_type::symbol_left_top:     { return sprites.symbol_left_top;     }
    case part_type::symbol_right_top:    { return sprites.symbol_right_top;    }
    case part_type::symbol_left_bottom:  { return sprites.symbol_left_bottom;  }
    case part_type::symbol_right_bottom: { return sprites.symbol_right_bottom; }
    case part_type::background:          { return sprites.background;          }
    case part_type::text_area:           { return sprites.text_area;           }
    case part_type::keywords:            { return sprites.keywords;            }
    default: {return nullptr;}
    }
}

void card::init_card_view(){
    current_card_view = card_view::create();
    setup_part(part_type::background,          card_position(0,0) );
    setup_part(part_type::image,               card_position(0,0) );
    setup_part(part_type::text_area,           card_position(0,0) );
    setup_part(part_type::border,              card_position(0,0) );
    setup_part(part_type::name,                card_position(0,0) );
    setup_part(part_type::type,                card_position(0,0) );
    setup_part(part_type::text_area,           card_position(0,0) );
    setup_part(part_type::keywords,            card_position(0,0) );
    setup_part(part_type::symbol_left_top,     card_position(0,0) );
    setup_part(part_type::symbol_right_top,    card_position(0,0) );
    setup_part(part_type::symbol_left_bottom,  card_position(0,0) );
    setup_part(part_type::symbol_right_bottom, card_position(0,0) );

    _mouseListener = EventListenerMouse::create();
//    _mouseListener->
//    _mouseListener->onMouseMove = [] (EventMouse* event) {
//        std::cout << "mouse move: [" << event->getCursorX() << "] : [" << event->getCursorY() << "]" << std::endl;
//    };
    _mouseListener->onMouseUp = [] (EventMouse* event) {
        Node* targ = event->getCurrentTarget();
        Vec2 loc = event->getLocation();
        Vec2 loc_view = event->getLocationInView();
        std::cout << "mouse up: [" << event->getCursorX() << "] : [" << event->getCursorY() << "]" << std::endl;
        std::cout << "targ: [" << targ->getName() << "]" << std::endl;
        std::cout << "targp: [" << targ << "]" << std::endl;
        std::cout << "loc: [" << loc.x << "] : [" << loc.y << "]" << std::endl;
        std::cout << "loc_view: [" << loc_view.x << "] : [" << loc_view.y << "]" << std::endl;
    };
//    _mouseListener->onMouseDown = CC_CALLBACK_1(MouseTest::onMouseDown, this);
//    _mouseListener->onMouseScroll = [] (EventMouse* event) {
//        std::cout << "mouse up: [" << event->getCursorX() << "] : [" << event->getCursorY() << "]" << std::endl;
//    };

//    std::cout << "dispatcher: " << dispatcher << std::endl;
    EventDispatcher* dispatcher = current_card_view->getEventDispatcher();//new EventDispatcher();//Director::getInstance()->getEventDispatcher();
    std::cout << "dispatcher: " << dispatcher << std::endl;
    std::cout << "target_node: " << current_card_view << std::endl;
    current_card_view->setName(this->name);
    std::cout << "target_node name: " << current_card_view->getName() << std::endl;
    std::cout << "ListenerID: " << _mouseListener->LISTENER_ID << std::endl;

//    if (nullptr != dispatcher) {
    dispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, current_card_view);

    Rect bounds = current_card_view->getBoundingBox();
    PhysicsBody* body = PhysicsBody::createBox(bounds.size);
    std::cout << "PhysicsBody* body: " << body << std::endl;
    if (nullptr != body) {
        body->setDynamic(false);
        body->setContactTestBitmask(0xFFFFFFFF);
        current_card_view->addComponent(body);
    }
//    dispatcher->setEnabled(true);
//    first_card->get_card_view()->setEventDispatcher(dispatcher);
//    background_view->setEventDispatcher(dispatcher);
//    std::cout << "nullptr red" << std::endl;
//    } else {

//    }

}

card_view*card::get_card_view(){
    return current_card_view;
}

card::content_sprites::content_sprites() :
    border(nullptr),
    image(nullptr),
    name(nullptr),
    type(nullptr),
    symbol_left_top(nullptr),
    symbol_right_top(nullptr),
    symbol_left_bottom(nullptr),
    symbol_right_bottom(nullptr),
    background(nullptr),
    text_area(nullptr),
    keywords(nullptr) {}
