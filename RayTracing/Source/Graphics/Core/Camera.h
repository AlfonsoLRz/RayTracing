#pragma once

#include "Geometry/3D/Ray3D.h"
#include "Graphics/Core/CGEnumerations.h"

/**
*	@file Camera.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 07/09/2019
*/

/**
*	@brief Generic camera for a graphic application.
*/
class Camera
{
protected:
	// [Fixed values: by default initialization]
	const static vec3	EYE, LOOK_AT, UP;
	const static float	ZNEAR, ZFAR;
	const static float	FOV_X;

protected:
	// [Generic parameters]
	float			_aspect;							//!< Ratio between width and height of field of view
	vec3			_eye, _lookAt, _up;					//!< Look at call parameters
	float			_focalLength;						//!<
	vec3			_lowerLeftCorner;					//!<
	vec3			_n, _u, _v;							//!< Camera axes to apply movements
	vec3			_vertical, _horizontal;				//!<
	float			_viewportWidth, _viewportHeight;	//!<
	float			_zNear, _zFar;						//!< Boundaries in the camera z axis

	Camera*			_backupCamera;						//!< Copy of the initial camera so the user can reset it anytime

	// [Perspective parameters]
	float			_fovY,								//!< Field of view (radians) in y axis
					_fovX;								//!< Field of view (radians) in the x axis, just as the user chooses it. Saved only for interface purposes	

protected:
	/**
	*	@brief Calculates the axes from the camera coordinate system.
	*	@param n z axis.
	*	@param u x axis.
	*	@param v y axis.
	*/
	void computeAxes(vec3& n, vec3& u, vec3& v);

	/**
	*	@brief Calculates the aperture angle in the y axis.
	*/
	float computeFovY();

	/**
	*	@brief Computes the lower left corner of our camera plane. 
	*/
	void computeLowerLeftCorner();

	/**
	*	@brief Copies the camera attributes from the specified camera to this one.
	*	@param camera Camera where parameters are taken from.
	*/
	void copyCameraAttributes(const Camera* camera);

public:
	/**
	*	@brief Default constructor. Initializes the camera with some fixed values.
	*	@param width Width of screen (persp) or width of canonical view volume (ortho).
	*	@param height Height of screen (persp) or height of canonical view volume (ortho).
	*/
	Camera(const uint16_t width, const uint16_t height);

	/**
	*	@brief Copy constructor.
	*	@param camera Camera to be cloned.
	*/
	Camera(const Camera& camera);

	/**
	*	@brief Frees resources.
	*/
	virtual ~Camera();

	/**
	*	@brief Assignment operator overriding.
	*	@param camera Camera to be cloned.
	*/
	Camera& operator=(const Camera& camera);
	
	/// [Interface-adapted methods]

	/**
	*	@return Aspect value given by the camera view dimensions.
	*/
	float getAspect() const { return _aspect; }

	/**
	*	@return Camera position.
	*/
	vec3 getEye() const { return _eye; }

	/**
	*	@return Field of view in the y axis.
	*/
	float getFovY() const { return _fovY; }

	/**
	*	@return Position where the camera looks at.
	*/
	vec3 getLookAt() const { return _lookAt; }

	/**
	*	@brief World ray that traverses the focal plane through normalized values u and v. 
	*/
	Ray3D getRay(float u, float v);
	
	/**
	*	@return Maximum z on the camera system coordinate until the scene is discarded.
	*/
	float getZFar() const { return _zFar; }

	/**
	*	@return Minimum z on the camera system coordinate until the scene is taken into account.
	*/
	float getZNear() const { return _zNear; }

	/**
	*	@brief Restores the values from the last saved camera.
	*/
	void reset();

	/**
	*	@brief Saves the current configuration so it can be the starting point of future resets.
	*/
	void saveCamera();

	/**
	*	@brief Modifies the aperture angle of the camera on the x axis.
	*	@param fovX Aperture angle on the x axis.
	*/
	void setFovX(const float fovX);

	/**
	*	@brief Modifies the aperture angle of the camera on the y axis.
	*	@param fovX Aperture angle on the x axis.
	*/
	void setFovY(const float fovY);

	/**
	*	@brief Modifies the position where the camera looks at.
	*	@param position New position where the camera looks at.
	*/
	void setLookAt(const vec3& position);

	/**
	*	@brief Modifies the position where the camera is placed.
	*	@param position New position where the camera is placed.
	*/
	void setPosition(const vec3& position);

	/**
	*	@brief Modifies the aspect of the view volume in x and y axes.
	*	@param width Width of screen (persp) or width of canonical view volume (ortho).
	*	@param height Height of screen (persp) or height of canonical view volume (ortho).
	*/
	void setRaspect(const uint16_t width, const uint16_t height);

	/**
	*	@brief Modifies the up vector.
	*/
	void setUp(const vec3& up);

	/**
	*	@brief Modifies the maximum z where the camera discards the scene.
	*	@param zfar New value on the camera z axis.
	*/
	void setZFar(const float zfar);

	/**
	*	@brief Modifies the minimum z where the camera takes into account the scene.
	*	@param znear New value on the camera z axis.
	*/
	void setZNear(const float znear);

	/// [Movements]

	/**
	*	@brief Positive translation on the camera y axis.
	*	@param speed Determines the amount of units to translate the camera.
	*/
	void boom(float speed);

	/**
	*	@brief Negative translation on the camera y axis.
	*	@param speed Determines the amount of units to translate the camera.
	*/
	void crane(float speed);

	/**
	*	@brief Translation on the camera z axis.
	*	@param speed Determines the amount of units to translate the camera.
	*/
	void dolly(float speed);

	/**
	*	@brief Orbit movement of the camera over the focused point (y axis).
	*	@param speed Determines the amount of units to rotate the camera.
	*/
	void orbitXZ(float speed);

	/**
	*	@brief Orbit movement of the camera around the focused point (x, z axes).
	*	@param speed Determines the amount of units to rotate the camera.
	*/
	void orbitY(float speed);

	/**
	*	@brief Rotation of the camera around a (0, 1, 0) vector placed at the camera eye.
	*	@param speed Determines the amount of units to rotate the camera.
	*/
	void pan(float speed);

	/**
	*	@brief Rotation of the camera around its x axis.
	*	@param speed Determines the amount of units to translate the camera.
	*/
	void tilt(float speed);

	/**
	*	@brief Translation on the camera x axis.
	*	@param speed Determines the amount of units to translate the camera.
	*/
	void truck(float speed);

	/**
	*	@brief Getting closer / further to focus point.
	*	@param speed Determines the amount of units to zoom the camera.
	*/
	void zoom(float speed);
};



