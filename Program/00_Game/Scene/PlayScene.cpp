#include "PlayScene.h"

#include "../../01_Engine/System.h"
#include "../../01_Engine/Mesh.h"
#include "../../01_Engine/Camera/PostureControlCamera.h"
#include "../../01_Engine/Font.h"
#include "../../01_Engine/ResourceManager.h"
#include "../../01_Engine/Intersect.h"
#include "../../02_Library/Math.h"
#include "../../02_Library/Input.h"
#include "../../02_Library/Utility.h"

#include "../GameObject/AdvanceUnit.h"

const int SIZE = 50;
const int DIV = 5;

PlayScene::PlayScene()
: mScreenW(0), mScreenH(0)
, mFirstPosX(0), mFirstPosZ(0)
, mCamera(nullptr), mCursor(nullptr)
, mMode(MODE::EDIT_MODE)
{
	tkl::System::GetInstance()->GetWindowSize(&mScreenW, &mScreenH);

	// 3D�J��������
	mCamera = std::make_shared<tkl::PostureControlCamera>(mScreenW, mScreenH);
	mCamera->SetPosition(tkl::Vector3(100, 100, 300));

	// �O���b�h����
	mGrid = tkl::Mesh::CreateGround(SIZE, DIV);

	// �J�[�\������
	mCursor = tkl::Mesh::CreatePlane(SIZE);
	mCursor->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test2.bmp"));
	mCursor->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));

	// �t�B�[���h����
	std::vector<std::vector<std::string>> map = tkl::LoadCsv("Resource/test.csv");
	for(int i  = 0; i < map.size(); ++i){
		std::vector<tkl::CELL> fields;
		for(int j = 0; j < map[i].size(); ++j){
			fields.emplace_back(tkl::CELL(i, j, static_cast<tkl::STATUS>(std::stoi(map[i][j]))));
		}
		mFields.emplace_back(fields);
	}
	
	// �o�H����(����)
	tkl::Algorithm::RouteSearch(DIV, DIV, mFields, mRoute);
	mRouteCount = mRoute.size() - 1;

	mFirstPosX = -SIZE * DIV * 0.5f + (SIZE >> 1);
	mFirstPosZ = mFirstPosX;

	// �i�R���j�b�g�𐶐�
	std::shared_ptr<AdvanceUnit> unit = std::make_shared<AdvanceUnit>(SIZE, DIV, mRoute);
	mAdvanceList.emplace_back(unit);
}

PlayScene::~PlayScene()
{}

std::shared_ptr<BaseScene> PlayScene::Update(float deltaTime)
{
	std::shared_ptr<BaseScene> nextScene = shared_from_this();

	mCamera->Update();

	// �}�E�X���W�����Ƀ��C���΂�
	int mousePosX = 0, mousePosY = 0;
	tkl::Input::GetMousePoint(&mousePosX, &mousePosY);
	tkl::Vector3 ray = tkl::Vector3::CreateScreenRay(mousePosX, mousePosY, 
		mScreenW, mScreenH, mCamera->GetView(), mCamera->GetProjection());

	// ���C�ƕ��ʂ̓����蔻��
	tkl::Vector3 hit;
	if(tkl::IsIntersectLinePlane(mCamera->GetPosition(), mCamera->GetPosition() + ray * 1000.0f,
		{1, 0, 0}, tkl::Vector3::UNITY, &hit))
	{
		PriDrawSelectField(hit);
	}

	//******************************************************************
	// TODO�F�ŒZ�o�H�\���p(�f�o�b�O�Ƃ��ČĂяo������)
	for(int i = 0; i < mRoute.size(); ++i){
		std::shared_ptr<tkl::Mesh> mesh = tkl::Mesh::CreatePlane(SIZE);

		float posX = mFirstPosX + SIZE * mRoute[i].column;
		float posZ = mFirstPosZ + SIZE * mRoute[i].row;
		mesh->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/test.jpg"));
		mesh->SetPosition(tkl::Vector3(posX, 0, posZ));
		mesh->SetRotation(tkl::Quaternion::RotationAxis(tkl::Vector3::UNITX, tkl::ToRadian(90)));
		mesh->Draw(mCamera);
	}
	
	//******************************************************************
	// ���[�h�ύX
	if(tkl::Input::IsKeyDownTrigger(eKeys::KB_ENTER)) mMode = MODE::PLAY_MODE;

	std::string str = (mMode == MODE::PLAY_MODE) ? "�v���C���[�h" : "�G�f�B�b�g���[�h";
	tkl::Font::DrawStringEx(0, 0, str.c_str());

	if(mMode == MODE::PLAY_MODE){
		for(auto iter = mAdvanceList.begin(); iter != mAdvanceList.end(); ++iter){
			(*iter)->Move(deltaTime);
		}
	}
	for (auto iter = mAdvanceList.begin(); iter != mAdvanceList.end(); ++iter) {
		(*iter)->Draw(mCamera);
	}


	//******************************************************************
	// ��Q���̕`��
	for(int i = 0; i < mObstacles.size(); ++i){
		mObstacles[i]->Draw(mCamera);
	}

	mGrid->Draw(mCamera);

	return nextScene;
}

// �I�����Ă���t�B�[���h��`��
void PlayScene::PriDrawSelectField(const tkl::Vector3& pos)
{
	if(mMode == MODE::PLAY_MODE){ return; }

	for(int h = 0; h < mFields.size(); ++h){
		for(int w = 0; w < mFields[h].size(); ++w){
			float posX = mFirstPosX + SIZE * w;
			float posZ = mFirstPosZ + SIZE * h;
			if(!tkl::IsIntersectPointRect(pos.mX, pos.mZ, posX, posZ, SIZE)){ continue; }

			if(mFields[h][w].status != tkl::STATUS::EDITABLE){ continue; }

			mCursor->SetPosition(tkl::Vector3(posX, 0, posZ));
			mCursor->Draw(mCamera);

			if(tkl::Input::IsMouseDownTrigger(eMouse::MOUSE_LEFT)){
				// ��Q���̐���
				std::shared_ptr<tkl::Mesh> obstacle = tkl::Mesh::CreateBox(SIZE >> 1);
				obstacle->SetTexture(tkl::ResourceManager::GetInstance()->CreateTextureFromFile("Resource/saikoro_image.png"));
				obstacle->SetPosition(tkl::Vector3(posX, 12.5f, posZ));
				mObstacles.emplace_back(obstacle);

				// �o�H�ĒT��
				int prevSize = mRoute.size();
				mFields[h][w].status = tkl::STATUS::UNIT;
//				tkl::Algorithm::RouteSearch(DIV, DIV, mFields, mRoute);

//				int newSize = mRoute.size();
//				mRouteCount = mRouteCount + abs(prevSize - newSize);
			}
		}
	}
}