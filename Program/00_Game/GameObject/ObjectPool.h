#ifndef _OBJECTPOOL_H_
#define _OBJECTPOOL_H_

template <class T>
class ObjectPool
{
public:
	ObjectPool() : mObjects(nullptr), mSize(0){}
	virtual ~ObjectPool(){}

	// ����
	void Create(unsigned int size){
		mObjects = new T[size];
		mSize = size;
	}

	// �j��
	void Destroy(){
		delete[] mObjects;
	}

	// ���g�p�I�u�W�F�N�g���擾
	T* Recycle(){
		for(unsigned int i = 0; i < mSize; ++i){
			if(mObjects[i].mIsExists == false){
				mObjects[i].mIsExists = true;
				return &mObjects[i];
			}
		}

		// ������Ȃ�����
		return nullptr;
	}

	// �X�V
	void Update(){
		for(unsigned int i = 0; i < mSize; ++i){
			if(!mObjects[i].mExists){ continue; }

			// �������Ă���I�u�W�F�N�g�̂ݍX�V
			mObjects[i].Update();
		}
	}

	// �`��
	void Draw(){
		for(unsigned int i = 0; i < mSize; ++i){
			if(!mObjects[i].mExists){ continue; }

			// �������Ă���I�u�W�F�N�g�̂ݕ`��
			mObjects[i].Draw();
		}
	}

	// �������̃J�E���g
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