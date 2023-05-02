// Copyright 2023. Jiwon-Nam All rights reserved.

#pragma once

#include <cmath>
#include <memory>
#include <limits>
#include <stdlib.h>
#include <time.h>

namespace Math
{
	const float PI = 3.1415926535f;
	const float INF = std::numeric_limits<float>::infinity();

	inline float ToRad(float Deg) { return Deg * PI / 180.f; }
	inline float ToDeg(float Rad) { return Rad * 180.f / PI; }
	inline bool IsNearZero(float Val, float Epsilon = 0.001f){ return fabs(Val) <= Epsilon; }

	inline float Cos(float Rad) { return cosf(Rad); }
	inline float Sin(float Rad) { return sinf(Rad); }
	inline float Tan(float Rad) { return tanf(Rad); }

	inline float Acos(float Rad) { return acosf(Rad); }
	inline float Asin(float Rad) { return asinf(Rad); }
	inline float Atan(float Rad) { return atanf(Rad); }

	inline float Sec(float Rad) { return 1.f / cosf(Rad); }
	inline float Csc(float Rad) { return 1.f / sinf(Rad); }
	inline float Cot(float Rad) { return 1.f / tanf(Rad); }

	inline float Abs(float Val) { return fabs(Val); }
	inline float Lerp(float Start, float End, float Rate) { return Start + Rate * (End - Start); }
	inline float Sqrt(float Val) { return sqrtf(Val); }
	inline float Fmod(float Num, float Den) { return fmod(Num, Den); }

	template <typename T>
	T Max(const T& Left, const T& Right) { return (Left < Right ? Right : Left); }

	template <typename T>
	T Min(const T& Left, const T& Right) { return (Left > Right ? Right : Left); }

	template <typename T>
	T Clamp(const T& Val, const T& Lower, const T& Upper) { return Min(Upper, Max(Lower, Val)); }

	template <typename T>
	T Random(T Min, T Max)
	{
		srand(time(NULL));

		T RandNum = (rand() % (Min - Max + 1)) + Min;
		return RandNum;
	}
}

class Vector2
{
public:
	float X;
	float Y;

	Vector2() : X(0.f), Y(0.f){}
	explicit Vector2(float _x, float _y) : X(_x), Y(_y){}

	void Set(float _x, float _y) { X = _x, Y = _y; }

	float Square() const { return (X * X + Y * Y); }
	float Length() const { return (Math::Sqrt(Square())); }

	friend Vector2 operator+(const Vector2& Left, const Vector2& Right)
	{
		return Vector2(Left.X + Right.X, Left.Y + Right.Y);
	}

	friend Vector2 operator-(const Vector2& Left, const Vector2& Right)
	{
		return Vector2(Left.X - Right.X, Left.Y - Right.Y);
	}

	friend Vector2 operator*(float Scalar, const Vector2& Vec)
	{
		return Vector2(Scalar * Vec.X, Scalar * Vec.Y);
	}

	friend Vector2 operator*(const Vector2& Vec, float Scalar)
	{
		return Vector2(Scalar * Vec.X, Scalar * Vec.Y);
	}

	Vector2& operator*=(float Scalar)
	{
		X *= Scalar;
		Y *= Scalar;
		return *this;
	}

	Vector2& operator+=(const Vector2& Right)
	{
		X += Right.X;
		Y += Right.Y;
		return *this;
	}

	Vector2& operator-=(const Vector2& Right)
	{
		X -= Right.X;
		Y -= Right.Y;
		return *this;
	}
	
	void Norm()
	{
		float Len = Length();
		X /= Len, Y /= Len;
	}

	static Vector2 Norm(Vector2& Vec)
	{
		Vector2 Temp = Vec;
		Temp.Norm();
		return Temp;
	}

	static float Dot(const Vector2& Left, const Vector2& Right)
	{
		return (Left.X * Right.X + Left.Y * Right.Y);
	}

	static Vector2 Lerp(const Vector2& Left, const Vector2& Right, float Rate)
	{
		return Vector2(Left + Rate * (Right - Left));
	}

