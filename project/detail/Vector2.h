#include "../Vector2.h"

template<class T>
Vector2Temple<T>::Vector2Temple()
{
	x_ = 0;
	y_ = 0;
}
template<class T>
Vector2Temple<T>::Vector2Temple(T x, T y)
{
	x_ = x;
	y_ = y;
}

template<class T>
Vector2Temple<T>::~Vector2Temple()
{

}

template<class T>
Vector2Temple<T>  Vector2Temple<T>::operator+ (Vector2Temple<T> vec)
{
	return { x_ + vec.x_, y_ + vec.y_ };
}
template<class T>
Vector2Temple<T>  Vector2Temple<T>::operator- (Vector2Temple<T> vec)
{
	return { x_ - vec.x_, y_ - vec.y_ };
}
template<class T>
Vector2Temple<T>  Vector2Temple<T>::operator/ (Vector2Temple<T> vec)
{
	Vector2Temple back = {x_,y_};

	if (vec.x_) back.x_ /= vec.x_;
	if (vec.y_) back.y_ /= vec.y_;

	return back;
}
template<class T>
Vector2Temple<T>  Vector2Temple<T>::operator* (Vector2Temple<T> vec)
{
	return { x_ * vec.x_, y_ * vec.y_ };
}
template<class T>
Vector2Temple<T>  Vector2Temple<T>::operator% (Vector2Temple<T> vec)
{
	return { x_ % vec.x_, y_ % vec.y_ };
}

template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator= (const Vector2Temple<T>& vec)
{
	x_ = vec.x_;
	y_ = vec.y_;
	return *this;
}

template<class T>
T& Vector2Temple<T>::operator[](int no)
{
	if     (no == 0) return x_;
	else if(no == 1) return y_;
	else             return x_;
}

template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator+=(const Vector2Temple<T>& vec)
{
	x_ += vec.x_;
	y_ += vec.y_;
	return *this;
}
template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator-=(const Vector2Temple<T>& vec)
{
	x_ -= vec.x_;
	y_ -= vec.y_;
	return *this;
}
template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator*=(const Vector2Temple<T>& vec)
{
	x_ *= vec.x_;
	y_ *= vec.y_;
	return *this;
}
template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator/=(const Vector2Temple<T>& vec)
{
	if (vec.x_) x_ /= vec.x_;
	else        x_  = 0;
	
	if (vec.y_) y_ /= vec.y_;
	else        y_  = 0;

	return *this;
}
template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator%=(const Vector2Temple<T>& vec)
{
	if (vec.x_) x_ %= vec.x_;
	else        x_ = 0;

	if (vec.y_) y_ %= vec.y_;
	else        y_ = 0;

	return *this;
}
template<class T>
Vector2Temple<T>  Vector2Temple<T>::operator+ () const
{
	return *this;
}
template<class T>
Vector2Temple<T>  Vector2Temple<T>::operator- () const
{
	return { -x_,-y_ };
}

template<class T>
bool Vector2Temple<T>::operator< (const Vector2Temple<T> vec)const
{
	return (x_ < vec.x_ && y_ < vec.y_);
}
template<class T>
bool Vector2Temple<T>::operator> (const Vector2Temple<T> vec)const
{
	return (x_ > vec.x_ && y_ > vec.y_);
}
template<class T>
bool Vector2Temple<T>::operator<=(const Vector2Temple<T> vec)const
{
	return (x_ <= vec.x_ && y_ <= vec.y_);
}
template<class T>
bool Vector2Temple<T>::operator>=(const Vector2Temple<T> vec)const
{
	return (x_ >= vec.x_ && y_ >= vec.y_);
}
template<class T>
bool Vector2Temple<T>::operator==(const Vector2Temple<T> vec)const
{
	return (x_ == vec.x_ && y_ == vec.y_);
}
template<class T>
bool Vector2Temple<T>::operator!=(const Vector2Temple<T> vec) const
{
	return !(x_ == vec.x_ && y_ == vec.y_);
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

template<class T>
Vector2Temple<T> operator*(const Vector2Temple<T>& vec, T num)
{
	return { vec.x_ * num, vec.y_ * num };
}
template<class T>
Vector2Temple<T> operator*(T num, const Vector2Temple<T>& vec)
{
	return { vec.x_ * num, vec.y_ * num };
}
template<class T>
Vector2Temple<T> operator/(const Vector2Temple<T>& vec, T num)
{
	if (num != 0) return { vec.x_ / num, vec.y_ / num };

	return{ 0,0 };
}

template<class T>
bool operator< (const Vector2Temple<T> vec, const T num)
{
	return (vec.x_ < num && vec.y_ < num);
}
template<class T>
bool operator< (const T num, const Vector2Temple<T> vec)
{
	return (num < vec.x_ && num < vec.y_);
}
template<class T>
bool operator> (const Vector2Temple<T> vec, const T num)
{
	return (vec.x_ > num && vec.y_ > num);
}
template<class T>
bool operator> (const T num, const Vector2Temple<T> vec)
{
	return (num > vec.x_ && num > vec.y_);
}
template<class T>
bool operator<=(const Vector2Temple<T> vec, const T num)
{
	return (vec.x_ <= num && vec.y_ <= num);
}
template<class T>
bool operator<=(const T num, const Vector2Temple<T> vec)
{
	return (num <= vec.x_ && num <= vec.y_);
}
template<class T>
bool operator>=(const Vector2Temple<T> vec, const T num)
{
	return (vec.x_ >= num && vec.y_ >= num);
}
template<class T>
bool operator>=(const T num, const Vector2Temple<T> vec)
{
	return (num >= vec.x_ && num >= vec.y_);
}
template<class T>
bool operator==(const Vector2Temple<T> vec, const T num)
{
	return (vec.x_ == num && vec.y_ == num);
}
template<class T>
bool operator==(const T num, const Vector2Temple<T> vec)
{
	return (num == vec.x_ && num == vec.y_);
}
template<class T>
bool operator!=(const Vector2Temple<T> vec, const T num)
{
	return !(vec.x_ == num && vec.y_ == num);
}
template<class T>
bool operator!=(const T num, const Vector2Temple<T> vec)
{
	return !(num == vec.x_ && num == vec.y_);
}
