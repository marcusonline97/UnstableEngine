#pragma once

#include <cereal/cereal.hpp>
#include <string>

/*
It's a helper class that manages file paths in a flexible way.
Instead of hardcoding where files are stored,
it lets you use virtual paths like "ER:SomeFolder/SomeFile.txt" that automatically map to real locations depending on your setup.
*/

class uePath
{
public:
	uePath() = default;

	template<class Archive>
	std::string save_minimal(Archive const&) const
	{
		return _virtualpath
	}

	template<class Archive>
	void load_minimal(Archive const&, std::string const& value)
	{
		_virtualPath = value;
		fixSlashes(_virtualPath);
		_realPath = findRealPathFromVirtualPath(_virtualPath);
		_hash = std::hash<std::string>()(_virtualPath);
	}

	uePath(const char* virtualPath);

	explicit uePath(const std::string &virtualPath);
	explicit uePath(const std::string& path, bool virtualPath);

    // Returns the drive, like "GR:"
    [[nodiscard]] std::string getPathVirtualDrive() const;

    [[nodiscard]] std::string getVirtualPath() const;
    [[nodiscard]] std::string getVirtualPath();

    [[nodiscard]] std::string getRealPath() const;
    [[nodiscard]] std::string getRealPath();

    [[nodiscard]] std::string getRealPathConst() const;
    [[nodiscard]] std::string getVirtualPathConst() const;

    [[nodiscard]] std::string getVirtualFolder() const;

    bool isEmpty();

    std::string getFileEnding() const;

    std::string getFileNameNoEnding() const;

    bool operator==(const uePath& other) const;

    bool operator<(const uePath& other) const;

    friend class std::hash<uePath>;

    // Below operator broke Lua bindings for some reason:
    // friend std::ostream &operator<<(std::ostream &stream, const jlePath &path);

    std::string _virtualPath;

    size_t hash() const;

private:
    mutable std::string _realPath;

private:
    static std::string findVirtualPathFromRealPath(const std::string& realPath);
    static std::string findRealPathFromVirtualPath(const std::string& virtualPath);

    static void fixSlashes(std::string& str);

    size_t _hash;
};

namespace std
{
    template <>
    struct hash<uePath> {
        std::size_t
            operator()(const uePath& path) const
        {
            return path._hash;
        }
    };
} // namespace std

