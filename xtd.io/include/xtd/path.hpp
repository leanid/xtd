/// @file
/// @brief Contains xtd::tunit::unit_test class.
#pragma once

/// @todo remove comment when drive_into.hpp will be create
//#include "drive_into.hpp"
#include "file.hpp"
#include <cstdlib>
#include <random>
#include <regex>
#include <sstream>
#include <string>

/// @cond
std::string __get_current_dirirectory();
/// @endcond

//#include <iostream>

/// @brief The xtd namespace contains all fundamental classes to access Hardware, Os, System, and more.
namespace xtd {
  /// @brief The xtd::IO namespace contains types that allow reading and writing to files and data streams, and types that provide basic file and directory support.
  namespace io {
    /// @brief Performs operations on std::basic_string instances that contain file or directory path information. These operations are performed in a cross-platform manner.
    class path {
    public:
      /// @cond
      path() = delete;
      /// @endcond
      
      /// @brief Provides a platform-specific alternate character used to separate directory levels in a path string that reflects a hierarchical file system organization.
      /// @par Examples
      /// The following code example demonstrates the use of the alt_directory_separator_char() property.
      /// @include directory_separator_char.cpp
      template<typename Char>
      static Char alt_directory_separator_char() noexcept {return static_cast<Char>('/');}
      
      /// @brief Provides a platform-specific alternate character used to separate directory levels in a path string that reflects a hierarchical file system organization.
      /// @par Examples
      /// The following code example demonstrates the use of the alt_directory_separator_char() property.
      /// @include directory_separator_char.cpp
      static char alt_directory_separator_char() noexcept {return alt_directory_separator_char<char>();}
      
      /// @brief Changes the extension of a path string.
      /// @param path The path information to modify. The path cannot contain any of the characters defined in GetInvalidPathChars.
      /// @param extension The new extension (with or without a leading period). Specify null to remove an existing extension from path.
      /// @return string The modified path information.
      /// @note On Windows-based desktop platforms, if path is an empty string (""), the path information is returned unmodified. If extension is empty string (""), the returned string contains the specified path with its extension removed. If path has no extension, and extension is not empty, the returned path string contains extension appended to the end of path.
      /// @remarks If neither path nor extension contains a period (.), change_extension adds the period.
      /// @remarks The extension parameter can contain multiple periods and any valid path characters, and can be any length. If extension is empty (""), the returned string contains the contents of path with the last period and all characters following it removed.
      /// @remarks If extension is an empty string, the returned path string contains the contents of path with any characters following the last period removed.
      /// @remarks If extension does not contain a leading period, the period is added.
      /// @remarks If path contains a multiple extension separated by multiple periods, the returned string contains the contents of path with the last period and all characters following it replaced by extension. For example, if path is "\Dir1\examples\pathtests.csx.txt" and extension is "cs", the modified path is "\Dir1\examples\pathtests.csx.cs".
      /// @remarks It is not possible to verify that the returned results are valid in all scenarios. For example, if path is empty, extension is appended.
      template<typename Char>
      static std::basic_string<Char> change_extension(const std::basic_string<Char>& path, const std::basic_string<Char>& extension) {
        std::basic_string<Char> path_without_extension = combine(get_directory_name(path), get_file_name_without_extension(path));
        if (path_without_extension.empty() && !extension.empty()) return extension;
        if (extension.empty()) return path_without_extension;
        std::stringstream ss;
        ss << path_without_extension;
        if (path_without_extension[path_without_extension.size() - 1] != static_cast<Char>('.')  && extension[0] != static_cast<Char>('.')) ss << static_cast<Char>('.');
        ss << extension;
        return ss.str();
      }
      
      /// @cond
      template<typename Char>
      static std::basic_string<Char> change_extension(const Char* path, const Char* extension) {return change_extension(std::basic_string<Char>(path), std::basic_string<Char>(extension));}
      template<typename Char>
      static std::basic_string<Char> change_extension(const std::basic_string<Char>& path, const Char* extension) {return change_extension(path, std::basic_string<Char>(extension));}
      template<typename Char>
      static std::basic_string<Char> change_extension(const Char* path, const std::basic_string<Char>& extension) {return change_extension(std::basic_string<Char>(path), extension);}
      /// @endcond
      
