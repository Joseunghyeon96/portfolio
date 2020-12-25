#pragma once

template <typename T>
class SingletonBase
{
protected:
	/*
	�̱����̶�, ���� ����ϴ� ���� �޸𸮿� ���ֽ���
	��� ��ü������ ������ �� �� �ְ� �ϴ� ������ ����
	*/

	static T* singleton;

	SingletonBase() {};
	~SingletonBase() {};

public:
	// �̱��� ������
	static T* GetSingleton(void);
	// �̱��� ���� �Լ�
	void ReleaseSingleton(void);

};

// �̱��� �ʱ�ȭ
template <typename T>
T* SingletonBase<T>::singleton = 0;

template <typename T>
T * SingletonBase<T>::GetSingleton(void)
{
	// ���࿡ �̱���ȭ�� �Ǿ����� �ʴٸ� �̱��� ȭ(�����Ҵ�)
	if (!singleton)
	{
		singleton = new T;
	}

	return singleton;
}

template <typename T>
void SingletonBase<T>::ReleaseSingleton(void)
{
	// �̱����� ������
	if (singleton)
	{
		// �����Ҵ��߱� ������ �޸𸮿��� ����
		delete singleton;

		singleton = 0;
	}
}