#ifndef _EFFECTBASE_H_
#define _EFFECTBASE_H_

class EffectBase
{
public:
	EffectBase() : mIsEnabled(true){}
	virtual ~EffectBase(){}
	
	virtual void Update(float deltaTime){}
	virtual void Draw(){}

	virtual bool IsEnabled(){ return mIsEnabled; }

protected:
	bool mIsEnabled;
};

#endif