      /// @brief Combines two path strings.
      /// @param path1 The first path.
      /// @param path2 The second path.
      /// @return A string containing the combined paths. If one of the specified paths is a zero-length string, this method returns the other path. If path2 contains an absolute path, this method returns path2.
      /// @remarks an empty string if path contains one or more of the invalid characters.
      template<typename Char>
      static std::basic_string<Char> combine(const std::basic_string<Char>& path1, const std::basic_string<Char>& path2) noexcept {
        // if (path1.IndexOfAny(GetInvalidPathChars()) != -1 || path2.IndexOfAny(GetInvalidPathChars()) != -1)  return {};
        if (path2.empty()) return path1;
        if (path1.empty() || is_path_rooted(path2)) return path2;
        
        std::basic_stringstream<Char> ss;
        ss << path1;
        if (path1[path1.size() - 1] != directory_separator_char()) ss <<  directory_separator_char<Char>();
        ss << path2;
        return ss.str();
      }
      
      /// @cond
      template<typename Char>
      static std::basic_string<Char> combine(const Char* path1, const Char* path2) noexcept {return combine(std::basic_string<Char>(path1), std::basic_string<Char>(path2));}
      template<typename Char>
      static std::basic_string<Char> combine(const std::basic_string<Char>& path1, const Char* path2) noexcept {return combine(path1, std::basic_string<Char>(path2));}
      template<typename Char>
      static std::basic_string<Char> combine(const Char* path1, const std::basic_string<Char>& path2) noexcept {return combine(std::basic_string<Char>(path1), path2);}
      /// @endcond
      
      /// @brief Combines three path strings.
      /// @param path1 The first path.
      /// @param path2 The second path.
      /// @param path3 The third path.
      /// @return A string containing the combined paths. If one of the specified paths is a zero-length string, this method returns the other path. If path2 contains an absolute path, this method returns path2.
      /// @remarks an empty string if path contains one or more of the invalid characters.
      template<typename T>
      static auto combine(T path1, T path2, T path3) noexcept {
        return combine(combine(path1, path2), path3);
      }
      
      /// @brief Combines four path strings.
      /// @param path1 The first path.
      /// @param path2 The second path.
      /// @param path3 The third path.
      /// @param path4 The fourth path.
      /// @return A string containing the combined paths. If one of the specified paths is a zero-length string, this method returns the other path. If path2 contains an absolute path, this method returns path2.
      /// @remarks an empty string if path contains one or more of the invalid characters.
      template<typename T>
      static auto combine(T path1, T path2, T path3, T path4) noexcept {
        return combine(combine(combine(path1, path2), path3), path4);
      }
      
      /// @brief Combines path strings array.
      /// @param paths The path array.
      /// @return A string containing the combined paths. If one of the specified paths is a zero-length string, this method returns the other path. If path2 contains an absolute path, this method returns path2.
      /// @remarks an empty string if path contains one or more of the invalid characters.
      template<typename Char, typename T>
      static std::basic_string<Char> combine(T paths) noexcept {
        std::basic_string<Char> result;
        for (auto path : paths)
          result = combine(result, path);
        return result;
      }
      
      /// @cond
      template<typename T>
      static std::basic_string<char> combine(T paths) noexcept {
        std::basic_string<char> result;
        for (auto path : paths)
          result = combine(result, path);
        return result;
      }
      /// @endcond
      
      /// @brief Combines path strings array.
      /// @param paths The path array.
      /// @return A string containing the combined paths. If one of the specified paths is a zero-length string, this method returns the other path. If path2 contains an absolute path, this method returns path2.
      /// @remarks an empty string if path contains one or more of the invalid characters.
      template<typename Char>
      static std::basic_string<Char> combine(const std::initializer_list<std::basic_string<Char>>& paths) noexcept {
        std::basic_string<Char> result;
        for (auto path : paths)
          result = combine(result, path);
        return result;
      }
      
      /// @cond
      template<typename Char, typename T>
      static std::basic_string<Char> combine(const std::initializer_list<T>& paths) noexcept {
        std::basic_string<Char> result;
        for (auto path : paths)
          result = combine(result, path);
        return result;
      }
      
