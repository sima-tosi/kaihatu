#pragma once

template<class T> class Vector2Temple
{
public:
	Vector2Temple();
	Vector2Temple(T x, T y);
	~Vector2Temple();

	T x_;
	T y_;

	// “ñ€‰‰Zq
	Vector2Temple operator+(Vector2Temple vec);
	Vector2Temple operator-(Vector2Temple vec);
	Vector2Temple operator/(Vector2Temple vec);
	Vector2Temple operator*(Vector2Temple vec);
	Vector2Temple operator%(Vector2Temple vec);

	// ‘ã“ü‰‰Zq
	Vector2Temple& operator=(const Vector2Temple& vec);

	// “Y‚¦š‰‰Zq
	T& operator[](int no);

	// ’P€‰‰Zq
	Vector2Temple& operator+=(const Vector2Temple& vec);
	Vector2Temple& operator-=(const Vector2Temple& vec);
	Vector2Temple& operator*=(const Vector2Temple& vec);
	Vector2Temple& operator/=(const Vector2Temple& vec);
	Vector2Temple& operator%=(const Vector2Temple& vec);
	Vector2Temple  operator+()const;
	Vector2Temple  operator-()const;

	// ”äŠr‰‰Zq
	bool operator< (const Vector2Temple vec)const;
	bool operator> (const Vector2Temple vec)const;
	bool operator<=(const Vector2Temple vec)const;
	bool operator>=(const Vector2Temple vec)const;
	bool operator==(const Vector2Temple vec)const;
	bool operator!=(const Vector2Temple vec)const;
};

template<class T>
Vector2Temple<T> operator*(const Vector2Temple<T>& vec, T num);
template<class T>
Vector2Temple<T> operator*(T num, const Vector2Temple<T>& vec);
template<class T>
Vector2Temple<T> operator/(const Vector2Temple<T>& vec, T num);

template<class T>
bool operator< (const Vector2Temple<T> vec, const T num);
template<class T>
bool operator< (const T num, const Vector2Temple<T> vec);
template<class T>
bool operator> (const Vector2Temple<T> vec, const T num);
template<class T>
bool operator> (const T num, const Vector2Temple<T> vec);
template<class T>
bool operator<=(const Vector2Temple<T> vec, const T num);
template<class T>
bool operator<=(const T num, const Vector2Temple<T> vec);
template<class T>
bool operator>=(const Vector2Temple<T> vec, const T num);
template<class T>
bool operator>=(const T num, const Vector2Temple<T> vec);
template<class T>
bool operator==(const Vector2Temple<T> vec, const T num);
template<class T>
bool operator==(const T num, const Vector2Temple<T> vec);
template<class T>
bool operator!=(const Vector2Temple<T> vec, const T num);
template<class T>
bool operator!=(const T num, const Vector2Temple<T> vec);


using Vector2 = Vector2Temple<int>;
using Vector2F = Vector2Temple<float>;
using Vector2D = Vector2Temple<double>;

#include "detail/Vector2.h"