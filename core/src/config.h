#pragma once
#include <json.hpp>
#include <thread>
#include <string>
#include <mutex>

using nlohmann::json;

class ConfigManager {
public:
    ConfigManager();
    ~ConfigManager();
    void setPath(std::string file);
    void load(json def, bool lock = true);
    void save(bool lock = true);
    void enableAutoSave();
    void disableAutoSave();
    void aquire();
    void release(bool changed = false);

    json conf;
    
private:
    static void autoSaveWorker(ConfigManager* _this);

    std::string path = "";
    bool changed = false;
    bool autoSaveEnabled = false;
    std::thread autoSaveThread;
    std::mutex mtx;

};