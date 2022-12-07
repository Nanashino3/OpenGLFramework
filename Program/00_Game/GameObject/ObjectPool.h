#ifndef _OBJECTPOOL_H_
#define _OBJECTPOOL_H_

template <class T>
class ObjectPool
{
public:
	ObjectPool() : mObjects(nullptr), mSize(0){}
	virtual ~ObjectPool(){}

	// 生成
	void Create(unsigned int size){
		mObjects = new T[size];
		mSize = size;
	}

	// 破棄
	void Destroy(){
		delete[] mObjects;
	}

	// 未使用オブジェクトを取得
	T* Recycle(){
		for(unsigned int i = 0; i < mSize; ++i){
			if(mObjects[i].mIsExists == false){
				mObjects[i].mIsExists = true;
				return &mObjects[i];
			}
		}

		// 見つからなかった
		return nullptr;
	}

	// 更新
	void Update(){
		for(unsigned int i = 0; i < mSize; ++i){
			if(!mObjects[i].mExists){ continue; }

			// 生存しているオブジェクトのみ更新
			mObjects[i].Update();
		}
	}

	// 描画
	void Draw(){
		for(unsigned int i = 0; i < mSize; ++i){
			if(!mObjects[i].mExists){ continue; }

			// 生存しているオブジェクトのみ描画
			mObjects[i].Draw();
		}
	}

	// 生存数のカウント
	unsigned int Count(){
		unsigned int cnt = 0;
		for(unsigned int i = 0; i < mSize; ++i){
			if(mObjects[i].mExists){ cnt++; }
		}
		return cnt;
	}

protected:
	T* mObjects;
	unsigned int mSize;
};

#endif