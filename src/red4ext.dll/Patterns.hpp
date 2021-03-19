#pragma once

class Patterns
{
public:
    static Patterns* Get();

    uintptr_t Find(const uint8_t* aPattern, size_t aPatternSize, size_t aExpectedMatches, size_t aIndex = 0,
                   uint8_t aWildcard = 0xCC, bool aIsRequired = false);

    uintptr_t Find(std::initializer_list<uint8_t> aPattern, size_t aExpectedMatches, size_t aIndex = 0,
                   uint8_t aWildcard = 0xCC, bool aIsRequired = false);

private:
    Patterns() = default;
    ~Patterns() = default;
};