      template<typename T>
      static std::basic_string<char> combine(const std::initializer_list<T>& paths) noexcept {
        std::basic_string<char> result;
        for (auto path : paths)
          result = combine(result, path);
        return result;
      }
      /// @endcond
      
      /// @brief Provides a platform-specific character used to separate directory levels in a path string that reflects a hierarchical file system organization.
      /// @par Examples
      /// The following code example demonstrates the use of the directory_separator_char() property.
      /// @include directory_separator_char.cpp
      template<typename Char>
      static Char directory_separator_char() noexcept {
        return __is_windows_os() ? static_cast<Char>('\\') : static_cast<Char>('/');
      }
      
      /// @brief Provides a platform-specific character used to separate directory levels in a path string that reflects a hierarchical file system organization.
      /// @par Examples
      /// The following code example demonstrates the use of the directory_separator_char() property.
      /// @include directory_separator_char.cpp
      static char directory_separator_char() noexcept {return directory_separator_char<char>();}
      
      /// @brief Returns the directory information for the specified path string.
      /// @param path the path of a file or directory.
      /// @return A string containing directory information for path, or null if path denotes a root directory, is the empty string ("").
      /// @remarks Returns string empty if path does not contain directory information.
      template<typename Char>
      static std::basic_string<Char> get_directory_name(const std::basic_string<Char>& path) {
        size_t index = path.rfind(directory_separator_char<Char>());
        if (index == std::basic_string<Char>::npos) return {};
        std::basic_string<Char> directory = path.substr(0, index);
        return directory;
      }
      
      /// @cond
      template<typename Char>
      static std::basic_string<Char> get_directory_name(const Char* path) {return get_directory_name(std::basic_string<Char>(path));}
      /// @endcond
      
      /// @brief Returns the extension of the specified path string.
      /// @param path The path string from which to get the extension.
      /// @return A System::string containing the extension of the specified path (including the ".") or System::string.Empty.
      /// @remarks If path is empty, GetExtension returns string empty. If path does not have extension information, GetExtension returns string empty.
      template<typename Char>
      static std::basic_string<Char> get_extension(const std::basic_string<Char>& path) {
        std::basic_string<Char> file = get_file_name(path);
        size_t index = file.rfind('.');
        return index == std::basic_string<Char>::npos ? "" : file.substr(index);
      }
      
      /// @cond
      template<typename Char>
      static std::basic_string<Char> get_extension(const Char* path) {return get_extension(std::basic_string<Char>(path));}
      /// @endcond
      
      template<typename Char>
      static std::basic_string<Char> get_file_name(const std::basic_string<Char>& path) {
        size_t index = path.rfind(directory_separator_char<Char>());
        return (index ==std::basic_string<Char>::npos) ? path : path.substr(index + 1);
      }
      
      /// @cond
      template<typename Char>
      static std::basic_string<Char> get_file_name(const Char* path) {return get_file_name(std::basic_string<Char>(path));}
      /// @endcond
      
      template<typename Char>
      static std::basic_string<Char> get_file_name_without_extension(const std::basic_string<Char>& path) {
        std::basic_string<Char> file = get_file_name(path);
        size_t index = file.rfind('.');
        return (index == std::basic_string<Char>::npos) ? file : file.substr(0, index);
      }
      
      /// @cond
      template<typename Char>
      static std::basic_string<Char> get_file_name_without_extension(const Char* path) {return get_file_name_without_extension(std::basic_string<Char>(path));}
      /// @endcond
      
