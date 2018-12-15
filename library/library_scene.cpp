
#include "library_scene.hpp"
#include "engine_helper/scenes_handler.hpp"

//#include "cocos/ui/CocosGUI.h"
//#include "extensions/cocos-ext.h"
#include "extensions/GUI/CCScrollView/CCScrollView.h"


USING_NS_CC;


namespace  {
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

} // namespace



cocos2d::Scene *library_scene::createScene(){
    return library_scene::create();
}


void library_scene::update(float delta) {
    // implement update code
}


void library_scene::return_to_main_menu(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
//    Director::getInstance()->end();
    scenes_handler::instance().return_to_main_screen();
}


MenuItem *library_scene::get_return_to_main_menu_item(){
    auto return_to_main_menu_item = cocos2d::MenuItemImage::create(
                "res/menu_items/menu_tem_1.png",
                "res/menu_items/menu_tem_2.png",
                CC_CALLBACK_1(library_scene::return_to_main_menu, this));

    if (nullptr != return_to_main_menu_item) {
        float x = origin.x + visibleSize.width - return_to_main_menu_item->getContentSize().width/2;
        float y = origin.y + return_to_main_menu_item->getContentSize().height/2;
        return_to_main_menu_item->setPosition(cocos2d::Vec2(x,y));
    }

    auto label = cocos2d::Label::createWithTTF("Return", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        const float up_offset = 5;
        label->setPosition(Vec2(origin.x + return_to_main_menu_item->getContentSize().width/2,
                                origin.y + return_to_main_menu_item->getContentSize().height - label->getContentSize().height + up_offset));

        // add the label as a child to this layer
        return_to_main_menu_item->addChild(label, 1);
    }

    return return_to_main_menu_item;
}


void library_scene::create_menu_items() {
    menu_items.pushBack(get_return_to_main_menu_item());
}

const cocos2d::Vector<MenuItem *> &library_scene::get_menu_items(){
    if (!menu_items.size()) {
        create_menu_items();
    }

    return menu_items;
}

bool library_scene::init() {
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }


    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    // add a "close" icon to exit the progress. it's an autorelease object

    // create menu, it's an autorelease object
    auto menu = Menu::createWithArray(get_menu_items());
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
    // добавляем левую колонку
    // сначала надо создать необходимые спрайты.
    auto bg_sprite = cocos2d::Sprite::create(std::string{"res/library/left_column_bg.png"});
    auto frame_sprite = cocos2d::Sprite::create("res/library/left_column_frame.png");

    block_data data(
        "Effects",
        bg_sprite->getContentSize().width,
        bg_sprite->getContentSize().height,
        cocos2d::Sprite::create(), cocos2d::Sprite::create(), cocos2d::Sprite::create(),
        bg_sprite, frame_sprite);

    left_column column(data);
    column.setup_pos(origin.x + bg_sprite->getContentSize().width/2, visibleSize.height/2);

    block_data header_data(
                "header",
                bg_sprite->getContentSize().width,
                20.0,
                cocos2d::Sprite::create(), cocos2d::Sprite::create(), cocos2d::Sprite::create(),
                bg_sprite, frame_sprite);
    block_data block1(
                "block1",
                bg_sprite->getContentSize().width,
                20.0,
                cocos2d::Sprite::create(), cocos2d::Sprite::create(), cocos2d::Sprite::create(),
                bg_sprite, frame_sprite);
    std::vector<block> blocks;
    blocks.push_back(block1);
    std::vector<group> groups;
    group group_one(header_data, blocks);
    groups.push_back(group_one);
    column.setup_groups(groups);
//    auto scroll_view = cocos2d::extension::ScrollView::create(column.get_view_node()->getContentSize());
//    scroll_view->addChild(column.get_view_node(), 1);
//    scroll_view->setPosition(400,400);
//    scroll_view->setVisible(true);
    this->addChild(column.get_view_node(), 1);

    scroll_tab_data tab_data;
    tab_data.backgrond = cocos2d::Sprite::create("res/library/scroll_tab/vertical_bg.png");
    tab_data.up_arrow = button("res/library/scroll_tab/up_arrow_inactive.png",
                               "res/library/scroll_tab/up_arrow_inactive.png",
//                               "res/library/scroll_tab/up_arrow_active.png",
                               "res/library/scroll_tab/up_arrow_inactive.png");

    tab_data.down_arrow = button("res/library/scroll_tab/down_arrow_inactive.png",
                                 "res/library/scroll_tab/down_arrow_inactive.png",
//                                 "res/library/scroll_tab/down_arrow_active.png",
                                 "res/library/scroll_tab/down_arrow_inactive.png");

    scroll_view test_scroll(200, 200, tab_orientation::vertical, tab_data);
//    test_scroll.get_view_node()->setPosition(500,500);
    test_scroll.setup_background(cocos2d::Sprite::create("res/library/left_column_bg.png"));
    test_scroll.set_position(800,500);
    auto scroll_menu = Menu::createWithArray(test_scroll.get_menu_items());
    this->addChild(scroll_menu, 5);
    this->addChild(test_scroll.get_view_node(), 1);

    return true;
}
