#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include <list>
#include <memory>
#include <unordered_map>

class GameObject;
class AdvanceUnit;
class Bullet;
class DefenseUnit;
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
		PriAddObject(obj);
		return obj;
	}
	void Update(std::shared_ptr<GameParameter> param);

	template <class T>
	std::list<std::shared_ptr<GameObject>>* GetObjectList()
	{
		return mListMap[typeid(T).name()];;
	}

private:
	void PriAddObject(std::shared_ptr<AdvanceUnit> obj);
	void PriAddObject(std::shared_ptr<Bullet> obj);
	void PriAddObject(std::shared_ptr<DefenseUnit> obj);

private:
	ObjectManager();
	~ObjectManager();

private:
	static ObjectManager* sMyInstance;

	// MEMO：マップに登録する時にリストの実体で登録してたため循環参照になってた
	// リストのアドレスを登録することで同じアドレスを参照するように修正
	std::unordered_map<const char*, std::list<std::shared_ptr<GameObject>>*> mListMap;
	std::list<std::shared_ptr<GameObject>> mAdvanceList;
	std::list<std::shared_ptr<GameObject>> mBulletList;
	std::list<std::shared_ptr<GameObject>> mDefenseList;
};

#endif