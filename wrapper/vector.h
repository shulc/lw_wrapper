#pragma once

#include "glm.hpp"


using TVectorF = glm::vec3;
using TVectorD = glm::dvec3;

TVectorF project(const TVectorF& p, const TVectorF& proj)
{
	if (proj == glm::vec3(0, 0, 0)) {
		return glm::vec3(0, 0, 0);
	}

	const float mul = dot(p, proj) / dot(proj, proj);
	return proj * mul;
}

/*
struct TVectorF : public glm::vec3 {
    using TBase = glm::vec3;

    TVectorF() : TBase() {}
    TVectorF(const TVectorF& v) : TBase(v) {}
    TVectorF(const TBase& v) : TBase(v) {}
    TVectorF(TVectorF &&v): TBase(std::move(v)){}
    TVectorF(TBase&& v) : TBase(std::move(v)) {}
    TVectorF operator=(const TVectorF& v) {
        *this = v;
        return *this;
    }

    float Length() const {
        return glm::length(*(TBase*)(this));
    }
};
*/
