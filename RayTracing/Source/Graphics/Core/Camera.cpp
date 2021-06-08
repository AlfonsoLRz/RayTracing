#include "stdafx.h"
#include "Camera.h"

#include "Utilities/BasicOperations.h"
#include "Utilities/RandomUtilities.h"

// [ Static parameters initialization]

const vec3 Camera::EYE					= vec3(-2.0f, 2.0f, 1.0f);
const vec3 Camera::LOOK_AT				= vec3(0.0f, 0.0f, -1.0f);
const vec3 Camera::UP					= vec3(0.0f, 1.0f, 0.0f);

const float Camera::ZNEAR				= 0.1f;
const float Camera::ZFAR				= 80.0f;

const float Camera::FOV_Y				= 20.0f;


/// [Public methods]

Camera::Camera(const uint16_t width, const uint16_t height): _backupCamera(nullptr)
{
	_eye			= EYE;
	_lookAt			= LOOK_AT;
	_up				= UP;

	_zNear			= ZNEAR;
	_zFar			= ZFAR;

	_fovY			= glm::radians(FOV_Y);
	_aspect			= float(width) / height;
	_focusDistance	= 1.0f;
	_lensRadius		= 0.0f;
	_timeFrame		= vec2(.0f);

	this->buildDescription();
	this->saveCamera();
}

Camera::Camera(const Camera& camera) : _backupCamera(nullptr)
{
	this->copyCameraAttributes(&camera);
}

Camera::~Camera()
{
	delete _backupCamera;
}

Camera& Camera::operator=(const Camera& camera)
{
	if (this != &camera)
	{
		this->copyCameraAttributes(&camera);
	}

	return *this;
}

Camera* Camera::buildDescription()
{
	float h = tan(_fovY / 2.0f);

	_focalLength = 1.0f;
	_viewportHeight = 2.0f * h;
	_viewportWidth = _viewportHeight * _aspect;

	this->computeAxes(_n, _u, _v);
	this->computeLowerLeftCorner();

	return this;
}

Ray3D Camera::getRay(float u, float v)
{
	vec3 randomDistance = _lensRadius * RandomUtilities::getUniformRandomInUnitDisk();
	vec3 offset = randomDistance.x * _u + randomDistance.y * _v;
	
	return Ray3D(_eye + offset, _lowerLeftCorner + u * _horizontal + v * _vertical - _eye - offset, RandomUtilities::getUniformRandom(_timeFrame.x, _timeFrame.y));
}

Camera* Camera::reset()
{
	this->copyCameraAttributes(_backupCamera);

	return this;
}

Camera* Camera::saveCamera()
{
	delete _backupCamera;
	_backupCamera = nullptr;
	_backupCamera = new Camera(*this);

	return this;
}

Camera* Camera::setAperture(const float aperture)
{
	_lensRadius = aperture / 2.0f;

	return this;
}

Camera* Camera::setFocusDistance(const float focusDistance)
{
	_focusDistance = focusDistance;

	return this;
}

Camera* Camera::setFovY(const float fovY)
{
	_fovY = glm::radians(fovY);
	
	return this;
}

Camera* Camera::setLookAt(const vec3& position)
{
	_lookAt = position;
	this->computeAxes(_n, _u, _v);

	return this;
}

Camera* Camera::setPosition(const vec3& position)
{
	_eye = position;
	this->computeAxes(_n, _u, _v);

	return this;
}

Camera* Camera::setRaspect(const uint16_t width, const uint16_t height)
{
	_aspect = float(width) / height;
	_viewportWidth = _viewportHeight * _aspect;
	this->computeLowerLeftCorner();

	return this;
}

Camera* Camera::setTimeFrame(const vec2 timeFrame)
{
	_timeFrame = timeFrame;

	return this;
}

Camera* Camera::setUp(const vec3& up)
{
	_up = up;
	this->computeAxes(_n, _u, _v);

	return this;
}

Camera* Camera::setZFar(const float zfar)
{
	_zFar = zfar;

	return this;
}

Camera* Camera::setZNear(const float znear)
{
	_zNear = znear;

	return this;
}

// [Movements] 

void Camera::boom(float speed)
{
	const glm::mat4 translationMatrix = glm::translate(mat4(1.0f), _v * speed);			// Translation in y axis

	_eye	= vec3(translationMatrix * vec4(_eye, 1.0f));
	_lookAt = vec3(translationMatrix * vec4(_lookAt, 1.0f));
}

void Camera::crane(float speed)
{
	boom(-speed);					// Implemented as another method to take advantage of nomenclature
}	

void Camera::dolly(float speed)
{
	const mat4 translationMatrix = glm::translate(mat4(1.0f), -_n * speed);			// Translation in z axis
	_eye	= vec3(translationMatrix * vec4(_eye, 1.0f));
	_lookAt = vec3(translationMatrix * vec4(_lookAt, 1.0f));
}

