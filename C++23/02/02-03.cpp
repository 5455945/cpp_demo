#include "02-03.h"

// 3����������std::expected��P0323��
// ������ּ�ڽ�����������⣬��������һ���µ�ͷ�ļ�<expected>��
// ��������߼���ϵ��һ��������ϵ�������������������ִ���߼�A������ִ���߼�B������Ҫ׼ȷ�Ĵ�����Ϣ����ȡ��Ӧ�Ĵ�ʩ��
// Ŀǰ���õķ�ʽ��ʹ�ô�������쳣������Щ��ʽʹ��������Ȼ����಻��֮����
// std::expected<T, E>��ʾ�������൱��std::variant��std::optional�Ľ���壬
// �����Ա���T�����������ͣ���E����������ͣ�����ӿ���std::optional���ơ�������һ���򵥵����ӣ�

#include <expected>
#include <string>
#include <iostream>

enum class Status : uint8_t {
    Ok,
    connection_error,
    no_authority,
    format_error,
};

bool connected() {
    return true;
}

bool has_authority() {
    return false;
}

bool format() {
    return false;
}

std::expected<std::string, Status> read_data() {
    if (!connected())
        return std::unexpected<Status> { Status::connection_error };
    if (!has_authority())
        return std::unexpected<Status> { Status::no_authority };
    if (!format())
        return std::unexpected<Status> { Status::format_error };

    return { "my expected type" };
}

void test02_03_01() {
    auto result = read_data();
    if (result) {
        std::cout << result.value() << "\n";
    }
    else {
        std::cout << "error code: " << (int)result.error() << "\n";
    }
}


void test02_03() {
    test02_03_01();
}