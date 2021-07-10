#include "stdafx.h"
#include "PDF.h"

#include "Utilities/RandomUtilities.h"

// [Cosine PDF]

vec3 CosinePDF::generate() const
{
	return _orthoBasis.localVector(RandomUtilities::getUniformRandomCosineDirection());
}

float CosinePDF::value(const vec3& direction) const
{
	float cosine = glm::dot(glm::normalize(direction), _orthoBasis.w());

	return cosine <= 0 ? .0f : cosine / glm::pi<float>();
}

// [Hittable PDF]

vec3 HittablePDF::generate() const
{
	return _hittable->random(_origin);
}

float HittablePDF::value(const vec3& direction) const
{
	return _hittable->pdfValue(_origin, direction);
}

// [Mixture PDF]

MixturePDF::MixturePDF(std::shared_ptr<PDF> pdf1, std::shared_ptr<PDF> pdf2)
{
	_pdf[0] = pdf1; _pdf[1] = pdf2;
}

vec3 MixturePDF::generate() const
{
	if (RandomUtilities::getUniformRandom() < .5f)
		return _pdf[0]->generate();

	return _pdf[1]->generate();
}

float MixturePDF::value(const vec3& direction) const
{
	return .5f * _pdf[0]->value(direction) + .5f * _pdf[1]->value(direction);
}
