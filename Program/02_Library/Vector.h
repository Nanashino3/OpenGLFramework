//****************************************************************************
// ファイル名：Vector(ベクトルクラス)
// 作　成　日：2022/10/6
#ifndef _VECTOR_H_
#define _VECTOR_H_

namespace tkl
{
class Matrix;
class Quaternion;
class Vector3
{
public:
	union{
		struct{
			float mX, mY, mZ;
		};
		float mVec[3];
	};

	Vector3() : mX(0.0f), mY(0.0f), mZ(0.0f){}
	Vector3(float x, float y, float z) : mX(x), mY(y), mZ(z){}

	//******************************************************
	// 単項演算子
	Vector3 operator-() const;
	//******************************************************

	//******************************************************
	// ベクトル同士の計算
	Vector3 operator+(const Vector3& a) const;
	Vector3& operator+=(const Vector3& a);
	Vector3 operator-(const Vector3& a) const;
	Vector3& operator-=(const Vector3& a);
	bool operator==(const Vector3& a);
	//******************************************************

	//******************************************************
	// ベクトルとスカラーの計算
	Vector3 operator+(float s) const;
	Vector3& operator+=(float s);
	Vector3 operator-(float s) const;
	Vector3& operator-=(float s);
	Vector3 operator*(float s) const;
	Vector3& operator*=(float s);
	//******************************************************

	// ベクトルの配列を返す
	float* GetData() const { return (float*)(&mVec[0]); }

	// ベクトルの正規化
	static Vector3 Normalize(const Vector3& v);
	// ベクトルの外積
	static Vector3 Cross(const Vector3& v1, const Vector3& v2);
	// ベクトルの内積
	static float Dot(const Vector3& v1, const Vector3& v2);
	// 2点間の距離を求める
	static float Distance(const Vector3& v1, const Vector3& v2);
	// 長さを求める
	static float Magnitude(const Vector3& v1);

	// ベクトルをクォータニオンに射影する
	static Vector3 TransformCoord(const Vector3& v, const Quaternion& q);
	// ベクトルをマトリックスに射影する
	static Vector3 TransformCoord(const Vector3& v, const Matrix& m);
	// スクリーン上にレイを作成
	static Vector3 CreateScreenRay(const Vector3& screenPos, int screenW, int screenH, const tkl::Matrix& view, const tkl::Matrix& projection);

	static Vector3 ConvertWorldPosToScreenPos(int screenW, int screenH, const tkl::Vector3& worldPos, const tkl::Matrix& view, const tkl::Matrix& projection);

	static const Vector3 ZERO;
	static const Vector3 UNITX;
	static const Vector3 UNITY;
	static const Vector3 UNITZ;
	static const Vector3 NEG_UNITX;
	static const Vector3 NEG_UNITY;
	static const Vector3 NEG_UNITZ;
};

} // namespace tkl

#endif