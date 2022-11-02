#pragma once

#include "../02_Library/Vector.h"
namespace tkl
{
	//*****************************************************************************
	// work... 線分と平面の衝突判定
	// arg1... 線分の始点
	// arg2... 線分の終点
	// arg3... 平面上の座標 ( 0, 0, 0 以外 )
	// arg4... 平面の法線
	// arg5... 衝突点の受け取り用( 必要なければ省略可 )
	// ret.... [衝突している : true] [衝突していない : false]
	// tips... 衝突していない場合 arg5 で渡した引数は変化なし
	bool IsIntersectLinePlane(const Vector3& lineStart, const Vector3& lineEnd,
							  const Vector3& planePos, const Vector3& planeNormal,
							  Vector3* intersectPos = nullptr);
}