void Camera::orbitXZ(float speed)
{
	const mat4 rotationMatrix = glm::rotate(mat4(1.0f), speed, _u);				// We will pass over the scene, x or z axis could be used
	
	_eye	= vec3(rotationMatrix * vec4(_eye - _lookAt, 1.0f)) + _lookAt;
	_u		= vec3(rotationMatrix * vec4(_u, 0.0f));		
	_v		= vec3(rotationMatrix * vec4(_v, 0.0f));
	_n		= vec3(rotationMatrix * vec4(_n, 0.0f));
	_up		= glm::normalize(glm::cross(_n, _u));						// Free rotation => we can look down or up
}

void Camera::orbitY(float speed)
{
	const mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), speed, glm::vec3(0.0, 1.0f, 0.0f));

	_u		= vec3(rotationMatrix * vec4(_u, 0.0f));
	_v		= vec3(rotationMatrix * vec4(_v, 0.0f));
	_n		= vec3(rotationMatrix * vec4(_n, 0.0f));
	_up		= glm::normalize(glm::cross(_n, _u));								// This movement doesn't change UP, but it could occur as a result of previous operations
	_eye	= vec3(rotationMatrix * vec4(_eye - _lookAt, 1.0f)) + _lookAt;
}

void Camera::pan(float speed)
{
	const mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), speed, vec3(0.0f, 1.0f, 0.0f));

	/**
	*	Up vector can change, not in the original position tho. Example: orbit XZ (rotated camera) + pan
	*/
	_u		= vec3(rotationMatrix * vec4(_u, 0.0f));
	_v		= vec3(rotationMatrix * vec4(_v, 0.0f));
	_n		= vec3(rotationMatrix * vec4(_n, 0.0f));
	_up		= glm::normalize(glm::cross(_n, _u));
	_lookAt = vec3(rotationMatrix * vec4(_lookAt - _eye, 1.0f)) + _eye;	
}

void Camera::tilt(float speed)
{
	const mat4 rotationMatrix = glm::rotate(mat4(1.0f), speed, _u);

	const vec3 n = glm::vec3(rotationMatrix * glm::vec4(_n, 0.0f));							
	float alpha = glm::acos(glm::dot(n, glm::vec3(0.0f, 1.0f, 0.0f)));

	if (alpha < speed || alpha > (glm::pi<float>() - speed))
	{
		return;
	}

	_v		= glm::vec3(rotationMatrix * glm::vec4(_v, 0.0f));		
	_n		= n;														
	_up		= glm::normalize(glm::cross(_n, _u));											// It could change because of the rotation
	_lookAt = glm::vec3(rotationMatrix * glm::vec4(_lookAt - _eye, 1.0f)) + _eye;
}

void Camera::truck(float speed)
{
	const mat4 translationMatrix = glm::translate(mat4(1.0f), _u * speed);				// Translation in x axis

	_eye	= vec3(translationMatrix * vec4(_eye, 1.0f));
	_lookAt = vec3(translationMatrix * vec4(_lookAt, 1.0f));
}

void Camera::zoom(float speed)
{
	float newAngle = _fovY - speed;

	if (newAngle < glm::pi<float>() && newAngle > 0.0f)
	{
		this->setFovY(newAngle);
	}
}

/// [Private methods]

void Camera::computeAxes(vec3& n, vec3& u, vec3& v)
{
	n = glm::normalize(_eye - _lookAt);							// z axis
	
	if (BasicOperations::equal(n,-_up))							// x axis: UP x n is 0 as both vectors are parallel. Since up and n are normalized we can check if they are equal (with epsilon checkup)
	{
		u = glm::normalize(glm::cross(vec3(0.0f, 0.0f, -1.0f), n));
	}
	else if (BasicOperations::equal(n, _up))
	{
		u = glm::normalize(glm::cross(vec3(0.0f, 0.0f, 1.0f), n));
	}
	else
	{
		u = glm::normalize(glm::cross(_up, n));
	}
	v = glm::normalize(glm::cross(n, u));						// y axis
}

void Camera::computeLowerLeftCorner()
{
	_horizontal = _focusDistance * _viewportWidth * _u;
	_vertical = _focusDistance * _viewportHeight * _v;
	_lowerLeftCorner = _eye - _horizontal / 2.0f - _vertical / 2.0f - _focusDistance * _n;
}

void Camera::copyCameraAttributes(const Camera* camera)
{
	this->_eye				= camera->_eye;
	this->_lookAt			= camera->_lookAt;
	this->_up				= camera->_up;

	this->_zNear			= camera->_zNear;
	this->_zFar				= camera->_zFar;

	this->_aspect			= camera->_aspect;
	this->_viewportWidth	= camera->_viewportWidth;
	this->_viewportHeight	= camera->_viewportHeight;

	this->_focalLength		= camera->_focalLength;
	this->_horizontal		= camera->_horizontal;
	this->_lowerLeftCorner	= camera->_lowerLeftCorner;
	this->_vertical			= camera->_vertical;

	this->_n				= camera->_n;
	this->_u				= camera->_u;
	this->_v				= camera->_v;

	this->_fovY				= camera->_fovY;

	if (camera->_backupCamera)
	{
		delete this->_backupCamera;
		this->_backupCamera = new Camera(*camera->_backupCamera);
	}
}