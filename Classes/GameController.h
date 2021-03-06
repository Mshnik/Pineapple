//
//  GameController.h
//  PlatformerDemo
//
//  This is the most important class in this demo.  This class manages the gameplay
//  for this demo.  It also handles collision detection. There is not much to do for
//  collisions; our WorldController class takes care of all of that for us.  This
//  controller mainly transforms input into gameplay.
//
//  WARNING: There are a lot of shortcuts in this design that will do not adapt well
//  to data driven design.  This demo has a lot of simplifications to make it a bit
//  easier to see how everything fits together.  However, the model classes and how
//  they are initialized will need to be changed if you add dynamic level loading.
//
//  This file is based on the CS 3152 PhysicsDemo Lab by Don Holden, 2007
//
//  Author: Walker White
//  Version: 1/15/15
//
#ifndef __PF_GAME_CONTROLLER_H__
#define __PF_GAME_CONTROLLER_H__

#include "AbsScreenController.h"
#include "InputController.h"
#include "PauseController.h"
#include "HUDController.h"
#include "LevelModel.h"
#include "BackgroundView.h"
#include "LoseView.h"
#include "WinView.h"
#include "TutorialView.h"
#include "Sounds.h"

// We need a lot of forward references to the classes used by this controller
// These forward declarations are in cocos2d namespace
namespace cocos2d {
    class RootLayer;
    class WorldController;
    class SceneManager;
}

// These forward declarations are in the project
class CollisionController;

using namespace cocos2d;
using namespace std;

#pragma mark -
#pragma mark GameController
/**
 * Instance is a controls the gameplay for the demo.
 *
 * A world has its own objects, assets, and input controller.  Thus this is
 * really a mini-GameEngine in its own right.  The only thing that it does
 * not do is create the scene graph root; that is shared with it by the 
 * game root (which has scaled the scene graph to fix the device with the
 * desired aspect ratio).
 */
class GameController : public AbsScreenController {
protected:    
    /** Reference to the physics root of the scene graph */
    Node* _worldnode;
    /** Reference to the debug root of the scene graph */
    Node* _debugnode;
    /** Reference to the background node */
    Node* _backgroundnode;
    
    /** Visual representation of left and right movement buttons, buttons don't have any function
     *  Just used to easily change between two textures */
    Button* _moveLeftView;
    Button* _moveRightView;
    
    /** The node that is the root of the lose splash screen */
    Node* _loseroot;
    /** Reference to the lose splash screen */
    LoseView* _loseview;
    /** True once the loseview is visible */
    bool _loseViewVisible;
    
    /** The node that is the root of the win splash screen */
    Node* _winroot;
    /** Reference to the win splash screen */
    WinView* _winview;
    /** True once the winview is visible */
    bool _winViewVisible;
    
    /** The node that is the root of the tutorial splash screen */
    Node* _tutorialroot;
    /** Reference to the tutorial splash screens */
    vector<TutorialView*> _tutorialviews;
    
    /** The Box2D world */
    WorldController* _world;

	/** Reference to the splat */
	AnimationNode* _splatCycle;
	/** Current frame of the splatcycle */
	float _splatFrame;
	/** Whether there is a splat on the screen */
	bool _hasSplat;
	/** Size of root */
	Size _rootSize;

	/** Reference to the fridge door */
	PolygonNode* _fridgeDoor;
    
    /** The background view */
    BackgroundView* _background;
    /** Reference to current level */
    LevelModel* _level;
    
    /** The index of this level in the array of levels */
    int _levelIndex;
    /** Name of the level that is currently loaded */
    string _levelKey;
    /** Filename of the level that is currently loaded */
    string _levelFile;
    
    /** Controller for collision handling */
    CollisionController* _collision;
    
    /** Whether or note this game is still active */
    bool _active;
    /** Whether we have completed this "game" */
    bool _complete;
    /** Whether or not debug mode is active */
    bool _debug;
    /** Whether we have failed at this world (and need a reset) */
    bool _failed;
	/** Distance between start of level and left side of screen */
    float _levelOffset;
    /** True if this is reloading */
    bool _isReloading;
    /** True once the autoFF feature has been applied */
    bool _autoFFOn;
    
    /** Mark set to handle more sophisticated collision callbacks */
    unordered_set<b2Fixture*> _sensorFixtures;
    
    /** True when a reset function finishes, false at the end of OnReset() */
    bool _resetInProgress;
    /** True if the ff button was on before a reset */
    bool _ffWasOn;
    
    /** A reference to the blender sound */
    Sound* _blenderSound;
    
#pragma mark Internal Object Management
    /**
     * Lays out the game geography.
     */
    void populate();
    
    /**
     * Immediately adds the object to the physics world
     *
     * Objects have a z-order.  This is the order they are drawn in the scene
     * graph node.  Objects with the different textures should have different
     * z-orders whenever possible.  This will cut down on the amount of drawing done
     *
     * param  obj       The object to add
     * param  zOrder    The drawing order
     *
     * @retain a reference to the obstacle
     */
    void addObstacle(Obstacle* obj, int zOrder);
    
public:
#pragma mark -
#pragma mark Initialization
    /**
     * Initializes the controller contents, and starts the game
     *
     * The constructor does not allocate any objects or memory.  This allows
     * us to have a non-pointer reference to this controller, reducing our
     * memory allocation.  Instead, allocation happens in this method.
     *
     * The game world is scaled so that the screen coordinates do not agree
     * with the Box2d coordinates.  This initializer uses the default scale.
     * 
     * @retain a reference to the root layer
     * @return  true if the controller is initialized properly, false otherwise.
     */
    bool init(Node* root, InputController* input, int levelIndex, string levelKey, string levelFile);

