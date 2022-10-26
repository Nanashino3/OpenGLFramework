#include "PostureControlCamera.h"

#include "../../02_Library/Math.h"
#include "../../02_Library/Input.h"

PostureControlCamera::PostureControlCamera(int screenWidth, int screenHeight)
: Camera(screenWidth, screenHeight)
, mOnClickPos(tkl::Vector3::ZERO)
, mMovePos(tkl::Vector3::ZERO)
, mIsMouseMove(false)
{}

PostureControlCamera::~PostureControlCamera()
{}

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
	mViewProjection  = tkl::Matrix::CreatePerspectiveProjection(mAngle, mAspect, mNear, mFar);
	mViewProjection *= tkl::Matrix::CreateLookAt(mCamPos, mTargetPos, mUpVector);
}

// ���͏���
void PostureControlCamera::Input()
{
	// �N���b�N�������W���L�^����
	int tempPosX = 0, tempPosY = 0;
	if(tkl::Input::IsMouseDownTrigger(eMouse::MOUSE_CENTER, eMouse::MOUSE_RIGHT)){
		tkl::Input::GetMousePoint(&tempPosX, &tempPosY);
		mOnClickPos = tkl::Vector3(tempPosX, tempPosY, 0);
	}
	// �N���b�N�������W������������
	if(tkl::Input::IsMouseReleaseTrigger(eMouse::MOUSE_CENTER, eMouse::MOUSE_RIGHT)){
		mOnClickPos = tkl::Vector3(tkl::Vector3::ZERO);
		mMovePos = tkl::Vector3(tkl::Vector3::ZERO);
	}

	// ���݈ʒu���擾
	tempPosX = 0, tempPosY = 0;
	if(tkl::Input::IsMouseDown(eMouse::MOUSE_CENTER, eMouse::MOUSE_RIGHT)){
		tkl::Input::GetMousePoint(&tempPosX, &tempPosY);

		// �}�E�X�ړ����Ă��邩�ǂ���
		mIsMouseMove = true;
		if(mMovePos.mX == tempPosX && mMovePos.mY == tempPosY){
			mIsMouseMove = !mIsMouseMove;
			mOnClickPos = mMovePos;
		}else{
			mMovePos.mX = static_cast<float>(tempPosX);
			mMovePos.mY = static_cast<float>(tempPosY);
		}
	}
}

// �ړ�����
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
		mRotation *= tkl::Quaternion::RotationAxis({ 0, 1, 0 }, tkl::ToRadian(dx * 5.0f));
	}
}