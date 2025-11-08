#ifndef CONFIG_H
#define CONFIG_H

#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace Config {
    struct GraphicsConfig {
        int width = 1280;
        int height = 720;
        bool fullscreen = false;
        bool vsync = true;
    };

    struct InputConfig {
        std::unordered_map<int, std::unordered_set<uint16_t>> key_to_buttons;
        std::unordered_map<uint16_t, std::unordered_set<int>> button_to_keys;

        void setBinding (int key, uint16_t button) {
            //key_to_buttons[key].push_back(button);
            //button_to_keys[button].push_back(key);
            key_to_buttons[key].insert(button);
            button_to_keys[button].insert(key);
        }
    };

    struct Config {
        GraphicsConfig graphics;
        InputConfig input;
    };

    void loadConfigDefault (Config &config);
    bool loadConfig (Config &config, const char *path);
    bool saveConfig (Config &config, const char *path);
}

#endif // CONFIG_H