    /**
     * Initializes the controller contents, and starts the game
     *
     * The constructor does not allocate any objects or memory.  This allows
     * us to have a non-pointer reference to this controller, reducing our
     * memory allocation.  Instead, allocation happens in this method.
     *
     * The game world is scaled so that the screen coordinates do not agree
     * with the Box2d coordinates.  The bounds are in terms of the Box2d
     * world, not the screen.
     *
     * @param bounds The game bounds in Box2d coordinates
     * @param scale  The difference between screen and Box2d coordinates
     *
     * @retain a reference to the root layer
     * @return  true if the controller is initialized properly, false otherwise.
     */
    bool init(Node* root, InputController* input, int levelIndex, string levelKey, string levelFile, const Rect& rect);
    
    
#pragma mark -
#pragma mark State Access
    /** Returns the levelindex of the currently playing level */
    int getLevelIndex() { return _levelIndex; }
    
    int getScore() {
        if (_level) { return _level->getKidsRemaining(); }
        else { return 0; }
    }
    
    /**
     * Returns true if the gameplay controller is currently active
     *
     * @return true if the gameplay controller is currently active
     */
    bool isActive( ) const { return _active; }

    /**
     * Returns true once this has been initted 
     */
    bool isInitted() const { return _isInitted; }
    
    /**
     * Returns true if debug mode is active.
     *
     * If true, all objects will display their physics bodies.
     *
     * @return true if debug mode is active.
     */
    bool isDebug( ) const { return _debug; }
    
    /**
     * Sets whether debug mode is active.
     *
     * If true, all objects will display their physics bodies.
     *
     * @param value whether debug mode is active.
     */
    void setDebug(bool value) { _debug = value; _debugnode->setVisible(value); }
    
    /** True if this is fastforwarding */
    bool isFastForwarding() {
        return HUDController::isFastForwarding();
    }
    
    /**
     * Returns true if the level is completed.
     *
     * If true, the level will advance after a countdown
     *
     * @return true if the level is completed.
     */
    bool isComplete( ) const { return _complete; }
    
    /**
     * Sets whether the level is completed.
     *
     * If true, the level will advance after a countdown
     *
     * @param value whether the level is completed.
     */
    void setComplete(bool value);
    
    /**
     * Returns true if the level is failed.
     *
     * If true, the level will reset after a countdown
     *
     * @return true if the level is failed.
     */
    bool isFailure() const { return _failed; }
    
    /**
     * Sets whether the level is failed.
     *
     * If true, the level will reset after a countdown
     *
     * @param value whether the level is failed.
     */
    void setFailure(bool value);
    
    /** Returns true if the autoFF feature is on */
    bool isFF() const { return _autoFFOn; }
    
    /** Turns the auto fast forward feature on or off.
     * Used when will gets to the fridge */
    void setFF(bool value);
    
    float getBlenderVolScale();
    
    
#pragma mark -
#pragma mark Allocation
    /**
     * Creates a new game world with the default values.
     *
     * This constructor does not allocate any objects or start the controller.
     * This allows us to use a controller without a heap pointer.
     */
    GameController();
    
    /**
     * Disposes of all (non-static) resources allocated to this mode.
     *
     * This method is different from dispose() in that it ALSO shuts off any
     * static resources, like the input controller.
     */
    ~GameController();
    
    /**
     * Disposes of all (non-static) resources allocated to this mode.
     */
    void dispose();

    
#pragma mark -
#pragma mark Collision Handling
    
    /**
     * Checks for victory, triggering it if it occurs
     * Specifically, sees if every living child has reached the goal
     *
     * @return true if victory has occurred
     */
    bool checkForVictory();

    
#pragma mark -
#pragma mark Gameplay Handling
    
    void reset() { reset(_levelIndex, _levelKey, _levelFile); }
    
    /**
     * Resets the status of the game so that we can play again.
     *
     * This method disposes of the world and creates a new one.
     */
    void reset(int levelIndex, string levelKey, string levelFile) ;
    
    /** Called after the asynced level reloading finishes.
      * a helper for reset() */
    void onReset();

    /**
     * Executes the core gameplay loop of this world.
     *
     * This method contains the specific update code for this mini-game. It does
     * not handle collisions, as those are managed by the parent class WorldController.
     * This method is called after input is read, but before collisions are resolved.
     * The very last thing that it should do is apply forces to the appropriate objects.
     *
     * @param  delta    Number of seconds since last animation frame
     */
    void update(float dt) override;

	/**
	* Compute offsets for horizontal scrolling.
	*/
	void handleScrolling();

	/**
	* Activate the splat effect when shit hits the fan
	*/
	void activateSplat(Texture2D* image);
    
    /** Overridden version of setTransitionStatus */
    void setTransitionStatus(int status) override {
        AbsScreenController::setTransitionStatus(status);
        if (_blenderSound != nullptr && SoundEngine::getInstance()->isActiveEffect(BLENDER_SOUND) &&
            (status == TRANSITION_TO_EXIT || status == TRANSITION_TO_LEVEL_SELECT || status == TRANSITION_TO_HOME)) {
            SoundEngine::getInstance()->stopEffect(BLENDER_SOUND);
        }
    }

};

#endif /* defined(__PF_GAME_CONTROLLER_H__) */