	static Vector2 Reflect(const Vector2& Vec, const Vector2& Norm)
	{
		return Vec - 2.f * Vector2::Dot(Vec, Norm) * Norm;
	}

	static Vector2 Transform(const Vector2& Vec, const class Matrix3& Mat, float W = 1.f);

	static const Vector2 Zero;
	static const Vector2 UnitX;
	static const Vector2 UnitY;
};

class Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3() : X(0.f), Y(0.f), Z(0.f){}
	explicit Vector3(float _x, float _y, float _z) : X(_x), Y(_y), Z(_z) {}

	void Set(float _x, float _y, float _z) { X = _x, Y = _y, Z = _z; }

	float Square() const { return (X * X + Y * Y + Z * Z); }
	float Length() const { return (Math::Sqrt(Square())); }

	friend Vector3 operator+(const Vector3& Left, const Vector3& Right)
	{
		return Vector3(Left.X + Right.X, Left.Y + Right.Y, Left.Z + Right.Z);
	}

	friend Vector3 operator-(const Vector3& Left, const Vector3& Right)
	{
		return Vector3(Left.X - Right.X, Left.Y - Right.Y, Left.Z - Right.Z);
	}

	friend Vector3 operator*(float Scalar, const Vector3& Vec)
	{
		return Vector3(Scalar * Vec.X, Scalar * Vec.Y, Scalar * Vec.Z);
	}

	friend Vector3 operator*(const Vector3& Vec, float Scalar)
	{
		return Vector3(Scalar * Vec.X, Scalar * Vec.Y, Scalar * Vec.Z);
	}

	Vector3& operator*=(float Scalar)
	{
		X *= Scalar;
		Y *= Scalar;
		Z *= Scalar;
		return *this;
	}

	Vector3& operator+=(const Vector3& Right)
	{
		X += Right.X;
		Y += Right.Y;
		Z += Right.Z;
		return *this;
	}

	Vector3& operator-=(const Vector3& Right)
	{
		X -= Right.X;
		Y -= Right.Y;
		Z -= Right.Z;
		return *this;
	}
	
	void Norm()
	{
		float Len = Length();
		X /= Len, Y /= Len, Z /= Len;
	}

	static Vector3 Norm(const Vector3& Vec)
	{
		Vector3 Temp = Vec;
		Temp.Norm();
		return Temp;
	}

	static float Dot(const Vector3& Left, const Vector3& Right)
	{
		return (Left.X * Right.X + Left.Y * Right.Y + Left.Z * Right.Z);
	}

	static Vector3 Cross(const Vector3& Left, const Vector3& Right)
	{
		Vector3 Temp;
		Temp.X = Left.Y * Right.Z - Left.Z * Right.Y;
		Temp.Y = Left.Z * Right.X - Left.X * Right.Z;
		Temp.Z = Left.X * Right.Y - Left.Y * Right.X;
		return Temp;
	}

	static Vector3 Lerp(const Vector3& Left, const Vector3& Right, float Rate)
	{
		return Vector3(Left + Rate * (Right - Left));
	}

	static Vector3 Reflect(const Vector3& Vec, const Vector3& Norm)
	{
		return Vec - 2.f * Vector3::Dot(Vec, Norm) * Norm;
	}

	static Vector3 Transform(const Vector3& Vec, const class Matrix4& Mat, float W = 1.f);
	static Vector3 Transform(const Vector3& Vec, const class Quaternion& Quater);

	static const Vector3 Zero;
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
	static const Vector3 Inf;
};

class Matrix3
{
public:
	float Mat[3][3];

	Matrix3() { *this = Matrix3::Identity; }
	explicit Matrix3(float _mat[3][3]) { memcpy(Mat, _mat, (3 * 3) * sizeof(float)); }

	friend Matrix3 operator*(const Matrix3& Left, const Matrix3& Right)
	{
		Matrix3 Temp;

		for (short i = 0; i < 3; ++i)
		{
			for (short j = 0; j < 3; ++j)
			{
				Temp.Mat[i][j] = 
					Left.Mat[i][0] * Right.Mat[0][j] +
					Left.Mat[i][1] * Right.Mat[1][j] +
					Left.Mat[i][2] * Right.Mat[2][j];
			}
		}
		return Temp;
	}

