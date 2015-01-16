#pragma once

class Coords2D
{
private:
	float X, Y;

public:

	// Constructors
	Coords2D() : X (0.0f), Y(0.0f) {}
	Coords2D(float x, float y) : X (x), Y(y) {}

	// Copy Constructor
	Coords2D(const Coords2D& param) { this->X = param.X; this->Y = param.Y; }

	// Adding coordinates
	friend inline Coords2D operator + (const Coords2D& param1, const Coords2D& param2)
	{
		return Coords2D(param1.X + param2.X, param1.Y + param2.Y);
	}

	// Subtracting coordinates
	friend inline Coords2D operator - (const Coords2D& param1, const Coords2D& param2)
	{
		return Coords2D(param1.X - param2.X, param1.Y - param2.Y);
	}

	// Multiplying coordinates by other coordinates
	friend inline Coords2D operator *(const Coords2D& param1, const Coords2D& param2)
	{
		return Coords2D(param1.X * param2.X, param1.Y * param2.Y);
	}

	// Dividing coordinates by other coordinates
	friend inline Coords2D operator/(const Coords2D& param1, const Coords2D& param2)
	{
		return Coords2D(param1.X / param2.X, param1.Y / param2.Y);
	}

	// Adding a number to coordinates
	inline Coords2D& Coords2D::operator+=(const float number)
	{
		X += number;
		Y += number;
		return *this;
	}


	// Subtracting a number from coordinates
	inline Coords2D& Coords2D::operator-=(const float number)
	{
		X -= number;
		Y -= number;
		return *this;
	}

	// Multiplying coordinates by a number
	inline Coords2D& operator*(const Coords2D& param, float number)
	{
		return Coords2D(param.X * number, param.Y * number);
	}

	// Dividing coordinates by a number
	friend inline Coords2D operator/(const Coords2D& param, float number)
	{
		return Coords2D(param.X / number, param.Y / number);
	}

	// Negating coordinates (uses the overloaded multiplier operator)
	inline Coords2D operator -(Coords2D& param)
	{
		return param * -1;
	}

	// Not equal to another set of coordinates
	inline bool Coords2D::operator!=(const Coords2D& param) const
	{
		return X != param.X || Y != param.Y;
	}

	// equal to another vector (uses != overloaded operator)
	inline bool Coords2D::operator==(const Coords2D& param) const
	{
		return (*this != param) == false;
	}

	// Coords2D = Coords2D + another Coords2D
	inline Coords2D& Coords2D::operator+=(const Coords2D& param)
	{
		X += param.X;
		Y += param.Y;
		return *this;
	}

	// vector = vector - another vector
	inline Coords2D& Coords2D::operator-=(const Coords2D& param)
	{
		X -= param.X;
		Y -= param.Y;
		return *this;
	}

	Coords2D operator + (float param)
	{
		Coords2D temp;
		temp.x += param;
		temp.y += param;
		return temp;
	}
	Coords2D operator - (float param)
	{
		Coords2D temp;
		temp.x -= param;
		temp.y -= param;
		return temp;
	}
	Coords2D operator / (float param)
	{
		Coords2D temp;
		temp.x /= param;
		temp.y /= param;
		return temp;
	}
	//Coords2D operator * (float param)
	//{
	//	Coords2D temp;
	//	temp.x *= param;
	//	temp.y *= param;
	//	return temp;
	//}
	bool operator > (Coords2D param)
	{
		if ( x + y > param.x + param.y )
			return 1;
		else
			return 0;
	}
	bool operator >= (Coords2D param)
	{
		if ( x + y >= param.x + param.y )
			return 1;
		else
			return 0;
	}
	bool operator < (Coords2D param)
	{
		if ( x + y < param.x + param.y )
			return 1;
		else
			return 0;
	}
	bool operator <= (Coords2D param)
	{
		if ( x + y <= param.x + param.y )
			return 1;
		else
			return 0;
	}


	bool operator == (Coords2D param)
	{
		if ( x == param.x && y == param.y )
			return 1;
		else
			return 0;
	}

	float GetDistanceFrom( Coords2D point )
	{
		Coords2D dist;
		float distance;

		dist.x = ( point.x - x ) * ( point.x - x );
		dist.y = ( point.y - y ) * ( point.y - y );

		distance = sqrt( dist.x + dist.y );
		return distance;
	}
};