      /// @brief Returns the absolute path for the specified path string.
      /// @param path The file or directory for which to obtain absolute path information.
      /// @return A string containing the fully qualified location of path, such as "C:\\MyFile.txt".
      template<typename Char>
      static std::basic_string<Char> get_full_path(const std::basic_string<Char>& path) {
        std::basic_regex<Char> r(std::basic_string<Char>("\\") + directory_separator_char<Char>() + std::basic_string<Char>("+"));
        std::vector<std::basic_string<Char>> directories;
        for (std::sregex_token_iterator it(path.begin(), path.end(), r, -1), end; it != end; ++it)
          if (*it != "") directories.push_back(*it);
        
        std::basic_string<Char> fullPath;
        
        if (path[0] != directory_separator_char<Char>()) fullPath = __get_current_dirirectory();
        for (auto item : directories) {
          if (item == ".." && fullPath.rfind(directory_separator_char<Char>()) != -1)
            fullPath = fullPath.substr(0, fullPath.rfind(directory_separator_char<Char>()));
          else if (item != ".") {
            std::basic_stringstream<Char> ss;
            ss << fullPath<< directory_separator_char<Char>() << item;
            fullPath = ss.str();
          }
        }
        
        if (path[path.size() - 1] == directory_separator_char<Char>()) {
          std::basic_stringstream<Char> ss;
          ss << fullPath << directory_separator_char<Char>();
          fullPath = ss.str();
        }
        
        return fullPath;
      }
      
      /// @cond
      template<typename Char>
      static std::basic_string<Char> get_full_path(const Char* path) {return get_full_path(std::basic_string<Char>(path));}
      /// @endcond;
      
      /// @brief Gets an array containing the characters that are not allowed in path names.
      /// @return An array containing the characters that are not allowed in path names.
      /// @remarks The array returned from this method is not guaranteed to contain the complete set of characters that are invalid in file and directory names. The full set of invalid characters can vary by file system. For example, on Windows-based desktop platforms, invalid path characters might include ASCII/Unicode characters 1 through 31, as well as quote ("), less than (<), greater than (>), pipe (|), backspace (\b), null (\0) and tab (\t).
      template<typename Char>
      static std::vector<Char> get_invalid_path_chars() noexcept {return {34, 60, 62, 124, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0};}
      
      /// @brief Gets an array containing the characters that are not allowed in path names.
      /// @return An array containing the characters that are not allowed in path names.
      /// @remarks The array returned from this method is not guaranteed to contain the complete set of characters that are invalid in file and directory names. The full set of invalid characters can vary by file system. For example, on Windows-based desktop platforms, invalid path characters might include ASCII/Unicode characters 1 through 31, as well as quote ("), less than (<), greater than (>), pipe (|), backspace (\b), null (\0) and tab (\t).
      static std::vector<char> get_invalid_path_chars() noexcept {return get_invalid_path_chars<char>();}
      
      /// @brief Gets the root directory information of the specified path.
      /// @param path The path from which to obtain root directory information.
      /// @return A string containing the root directory of path, such as "C:\", or null if
      /// @return path is null, or an empty string if path does not contain root directory
      /// @return information.
      template<typename Char>
      static std::basic_string<Char> get_path_root(const std::basic_string<Char>& path) noexcept {return is_path_rooted(path) ? path.substr(0, __get_index_path_rooted(path) + 1) : "";}
      
      /// @cond
      template<typename Char>
      static std::basic_string<Char> get_path_root(const Char* path) noexcept {return get_path_root(std::basic_string<Char>(path));}
      /// @endcond
      
      /// @brief Returns a random folder name or file name.
      /// @return A random folder name or file name.
      /// @remarks The get_random_file_name method returns a cryptographically strong, random string that can be used as either a folder name or a file name. Unlike GetTempFileName, get_random_file_name does not create a file. When the security of your file system is paramount, this method should be used instead of GetTempFileName.
      template<typename Char>
      static std::basic_string<Char> get_random_file_name() {
        static std::basic_string<Char> valid_chars = {static_cast<Char>('"'), static_cast<Char>('1'), static_cast<Char>('2'), static_cast<Char>('3'), static_cast<Char>('4'), static_cast<Char>('5'), static_cast<Char>('6'), static_cast<Char>('7'), static_cast<Char>('8'), static_cast<Char>('9'), static_cast<Char>('0'), static_cast<Char>('a'), static_cast<Char>('b'), static_cast<Char>('c'), static_cast<Char>('d'), static_cast<Char>('e'), static_cast<Char>('f'), static_cast<Char>('g'), static_cast<Char>('h'), static_cast<Char>('i'), static_cast<Char>('j'), static_cast<Char>('k'), static_cast<Char>('l'), static_cast<Char>('m'), static_cast<Char>('n'), static_cast<Char>('o'), static_cast<Char>('p'), static_cast<Char>('q'), static_cast<Char>('r'), static_cast<Char>('s'), static_cast<Char>('t'), static_cast<Char>('u'), static_cast<Char>('v'), static_cast<Char>('w'), static_cast<Char>('x'), static_cast<Char>('y'), static_cast<Char>('z')};
        std::random_device rand;
        std::basic_string<Char> random_file_name;
        
        for (size_t i = 0; i < 11; i++) {
          random_file_name += valid_chars[std::uniform_int_distribution<size_t> {0, valid_chars.size() - 1}(rand)];
          if (i == 7)
            random_file_name += static_cast<Char>('.');
        }
        
        return random_file_name;
      }
      
