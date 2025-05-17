#include <Ogre.h>
#include <Bites/OgreApplicationContext.h>
#include <Bites/OgreInput.h>
#include <iostream>

// This class handles keyboard input events
class KeyHandler : public OgreBites::InputListener {
public:
    // Called when a key is pressed
    bool keyPressed(const OgreBites::KeyboardEvent& evt) override
    {
        // If ESC key is pressed, signal Ogre to end rendering (close app)
        if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
        {
            Ogre::Root::getSingleton().queueEndRendering();
        }
        return true; // event handled
    }
};

// Main application class derived from Ogre's ApplicationContext
class BasicApp : public OgreBites::ApplicationContext {
public:
    BasicApp() : OgreBites::ApplicationContext("The Worst Game") {}

    // Keep an instance of the input handler as a member variable
    KeyHandler keyHandler;

    // Setup method is called once Ogre is initialized
    void setup() override {
        // Call base setup to initialize basic stuff
        OgreBites::ApplicationContext::setup();

        // Get the Ogre root object (main engine controller)
        Ogre::Root* root = getRoot();

        // Create a SceneManager to handle objects and scene hierarchy
        Ogre::SceneManager* scnMgr = root->createSceneManager();

        // Get the RTShader system to support shaders and register the SceneManager with it
        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(scnMgr);

        // Create a light source so we don't get a black screen
        Ogre::Light* light = scnMgr->createLight("MainLight");
        Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        lightNode->setPosition(0, 10, 15);  // Position light above and in front
        lightNode->attachObject(light);

        // Create a camera scene node positioned a bit away from origin, looking forward
        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        camNode->setPosition(0, 0, 50);
        camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

        // Create the camera itself and configure near clipping and aspect ratio
        Ogre::Camera* cam = scnMgr->createCamera("myCam");
        cam->setNearClipDistance(5);
        cam->setAutoAspectRatio(true);
        camNode->attachObject(cam);

        // Tell Ogre to render the scene from this camera into the window viewport
        getRenderWindow()->addViewport(cam);

        // Load a 3D model entity and attach it to a new scene node for rendering
        Ogre::Entity* ent = scnMgr->createEntity("athene.mesh");
        Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
        node->attachObject(ent);

        // Register the input listener so it receives keyboard events
        addInputListener(&keyHandler);
    }
};

int main() {
    try {
        BasicApp app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    } catch (const Ogre::Exception& e) {
        std::cerr << "An exception has occurred: " << e.getFullDescription() << std::endl;
        return 1;
    }
    return 0;
}
