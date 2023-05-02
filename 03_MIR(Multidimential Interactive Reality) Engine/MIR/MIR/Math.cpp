// Copyright 2023. Jiwon-Nam All rights reserved.

#include "Math.h"

const Vector2 Vector2::Zero(0.f, 0.f);
const Vector2 Vector2::UnitX(1.f, 0.f);
const Vector2 Vector2::UnitY(0.f, 1.f);

const Vector3 Vector3::Zero(0.f, 0.f, 0.f);
const Vector3 Vector3::UnitX(1.f, 0.f, 0.f);
const Vector3 Vector3::UnitY(0.f, 1.f, 0.f);
const Vector3 Vector3::UnitZ(0.f, 0.f, 1.f);
const Vector3 Vector3::Inf(Math::INF, Math::INF, Math::INF);

static float M3Id[3][3] =
{
	{1.f, 0.f, 0.f},
	{0.f, 1.f, 0.f},
	{0.f, 0.f, 1.f}
};

const Matrix3 Matrix3::Identity(M3Id);

static float M4Id[4][4] =
{
	{1.f, 0.f, 0.f, 0.f},
	{0.f, 1.f, 0.f, 0.f},
	{0.f, 0.f, 1.f, 0.f},
	{0.f, 0.f, 0.f, 1.f}
};

const Matrix4 Matrix4::Identity(M4Id);

const Quaternion Quaternion::Identity(0.f, 0.f, 0.f, 1.f);

Vector2 Vector2::Transform(const Vector2& Vec, const Matrix3& Mat, float W)
{
	Vector2 Temp
	(
		Vec.X * Mat.Mat[0][0] + Vec.Y * Mat.Mat[1][0] + W * Mat.Mat[2][0],
		Vec.Y * Mat.Mat[0][1] + Vec.Y * Mat.Mat[1][1] + W * Mat.Mat[2][1]
	);
	return Temp;
}

Vector3 Vector3::Transform(const Vector3& Vec, const Matrix4& Mat, float W)
{
	Vector3 Temp
	(
		Vec.X * Mat.Mat[0][0] + Vec.Y * Mat.Mat[1][0] + Vec.Z * Mat.Mat[2][0] + W * Mat.Mat[3][0],
		Vec.Y * Mat.Mat[0][1] + Vec.Y * Mat.Mat[1][1] + Vec.Z * Mat.Mat[2][1] + W * Mat.Mat[3][1],
		Vec.Z * Mat.Mat[0][2] + Vec.Y * Mat.Mat[1][2] + Vec.Z * Mat.Mat[2][2] + W * Mat.Mat[3][2]
	);
	return Temp;
}

Vector3 Vector3::Transform(const Vector3& Vec, const Quaternion& Quater)
{
	Vector3 Qv(Quater.X, Quater.Y, Quater.Z), Temp = Vec;
	Temp += 2.f * Vector3::Cross(Qv, Vector3::Cross(Qv, Vec) + Quater.W * Vec);
	return Temp;
}

void Matrix4::Invert()
{
	const short Size = 4;
    float AugMat[Size][2 * Size];

    for (short i = 0; i < Size; ++i)
    {
        for (short j = 0; j < Size; ++j)
        {
            AugMat[i][j] = Matrix4::Mat[i][j];
        }
        AugMat[i][i + Size] = 1.0;
    }

    for (int i = 0; i < Size; ++i)
    {
        float pivot = AugMat[i][i];

        for (short j = 0; j < 2 * Size; ++j)
        {
            AugMat[i][j] /= pivot;
        }

        for (short j = 0; j < Size; ++j)
        {
            if (i != j)
            {
                float Factor = AugMat[j][i];
                
                for (short k = 0; k < 2 * Size; ++k)
                {
                    AugMat[j][k] -= Factor * AugMat[i][k];
                }
            }
        }
    }

    for (short i = 0; i < Size; i++)
    {
        for (short j = 0; j < Size; ++j)
        {
            Matrix4::Mat[i][j] = AugMat[i][j + Size];
        }
    }
}

float Calculas::NumericDifferentiate(float X, float H = 1.0e-8)
{
	return (Calculas::Function(X + H) - Calculas::Function(X)) / H;
}

float Calculas::NumericIntegrate(float Start, float End, int Interval)
{
    float H = (End - Start) / Interval;
    float X = Start;
    float Sum = 0;

    while (Interval--)
    {
        Sum += (Calculas::Function(X) + Calculas::Function(X + H)) * H / 2;
        X += H;
    }
    return Sum;
}