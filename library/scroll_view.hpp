#ifndef __SCROLL_VIEW_SCENE_H__
#define __SCROLL_VIEW_SCENE_H__
/// класс для создания table_view

#include "cocos2d.h"
#include <string>
#include <vector>

using view_size_type = int;
using view_count_type = int;


class button {
    cocos2d::MenuItemImage* button_item;
    cocos2d::Node* button_node;

    cocos2d::Sprite* selected;
    cocos2d::Sprite* normal;
    cocos2d::Sprite* disabled;

    cocos2d::ccMenuCallback callback;
    void set_size(){
        width = button_item->getContentSize().width;
        height = button_item->getContentSize().height;
    }
    void load_sprites(const std::string& normal_image,
                      const std::string& selected_image,
                      const std::string& disabled_image){
        selected = cocos2d::Sprite::create(normal_image);
        normal   = cocos2d::Sprite::create(selected_image);
        disabled = cocos2d::Sprite::create(disabled_image);
        button_node->addChild(normal, 1);
    }
//    void setup_event_listener() {
//        auto contactListener = EventListenerPhysicsContact::create();
//            contactListener->onContactBegin = [this] (PhysicsContact& contact) -> bool {
//                auto nodeA = contact.getShapeA()->getBody()->getNode();
//                auto nodeB = contact.getShapeB()->getBody()->getNode();

//                if (nodeA && nodeB) {
//                    if ((nodeA->getTag() == 11) || nodeB->getTag() == 11) {std::cout << "cursor " ; }

//                    std::cout << "contact" << std::endl;
//                }
//                return true;
//            };
//        _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
//    }

public:
    view_size_type width, height;
    button(): button_item(nullptr), width(0), height(0){}
    button(const std::string& lable_text,
           const std::string& normal_image,
           const std::string& selected_image,
           const std::string& disabled_image,
           const cocos2d::ccMenuCallback& callback) : callback(callback) {
        button_item = cocos2d::MenuItemImage::create(normal_image, selected_image, disabled_image, callback);
        button_node = cocos2d::Node::create();
        load_sprites(normal_image, selected_image, disabled_image);
        add_lable(lable_text);
        set_size();
    }
    button(const std::string& lable_text,
           const std::string& normal_image,
           const std::string& selected_image,
           const std::string& disabled_image){
        button_item = cocos2d::MenuItemImage::create(normal_image, selected_image, disabled_image);
        add_lable(lable_text);
        button_node = cocos2d::Node::create();
        load_sprites(normal_image, selected_image, disabled_image);
        set_size();
    }
    button(const std::string& normal_image,
           const std::string& selected_image,
           const std::string& disabled_image){
        button_item = cocos2d::MenuItemImage::create(normal_image, selected_image, disabled_image);
        button_node = cocos2d::Node::create();
        load_sprites(normal_image, selected_image, disabled_image);
        set_size();
    }
    cocos2d::MenuItemImage* get_menu_item(){
        return button_item;
    }

    void add_lable(const std::string& lable_text) {
        if (!lable_text.empty()) {
            auto label = cocos2d::Label::createWithTTF(lable_text, "fonts/Marker Felt.ttf", 24);
            const float up_offset = 5;
            label->setPosition(cocos2d::Vec2(button_item->getContentSize().width/2,
                                    button_item->getContentSize().height - label->getContentSize().height + up_offset));
            button_item->addChild(label, 1);
        }
    }

    void set_callback(const cocos2d::ccMenuCallback& callback){
        button_item->setCallback(callback);
    }

    void add_to(cocos2d::Node* node, int z_pos = 1){
        node->addChild(button_item, z_pos);
    }

    void select(){
        button_node->removeAllChildren();
        button_node->addChild(selected);
    }
    void deselect(){
        button_node->removeAllChildren();
        button_node->addChild(normal);
    }
    void disable(){
        button_node->removeAllChildren();
        button_node->addChild(disabled);
    }

    void on_select() {
        select();
    }
    void on_release() {
        deselect();
    }

    cocos2d::Node* get_item(){
        return button_node;
    }

};

struct scroll_tab_data{
    button up_arrow;
    button down_arrow;
    button left_arrow;
    button right_arrow;

    cocos2d::Sprite* backgrond;
    scroll_tab_data(){}
};

enum class tab_orientation{
    vertical, horizontal
};

class scroll_tab
{
    // спрайты которые будут отвечать за отрисовку scroll_tab
    // спрайты стрелок отправления
    tab_orientation orientation;

