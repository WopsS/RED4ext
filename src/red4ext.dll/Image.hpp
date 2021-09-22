#pragma once

class Image
{
public:
    static Image* Get();

    bool IsCyberpunk() const;

    bool IsSupported() const;
    const RED4ext::VersionInfo& GetVersion() const;
    const RED4ext::VersionInfo GetSupportedVersion() const;

private:
    Image();
    ~Image() = default;

    bool m_isCyberpunk;
    RED4ext::VersionInfo m_version;
};
