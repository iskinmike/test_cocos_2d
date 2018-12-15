#ifndef __TABLE_VIEW_SCENE_H__
#define __TABLE_VIEW_SCENE_H__
/// класс для создания table_view

#include "cocos2d.h"
#include <string>
#include <vector>

using view_size_type = int;
using view_count_type = int;

// Таблца будет следующего вида:
// группа А

struct block_data {
    cocos2d::Sprite* active;
    cocos2d::Sprite* inactive;
    cocos2d::Sprite* hoovered;
    cocos2d::Sprite* background;
    cocos2d::Sprite* frame;
    view_size_type width;
    view_size_type height;
    std::string lable;

    block_data(
        const std::string& lable,
        view_size_type width,
        view_size_type height,
        cocos2d::Sprite* active,
        cocos2d::Sprite* inactive,
        cocos2d::Sprite* hoovered,
        cocos2d::Sprite* background,
        cocos2d::Sprite* frame);
};

class block {
    block_data data;
protected:
    cocos2d::Node* block_view_node;
    cocos2d::Label* lable;
    cocos2d::Node* block_state;
public:

    block(const block_data& data);

    void activate();

    void deactivate();

    void hoovered();

    cocos2d::Node* get_view_node();

    // нужны методы для заполнения блоков
};


class table_view
{
    // У него должно быть поле с размером
    view_size_type width;
    view_size_type height;

    view_size_type cell_width;
    view_size_type cell_height;

    view_count_type cells_count;

public:
    table_view(const std::string& name);
    ~table_view();
};


class group : public block
{
public:
    std::vector<block> blocks;
    group(const block_data& header_data, const std::vector<block>& blocks) : block(header_data), blocks(blocks){}
    ~group(){}
    // нужны методы для заполнения вектора блоков
};


class left_column : public block {
    // всякие свойства определяющие отрисовку границ и прочего
public:
    ~left_column(){}
    std::vector<group> groups;
    left_column(const block_data& data) : block(data){}

    left_column(const block_data& data, const std::vector<group>& groups);
    // нужны методы для заполнения групп
    void setup_groups(const std::vector<group>& groups);

    void setup_pos(float x, float y);

    cocos2d::Node* generate_node_view();
};




#endif // __TABLE_VIEW_SCENE_H__
