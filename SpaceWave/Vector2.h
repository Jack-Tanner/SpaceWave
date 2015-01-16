#pragma once

namespace Math
{
	class Vector2
	{
	public:
		//Constructors
		Vector2() : X (0.0f), Y(0.0f) {}
		Vector2(float x, float y) : X (x), Y(y) {}

		//Copy Constructor
		Vector2(const Vector2& vec) {this->X = vec.X; this->Y = vec.Y; }

		//Destructor
		~Vector2() {};

		//Operators
		inline bool Vector2::operator!=(const Vector2& vector) const
		{
			return X != vector.X || Y != vector.Y;
		}
		inline bool Vector2::operator==(const Vector2& vect) const
		{
			return (*this != vect) == false;
		}
		inline Vector2& Vector2::operator+=(const Vector2& pVector)
		{
			X += pVector.X;
			Y += pVector.Y;
			return *this;
		}
		inline Vector2& Vector2::operator-=(const Vector2& pVector)
		{
			X -= pVector.X;
			Y -= pVector.Y;
			return *this;
		}	
		inline Vector2& Vector2::operator+=(float num)
		{
			X += num;
			Y += num;
			return *this;
		}
		inline Vector2& Vector2::operator-=(float num)
		{
			X -= num;
			Y -= num;
			return *this;
		}
		inline Vector2& Vector2::operator/=(float num)
		{
			X /= num;
			Y /= num;
			return *this;
		}
		friend inline Vector2 operator+(const Vector2& vect1,const Vector2& vect2)
		{
			return Vector2(vect1.X + vect2.X,vect1.Y + vect2.Y);
		}
		friend inline Vector2 operator-(const Vector2& vect1,const Vector2& vect2)
		{
			return Vector2(vect1.X - vect2.X,vect1.Y - vect2.Y);
		}
		inline Vector2 operator-(Vector2& vect)
		{
			return vect * -1;
		}
		friend inline Vector2 operator*(const Vector2& vect1, float value)
		{
			return Vector2(vect1.X * value,vect1.Y * value);
		}
		friend inline Vector2 operator/(const Vector2& vect1, float value)
		{
			return Vector2(vect1.X / value,vect1.Y / value);
		}
		friend inline Vector2 operator*(const Vector2& vect1,const Vector2& vect2)
		{
			return Vector2(vect1.X * vect2.X,vect1.Y * vect2.Y);
		}
		friend inline Vector2 operator/(const Vector2& vect1,const Vector2& vect2)
		{
			return Vector2(vect1.X / vect2.X,vect1.Y / vect2.Y);
		}

		inline float GetX(){return this->X;}
		inline float GetY(){return this->Y;}

	private:
		float X, Y;
	};
}
