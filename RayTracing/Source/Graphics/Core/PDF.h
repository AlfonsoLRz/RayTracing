#pragma once

/**
*	@file PDF.h
*	@authors Alfonso López Ruiz (alr00048@red.ujaen.es)
*	@date 19/04/2021
*/

#include "Graphics/Core/Hittable.h"
#include "Utilities/ONB.h"

/**
*	@brief Probability distribution. Base class.
*/
class PDF
{
public:
	/**
	*	@brief Constructor. 
	*/
	PDF() {}

	/**
	*	@brief Destructor.
	*/
	~PDF() {}

	/**
	*	@brief Determines outgoing direction. 
	*/
	virtual vec3 generate() const = 0;

	/**
	*	@brief Probability distribution over a surface, given an incoming direction.
	*/
	virtual float value(const vec3& direction) const = 0;
};

/**
*	@brief Cosine probability distribution.
*/
class CosinePDF : public PDF
{
protected:
	ONB _orthoBasis;			//!< Orthonormal basis given the normal of surface

public:
	/**
	*	@brief Constructor.
	*/
	CosinePDF(const vec3& normal) { _orthoBasis.buildFromW(normal); }

	/**
	*	@brief Determines outgoing direction.
	*/
	virtual vec3 generate() const;

	/**
	*	@brief Probability distribution over a surface, given its normal.
	*/
	virtual float value(const vec3& direction) const;
};

/**
*	@brief Probability distribution for a hittable object.
*/
class HittablePDF : public PDF
{
protected:
	std::shared_ptr<Hittable>	_hittable;			//!< Hittable over which the PDF acts
	vec3						_origin;			//!< Origin source of hittable model

public:
	/**
	*	@brief Constructor.
	*/
	HittablePDF(std::shared_ptr<Hittable> hittable, const vec3& origin) : _hittable(hittable), _origin(origin) {}

	/**
	*	@brief Determines outgoing direction.
	*/
	virtual vec3 generate() const;

	/**
	*	@brief Probability distribution over a surface, given its normal.
	*/
	virtual float value(const vec3& direction) const;
};

/**
*	@brief Mixture of several PDFs.
*/
class MixturePDF : public PDF
{
protected:
	std::shared_ptr<PDF> _pdf[2];			//!< PDFs to be mixed

public:
	/**
	*	@brief Constructor.
	*/
	MixturePDF(std::shared_ptr<PDF> pdf1, std::shared_ptr<PDF> pdf2);

	/**
	*	@brief Determines outgoing direction.
	*/
	virtual vec3 generate() const;

	/**
	*	@brief Probability distribution over a surface, given its normal.
	*/
	virtual float value(const vec3& direction) const;
};
