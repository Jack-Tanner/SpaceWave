#pragma once

namespace vctr
{
	class GameVector
	{
	private:
		float X;
		float Y;

	public:
		// Constructors
		GameVector() : X (0.0f), Y(0.0f) {}
		GameVector(float x, float y) : X (x), Y(y) {}

		// Copy Constructor
		GameVector(const GameVector& vect) { this->X = vect.X; this->Y = vect.Y; }

		// Destructor
		~GameVector() {};

		// Operators
		// Not equal to another vector
		inline bool GameVector::operator!=(const GameVector& vec1) const
		{
			return X != vec1.X || Y != vec1.Y;
		}

		// equal to another vector
		inline bool GameVector::operator==(const GameVector& vec2) const
		{
			return (*this != vec2) == false;
		}

		// vector = vector + another vector
		inline GameVector& GameVector::operator+=(const GameVector& pVector)
		{
			X += pVector.X;
			Y += pVector.Y;
			return *this;
		}

		// vector = vector - another vector
		inline GameVector& GameVector::operator-=(const GameVector& pVector)
		{
			X -= pVector.X;
			Y -= pVector.Y;
			return *this;
		}

		// vector = vector + number
		inline GameVector& GameVector::operator+=(const float number)
		{
			X += number;
			Y += number;
			return *this;
		}

		// vector = vector - number
		inline GameVector& GameVector::operator-=(const float number)
		{
			X -= number;
			Y -= number;
			return *this;
		}

		// vector = vector / number
		inline GameVector& GameVector::operator/=(const float number)
		{
			X /= number;
			Y /= number;
			return *this;
		}

		friend inline GameVector operator+(const GameVector& vect1, const GameVector& vect2)
		{
			return GameVector(vect1.X + vect2.X, vect1.Y + vect2.Y);
		}
		friend inline GameVector operator-(const GameVector& vect1, const GameVector& vect2)
		{
			return GameVector(vect1.X - vect2.X, vect1.Y - vect2.Y);
		}
		inline GameVector operator-(GameVector& vect)
		{
			return vect * -1;
		}
		friend inline GameVector operator*(const GameVector& vect1, float number)
		{
			return GameVector(vect1.X * number, vect1.Y * number);
		}
		friend inline GameVector operator/(const GameVector& vect1, float number)
		{
			return GameVector(vect1.X / number, vect1.Y / number);
		}
		friend inline GameVector operator*(const GameVector& vect1, const GameVector& vect2)
		{
			return GameVector(vect1.X * vect2.X, vect1.Y * vect2.Y);
		}
		friend inline GameVector operator/(const GameVector& vect1, const GameVector& vect2)
		{
			return GameVector(vect1.X / vect2.X, vect1.Y / vect2.Y);
		}
		
		inline float GetX(){return this->X;}
		inline float GetY(){return this->Y;}

	};
}