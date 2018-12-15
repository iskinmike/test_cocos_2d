
#include "cocos2d.h"
#include <string>

typedef cocos2d::Sprite area_view;
typedef cocos2d::Sprite field_view;

#ifndef position
typedef cocos2d::Vec2 position;
#endif

enum class area_type {
  rival, player, decks, control, 
  info, battle, environment, active
};

/// Оcуществляет контроль за происходящим на игровом поле
class game_field
{
    struct content_areas{
        area_view* rival;
        area_view* player;
        area_view* decks;
        area_view* control;
        area_view* info;
        area_view* battle;
        area_view* environment;
        area_view* active;
        content_areas();
    } areas;

    field_view* current_field_view;

    void setup_view(area_type type, position pos){
        area_view* view = this->get_view(type);
        if (nullptr == view) return;
        view->setPosition(pos);
        current_field_view->addChild(view, 0);
    }

public:
    game_field();
    ~game_field();

    void set_view(area_view* view, area_type type);
    area_view* get_view(area_type type);

    void init_card_view(position pos);
    field_view* getCurrent_field_view() const;
    void setCurrent_field_view(field_view* value);
};