	Matrix3& operator*=(const Matrix3& Right)
	{
		*this = *this * Right;
		return *this;
	}

	static Matrix3 CreateScale(float X, float Y)
	{
		float Temp[3][3] =
		{
			{X, 0.f, 0.f},
			{0.f, Y, 0.f},
			{0.f, 0.f, 1.f},
		};
		return Matrix3(Temp);
	}

	static Matrix3 CreateScale(const Vector2& Vec) { return CreateScale(Vec.X, Vec.Y); }
	static Matrix3 CreateScale(float Scale) { return CreateScale(Scale, Scale); }

	static Matrix3 CreateRotation(float Rad)
	{
		float Temp[3][3] =
		{
			{Math::Cos(Rad), Math::Sin(Rad), 0.f},
			{-Math::Sin(Rad), Math::Cos(Rad), 0.f},
			{0.f, 0.f, 1.f}
		};
		return Matrix3(Temp);
	}

	static Matrix3 CreateTranslation(const Vector2& Vec)
	{
		float Temp[3][3] =
		{
			{1.f, 0.f, 0.f},
			{0.f, 1.f, 0.f},
			{Vec.X, Vec.Y, 1.f}
		};
		return Matrix3(Temp);
	}

	static const Matrix3 Identity;
};

class Matrix4
{
public:
	float Mat[4][4];

	Matrix4() { *this = Matrix4::Identity; }
	explicit Matrix4(float _mat[4][4]) { memcpy(Mat, _mat, (4 * 4) * sizeof(float)); }

	friend Matrix4 operator*(const Matrix4& Left, const Matrix4& Right)
	{
		Matrix4 Temp;

		for (short i = 0; i < 4; ++i)
		{
			for (short j = 0; j < 4; ++j)
			{
				Temp.Mat[i][j] = 
					Left.Mat[i][0] * Right.Mat[0][j] +
					Left.Mat[i][1] * Right.Mat[1][j] +
					Left.Mat[i][2] * Right.Mat[2][j];
			}
		}
		return Temp;
	}

	Matrix4& operator*=(const Matrix4& Right)
	{
		*this = *this * Right;
		return *this;
	}

	void Invert();

	Vector3 GetTranslation() const { return Vector3(Mat[3][0], Mat[3][1], Mat[3][2]); }

	Vector3 GetXAxis() const { return Vector3::Norm(Vector3(Mat[0][1], Mat[0][1], Mat[0][2])); }
	Vector3 GetYAxis() const { return Vector3::Norm(Vector3(Mat[1][1], Mat[1][1], Mat[1][2])); }
	Vector3 GetZAxis() const { return Vector3::Norm(Vector3(Mat[2][1], Mat[2][1], Mat[2][2])); }

	Vector3 GetScale() const
	{
		Vector3 Temp;
		Temp.X = Vector3(Mat[0][1], Mat[0][1], Mat[0][2]).Length();
		Temp.Y = Vector3(Mat[1][1], Mat[1][1], Mat[1][2]).Length();
		Temp.Z = Vector3(Mat[2][1], Mat[2][1], Mat[2][2]).Length();
		return Temp;
	}

	static Matrix4 CreateScale(float X, float Y, float Z)
	{
		float Temp[4][4] =
		{
			{X, 0.f, 0.f, 0.f},
			{0.f, Y, 0.f, 0.f},
			{0.f, 0.f, Z, 0.f},
			{0.f, 0.f, 0.f, 1.f},
		};
		return Matrix4(Temp);
	}

	static Matrix4 CreateScale(const Vector3& Vec) { return CreateScale(Vec.X, Vec.Y, Vec.Z); }
	static Matrix4 CreateScale(float Scale) { return CreateScale(Scale, Scale, Scale); }

	static Matrix4 CreateRotationX(float Rad)
	{
		float Temp[4][4] =
		{
			{1.f, 0.f, 0.f, 0.f},
			{0.f, Math::Cos(Rad), Math::Sin(Rad), 0.f},
			{0.f, -Math::Sin(Rad), Math::Cos(Rad), 0.f},
			{0.f, 0.f, 0.f, 1.f}
		};
		return Matrix4(Temp);
	}

