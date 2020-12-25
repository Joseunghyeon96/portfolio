#pragma once

template <typename T>
class SingletonBase
{
protected:
	/*
	싱글톤이란, 자주 사용하는 것을 메모리에 상주시켜
	어느 객체에서든 접근이 될 수 있게 하는 디자인 패턴
	*/

	static T* singleton;

	SingletonBase() {};
	~SingletonBase() {};

public:
	// 싱글톤 접근자
	static T* GetSingleton(void);
	// 싱글톤 해제 함수
	void ReleaseSingleton(void);

};

// 싱글톤 초기화
template <typename T>
T* SingletonBase<T>::singleton = 0;

template <typename T>
T * SingletonBase<T>::GetSingleton(void)
{
	// 만약에 싱글톤화가 되어있지 않다면 싱글톤 화(동적할당)
	if (!singleton)
	{
		singleton = new T;
	}

	return singleton;
}

template <typename T>
void SingletonBase<T>::ReleaseSingleton(void)
{
	// 싱글톤이 있으면
	if (singleton)
	{
		// 동적할당했기 때문에 메모리에서 해제
		delete singleton;

		singleton = 0;
	}
}