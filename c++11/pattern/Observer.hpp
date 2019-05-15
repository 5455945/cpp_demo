#include <iostream>
#include <string>
#include <functional>
#include <map>
using namespace std;

#include "NonCopyable.hpp"

template<typename Func>
class Events : NonCopyable {
public:
   //ע��۲��ߣ�֧����ֵ����
   int Connect(Func&& f) {
       return Assgin(f);
   }
   
    //ע��۲���
   int Connect(const Func& f) {
       return Assgin(f);
   }
    //�Ƴ��۲���
    void Disconnect(int key) {
        m_connections.erase(key);
    }

    //֪ͨ���еĹ۲���
    template<typename... Args>
    void Notify(Args&&... args) {
        for (auto& it: m_connections) {
            it.second(std::forward<Args>(args)...);
        }
    }

private:
    //����۲��߲�����۲��ߵı��
    template<typename F>
    int Assgin(F&& f) {
        int k=m_observerId++;
        m_connections.emplace(k, std::forward<F>(f));
        return k;
    }

    int m_observerId=0;//�۲��߶�Ӧ�ı��
    std::map<int, Func> m_connections;//�۲����б�
};
