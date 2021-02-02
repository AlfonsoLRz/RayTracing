#pragma once

#include "Geometry/Animation/LinearInterpolation.h"
#include "Graphics/Application/LiDARParameters.h"
#include "Graphics/Application/PointCloudParameters.h"
#include "Graphics/Application/Renderer.h"
#include "Graphics/Application/RenderingParameters.h"
#include "Utilities/Singleton.h"

/**
*	@file GUI.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 08/05/2019
*/

/**
*	@brief Wrapper for GUI graphics which allows the user to interact with the scene.
*/
class GUI: public Singleton<GUI>
{
	friend class Singleton<GUI>;

protected:
	const static unsigned	MAX_RETURN, MIN_RETURN;

protected:
	LiDARParameters*		_lidarParams;						//!< Reference to LiDAR parameters
	PointCloudParameters*	_pointCloudParams;					//!< Reference to parameters of point cloud files
	Renderer*				_renderer;							//!< Access to current scene
	RenderingParameters*	_renderingParams;					//!< Reference to rendering parameters

	// GUI state
	bool					_showAboutUs;						//!< About us window
	bool					_showControls;						//!< Shows application controls
	bool					_showLidarASPRSClasses;				//!< Shows a window where all ASPRS classes are related to a color
	bool					_showLidarCustomClasses;			//!< Displays custom classes of the scene
	bool					_showLidarSettings;					//!< Displays a window which allows the user to modify the LiDAR parameters
	bool					_showPointCloudSettings;			//!< Displays a window which allows the user to customize the point cloud saving process
	bool					_showRenderingSettings;				//!< Displays a window which allows the user to modify the rendering parameters
	bool					_showSceneSettings;					//!< Displays a window with all the model components and their variables
	bool					_showScreenshotSettings;			//!< Shows a window which allows to take an screenshot at any size

	// Retrieved information
	std::map<std::string, vec3>*	_customClasses;				//!< Custom classes and their colors
	std::map<std::string, vec3>*	_lidarClasses;				//!< ASPRS classes and their colors
	std::vector<vec2>				_lidarPath;					//!< Aerial path drawn by the user

protected:
	/**
	*	@brief Constructor of GUI context provided by a graphics library (Dear ImGui).
	*/
	GUI();

	/**
	*	@brief Creates the complete GUI.
	*/
	void createMainLayout();
	
	/**
	*	@brief Creates the navbar.
	*/
	void createMenu();

	/**
	*	@brief Calls ImGui::Spacing() for n times in a clean way.
	*/
	void leaveSpace(const unsigned numSlots);

	/**
	*	@brief Renders a help icon with a message.
	*/
	void renderHelpMarker(const char* message);

	/**
	*	@brief Shows a window where some information about the project is displayed.
	*/
	void showAboutUsWindow();

	/**
	*	@brief Shows a tab item with LiDAR aerial settings.
	*/
	void showAerialTabItem();

	/**
	*	@brief Displays a table with the application controls (mouse, keyboard, etc).
	*/
	void showControls();

	/**
	*	@brief Shows a tab item with LiDAR land settings.
	*/
	void showLandTabItem();

	/**
	*	@brief Shows a window with a list of ASPRS classes and their linked colors.
	*/
	void showLiDARASPRSClasses();

	/**
	*	@brief Shows a window with a list of custom classes and their linked colors.
	*/
	void showLiDARCustomClasses();

	/**
	*	@brief Shows a window with lidar configuration.
	*/
	void showLiDARSettings();

	/**
	*	@brief Builds the tab of LiDAR settings with general parameters of LiDAR (not related to terrestrial nor aerial).
	*/
	void showLiDARTabItem();

	/**
	*	@brief Shows a window with settings about the point cloud file.
	*/
	void showPointCloudSettings();

	/**
	*	@brief Shows a window with general rendering configuration.
	*/
	void showRenderingSettings();

	/**
	*	@brief Shows a list of models in the scene which can be modified.
	*/
	void showSceneSettings();

	/**
	*	@brief Shows a window with framebuffer and screenshot configuration.
	*/
	void showScreenshotSettings();

public:
	/**
	*	@brief Destructor.
	*/
	virtual ~GUI();

	/**
	*	@brief Initializes the context provided by an interface library.
	*	@param window Window provided by GLFW.
	*	@param openGLMinorVersion Minor version of OpenGL 4.
	*/
	void initialize(GLFWwindow* window, const int openGLMinorVersion);

	/**
	*	@brief Renders the interface components.
	*/
	void render();
};

