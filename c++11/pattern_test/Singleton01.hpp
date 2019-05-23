#pragma once
template <typename T>
class Singleton01 {
public:
	// ֧��0�������Ĺ��캯��
	static T* Instance() {
		if (m_pInstance == nullptr) {
			m_pInstance = new T();
		}
		return m_pInstance;
	}

	// ֧��1�������Ĺ��캯��
	template <typename T0>
	static T* Instance(T0 arg0) {
		if (m_pInstance == nullptr) {
			m_pInstance = new T(arg0);
		}
		return m_pInstance;
	}

	// ֧��2�������Ĺ��캯��
	template <typename T0, typename T1>
	static T* Instance(T0 arg0, T1 arg1) {
		if (m_pInstance == nullptr) {
			m_pInstance = new T(arg0, arg1);
		}
		return m_pInstance;
	}

	// ֧��3�������Ĺ��캯��
	template <typename T0, typename T1, typename T2>
	static T* Instance(T0 arg0, T1 arg1, T2 arg2) {
		if (m_pInstnace == nullptr) {
			m_pInstance = new T(arg0, arg1, arg2);
		}
		return m_pInstance;
	}

	// ֧��4�������Ĺ��캯��
	template <typename T0, typename T1, typename T2, typename T3>
	static T* Instance(T0 arg0, T1 arg1, T2 arg2, T3 arg3) {
		if (m_pInstance == nullptr) {
			m_pInstance new T(arg0, arg1, arg2, arg3);
		}
		return m_pInstance;
	}

	// ֧��5�������Ĺ��캯��
	template <typename T0, typename T1, typename T2, typename T3, typename T4>
	static T* Instance(T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4) {
		if (m_pInstance == nullptr) {
			m_pInstance = new T(arg0, arg1, arg2, arg3, arg4);
		}
		return m_pInstance;
	}

	// ֧��6�������Ĺ��캯��
	template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
	static T* Instance(T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5) {
		if (m_pInstance == nullptr) {
			m_pInstance = new T(arg0, arg1, arg2, arg3, arg4, arg5);
		}
		return m_pInstance;
	}

	// ��ȡ����
	static T* GetInstance() {
		if (m_pInstance == nullptr) {
			throw std::logic_error("the instance is not init, please initialize the instance first");
		}
		return m_pInstance;
	}

	// �ͷŵ���
	static void DestroyInstance() {
		delete m_pInstance;
		m_pInstance = nullptr;
	}

private:
	// �������ƺ͸�ֵ
	Singleton01() = delete;
	Singleton01(const Singleton01&) = delete;
	Singleton01& operator=(const Singleton01&) = delete;
	virtual ~Singleton01() = delete;

	static T* m_pInstance;
};

template<class T> T* Singleton01<T>::m_pInstance = nullptr;
