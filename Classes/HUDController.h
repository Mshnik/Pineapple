//
//  HUDController.h
//  Pineapple
//
//

#ifndef HUDController_h
#define HUDController_h

#include <stdio.h>
#include <cornell.h>
#include "ui/CocosGUI.h"
#include "Const.h"
#include "Texture.h"
#include "InputController.h"
#include "AbsScreenController.h"


#define         CHILDREN_STATUS_HORIZ_POS_RATIO  0
#define         PROGRESS_BAR_HORIZ_POS_RATIO     .15
#define         SOUND_BUTTON_HORIZ_POS_RATIO     .85
#define         PAUSE_BUTTON_HORIZ_POS_RATIO     .925

// singleton class
using namespace cocos2d;
using namespace cocos2d::ui;

/** Both controller and view for the pause screen, this is simple enough that they do not need
 *  to be separated.
 *  This is a singleton class, the window controller for the entire game
 */
class HUDController {
public:
    // add nodes to rootNode for the hud
    static void addHUD() {
        if (HUD_CONTROLLER) {
            HUD_CONTROLLER->_rootNode->addChild(HUD_CONTROLLER->_hudNode);
        } else {
            cout << "HUD CONTROLLER IS NULL\n";
        }
    }
    
    // remove nodes to rootNode for the hud
    static void removeHUD() {
        HUD_CONTROLLER->_rootNode->removeChild(HUD_CONTROLLER->_hudNode);
    }
    
    static void init(AbsScreenController* gameController, Node* worldNode, SceneManager* assets, Node* root, InputController* input);
    
    static void update() {
        // update children status icon
        // update progress bar
    }
    
    static void create() {
        if (!HUD_CONTROLLER) {
            HUD_CONTROLLER = new HUDController();
        }
    }
    
    static void release() {
        if (HUD_CONTROLLER) {
            HUD_CONTROLLER->~HUDController();
        }
    }
    
    
private:
    HUDController() { }
    ~HUDController() {
        _hudNode->release();
        // release children status nodes
        // release progress bar nodes
        // release sound node
        // release pause node
    }
    
    // static reference to singleton
    static HUDController* HUD_CONTROLLER;
    InputController* _inputController = nullptr;
    
    // reference to worldNode
    Node* _rootNode = nullptr;
    Node* _hudNode = nullptr;
    Vec2 _screenSize;
    
    /** Reference to the game controller this is pausing for */
    AbsScreenController* _gameController;
        
};

#endif /* HUDController_h */