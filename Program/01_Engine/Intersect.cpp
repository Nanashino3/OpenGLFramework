#include <cmath>
#include "Intersect.h"
#include "../02_Library/Math.h"

namespace tkl
{
//****************************************************************************
// 関数名：IsIntersectPointRect
// 概　要：衝突検知(点と矩形)
// 引　数：arg1 横方向成分の点
// 　　　：arg2 縦方向成分の点
// 　　　：arg3 横方向成分の矩形中心
// 　　　：arg4 縦方向成分の矩形中心
// 　　　：arg5 矩形のサイズ
// 戻り値： [衝突している : true]   [衝突していない : false]
// 詳　細：点と矩形の衝突検知を行い結果を返す
//****************************************************************************
bool IsIntersectPointRect(float ph, float pv, float rh, float rv, int size)
{
	return IsIntersectPointRect(ph, pv, rh, rv, size, size);
}

//****************************************************************************
// 関数名：IsIntersectPointRect
// 概　要：衝突検知(点と矩形)
// 引　数：arg1 横方向成分の点
// 　　　：arg2 縦方向成分の点
// 　　　：arg3 横方向成分の矩形中心
// 　　　：arg4 縦方向成分の矩形中心
// 　　　：arg5 横方向の矩形サイズ
// 　　　：arg6 縦方向の矩形サイズ
// 戻り値： [衝突している : true]   [衝突していない : false]
// 詳　細：点と矩形の衝突検知を行い結果を返す
//****************************************************************************
bool IsIntersectPointRect(float ph, float pv, float rh, float rv, int rhSize, int rvSize)
{
	float left	 = rh - (rhSize >> 1);
	float right	 = rh + (rhSize >> 1);
	float top	 = rv + (rvSize >> 1);
	float bottom = rv - (rvSize >> 1);

	if(left > ph)	{ return false; }
	if(right < ph)	{ return false; }
	if(top < pv)	{ return false; }
	if(bottom > pv)	{ return false; }

	return true;
}

//****************************************************************************
// 関数名：IsIntersectLinePlane
// 概　要：衝突検知(線分と平面)
// 引　数：arg1 線分の始点
// 　　　：arg2 線分の終点
// 　　　：arg3 平面上の座標 ( 0, 0, 0 以外 )
// 　　　：arg4 平面の法線
// 　　　：arg4 衝突点の受け取り用( 必要なければ省略可 )
// 戻り値： [衝突している : true]   [衝突していない : false]
// 詳　細：線分と矩形の衝突検知を行い結果を返す
// 　　　：衝突していない場合 arg5 で渡した引数は変化なし
//****************************************************************************
bool IsIntersectLinePlane(const Vector3& lineStart, const Vector3& lineEnd,
						  const Vector3& planePos, const Vector3& planeNormal,
						  Vector3* intersectPos)
{
	if(1 == GetSidesPointAndPlane(lineStart, planeNormal, planePos) && 1 == GetSidesPointAndPlane(lineEnd, planeNormal, planePos)){ return false; }
	if(-1 == GetSidesPointAndPlane(lineStart, planeNormal, planePos) && -1 == GetSidesPointAndPlane(lineEnd, planeNormal, planePos)){ return false; }

	Vector3 ln = lineEnd - lineStart;
	Vector3 pa = lineStart - planePos;
	Vector3 pb = lineEnd - planePos;

	float na = fabsf(Vector3::Dot(pa, planeNormal));
	float nb = fabsf(Vector3::Dot(pb, planeNormal));

	if(intersectPos){ *intersectPos = lineStart + ln * (na / (na + nb)); }

	return true;
}

//****************************************************************************
// 関数名：IsIntersectAABB
// 概　要：衝突検知(AABB同士)
// 引　数：arg1 1つ目の対象の位置
// 　　　：arg2 1つ目の対象のサイズ
// 　　　：arg3 2つ目の対象の位置
// 　　　：arg4 2つ目の対象のサイズ
// 戻り値： [衝突している : true]   [衝突していない : false]
// 詳　細：AABBとAABBの衝突検知を行い結果を返す
//****************************************************************************
bool IsIntersectAABB(const Vector3& v1, float v1Size, const Vector3& v2, float v2Size)
{
	tkl::Vector3 v1Min = tkl::Vector3(v1.mX - v1Size, v1.mY - v1Size, v1.mZ - v1Size);
	tkl::Vector3 v1Max = tkl::Vector3(v1.mX + v1Size, v1.mY + v1Size, v1.mZ + v1Size);
	tkl::Vector3 v2Min = tkl::Vector3(v2.mX - v2Size, v2.mY - v2Size, v2.mZ - v2Size);
	tkl::Vector3 v2Max = tkl::Vector3(v2.mX + v2Size, v2.mY + v2Size, v2.mZ + v2Size);

	return (v1Min.mX <= v2Max.mX && v1Max.mX >= v2Min.mX) && 
		   (v1Min.mY <= v2Max.mY && v1Max.mY >= v2Min.mY) && 
		   (v1Min.mZ <= v2Max.mZ && v1Max.mZ >= v2Min.mZ);
}

} // namespace tkl