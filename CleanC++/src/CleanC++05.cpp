// 5 �ִ�C++�ĸ߼�����
// 5.1 ��Դ����
// 5.1.1 ��Դ�������ʼ��(RAII:Resource Acquisition is Initialization)std::
// ����ʱ��ã�����ʱ�ͷţ����ڷ�Χ����Դ����
// 5.1.2 ����ָ��:std::unique_ptr,std::shared_ptr, std::weak_ptr
// ���ж�ռ����Ȩ��std::unique_ptr<T>
// ���й�������Ȩ��std::shared_ptr<T>
// ������Ȩ�����ܹ���ȫ���ʵ�std::weak_ptr<T>
// 5.1.3 ������ʾ��new��delete
//   ������ʹ��ջ�ڴ�
//   ��make_functions(make_unique<T>,make_shared<T>)�ڶ��Ϸ����ڴ�
//   ����ʹ������(��׼�⡢Boost����������)
//   �����ض��ĵ��������װ��Դ
// 5.1.4 �����ض���Դ
// windows��HANDLE typedef void *HANDLE;
#include <memory>
#include "windows.h"
const DWORD processId = 4711;
class Win32HandleCloser {
public:
    void operator()(HANDLE handle) const {
        if (handle != INVALID_HANDLE_VALUE) {
            CloseHandle(handle);
        }
    }
};
//using WinewSharedHandle = std::shared_ptr<HANDLE>; // ע��!
using Win32SharedHandle = std::shared_ptr<void>;
using Win32WeakHandle = std::weak_ptr<void>;
Win32SharedHandle processHandle{ OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId),
    Win32HandleCloser() };

//using Win32UniqueHandle = std::unique_ptr<void>; // ע��
// ��C++�в�������std::unique_ptr<void>����!������Ϊstd::shared_ptr<T>ʵ��������ɾ����
// ����std::unique_ptr<T>û�С����һ����֧������ɾ����Ҳ����ζ�������Դ洢�������͵Ķ�
// �󣬶��һ���ȷ���ͷŶ���ռ�õ��ڴ档

// 5.2 Move����
// 5.2.1 ʲô��Move����
// 5.2.2 ��ֵ����ֵ�Ĺ�ϵ
// 5.2.3 ��ֵ����
// 5.2.4 ��Ҫ����Move
// 5.2.5 ��ԭ���������������
// ��ԭ����ʵ��������ʱ��Ӧ�ò���Ҫ����/��������������Ҳ����Ҫ����/����copy/move������
// ��copy/move��ֵ���������C++����ָ��ͱ�׼������������Դ��
// 5.3 ����������Ĵ
// 5.3.1 �Զ������Ƶ�
// 5.3.2 ����ʱ����
// 5.3.3 ģ�����
// 5.4 ������δ������Ϊ
// ����δ������Ϊ!δ������Ϊ��һ�����صĴ��󣬲������ջᵼ�³���������Ϣ�س���
// 5.4 Type-Rich���
//  �û��Զ�������ֵ��SI units, Boost.Units
// 5.6 �˽���ʹ�õĿ�
// 5.6.1 ����ʹ��<algorithm>
//  C++17�м򵥵Ĳ����㷨
// 5.6.2 ����ʹ��Boost��
// 5.6.3 Ӧ���˽��һЩ��
// chrono��regex��filesystem
// Range-v3
// �������ݽṹ��libcds
// 5.7 ǡ�����쳣�ʹ��������
// 5.7.1 ������δȻ
// ǰ������������ֵ����������
// ���쳣��ȫ�������쳣��ȫ��ǿ�쳣��ȫ����֤���׳��쳣
// ����������£���֤���׳��쳣Ҫô�Ǿ���ǿ�Ƶģ�Ҫô��������ȷ����ģ�
// ���κ����������������뱣֤���׳��쳣
// Move����Ӧ�ñ�֤���׳��쳣
// Ĭ�Ϲ��캯����ò��׳��쳣
// ���κ�����£�swap�������뱣֤���׳��쳣!
// noexcept�����������(C++11)
// 5.7.2 �쳣���쳣--�����ϵ���˼
// 5.7.3 ������ָܻ��򾡿��˳�
// 5.7.4 �û��Զ����쳣
// 5.7.5 ֵ�����׳��������������Ͳ���
// 5.7.6 ע��catch����ȷ˳��
