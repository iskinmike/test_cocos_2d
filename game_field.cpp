#include "game_field.hpp"

game_field::content_areas::content_areas():
    rival(nullptr),
    player(nullptr),
    decks(nullptr),
    control(nullptr),
    info(nullptr),
    battle(nullptr),
    environment(nullptr),
    active(nullptr) {}

field_view* game_field::getCurrent_field_view() const
{
    return current_field_view;
}

void game_field::setCurrent_field_view(field_view* value)
{
    current_field_view = value;
}

game_field::game_field(){}

game_field::~game_field(){}

void game_field::set_view(area_view* view, area_type type){
    switch (type){
    case area_type::rival:       { areas.rival = view;       break; }
    case area_type::player:      { areas.player = view;      break; }
    case area_type::decks:       { areas.decks = view;       break; }
    case area_type::control:     { areas.control = view;     break; }
    case area_type::info:        { areas.info = view;        break; }
    case area_type::battle:      { areas.battle = view;      break; }
    case area_type::environment: { areas.environment = view; break; }
    case area_type::active:      { areas.active = view;      break; }
    }
}

area_view*game_field::get_view(area_type type){
    switch (type){
    case area_type::rival:       { return areas.rival;       }
    case area_type::player:      { return areas.player;      }
    case area_type::decks:       { return areas.decks;       }
    case area_type::control:     { return areas.control;     }
    case area_type::info:        { return areas.info;        }
    case area_type::battle:      { return areas.battle;      }
    case area_type::environment: { return areas.environment; }
    case area_type::active:      { return areas.active;      }
    default: {return nullptr;}
    }
}

void game_field::init_card_view(position pos){
    current_field_view = field_view::create();
    current_field_view->setPosition(pos);
    setup_view(area_type::rival,       position(0,0) );
    setup_view(area_type::player,      position(0,0) );
    setup_view(area_type::decks,       position(0,0) );
    setup_view(area_type::control,     position(0,0) );
    setup_view(area_type::info,        position(0,0) );
    setup_view(area_type::battle,      position(0,0) );
    setup_view(area_type::environment, position(0,0) );
    setup_view(area_type::active,      position(0,0) );
}
