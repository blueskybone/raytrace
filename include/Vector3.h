#ifndef _VECTOR3_H_
#define _VECTOR3_H_
#include <cmath>
typedef class Vector3
{
    public:
        float x;
        float y;
        float z;
    public:
        Vector3(){};

        Vector3(float inX, float inY, float inZ);

        Vector3(float inF);
		inline Vector3 operator+(const Vector3& v) const;

		inline Vector3 operator-(const Vector3& v) const;

		inline float operator*(const Vector3& v) const;

		inline Vector3 operator*(float scale) const;

		inline Vector3 operator/(float scale)const;

		inline Vector3 operator+=(const Vector3& v);

		inline Vector3 operator-=(const Vector3& v);

		inline bool operator=(const Vector3& v);

		inline bool operator==(const Vector3& v) const;

		inline Vector3 cross(const Vector3& v) const;

		inline Vector3 operator^(const Vector3& v) const;

		inline Vector3 norm();

		inline float Length()const;
}vec3;

inline Vector3::Vector3(float inF)
	: x(inF)
	, y(inF)
	, z(inF)
{

}
inline Vector3::Vector3(float inX, float inY, float inZ)
	: x(inX)
	, y(inY)
	, z(inZ)
{
	
}
inline Vector3 Vector3::operator+(const Vector3& v) const
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

inline Vector3 Vector3::operator-(const Vector3& v) const
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

inline float Vector3::operator*(const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z; 
}

inline Vector3 Vector3::operator*(float scale) const
{
	return Vector3(x * scale, y * scale, z * scale);
}

inline Vector3 Vector3::operator/(float scale) const
{
	return Vector3(x / scale, y / scale, z / scale);
}
inline Vector3 Vector3::operator+=(const Vector3& v)
{
	x += v.x; 
	y += v.y; 
	z += v.z;
	
	return *this;
}
inline Vector3 Vector3::operator-=(const Vector3& v)
{
	x -= v.x; 
	y -= v.y; 
	z -= v.z;
	
	return *this;
}

inline bool Vector3::operator==(const Vector3& v) const
{
	return (x == v.x && y == v.y && z == v.z);
}

inline bool Vector3::operator=(const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return true;
}
inline float Vector3::Length() const
{
	return sqrt(x * x + y * y + z * z);
}

inline Vector3 Vector3::cross(const Vector3& v) const
{
	return Vector3(x * v.x, y * v.y, z * v.z);
}

inline Vector3 Vector3::operator^(const Vector3& v) const
{
	return Vector3
	(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x
	);
}
inline Vector3 Vector3::norm()
{
	float len = this->Length();
	return Vector3(x / len, y / len, z / len);
}

#endif