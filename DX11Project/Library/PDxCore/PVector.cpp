#include "PVector.h"

namespace DX
{
	Vector3::Vector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;

	}

	Vector3::Vector3(const Vector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}

	Vector3::Vector3(float fx, float fy, float fz)
	{
		x = fx;
		y = fy;
		z = fz;
	}

	Vector3::~Vector3()
	{
	}

	Vector3 Vector3::operator+(Vector3 const& v)
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	Vector3 Vector3::operator-(Vector3 const& v)
	{
		return Vector3(x - v.x, y - v.y , z - v.z);
	}
	Vector3 Vector3::operator*(float const& scala)
	{
		return Vector3(x*scala, y*scala, z*scala);
	}
	Vector3 Vector3::operator/(float const& scala)
	{
		assert(scala != 0);

		float invert = 1.0f / scala;
		return Vector3(x * invert, y * invert, z * invert);
	}
	float Vector3::Dot(const Vector3& v)
	{
		return x * v.x + y * v.y + z * v.z;
	}
	Vector3 Vector3::Cross(const Vector3& v)
	{
		return Vector3(y * v.z - z * v.y,
						z * v.x - x * v.z,
						x * v.y - y * v.x);
	}
	float Vector3::Length()
	{
		return (float)sqrt(x*x + y*y + z*z);
	}
	Vector3 Vector3::Normalize()
	{
		float invert = 1.0f / Length();

		return Vector3(x * invert, y* invert, z* invert);
	}
	float Vector3::Angle(Vector3& v)
	{
		Vector3 v0 = Normalize();
		Vector3 v1 = v.Normalize();
		float dot = Dot(v1);
		return RADIAN_TO_DEGREE((acos(dot)));
	}
	bool Vector3::operator==(Vector3 const& v)
	{
		if (fabs(x - v.x) < kFloatEpsilon &&
			fabs(y - v.y) < kFloatEpsilon &&
			fabs(z - v.z) < kFloatEpsilon)
		{
			return true;
		}
		return false;
	}
	Vector4::Vector4()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}
	Vector4::Vector4(const Vector4& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}
	Vector4::Vector4(float fx, float fy, float fz, float fw)
	{
		x = fx; y = fy;
		z = fz; w = fw;
	}
	Vector4::~Vector4()
	{
	}
	Vector2::Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vector2::Vector2(const Vector2& v)
	{
		x = v.x;
		y = v.y;
	}
	Vector2::Vector2(float fx, float fy)
	{
		x = fx;
		y = fy;
	}
	Vector2::~Vector2()
	{
	}
}