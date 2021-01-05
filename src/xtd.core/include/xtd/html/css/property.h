#pragma once
#include <ostream>
#include <string>
#include <xtd/strings.h>

namespace xtd {
  namespace html {
    namespace css {
      /// @cond
      class parser;
      /// @endcond
      
      class property {
      public:
        property() = default;
        operator std::string() {return value_;}
        
        const std::string& key() const {return key_;}
        const std::string& value() const {return value_;}
        
        bool to_boolean() const {return xtd::parse<bool>(value_);}
        double to_double() const {return xtd::parse<double>(value_);}
        int8_t to_int8() const {return xtd::parse<int8_t>(value_);}
        int16_t to_int16() const {return xtd::parse<int16_t>(value_);}
        int32_t to_int32() const {return xtd::parse<int32_t>(value_);}
        int64_t to_int64() const {return xtd::parse<int64_t>(value_);}
        float to_single() const {return xtd::parse<float>(value_);}
        std::string to_string() const {return value_;}
        uint8_t to_uint8() const {return xtd::parse<uint8_t>(value_);}
        uint16_t to_uint16() const {return xtd::parse<uint16_t>(value_);}
        uint32_t to_uint32() const {return xtd::parse<uint32_t>(value_);}
        uint64_t to_uint64() const {return xtd::parse<uint64_t>(value_);}
        
        friend std::ostream& operator <<(std::ostream& os, const property& property) noexcept {return os << property.to_string();}
        
      private:
        friend class parser;
        explicit property(const std::string& key, const std::string& value) : key_(key), value_(value) {}
        std::string key_;
        std::string value_;
      };
    }
  }
}
