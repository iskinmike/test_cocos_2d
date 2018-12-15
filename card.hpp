
/// класс для создания карты
/// Может быть и хуже для скорости написания кода, но лучше для понимания.
/// Сделаем следующую вещь
///
/// Класс будет хранить спрайты, которые будут составлять карту.
/// 1. Рамка
/// 2. Изображение
/// 3. Имя
/// 4. Подтип
/// 5. Символ в левом верхнем углу
/// 6. Символ в правом верхнем углу
/// 7. Символ в левом нижнем углу
/// 8. Символ в правом нижнем углу
/// 9. Бэкграунд
/// 10. Текст карты
/// 11. Ключевые слова карты

#include "cocos2d.h"
#include <string>

typedef cocos2d::Sprite card_part;
typedef cocos2d::Sprite card_view;
typedef cocos2d::Vec2 card_position;

enum class part_type{
    border, image, name, type,
    symbol_left_top, symbol_right_top,
    symbol_left_bottom, symbol_right_bottom,
    background, text_area, keywords
};

class card
{
    struct content_sprites{
        card_part* border;
        card_part* image;
        card_part* name;
        card_part* type;
        card_part* symbol_left_top;
        card_part* symbol_right_top;
        card_part* symbol_left_bottom;
        card_part* symbol_right_bottom;
        card_part* background;
        card_part* text_area;
        card_part* keywords;
        content_sprites();
    } sprites;

    cocos2d::EventListenerMouse* _mouseListener;

    std::string name;
    std::string displayed_text;
    card_view* current_card_view;

    void setup_part(part_type type, card_position pos);
public:
    card(const std::string& name);
    ~card();

    void test();

    void set_part(card_part* part, part_type type);
    card_part* get_part(part_type type);

    void init_card_view();
    card_view* get_card_view();
  
    std::string getName() const;
    void setName(const std::string &value);
    std::string getDisplayed_text() const;
    void setDisplayed_text(const std::string &value);
};