	static Matrix4 CreateRotationY(float Rad)
	{
		float Temp[4][4] =
		{
			{Math::Cos(Rad), 0.f, -Math::Sin(Rad), 0.f},
			{0.f, 1.f, 0.f, 0.f},
			{Math::Sin(Rad), 0.f, Math::Cos(Rad), 0.f},
			{0.f, 0.f, 0.f, 1.f}
		};
		return Matrix4(Temp);
	}

	static Matrix4 CreateRotationZ(float Rad)
	{
		float Temp[4][4] =
		{
			{Math::Cos(Rad), Math::Sin(Rad), 0.f, 0.f},
			{-Math::Sin(Rad), Math::Cos(Rad), 0.f, 0.f},
			{0.f, 0.f, 1.f, 0.f},
			{0.f, 0.f, 0.f, 1.f}
		};
		return Matrix4(Temp);
	}

	static Matrix4 CreateFromQuaternion(const class Quaternion& Quater);

	static Matrix4 CreateTranslation(const Vector3& Vec)
	{
		float Temp[4][4] =
		{
			{1.f, 0.f, 0.f, 0.f},
			{0.f, 1.f, 0.f, 0.f},
			{0.f, 0.f, 1.f, 0.f},
			{Vec.X, Vec.Y, Vec.Z, 1.f}
		};
		return Matrix4(Temp);
	}

	static Matrix4 CreateLookAt(const Vector3& Eye, const Vector3& Target, const Vector3& Up)
	{
		Vector3 AxisZ = Vector3::Norm(Target - Eye);
		Vector3 AxisX = Vector3::Norm(Vector3::Cross(Up, AxisZ));
		Vector3 AxisY = Vector3::Norm(Vector3::Cross(AxisZ, AxisX));
		
		Vector3 Trans
		(
			-Vector3::Dot(AxisX, Eye),
			-Vector3::Dot(AxisY, Eye),
			-Vector3::Dot(AxisZ, Eye)
		);

		float Temp[4][4] =
		{
			{AxisX.X, AxisY.X, AxisZ.X, 0.f},
			{AxisX.Y, AxisY.Y, AxisZ.Y, 0.f},
			{AxisX.Z, AxisY.Z, AxisZ.Z, 0.f},
			{Trans.X, Trans.Y, Trans.Z, 1.f}
		};
		return Matrix4(Temp);
	}

	static Matrix4 CreateOrtho(float Width, float Height, float Near, float Far)
	{
		float Temp[4][4] =
		{
			{2.f / Width, 0.f, 0.f, 0.f},
			{0.f, 2.f / Height, 0.f, 0.f},
			{0.f, 0.f, 1.f / (Far - Near), 0.f},
			{0.f, 0.f, Near / (Near - Far), 0.f}
		};
		return Matrix4(Temp);
	}

	static Matrix4 CreatePerspectiveFOV(float FovY, float Width, float Height, float Near, float Far)
	{
		float ScaleY = Math::Cot(FovY / 2.f);
		float ScaleX = ScaleY * Height / Width;

		float Temp[4][4] =
		{
			{ScaleX, 0.f, 0.f, 0.f},
			{0.f, ScaleY, 0.f, 0.f},
			{0.f, 0.f, Far / (Far - Near), 0.f},
			{0.f, 0.f, -Near * Far / (Far - Near), 0.f}
		};
		return Matrix4(Temp);
	}

	static Matrix4 CreateProjView(float Width, float Height)
	{
		float Temp[4][4] =
		{
			{2.f / Width, 0.f, 0.f, 0.f},
			{0.f, 2.f / Height, 0.f, 0.f},
			{0.f, 0.f, 1.f, 0.f},
			{0.f, 0.f, 1.f, 1.f}
		};
		return Matrix4(Temp);
	}

	static const Matrix4 Identity;
};

class Quaternion
{
public:
	float X;
	float Y;
	float Z;
	float W;

