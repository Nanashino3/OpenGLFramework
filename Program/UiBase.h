#ifndef _UIBASE_H_
#define _UIBASE_H_

class UiBase
{
public:
	UiBase() : mIsEnabled(true){}
	virtual ~UiBase(){}

	virtual void Update(){}
	virtual void Draw(){}

	virtual bool IsEnabled(){ return mIsEnabled; }

protected:
	bool mIsEnabled;
};

#endif