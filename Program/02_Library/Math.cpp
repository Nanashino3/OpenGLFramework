//****************************************************************************
// ファイル名：Math
// 作　成　日：2022/10/6
#include "Math.h"

namespace tkl
{
//********************************************************************************
// name... GetSidesPointAndPlane
// work... 指定座標が平面の表裏どちらに存在するか判定する
// arg1... 指定座標
// arg2... 平面の法線
// arg3... 平面上に存在するどこかの座標
// ret.... 表...1 	裏...-1		平面上...0
// tips... none
int GetSidesPointAndPlane(const Vector3& v, const Vector3& pn, const Vector3& pv)
{
	Vector3 vec = v - pv;
	float a = Vector3::Dot(vec, pn);

	if(a > 0.0f){ 
		return 1;	// 表
	}else if(a < 0.0f){
		return -1;	// 裏
	}
	return 0;		// 平面上
}

} // namespace tkl