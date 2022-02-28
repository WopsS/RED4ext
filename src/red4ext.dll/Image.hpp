#pragma once

class Image
{
public:
    static Image* Get();

    bool IsCyberpunk() const;
    bool IsSupported() const;

    const RED4ext::FileVer& GetFileVersion() const;
    const RED4ext::SemVer& GetProductVersion() const;
    const RED4ext::FileVer GetSupportedVersion() const;

private:
    Image();
    ~Image() = default;

    bool m_isCyberpunk;
    RED4ext::FileVer m_fileVersion;
    RED4ext::SemVer m_productVersion;
};
