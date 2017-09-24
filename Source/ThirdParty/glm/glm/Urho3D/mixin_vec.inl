
static const vec ZERO;
static const vec LEFT;
static const vec RIGHT;
static const vec UP;
static const vec DOWN;
static const vec FORWARD;
static const vec BACK;
static const vec ONE;

Urho3D::String ToString() const;

const T* Data() const { return &(*this)[0]; }

GLM_FUNC_DECL vec(T data[])
{
    for (length_t i = 0; i < length(); ++i)
        (*this)[i] = data[i];
}