    scroll_tab_data data;
    cocos2d::Node* scroll_tab_view_node;


public:
    view_size_type width;
    view_size_type height;
    scroll_tab(scroll_tab_data& data, tab_orientation orientation) : data(data), orientation(orientation) {
        width = data.backgrond->getContentSize().width;
        height = data.backgrond->getContentSize().height;

        scroll_tab_view_node = cocos2d::Node::create();

        int z_level = 1;
        scroll_tab_view_node->addChild(data.backgrond, z_level++);

        switch (orientation){
            case tab_orientation::vertical: {
                height += data.up_arrow.get_item()->getContentSize().height +
                         data.down_arrow.get_item()->getContentSize().height;
                data.up_arrow.get_item()->setPosition(0, height - data.up_arrow.height/2);
                data.down_arrow.get_item()->setPosition(0, data.down_arrow.height/2);
                break;
            }
            case tab_orientation::horizontal: {
                width += data.right_arrow.get_item()->getContentSize().width +
                         data.left_arrow.get_item()->getContentSize().width;
                data.right_arrow.get_item()->setPosition(width - data.right_arrow.width/2, 0);
                data.left_arrow.get_item()->setPosition(data.left_arrow.width/2, 0);
                break;
            }
        }

//        scroll_tab_view_node->getPosition();

        scroll_tab_view_node->setContentSize(cocos2d::Size(width,height));

    }

    cocos2d::Node* get_view_node() {
        return scroll_tab_view_node;
    }

    void setup_up_callback(const cocos2d::ccMenuCallback& callback){
        data.up_arrow.set_callback(callback);
    }
    void setup_down_callback(const cocos2d::ccMenuCallback& callback){
        data.down_arrow.set_callback(callback);
    }
    void setup_right_callback(const cocos2d::ccMenuCallback& callback){
        data.right_arrow.set_callback(callback);
    }
    void setup_left_callback(const cocos2d::ccMenuCallback& callback){
        data.left_arrow.set_callback(callback);
    }

    cocos2d::MenuItemImage* get_up_item(){
        return data.up_arrow.get_menu_item();
    }
    cocos2d::MenuItemImage* get_down_item(){
        return data.down_arrow.get_menu_item();
    }
    cocos2d::MenuItemImage* get_right_item(){
        return data.right_arrow.get_menu_item();
    }
    cocos2d::MenuItemImage* get_left_item(){
        return data.left_arrow.get_menu_item();
    }

    void set_position(float x, float y){
//        scroll_tab_view_node->setPosition(0, 0);
        float origin_x = scroll_tab_view_node->getPositionX();
        float origin_y = scroll_tab_view_node->getPositionY();
        switch (orientation){
            case tab_orientation::vertical: {
                data.up_arrow.get_item()->setPosition(origin_x, origin_y + height - data.up_arrow.height/2);
                data.down_arrow.get_item()->setPosition(origin_x, origin_y + data.down_arrow.height/2);
                break;
            }
            case tab_orientation::horizontal: {
                data.right_arrow.get_item()->setPosition(origin_x + width - data.right_arrow.width/2, origin_y);
                data.left_arrow.get_item()->setPosition(origin_x + data.left_arrow.width/2, origin_y);
                break;
            }
        }
    }
};

class scroll_view
{
    tab_orientation orientation;

    view_size_type visible_area_width;
    view_size_type visible_area_height;

    view_size_type real_width;
    view_size_type real_height;

    scroll_tab tab;
    cocos2d::Node* scroll_view_node;
    cocos2d::Vector<cocos2d::MenuItem *> menu_items;
    cocos2d::Sprite* backgrond;
    void create_menu_items(){
        switch (orientation) {
            case tab_orientation::vertical: {
                menu_items.pushBack(tab.get_up_item());
                menu_items.pushBack(tab.get_down_item());
                break;
            }
            case tab_orientation::horizontal: {
                menu_items.pushBack(tab.get_left_item());
                menu_items.pushBack(tab.get_right_item());
                break;
            }
        }
    }

public:
    scroll_view(int width, int height, tab_orientation orientation, scroll_tab_data& tab_data)
        : orientation(orientation), visible_area_width(width), visible_area_height(height), tab(tab_data, orientation)
    {
        scroll_view_node = cocos2d::Node::create();
        float pos_x = 0;
        float pos_y = 0;
        // add tab
        switch (orientation) {
            case tab_orientation::vertical: {
                real_width = width + tab.width;
                real_height = height;
                pos_x = real_width - tab.width/2;
                pos_y = 0;
                break;
            }
            case tab_orientation::horizontal: {
                real_width = width;
                real_height = height + tab.height;
                pos_x = 0;
                pos_y = tab.height/2;
                break;
            }
        }
        scroll_view_node->setContentSize(cocos2d::Size(real_width, real_height));
        tab.get_view_node()->setPosition(pos_x, pos_y);
        scroll_view_node->addChild(tab.get_view_node(), 2);
    }

    void set_position(float x, float y){
        scroll_view_node->setPosition(x, y);
        tab.set_position(x, y);
    }

    void setup_background(cocos2d::Sprite* backgrond) {
        this->backgrond = backgrond;
        scroll_view_node->addChild(backgrond, 1);
    }

    cocos2d::Node* get_view_node() {
        return scroll_view_node;
    }

    const cocos2d::Vector<cocos2d::MenuItem *> get_menu_items(){
        if (!menu_items.size()) {
            create_menu_items();
        }

        return menu_items;
    }
};

#endif // __SCROLL_VIEW_SCENE_H__
