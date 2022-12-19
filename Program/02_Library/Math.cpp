//****************************************************************************
// �t�@�C�����FMath
// ��@���@���F2022/10/6
#include "Math.h"

namespace tkl
{
//********************************************************************************
// name... GetSidesPointAndPlane
// work... �w����W�����ʂ̕\���ǂ���ɑ��݂��邩���肷��
// arg1... �w����W
// arg2... ���ʂ̖@��
// arg3... ���ʏ�ɑ��݂���ǂ����̍��W
// ret.... �\...1 	��...-1		���ʏ�...0
// tips... none
int GetSidesPointAndPlane(const Vector3& v, const Vector3& pn, const Vector3& pv)
{
	Vector3 vec = v - pv;
	float a = Vector3::Dot(vec, pn);

	if(a > 0.0f){ 
		return 1;	// �\
	}else if(a < 0.0f){
		return -1;	// ��
	}
	return 0;		// ���ʏ�
}

} // namespace tkl