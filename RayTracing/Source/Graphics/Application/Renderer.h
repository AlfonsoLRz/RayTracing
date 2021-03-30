#pragma once

#include "Graphics/Application/Scene.h"
#include "Graphics/Application/RenderingParameters.h"
#include "Graphics/Core/FBOScreenshot.h"
#include "Graphics/Core/RayTracer.h"
#include "Utilities/Singleton.h"

/**
*	@file InputManager.h
*	@authors Alfonso L�pez Ruiz (alr00048@red.ujaen.es)
*	@date 01/02/2021
*/

/**
*	@brief Manages the scenes and graphic application state.
*/
class Renderer: public Singleton<Renderer>
{
	friend class Singleton<Renderer>;

protected:
	const static std::string SCENE_INDEX_FILENAME;

protected:
	// [Rendering]
	uint8_t										_currentScene;			//!< Active scene
	RayTracer*									_rayTracer;				//!<
	std::vector<std::unique_ptr<Scene>>			_scene;					//!< Array of scenes which can be represented. Components are only initialized when asked for
	std::unique_ptr<FBOScreenshot>				_screenshotFBO;			//!< Framebuffer which allows us to capture the scene (and save it) at higher resolution
	std::unique_ptr<RenderingParameters>		_state;					//!< Properties of rendering

protected:
	/**
	*	@brief Default constructor with the only purpose of initializing properly the attributes.
	*/
	Renderer();

	/**
	*	@brief  
	*/
	void bindFramebuffer(const GLuint id);

	/**
	*	@brief  
	*/
	void clearFramebuffer();

	/**
	*	@brief Creates an scene taking into account the type from the arguments.
	*	@param sceneType Index-name of scene type.
	*/
	Scene* createScene(const uint8_t sceneType);

	/**
	*	@brief Reads the index of the scene which needs to be loaded at first.
	*/
	uint8_t readSceneIndex();

public:
	/**
	*	@brief Destructor. Frees resources.
	*/
	virtual ~Renderer();

	/**
	*	@brief Initializes the OpenGL variables at the current context.
	*	@param width Canvas initial width.
	*	@param height Canvas initial height.
	*/
	void prepareOpenGL(const uint16_t width, const uint16_t height);

	/**
	*	@brief Draws the currently active scene.
	*/
	void render();

	// [Scene data]

	/**
	*	@return Current camera that allows us to capture the scene.
	*/
	Camera* getActiveCamera() const { return _scene[_currentScene]->getCameraManager()->getActiveCamera(); }

	/**
	*	@return Color of background under the scene.
	*/
	vec3 getBackgroundColor()  const { return _state->_backgroundColor; }

	/**
	*	@return Currently active scene.
	*/
	Scene* getCurrentScene() { return _scene[_currentScene].get(); }

	/**
	*	@return Wrapping class for rendering parameters (unique instance per renderer).
	*/
	RenderingParameters* getRenderingParameters() { return _state.get(); }

	/**
	*	@brief Renders the scene into an FBO.
	*	@param filename Path of file system where the image needs to be saved.
	*/
	bool getScreenshot(const std::string& filename);

	// [Events]

	/**
	*	@brief Resize event from canvas view.
	*	@param width New canvas width.
	*	@param height New canvas height.
	*/
	void resize(const uint16_t width, const uint16_t height);
};

