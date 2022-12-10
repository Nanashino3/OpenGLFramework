#include "Notifier.h"

#include "Observer.h"

Notifier* Notifier::sMyInstance = nullptr;
Notifier::Notifier()
{}

Notifier::~Notifier()
{}

Notifier* Notifier::GetInstance()
{
	if(!sMyInstance) sMyInstance = new Notifier;
	return sMyInstance;
}

void Notifier::DestroyInstance()
{
	delete sMyInstance;
}

// フィールド状態変化
void Notifier::FieldStateChange(int row, int column, std::shared_ptr<GameParameter> param)
{
	for(int i = 0; i < mObservers.size(); ++i){
		mObservers[i]->FieldStateChange(row, column, param);
	}
}