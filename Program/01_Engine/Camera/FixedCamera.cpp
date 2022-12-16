//****************************************************************************
// �t�@�C�����FFixedCamera(�Œ�J�����N���X)
// ��@���@���F2022/10/26
#include "FixedCamera.h"

namespace tkl
{
FixedCamera::FixedCamera(int screenWidth, int screenHeight)
: Camera(screenWidth, screenHeight)
{}

FixedCamera::~FixedCamera()
{}

//****************************************************************************
// �֐����FUpdate
// �T�@�v�F�X�V����
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�X�V�������s��
//****************************************************************************
void FixedCamera::Update()
{
	mView = tkl::Matrix::CreateLookAt(mCamPos, mTargetPos, mUpVector);
	mProjection = tkl::Matrix::CreatePerspectiveProjection(mAngle, mAspect, mNear, mFar);
}

} // namespace tkl