      /// @brief Returns a random folder name or file name.
      /// @return A random folder name or file name.
      /// @remarks The get_random_file_name method returns a cryptographically strong, random string that can be used as either a folder name or a file name. Unlike GetTempFileName, get_random_file_name does not create a file. When the security of your file system is paramount, this method should be used instead of GetTempFileName.
      static std::string get_random_file_name() {return get_random_file_name<char>();}
      
      /// @brief Creates a uniquely named, zero-byte temporary file on disk and returns the full path of that file.
      /// @return The full path of the temporary file.
      /// @remarks This method creates a temporary file with a .TMP file extension. The temporary file is created within the user’s temporary folder, which is the path returned by the GetTempPath method.
      /// @remarks The GetTempFileName method will raise an IOException if it is used to create more than 65535 files without deleting previous temporary files.
      /// @remarks The GetTempFileName method will raise an IOException if no unique temporary file name is available. To resolve this error, delete all unneeded temporary files.
      template<typename Char>
      static std::basic_string<Char> get_temp_file_name() {
        static std::basic_string<Char> valid_chars = {static_cast<Char>('1'), static_cast<Char>('2'), static_cast<Char>('3'), static_cast<Char>('4'), static_cast<Char>('5'), static_cast<Char>('6'), static_cast<Char>('7'), static_cast<Char>('8'), static_cast<Char>('9'), static_cast<Char>('0'), static_cast<Char>('a'), static_cast<Char>('b'), static_cast<Char>('c'), static_cast<Char>('d'), static_cast<Char>('e'), static_cast<Char>('f')};
        std::basic_string<Char> temp_file_name;
        do {
          static std::random_device rand;
          temp_file_name = "tmp";
          
          for (size_t i = 0; i < 8; i++) {
            if (i == 0)
              temp_file_name += valid_chars[std::uniform_int_distribution<size_t> {0, 9}(rand)];
            else
              temp_file_name += valid_chars[std::uniform_int_distribution<size_t> {0, valid_chars.size() - 1}(rand)];
          }
          temp_file_name += ".tmp";
        } while (file::exists(combine(get_temp_path(), temp_file_name)));
        file::create(combine(get_temp_path(), temp_file_name));
        return combine(get_temp_path(), temp_file_name);
      }
      
      /// @brief Creates a uniquely named, zero-byte temporary file on disk and returns the full path of that file.
      /// @return The full path of the temporary file.
      /// @remarks This method creates a temporary file with a .TMP file extension. The temporary file is created within the user’s temporary folder, which is the path returned by the GetTempPath method.
      /// @remarks The GetTempFileName method will raise an IOException if it is used to create more than 65535 files without deleting previous temporary files.
      /// @remarks The GetTempFileName method will raise an IOException if no unique temporary file name is available. To resolve this error, delete all unneeded temporary files.
      static std::string get_temp_file_name() {return get_temp_file_name<char>();}
      
