//****************************************************************************
// ファイル名：ObjectManager(オブジェクト管理者)
// 作　成　日：2022/12/8
#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include <list>
#include <memory>
#include <unordered_map>

class GameObject;
class GameParameter;
namespace tkl{ class Camera; }

class ObjectManager
{
public:
	static ObjectManager* GetInstance();
	static void DestroyInstance();

	//****************************************************************************
	// 関数名：Create
	// 概　要：作成(新規オブジェクト)
	// 引　数：arg1 ゲームパラメータ
	// 戻り値：オブジェクトのポインタ
	// 詳　細：新規オブジェクトを作成する。
	//       　※作成するオブジェクトのリストがなければ一緒に作成
	//****************************************************************************
	template <class T>
	std::shared_ptr<T> Create(std::shared_ptr<GameParameter>& param)
	{
		std::shared_ptr<T> newObject = std::make_shared<T>(param);

		// リストにオブジェクトを詰める
		auto list = mListMap[typeid(T).name()];
		list.emplace_back(newObject);
		mListMap[typeid(T).name()] = list;

		return newObject;
	}
	
	//****************************************************************************
	// 関数名：GetList
	// 概　要：リスト取得
	// 引　数：なし
	// 戻り値：指定したオブジェクトのリスト
	// 詳　細：指定したオブジェクトのリストを返す
	//****************************************************************************
	template <class T>
	const std::list<std::shared_ptr<GameObject>>* GetList()
	{
		return &mListMap[typeid(T).name()];
	}

	//****************************************************************************
	// 関数名：Collision
	// 概　要：衝突判定(オブジェクト)
	// 引　数：なし
	// 戻り値：なし
	// 詳　細：マップに登録済のオブジェクトリストに対して衝突判定を行う
	//****************************************************************************
	void Collision();

	//****************************************************************************
	// 関数名：Update
	// 概　要：更新処理(オブジェクト)
	// 引　数：arg1 ゲームパラメータ
	// 戻り値：なし
	// 詳　細：マップに登録済のオブジェクトリストに対して更新処理を行う
	//****************************************************************************
	void Update(std::shared_ptr<GameParameter>& param);

	//****************************************************************************
	// 関数名：Draw
	// 概　要：描画処理(オブジェクト)
	// 引　数：arg1 ゲームパラメータ
	// 戻り値：なし
	// 詳　細：マップに登録済のオブジェクトリストに対して描画処理を行う
	//****************************************************************************
	void Draw(std::shared_ptr<GameParameter>& param);

private:
	ObjectManager();
	~ObjectManager();

private:
	static ObjectManager* sMyInstance;
	std::unordered_map<const char*, std::list<std::shared_ptr<GameObject>>> mListMap;
};

#endif