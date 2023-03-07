//****************************************************************************
// ファイル名：Notifier(通知者クラス)
// 作　成　日：2022/12/11
#ifndef _NOTIFIER_H_
#define _NOTIFIER_H_

#include <vector>
#include <memory>

namespace tkl
{
class Vector3;
}

class Observer;
class GameParameter;

class Notifier
{
public:
	static Notifier* GetInstance();
	static void DestroyInstance();

	void FieldStateChange(int row, int column, std::shared_ptr<GameParameter> param);
	void DefeatAdvanceUnit(std::shared_ptr<GameParameter> param, const tkl::Vector3& position);
	void AddObserver(std::shared_ptr<Observer> obsever){ mObservers.emplace_back(obsever); }

private:
	Notifier();
	~Notifier();

private:
	static Notifier* sMyInstance;
	std::vector<std::shared_ptr<Observer>> mObservers;
};

#endif