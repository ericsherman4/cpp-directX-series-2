#pragma once
#include <cmath>

template<typename T> 
class Vec2_
{
public:
	Vec2_() = default;
	Vec2_(T x_in, T y_in)
		: x(x_in)
		, y(y_in)
	{
	}

	template<typename T_in>
	// explicit must specify the conversion
	explicit Vec2_(const Vec2_<T_in>& vec)
		: x(static_cast<T>(vec.x))
		, y(static_cast<T>(vec.y))
	{	
	}

	Vec2_ operator+(const Vec2_& rhs) const
	{
		return Vec2_(x + rhs.x, y + rhs.y);
	}
	Vec2_& operator+=(const Vec2_& rhs)
	{
		return *this = *this + rhs;
	}
	Vec2_ operator*(T rhs) const
	{
		return Vec2_(x * rhs, y * rhs);
	}
	Vec2_& operator*=(T rhs)
	{
		return *this = *this * rhs;
	}
	Vec2_ operator-(const Vec2_& rhs) const
	{
		return Vec2_(x - rhs.x, y - rhs.y);
	}
	Vec2_& operator-=(const Vec2_& rhs)
	{
		return *this = *this - rhs;
	}
	T GetLength() const
	{
		return static_cast<T>(std::sqrt(GetLengthSq()));
	}
	T GetLengthSq() const
	{
		return x * x + y * y;
	}
	Vec2_& Normalize()
	{
		return *this = GetNormalized();
	}
	Vec2_ GetNormalized() const
	{
		const T len = GetLength();
		if (len != static_cast<T>(0))
		{
			return *this * (static_cast<T>(1) / len);
		}
		return *this;
	}

public:
	T x;
	T y;
};

typedef Vec2_<float> Vec2;
typedef Vec2_<int> Vei2;
