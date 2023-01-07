//****************************************************************************
// �t�@�C�����FPostureControlCamera(�p������J�����N���X)
// ��@���@���F2022/10/26
#include "PostureControlCamera.h"

#include "../../02_Library/Math.h"
#include "../../02_Library/Input.h"

namespace tkl
{
PostureControlCamera::PostureControlCamera(int screenWidth, int screenHeight)
: Camera(screenWidth, screenHeight)
, mOnClickPos(tkl::Vector3::ZERO)
, mMovePos(tkl::Vector3::ZERO)
, mIsMouseMove(false)
{}

PostureControlCamera::~PostureControlCamera()
{}

//****************************************************************************
// �֐����FUpdate
// �T�@�v�F�X�V����
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�X�V�������s��
//****************************************************************************
void PostureControlCamera::Update()
{
	// �J�����Y�[���C���E�A�E�g(�W����������)
	float scrollVal = static_cast<float>(tkl::Input::GetMouseScrollValue() * 10.0f);
	mCamPos += Front() * scrollVal;

	Input();
	Move();

	// �����_�Ə�����x�N�g�����X�V
	mTargetPos = mCamPos + tkl::Vector3::TransformCoord(tkl::Vector3::NEG_UNITZ, mRotation);
	mUpVector = tkl::Vector3::TransformCoord(tkl::Vector3::UNITY, mRotation);

	// �s��
	mView = tkl::Matrix::CreateLookAt(mCamPos, mTargetPos, mUpVector);
	mProjection = tkl::Matrix::CreatePerspectiveProjection(mAngle, mAspect, mNear, mFar);
}

//****************************************************************************
// �֐����FInput
// �T�@�v�F���͏���
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF���͂ɂ�鏈�����s��
//****************************************************************************
void PostureControlCamera::Input()
{
	// �N���b�N�������W���L�^����
	float clickPosX = 0, clickPosY = 0;
	if(tkl::Input::IsMouseDownTrigger(eMouse::MOUSE_CENTER, eMouse::MOUSE_RIGHT)){
		tkl::Input::GetMousePoint(clickPosX, clickPosY);
		mOnClickPos = tkl::Vector3(clickPosX, clickPosY, 0.f);
	}
	// �N���b�N�������W������������
	if(tkl::Input::IsMouseReleaseTrigger(eMouse::MOUSE_CENTER, eMouse::MOUSE_RIGHT)){
		mOnClickPos = tkl::Vector3(tkl::Vector3::ZERO);
		mMovePos = tkl::Vector3(tkl::Vector3::ZERO);
	}

	// ���݈ʒu���擾
	clickPosX = 0, clickPosY = 0;
	if(tkl::Input::IsMouseDown(eMouse::MOUSE_CENTER, eMouse::MOUSE_RIGHT)){
		tkl::Input::GetMousePoint(clickPosX, clickPosY);

		// �}�E�X�ړ����Ă��邩�ǂ���
		mIsMouseMove = true;
		if(mMovePos.mX == clickPosX && mMovePos.mY == clickPosY){
			mIsMouseMove = !mIsMouseMove;
			mOnClickPos = mMovePos;
		}else{
			mMovePos.mX = static_cast<float>(clickPosX);
			mMovePos.mY = static_cast<float>(clickPosY);
		}
	}
}

//****************************************************************************
// �֐����FMove
// �T�@�v�F�ړ�����
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�K�����̈ړ�����
//****************************************************************************
void PostureControlCamera::Move()
{
	float dx = 0.0f, dy = 0.0f;
	if(mIsMouseMove){
		dx = (mOnClickPos.mX - mMovePos.mX) / (mScreenWidth >> 1);
		dy = (mOnClickPos.mY - mMovePos.mY) / (mScreenHeight >> 1);
	}

	tkl::Vector3 axis = tkl::Vector3::Cross(Front(), mUpVector);

	// ���s�ړ�
	if(tkl::Input::IsMouseDown(eMouse::MOUSE_CENTER)){
		mCamPos += axis * (10.0f * dx);
		mCamPos.mY -= 10.0f * dy;
	}

	// �����ړ�
	if(tkl::Input::IsMouseDown(eMouse::MOUSE_RIGHT)){
		mRotation *= tkl::Quaternion::RotationAxis(axis, tkl::ToRadian(dy * 5.0f));
		mRotation *= tkl::Quaternion::RotationAxis({0.f, 1.f, 0.f}, tkl::ToRadian(dx * 5.0f));
	}
}

} // namespace tkl