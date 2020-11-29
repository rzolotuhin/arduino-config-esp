#ifndef config_esp_h
#define config_eso_h

#include <map>

#ifdef ESP32
#include <SPIFFS.h>
#elif defined(ESP8266)
#include <FS.h>
#define FILE_READ "r"
#define FILE_WRITE "w"
#else
#error Platform not supported
#endif

namespace {
  class config {
    public:
      typedef std::map<String, String> list_t;
      typedef list_t::iterator iterator_t;
      typedef std::pair<iterator_t, bool> pair_t;
      
      void begin() {
        #ifdef ESP32
          SPIFFS.begin(true);
        #else
          SPIFFS.begin();
        #endif
      }
      
      void file(const char* name) { this->_file = name; }
      String file() { return String(this->_file); }

      template <typename any>
      bool add(const String &name, const any &value) { return this->add(name, String(value)); }
      bool add(const String &name, String value = "") {
        pair_t pair = this->_list.emplace(name, value);
        return pair.second;
      }

      const String &get(const String &name) { return this->get(name, String()); }
      template <typename any>
      const String &get(const String &name, const any &defaultValue) {
        iterator_t parameter = this->_list.find(name);
        if (parameter != this->_list.end()) return parameter->second;
        return String(defaultValue);
      }

      template <typename any>
      bool set(const String &name, const any &value) { return this->set(name, String(value)); }
      bool set(const String &name, const String &value) {
        iterator_t parameter = this->_list.find(name);
        if (parameter != this->_list.end()) return parameter->second = value;
        return false;
      }

      template <typename any>
      bool is(const String &name, const any &value) { return this->is(name, String(value)); }
      bool is(const String &name, const String &value) {
        iterator_t parameter = this->_list.find(name);
        if (parameter != this->_list.end()) return parameter->second == value;
        return false;
      }

      bool read() {
        if (!this->_list.empty() and SPIFFS.exists(this->_file)) {
          File confFile = SPIFFS.open(this->_file, FILE_READ);
          if (confFile and !confFile.isDirectory()) {
            String str;
            while(confFile.available()) {
              char c = char(confFile.read());
              if (c == '\n') {
                uint8_t separator = str.indexOf('\t');
                this->set(str.substring(0, separator), str.substring(separator + 1));
                str = "";
              } else str += c;
            }
            confFile.close();
            return true;
          }
        }
        return false;
      }

      bool write() {
        if (!this->_list.empty()) {
          File confFile = SPIFFS.open(this->_file, FILE_WRITE);
          if (confFile and !confFile.isDirectory()) {
            String str;
            for(auto &parameter: this->_list) {
              str += parameter.first + '\t' + parameter.second + '\n';
            }
            confFile.print(str);
            confFile.close();
            return true;
          }
        }
        return false;
      }

      void print(HardwareSerial &console) {
        console.println(u8"[config] parameters:");
        for(auto &parameter: this->_list) {
          console.printf(u8" - %s: %s\r\n",
            parameter.first.c_str(),
            parameter.second.c_str()
          );
        }
      }

      bool remove() {
        if (!SPIFFS.exists(this->_file)) return false;
        return SPIFFS.remove(this->_file);
      }

      list_t list() {
        return this->_list;
      }
    private:
      list_t _list;
      const char* _file = u8"/config.ini";
  } config;
}

#endif