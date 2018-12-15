
#include "table_view.hpp"
//#include <cocos2d/UIScrollView.h>


left_column::left_column(const block_data &data, const std::vector<group> &groups) : block{data}{
    setup_groups(groups);
}

void left_column::setup_groups(const std::vector<group> &groups) {
    this->groups = groups;
}

void left_column::setup_pos(float x, float y){
    // block_view_node - основная нода
    block_view_node->setPosition(x,y);
}

cocos2d::Node *left_column::generate_node_view(){
    cocos2d::Node* node = cocos2d::Node::create();

    node->addChild(get_view_node());
    return node;
}

block_data::block_data(const std::string &lable, view_size_type width, view_size_type height, cocos2d::Sprite *active, cocos2d::Sprite *inactive, cocos2d::Sprite *hoovered, cocos2d::Sprite *background, cocos2d::Sprite *frame)
    : active(active), inactive(inactive), hoovered(hoovered), background(background), frame(frame), width(width), height(height), lable(lable){}

block::block(const block_data &data)
    : data(data){
    block_view_node = cocos2d::Node::create();
    block_state = cocos2d::Node::create();
    block_state->addChild(data.inactive, 1);
    lable = cocos2d::Label::createWithTTF(data.lable, "fonts/Marker Felt.ttf", 24);
    const float frame_offset = 30;
    lable->setPosition(0/*frame_offset + lable->getContentSize().width/2*/,
                       data.height/2 - frame_offset - lable->getContentSize().height/2);
    int z_level = 1;
    block_view_node->addChild(data.background, z_level++);
    block_view_node->addChild(data.frame, z_level++);
    block_view_node->addChild(lable, z_level++);
    block_view_node->addChild(block_state, z_level++);
}

void block::activate() {
    block_state->removeAllChildrenWithCleanup(true);
    block_state->addChild(data.active, 1);
}

void block::deactivate() {
    block_state->removeAllChildrenWithCleanup(true);
    block_state->addChild(data.inactive, 1);
}

void block::hoovered() {
    block_state->removeAllChildrenWithCleanup(true);
    block_state->addChild(data.hoovered, 1);
}

cocos2d::Node *block::get_view_node(){
    return block_view_node;
}
