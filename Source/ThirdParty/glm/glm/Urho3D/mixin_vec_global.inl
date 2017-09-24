#include <cstdio>

namespace glm
{

template <class T, qualifier Q> const vec<3, T, Q> vec<3, T, Q>::ZERO(0, 0, 0);
template <class T, qualifier Q> const vec<3, T, Q> vec<3, T, Q>::LEFT(-1, 0, 0);
template <class T, qualifier Q> const vec<3, T, Q> vec<3, T, Q>::RIGHT(1, 0, 0);
template <class T, qualifier Q> const vec<3, T, Q> vec<3, T, Q>::UP(0, 1, 0);
template <class T, qualifier Q> const vec<3, T, Q> vec<3, T, Q>::DOWN(0, -1, 0);
template <class T, qualifier Q> const vec<3, T, Q> vec<3, T, Q>::FORWARD(0, 0, 1);
template <class T, qualifier Q> const vec<3, T, Q> vec<3, T, Q>::BACK(0, 0, -1);
template <class T, qualifier Q> const vec<3, T, Q> vec<3, T, Q>::ONE(1, 1, 1);

template <class T, qualifier Q>
Urho3D::String vec<3, T, Q>::ToString() const
{
    char tempBuffer[Urho3D::CONVERSION_BUFFER_LENGTH];
    sprintf(tempBuffer, "%d %d %d", x_, y_, z_);
    return Urho3D::String(tempBuffer);
}

}