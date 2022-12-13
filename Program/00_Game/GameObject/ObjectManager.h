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

	template <class T>
	std::shared_ptr<T> Create(std::shared_ptr<GameParameter>& param)
	{
		std::shared_ptr<T> newObject = std::make_shared<T>(param);

		// 新しいリストを作成
		if(mListMap.count(typeid(T).name()) == 0){
			std::list<std::shared_ptr<GameObject>> newList;
			mListMap[typeid(T).name()] = newList;
		}

		// リストにオブジェクトを詰める
		auto list = mListMap[typeid(T).name()];
		list.emplace_back(newObject);
		mListMap[typeid(T).name()] = list;

		return newObject;
	}
	
	void Update(std::shared_ptr<GameParameter>& param);

	template <class T>
	std::list<std::shared_ptr<GameObject>>& GetList()
	{
		return mListMap[typeid(T).name()];
	}

private:
	ObjectManager();
	~ObjectManager();

private:
	static ObjectManager* sMyInstance;
	std::unordered_map<const char*, std::list<std::shared_ptr<GameObject>>> mListMap;
};

#endif