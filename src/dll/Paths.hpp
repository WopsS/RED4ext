#pragma once

class Paths
{
public:
    Paths();
    ~Paths() = default;

    std::filesystem::path GetRootDir() const;
    std::filesystem::path GetX64Dir() const;

    std::filesystem::path GetExe() const;

    std::filesystem::path GetRED4extDir() const;
    std::filesystem::path GetLogsDir() const;
    std::filesystem::path GetPluginsDir() const;
    std::filesystem::path GetRedscriptPathsFile() const;

    std::filesystem::path GetR6Scripts() const;
    std::filesystem::path GetDefaultScriptsBlob() const;
    std::filesystem::path GetR6CacheModded() const;
    std::filesystem::path GetR6Dir() const;

    const std::filesystem::path GetConfigFile() const;

private:
    std::filesystem::path m_root;
    std::filesystem::path m_exe;
};