	Quaternion() { *this = Quaternion::Identity; }
	void Set(float _x, float _y, float _z, float _w) { X = _x, Y = _y, Z = _z, W = _w; }
	explicit Quaternion(float _x, float _y, float _z, float _w) { Set(_x, _y, _z, _w); }
	
	explicit Quaternion(const Vector3& Axis, float Rad)
	{
		float Scalar = Math::Sin(Rad / 2.f);
		X = Axis.X * Scalar, Y = Axis.Y * Scalar, Z = Axis.Z * Scalar, W = Math::Cos(Rad / 2.f);
	}

	void Conjugate() { X *= -1.f, Y *= -1.f, Z *= -1.f; }
	float Square() const { return (X * X + Y * Y + Z * Z + W * W); }
	float Length() const { return Math::Sqrt(Square()); }

	void Norm()
	{
		float Len = Length();
		X /= Len, Y /= Len, Z /= Len, W /= Len;
	}

	static Quaternion Norm(const Quaternion& Quater)
	{
		Quaternion Temp = Quater;
		Temp.Norm();
		return Temp;
	}

	static Quaternion Lerp(const Quaternion& Left, const Quaternion& Right, float Rate)
	{
		Quaternion Temp
		(
			Math::Lerp(Left.X, Right.X, Rate),
			Math::Lerp(Left.Y, Right.Y, Rate),
			Math::Lerp(Left.Z, Right.Z, Rate),
			Math::Lerp(Left.W, Right.W, Rate)
		);
		Temp.Norm();
		return Temp;
	}

	static float Dot(const Quaternion& Left, const Quaternion& Right)
	{
		return Left.X * Right.X + Left.Y * Right.Y + Left.Z * Right.Z + Left.W * Right.W;
	}

	static Quaternion Slerp(const Quaternion& Left, const Quaternion& Right, float Rate)
	{
		float RawCosm = Quaternion::Dot(Left, Right);
		float Cosom = RawCosm < 0.f ? -RawCosm : RawCosm;
		float Scale0, Scale1;

		if (Cosom < 0.9999f)
		{
			const float Rad = Math::Acos(Cosom);
			const float CscRad = Math::Csc(Rad);

			Scale0 = Math::Sin((1.f - Rate) * Rad) * CscRad;
			Scale1 = Math::Sin(Rate * Rad) * CscRad;
		}
		else
		{
			Scale0 = 1.f - Rate;
			Scale1 = Rate;
		}

		Scale1 *= RawCosm < 0.f ? -1 : 1;

		Quaternion Temp
		(
			Scale0 * Left.X + Scale1 * Right.X,
			Scale0 * Left.Y + Scale1 * Right.Y,
			Scale0 * Left.Z + Scale1 * Right.Z,
			Scale0 * Left.W + Scale1 * Right.W
		);

		Temp.Norm();
		return Temp;
	}

	static Quaternion Concatenate(const Quaternion& Q, const Quaternion& P)
	{
		Vector3 Qv(Q.X, Q.Y, Q.Z), Pv(P.X, P.Y, P.Z);
		Vector3 CrossVec = P.W * Qv + Q.W * Pv + Vector3::Cross(Pv, Qv);

		Quaternion Temp
		(
			CrossVec.X,
			CrossVec.Y,
			CrossVec.Z,
			P.W * Q.W - Vector3::Dot(Pv, Qv)
		);
		return Temp;
	}

	static const Quaternion Identity;
};

class Calculas
{
public:
	virtual float Function(float X);

	float NumericDifferentiate(float X, float H = 1.0e-8);
	float NumericIntegrate(float Start, float End, int Interval);
};

namespace Color
{
	static const Vector3 Black(0.f, 0.f, 0.f);
	static const Vector3 White(1.f, 1.f, 1.f);
	
	static const Vector3 Red(1.f, 0.f, 0.f);
	static const Vector3 Green(0.f, 1.f, 0.f);
	static const Vector3 Blue(0.f, 0.f, 1.f);
	
	static const Vector3 Yellow(1.f, 1.f, 0.f);
	static const Vector3 Magenta(1.f, 0.f, 1.f);
	static const Vector3 Cyan(0.f, 1.f, 1.f);
}