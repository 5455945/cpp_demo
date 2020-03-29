#ifndef NOSTD_SOURCE_LOCATION_HPP
#define NOSTD_SOURCE_LOCATION_HPP

#pragma once

#include <cstdint>

namespace std {
struct source_location {
public:
#if not defined(__apple_build_version__) and defined(__clang__) and (__clang_major__ >= 9)
    static constexpr source_location current(const char* fileName = __builtin_FILE(),
        const char* functionName = __builtin_FUNCTION(),
        const uint_least32_t lineNumber = __builtin_LINE(),
        const uint_least32_t columnOffset = __builtin_COLUMN()) noexcept
#elif defined(__GNUC__) and (__GNUC__ > 4 or (__GNUC__ == 4 and __GNUC_MINOR__ >= 8))
    static constexpr source_location current(const char* fileName = __builtin_FILE(),
        const char* functionName = __builtin_FUNCTION(),
        const uint_least32_t lineNumber = __builtin_LINE(),
        const uint_least32_t columnOffset = 0) noexcept
#else
    static constexpr source_location current(const char* fileName = "unsupported",
        const char* functionName = "unsupported",
        const uint_least32_t lineNumber = 0,
        const uint_least32_t columnOffset = 0) noexcept
#endif
    {
        return source_location(fileName, functionName, lineNumber, columnOffset);
    }

    source_location(const source_location&) = default;
    source_location(source_location&&) = default;

    constexpr const char* file_name() const noexcept
    {
        return fileName;
    }

    constexpr const char* function_name() const noexcept
    {
        return functionName;
    }

    constexpr uint_least32_t line() const noexcept
    {
        return lineNumber;
    }

    constexpr std::uint_least32_t column() const noexcept
    {
        return columnOffset;
    }

private:
    constexpr source_location(const char* fileName, const char* functionName, const uint_least32_t lineNumber,
        const uint_least32_t columnOffset) noexcept
        : fileName(fileName)
        , functionName(functionName)
        , lineNumber(lineNumber)
        , columnOffset(columnOffset)
    {
    }

    const char* fileName;
    const char* functionName;
    const std::uint_least32_t lineNumber;
    const std::uint_least32_t columnOffset;
};
} // namespace nostd

#endif