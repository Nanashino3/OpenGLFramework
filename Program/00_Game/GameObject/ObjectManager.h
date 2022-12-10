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
	std::shared_ptr<T> Create(std::shared_ptr<GameParameter> param)
	{
		std::shared_ptr<T> obj = std::make_shared<T>(param);

		auto list = mListMap[typeid(T).name()];
		list->emplace_back(obj);
		mListMap[typeid(T).name()] = list;
		
		return obj;
	}
	void Update(std::shared_ptr<GameParameter> param);

	template <class T>
	std::list<std::shared_ptr<GameObject>>* GetObjectList()
	{
		return mListMap[typeid(T).name()];
	}

private:
	ObjectManager();
	~ObjectManager();

private:
	static ObjectManager* sMyInstance;

	std::unordered_map<const char*, std::list<std::shared_ptr<GameObject>>*> mListMap;
	std::list<std::shared_ptr<GameObject>> mAdvanceList;
	std::list<std::shared_ptr<GameObject>> mBulletList;
	std::list<std::shared_ptr<GameObject>> mDefenseList;
};

#endif