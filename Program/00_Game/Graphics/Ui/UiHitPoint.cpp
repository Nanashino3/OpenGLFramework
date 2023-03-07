//****************************************************************************
// �t�@�C�����FUiHitPoint(�q�b�g�|�C���gUI�N���X)
// ��@���@���F2023/01/30
#include "UiHitPoint.h"

#include "../../../00_Game/GameObject/Parameter.h"
#include "../../../00_Game/GameObject/AdvanceUnit.h"

#include "../../../01_Engine/System.h"
#include "../../../01_Engine/ResourceManager.h"
#include "../../../01_Engine/Camera/ScreenCamera.h"
#include "../../../01_Engine/Graphics/Geometry/Mesh.h"
#include "../../../01_Engine/Graphics/Geometry/Texture.h"

static constexpr const char* BG_UI_FILE = "Resource/texture/ui/image_1.png";
static constexpr const char* UI_FILE = "Resource/texture/ui/image_2.png";

UiHitPoint::UiHitPoint(std::shared_ptr<Parameter> param)
: mScreenW(0), mScreenH(0)
, mMaxHitPoint(0.0f)
, mRectW(0.0f)
, mObject(nullptr)
, mParam(param)
, mTexture(nullptr)
, mBackGroundTexture(nullptr)
, m2DCam(nullptr)
{}

UiHitPoint::~UiHitPoint()
{}

//****************************************************************************
// �֐����FInitialize
// �T�@�v�F������
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�������������s��
//****************************************************************************
void UiHitPoint::Initialize(std::shared_ptr<AdvanceUnit> object)
{
	mObject = object;
	mMaxHitPoint = mObject->GetHitPoint();

	// �E�B���h�E�T�C�Y���擾��2D�p�J��������
	tkl::System::GetInstance()->GetWindowSize(&mScreenW, &mScreenH);
	m2DCam = std::make_shared<tkl::ScreenCamera>(mScreenW, mScreenH);

	// �q�b�g�|�C���g�̃e�N�X�`������
	mTexture = tkl::Mesh::CreateMeshForSprite();
	mTexture->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(UI_FILE));
	mRectW = (mTexture->GetTexture()->GetWidth()) * 0.5f;

	// �q�b�g�|�C���g�̔w�i�e�N�X�`������
	mBackGroundTexture = tkl::Mesh::CreateMeshForSprite();
	mBackGroundTexture->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile(BG_UI_FILE));
}

//****************************************************************************
// �֐����FUpdate
// �T�@�v�F�X�V����
// ���@���Farg1 �f���^�^�C��
// �߂�l�F�Ȃ�
// �ځ@�ׁF�X�V�������s��
//****************************************************************************
void UiHitPoint::Update()
{
	m2DCam->Update();

	// ���[���h���W���X�N���[�����W�֕ϊ�
	tkl::Vector3 unitPos = mObject->GetPosition();
	tkl::Vector3 screenPos 
		= tkl::Vector3::ConvertWorldPosToScreenPos(mScreenW, mScreenH, unitPos, mParam->GetCamera()->GetView(), mParam->GetCamera()->GetProjection());
	
	// �q�b�g�|�C���gUI�̔w�i
	tkl::Vector3 bgPos = tkl::Vector3(screenPos.mX, screenPos.mY + 30.0f, 0.0f);
	mBackGroundTexture->SetPosition(bgPos);

	// �q�b�g�|�C���gUI
	tkl::Vector3 uiPos = tkl::Vector3(screenPos.mX, screenPos.mY + 30.0f, 0.0f);
	float uiRatio = mObject->GetHitPoint() / mMaxHitPoint;
	uiPos.mX = screenPos.mX + (mRectW * uiRatio - mRectW);
	mTexture->SetPosition(uiPos);

	tkl::Vector3 uiScale = mTexture->GetScale();
	uiScale.mX = uiRatio;
	mTexture->SetScale(uiScale);

	// UI��\������Ώۂ������Ă��邩
	if(!mObject->IsAlive()){ mIsEnabled = false; }
}

//****************************************************************************
// �֐����FDraw
// �T�@�v�F�`�揈��
// ���@���F�Ȃ�
// �߂�l�F�Ȃ�
// �ځ@�ׁF�`�揈�����s��
//****************************************************************************
void UiHitPoint::Draw()
{
	mBackGroundTexture->Draw(m2DCam);
	mTexture->Draw(m2DCam);
}