      /// @brief Returns the path of the current user's temporary folder.
      /// @return string The path to the temporary folder, ending with a backslash.
      /// @remarks This method checks for the existence of environment variables in the following order and uses the first path found:
      /// * The path specified by the TMP environment variable.
      /// * The path specified by the TEMP environment variable.
      /// * The path specified by the USERPROFILE environment variable.
      /// * The Windows directory.
      template<typename Char>
      static std::basic_string<Char> get_temp_path() noexcept {
        if (__is_windows_os()) {
          if (getenv("TMP") != nullptr)  return getenv("TMP");
          if (getenv("TEMP") != nullptr) return getenv("TEMP");
          if (getenv("USERPROFILE") != nullptr) return getenv("USERPROFILE");
          return getenv("WINDIR");
        }
        if (getenv("TMPDIR") != nullptr) return getenv("TMPDIR");
        return "/tmp/";
      }
      
      /// @brief Returns the path of the current user's temporary folder.
      /// @return string The path to the temporary folder, ending with a backslash.
      /// @remarks This method checks for the existence of environment variables in the following order and uses the first path found:
      /// * The path specified by the TMP environment variable.
      /// * The path specified by the TEMP environment variable.
      /// * The path specified by the USERPROFILE environment variable.
      /// * The Windows directory.
      static std::string get_temp_path() noexcept {return get_temp_path<char>();}
      
      /// @brief Determines whether a path includes a file name extension.
      /// @param path The path to search for an extension.
      /// @return true if the characters that follow the last directory separator (\\ or /)
      /// @return or volume separator (:) in the path include a period (.) followed by one
      /// @return or more characters; otherwise, false.
      template<typename Char>
      static bool has_extension(const std::basic_string<Char>& path) {return !get_extension(path).empty();}
      
      /// @cond
      template<typename Char>
      static bool has_extension(const Char* path) {return has_extension(std::basic_string<Char>(path));}
      /// @endcond
      
      /// @brief Gets a value indicating whether the specified path string contains absolute or relative path information.
      /// @param path The path to test.
      /// @return true if path contains an absolute path; otherwise, false.
      /// @remarks This method also returns false if path is empty or an invalid path.
      /// @remarks If the caller does not have sufficient permissions to read the specified file, no exception is thrown and the method returns false regardless of the existence of path.
      template<typename Char>
      static bool is_path_rooted(const std::basic_string<Char>& path) noexcept {return __get_index_path_rooted(path) != -1;}
      
      /// @cond
      template<typename Char>
      static bool is_path_rooted(const char* path) noexcept {return is_path_rooted(std::basic_string<Char>(path));}
      /// @endcond
      
      /// @brief A platform-specific separator character used to separate path strings in environment variables.
      /// @par Examples
      /// The following code example demonstrates the use of the PathSeparator() property.
      /// @include directory_separator_char.cpp
      template<typename Char>
      static Char path_separator() noexcept {return static_cast<Char>(':');}
      
      /// @brief A platform-specific separator character used to separate path strings in environment variables.
      /// @par Examples
      /// The following code example demonstrates the use of the PathSeparator() property.
      /// @include directory_separator_char.cpp
      static char path_separator() noexcept {return path_separator<char>();}
      
      /// @brief Provides a platform-specific volume separator character.
      /// @par Examples
      /// The following code example demonstrates the use of the volume_separator_char() property.
      /// @include directory_separator_char.cpp
      template<typename Char>
      static Char volume_separator_char() noexcept {return  __is_windows_os() ? ':' : '/';}
      
      /// @brief Provides a platform-specific volume separator character.
      /// @par Examples
      /// The following code example demonstrates the use of the volume_separator_char() property.
      /// @include directory_separator_char.cpp
      static char volume_separator_char() noexcept {return  volume_separator_char<char>();}
      
    private:
      static bool __is_windows_os() noexcept {
#if defined(_WIN32)
        return true;
#else
        return false;
#endif
      }
      
      template<typename Char>
      static bool __is_drive(const std::basic_string<Char>& path) noexcept {
        /// @todo remove comment when drive_info::get_drives will be create
        /*
         for (auto drive : drive_info::get_drives())
         if (drive.name() == path)
         return true;
         */
        return false;
      }
      
      template<typename Char>
      static int __get_index_path_rooted(const std::basic_string<Char>& path) noexcept {
        int index = path.find(directory_separator_char());
        return (index == std::basic_string<Char>::npos || index == path.size() || (index != 0 && !__is_drive(path.substr(0, index + 1)))) ? -1 : index;
      }
    };
  }
}
