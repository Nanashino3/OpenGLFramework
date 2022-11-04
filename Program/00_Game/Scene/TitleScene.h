#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_

#include "BaseScene.h"
class TitleScene : public BaseScene, public std::enable_shared_from_this<TitleScene>
{
public:
	TitleScene();
	virtual ~TitleScene();

	virtual std::shared_ptr<BaseScene> Update() final;
};

#endif