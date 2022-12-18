//****************************************************************************
// ファイル名：Field(フィールドクラス)
// 作　成　日：2022/12/11
#include "Field.h"

#include "GameObject/Cell.h"
#include "GameObject/ObjectManager.h"
#include "GameObject/GameParameter.h"

#include "../01_Engine/Camera/Camera.h"
#include "../01_Engine/System.h"
#include "../01_Engine/Intersect.h"

#include "../02_Library/Input.h"
#include "../02_Library/Utility.h"

Field::Field(std::shared_ptr<Parameter> param)
{
	mParam = std::dynamic_pointer_cast<GameParameter>(param);

	// フィールド情報読み込み
	auto readField = tkl::LoadCsv("Resource/debug/test.csv");
	mParam->SetMapSize(MAP_SIZE);
	mParam->SetMapRow(readField.size());
	mParam->SetMapColumn(readField[0].size());

	// フィールド生成
	std::vector<std::vector<tkl::CELL>> fields;
	for(int r = 0; r < readField.size(); ++r){
		std::vector<tkl::CELL> cells;
		for(int c = 0; c < readField[r].size(); ++c){
			tkl::CELL cell = {r, c, static_cast<tkl::STATUS>(stoi(readField[r][c]))};
			cells.emplace_back(cell);

			std::shared_ptr<Cell> object = ObjectManager::GetInstance()->Create<Cell>(param);
			object->SetCellInfo(cell);
			object->Initialize();
		}
		fields.emplace_back(cells);
	}
	mParam->SetFields(fields);
}

Field::~Field()
{}

//****************************************************************************
// 関数名：Update
// 概　要：更新処理
// 引　数：なし
// 戻り値：なし
// 詳　細：フィールドクラスの更新処理
//****************************************************************************
void Field::Update()
{
	UpdateMousePos();

	// セルの状態を更新
	auto fields = mParam->GetFields();
	auto list = ObjectManager::GetInstance()->GetList<Cell>();
	for(auto it = list->begin(); it != list->end(); ++it){
		auto cell = std::dynamic_pointer_cast<Cell>(*it);
		tkl::CELL info = cell->GetCellInfo();

		cell->SetCellInfo(fields[info.row][info.column]);
	}
}

//****************************************************************************
// 関数名：Draw
// 概　要：描画
// 引　数：なし
// 戻り値：なし
// 詳　細：フィールドクラスの描画処理
//****************************************************************************
void Field::Draw()
{}

//****************************************************************************
// 関数名：UpdateMousePos(private)
// 概　要：描画
// 引　数：なし
// 戻り値：なし
// 詳　細：マウス座標を更新(2D画面座標→3D座標を求めている)
//****************************************************************************
void Field::UpdateMousePos()
{
	// ウィンドウサイズを取得
	int screenW, screenH;
	tkl::System::GetInstance()->GetWindowSize(&screenW, &screenH);

	// マウス座標を元にレイを飛ばす
	int screenMouseX = 0, screenMouseY = 0;
	tkl::Input::GetMousePoint(&screenMouseX, &screenMouseY);

	std::shared_ptr<tkl::Camera> camera = mParam->GetCamera();
	tkl::Vector3 ray = tkl::Vector3::CreateScreenRay(screenMouseX, screenMouseY,
		screenW, screenH, camera->GetView(), camera->GetProjection());

	// レイと平面の衝突判定
	tkl::Vector3 mousePos;
	tkl::IsIntersectLinePlane(camera->GetPosition(), camera->GetPosition() + ray * 1000.0f,
		{ 1, 0, 0 }, tkl::Vector3::UNITY, &mousePos);
	mParam->SetMousePos(mousePos);
}