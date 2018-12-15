#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>




USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

//    cocos2d::extension::TableView* view = cocos2d::extension::TableView::create();
//    auto view_data = view->getDataSource();
//    cocos2d::extension::TableViewDataSource view_data;
//    view_data.
//    view_data->
//    view->setVisible(true);
//    view->setViewSize(cocos2d::Size(100.0f, 100.0f));
//    view->setPosition(Vec2(100,100));
//    this->addChild(view, 1);
    // этот view создается и при 

    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("res/gameboard1.png");
//    if (sprite == nullptr)
//    {
//        problemLoading("'res/gameboard1.png'");
//    }
//    else
//    {
//        // position the sprite on the center of the screen
//        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

//        // add the sprite as a child to this layer
//        this->addChild(sprite, 0);
//    }

//    auto red_cube = Sprite::create("res/red_sqaure.png");
//    auto aqua_cube = Sprite::create("res/aqua_sqaure.png");
//    auto yellow_cube = Sprite::create("res/yellow_sqaure.png");

    objects.create_cube(Vec2(100 + origin.x, 200 + origin.y), "res/aqua_sqaure.png", "aqua");
    objects.create_cube(Vec2(100 + origin.x, 100 + origin.y), "res/red_sqaure.png", "red");
    objects.create_cube(Vec2(100 + origin.x, 300 + origin.y), "res/yellow_sqaure.png", "yellow");

    cursor = objects.getCubes().at(2);
    Rect bounds = cursor->getBoundingBox();
    PhysicsBody* body = PhysicsBody::createBox(bounds.size);
    std::cout << "PhysicsBody* body: " << body << std::endl;
    if (nullptr != body) {
//        body->addMass();
        body->setContactTestBitmask(0xFFFFFFFF);
        body->setDynamic(false);
        cursor->addComponent(body);
    }
    cursor->setTag(11);

    area_view* background_view = area_view::create();
    background_view->setTexture("res/gameboard2.png");
    field.set_view(background_view, area_type::environment);
    field.init_card_view(position(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(field.getCurrent_field_view(), 0);

    card_part* beast_image = card_part::create("res/beast.png");
    beast_image->setScale(0.25,0.25);

    card* first_card = new card("beast");
    first_card->set_part(card_part::create("res/Blank Card Pixel 001_4x.png"), part_type::background);
    first_card->set_part(beast_image, part_type::image);
    first_card->init_card_view();
    beast_image->setPosition(0,40);
    first_card->get_card_view()->setPosition(position(500,200));
    hand.push_back(first_card);
    this->addChild(first_card->get_card_view(), 1);


    card_part* beast_image_2 = card_part::create("res/beast.png");
    beast_image_2->setScale(0.25,0.25);

    card* second_card = new card("beast2");
    second_card->set_part(card_part::create("res/Blank Card Pixel 001_4x.png"), part_type::background);
    second_card->set_part(beast_image_2, part_type::image);
    second_card->init_card_view();
    beast_image->setPosition(0,40);
    second_card->get_card_view()->setPosition(position(700,200));
    hand.push_back(second_card);
    this->addChild(second_card->get_card_view(), 1);

//    if (nullptr != red_cube) {
//        red_cube->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//        this->addChild(red_cube, 1, "red");
//    } else {
//        problemLoading("'res/red_sqaure.png'");
//    }
//    if (nullptr != aqua_cube) {
//        aqua_cube->setPosition(Vec2(100 + origin.x, 200 + origin.y));
//        this->addChild(aqua_cube, 1);
//    } else {
//        problemLoading("'res/aqua_sqaure.png'");
//    }
//    if (nullptr != yellow_cube) {
//        yellow_cube->setPosition(Vec2(100 + origin.x, 300 + origin.y));
//        this->addChild(yellow_cube, 1);
//    } else {
//        problemLoading("'res/yellow_sqaure.png'");
//    }

    setup_objects();

    scheduleUpdateWithPriority(1);

    std::cout << "director dispatcher: " << Director::getInstance()->getEventDispatcher() << std::endl;
    std::cout << "scene dispatcher: " << this->getEventDispatcher() << std::endl;

    _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseMove = [this] (EventMouse* event) {
        static bool flag = false;
        flag = !flag;
//        std::cout << "mouse move: [" << event->getCursorX() << "] : [" << event->getCursorY() << "]" << std::endl;
        if (!flag) return;
//        auto moveTo = MoveTo::create(0.2f, event->getLocation());
        this->cursor->setPosition(event->getCursorX(), event->getCursorY());
    };

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_mouseListener, this);


    auto contactListener = EventListenerPhysicsContact::create();
        contactListener->onContactBegin = [this] (PhysicsContact& contact) -> bool {
            auto nodeA = contact.getShapeA()->getBody()->getNode();
            auto nodeB = contact.getShapeB()->getBody()->getNode();

            if (nodeA && nodeB) {
//                if (nodeA->getTag() == 11) {
//                    nodeB->removeFromParentAndCleanup(true);
//                }
//                else if (nodeB->getTag() == 11) {
//                    nodeA->removeFromParentAndCleanup(true);
//                }
                if ((nodeA->getTag() == 11) || nodeB->getTag() == 11) {std::cout << "cursor " ; }

                std::cout << "contact" << std::endl;
            }
            return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);


    return true;
}

void HelloWorld::update(float delta)
{
    Sprite* red = static_cast<Sprite*> (this->getChildByName("red"));
    if (red != nullptr) {
        float pos_x = red->getPositionX();
        float pos_y = red->getPositionY();
        pos_x++;
        pos_y++;
        red->setPosition(Vec2(pos_x, pos_y));
    } else {
//        std::cout << "nullptr red" << std::endl;
    }

}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::setup_objects(){
    for(auto obj: objects.getCubes()) {
        this->addChild(obj, 1, obj->getName());
        std::cout << "Add obj:" << obj->getName() << std::endl;
    }
}

controled_objects::controled_objects(){}

controled_objects::~controled_objects(){}

void controled_objects::create_cube(const cube_position &pos, const std::string &filename, const std::string &name, int z_order){
    auto tmp = cube::create(filename);
    cubes.push_back(tmp);
    cube* it = cubes[cubes.size()-1];
    it->setName(name);
    it->setPosition(pos);
}

std::vector<cube*> controled_objects::getCubes() const {
    return cubes;
}
