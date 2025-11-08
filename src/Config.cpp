#include <glfw/glfw3.h>
#include <yyjson.h>
#include <stdio.h>
#include <string>
#include <unordered_map>
#include "config.h"
#include "Input.h"

namespace Config {

    namespace Internal {
        // keymap
        static const std::unordered_map<std::string, int> STRING_TO_KEY = {
            {"space", GLFW_KEY_SPACE}, {"apostrophe", GLFW_KEY_APOSTROPHE},
            {"comma", GLFW_KEY_COMMA}, {"minus", GLFW_KEY_MINUS},
            {"period", GLFW_KEY_PERIOD}, {"slash", GLFW_KEY_SLASH},
            {"0", GLFW_KEY_0}, {"1", GLFW_KEY_1}, {"2", GLFW_KEY_2}, {"3", GLFW_KEY_3},
            {"4", GLFW_KEY_4}, {"5", GLFW_KEY_5}, {"6", GLFW_KEY_6}, {"7", GLFW_KEY_7},
            {"8", GLFW_KEY_8}, {"9", GLFW_KEY_9},
            {"a", GLFW_KEY_A}, {"b", GLFW_KEY_B}, {"c", GLFW_KEY_C}, {"d", GLFW_KEY_D},
            {"e", GLFW_KEY_E}, {"f", GLFW_KEY_F}, {"g", GLFW_KEY_G}, {"h", GLFW_KEY_H},
            {"i", GLFW_KEY_I}, {"j", GLFW_KEY_J}, {"k", GLFW_KEY_K}, {"l", GLFW_KEY_L},
            {"m", GLFW_KEY_M}, {"n", GLFW_KEY_N}, {"o", GLFW_KEY_O}, {"p", GLFW_KEY_P},
            {"q", GLFW_KEY_Q}, {"r", GLFW_KEY_R}, {"s", GLFW_KEY_S}, {"t", GLFW_KEY_T},
            {"u", GLFW_KEY_U}, {"v", GLFW_KEY_V}, {"w", GLFW_KEY_W}, {"x", GLFW_KEY_X},
            {"y", GLFW_KEY_Y}, {"z", GLFW_KEY_Z},
            {"up", GLFW_KEY_UP}, {"down", GLFW_KEY_DOWN}, 
            {"left", GLFW_KEY_LEFT}, {"right", GLFW_KEY_RIGHT},
            {"lshift", GLFW_KEY_LEFT_SHIFT}, {"rshift", GLFW_KEY_RIGHT_SHIFT},
            {"lctrl", GLFW_KEY_LEFT_CONTROL}, {"rctrl", GLFW_KEY_RIGHT_CONTROL},
            {"lalt", GLFW_KEY_LEFT_ALT}, {"ralt", GLFW_KEY_RIGHT_ALT},
            {"enter", GLFW_KEY_ENTER}, {"escape", GLFW_KEY_ESCAPE},
            {"tab", GLFW_KEY_TAB}, {"backspace", GLFW_KEY_BACKSPACE}
        };

        static const std::unordered_map<int, std::string> KEY_TO_STRING = {
            {GLFW_KEY_SPACE, "space"}, {GLFW_KEY_APOSTROPHE, "apostrophe"},
            {GLFW_KEY_COMMA, "comma"}, {GLFW_KEY_MINUS, "minus"},
            {GLFW_KEY_PERIOD, "period"}, {GLFW_KEY_SLASH, "slash"},
            {GLFW_KEY_0, "0"}, {GLFW_KEY_1, "1"}, {GLFW_KEY_2, "2"}, {GLFW_KEY_3, "3"},
            {GLFW_KEY_4, "4"}, {GLFW_KEY_5, "5"}, {GLFW_KEY_6, "6"}, {GLFW_KEY_7, "7"},
            {GLFW_KEY_8, "8"}, {GLFW_KEY_9, "9"},
            {GLFW_KEY_A, "a"}, {GLFW_KEY_B, "b"}, {GLFW_KEY_C, "c"}, {GLFW_KEY_D, "d"},
            {GLFW_KEY_E, "e"}, {GLFW_KEY_F, "f"}, {GLFW_KEY_G, "g"}, {GLFW_KEY_H, "h"},
            {GLFW_KEY_I, "i"}, {GLFW_KEY_J, "j"}, {GLFW_KEY_K, "k"}, {GLFW_KEY_L, "l"},
            {GLFW_KEY_M, "m"}, {GLFW_KEY_N, "n"}, {GLFW_KEY_O, "o"}, {GLFW_KEY_P, "p"},
            {GLFW_KEY_Q, "q"}, {GLFW_KEY_R, "r"}, {GLFW_KEY_S, "s"}, {GLFW_KEY_T, "t"},
            {GLFW_KEY_U, "u"}, {GLFW_KEY_V, "v"}, {GLFW_KEY_W, "w"}, {GLFW_KEY_X, "x"},
            {GLFW_KEY_Y, "y"}, {GLFW_KEY_Z, "z"},
            {GLFW_KEY_UP, "up"}, {GLFW_KEY_DOWN, "down"}, 
            {GLFW_KEY_LEFT, "left"}, {GLFW_KEY_RIGHT, "right"},
            {GLFW_KEY_LEFT_SHIFT, "lshift"}, {GLFW_KEY_RIGHT_SHIFT, "rshift"},
            {GLFW_KEY_LEFT_CONTROL, "lctrl"}, {GLFW_KEY_RIGHT_CONTROL, "rctrl"},
            {GLFW_KEY_LEFT_ALT, "lalt"}, {GLFW_KEY_RIGHT_ALT, "ralt"},
            {GLFW_KEY_ENTER, "enter"}, {GLFW_KEY_ESCAPE, "escape"},
            {GLFW_KEY_TAB, "tab"}, {GLFW_KEY_BACKSPACE, "backspace"}
        };

        static const std::unordered_map<std::string, uint16_t> STRING_TO_BUTTON = {
            {"move_left", Input::ButtonFlag::INPUT_MOVE_LEFT},
            {"move_right", Input::ButtonFlag::INPUT_MOVE_RIGHT},
            {"jump", Input::ButtonFlag::INPUT_JUMP},
            {"shot", Input::ButtonFlag::INPUT_SHOT}
        };

        static const std::unordered_map<uint16_t, std::string> BUTTON_TO_STRING = {
            {Input::ButtonFlag::INPUT_MOVE_LEFT, "move_left"},
            {Input::ButtonFlag::INPUT_MOVE_RIGHT, "move_right"},
            {Input::ButtonFlag::INPUT_JUMP, "jump"},
            {Input::ButtonFlag::INPUT_SHOT, "shot"}
        };

        // Helpers
        int get_int(yyjson_val *obj, const char *key, int defaultValue) {
            if (!obj) return defaultValue;
            yyjson_val *val = yyjson_obj_get(obj, key);
            return val && yyjson_is_int(val) ? yyjson_get_int(val) : defaultValue;
        }

        bool get_bool(yyjson_val *obj, const char *key, bool defaultValue) {
            if (!obj) return defaultValue;
            yyjson_val *val = yyjson_obj_get(obj, key);
            return val && yyjson_is_bool(val) ? yyjson_get_bool(val) : defaultValue;
        }

        double get_real(yyjson_val *obj, const char *key, double defaultValue) {
            if (!obj) return defaultValue;
            yyjson_val *val = yyjson_obj_get(obj, key);
            return val && yyjson_is_bool(val) ? yyjson_get_real(val) : defaultValue;
        }

        const char *get_str(yyjson_val *obj, const char *key, const char *defaultValue) {
            if (!obj) return defaultValue;
            yyjson_val *val = yyjson_obj_get(obj, key);
            return val && yyjson_is_str(val) ? yyjson_get_str(val) : defaultValue;
        }

        // Loaders
        void loadGraphicsConfig (GraphicsConfig &config, yyjson_val *graphicsObj) {
            if (!graphicsObj) return;

            config.width = get_int(graphicsObj, "width", config.width);
            config.height = get_int(graphicsObj, "height", config.height);
            config.vsync = get_bool(graphicsObj, "vsync", config.vsync);
            config.fullscreen = get_bool(graphicsObj, "fullscreen", config.fullscreen);
        }

        void loadInputConfig (InputConfig &config, yyjson_val *inputObj) {
            if (!inputObj) return;

            yyjson_val *bindings = yyjson_obj_get(inputObj, "bindings");
            if (!bindings) return;

            yyjson_val *key, *val;
            size_t idx, max;
            yyjson_obj_foreach(bindings, idx, max, key, val) {
                const char* buttonName = yyjson_get_str(key);
                if (!buttonName) continue;

                auto buttonIt = STRING_TO_BUTTON.find(buttonName);
                if (buttonIt == STRING_TO_BUTTON.end()) continue;

                uint16_t button = buttonIt->second;
                
                // single key
                if (yyjson_is_str(val)) {
                    const char *keyStr = yyjson_get_str(val);
                    auto keyIt = STRING_TO_KEY.find(keyStr);
                    if (keyIt != STRING_TO_KEY.end())
                        config.setBinding(keyIt->second, button);
                }
                // multiple keys
                else if (yyjson_is_arr(val)) {
                    yyjson_val *keys;
                    size_t keyIdx, keyMax;
                    yyjson_arr_foreach(val, keyIdx, keyMax, keys) {
                        if (!yyjson_is_str(keys)) continue;
                        const char *keyStr = yyjson_get_str(keys);
                        auto keyIt = STRING_TO_KEY.find(keyStr);
                        if (keyIt != STRING_TO_KEY.end())
                            config.setBinding(keyIt->second, button);
                    }
                }
            }
        }

        // Savers
        yyjson_mut_val *saveGraphicsConfig (yyjson_mut_doc *doc, const GraphicsConfig &config) {
            yyjson_mut_val *obj = yyjson_mut_obj(doc);
            
            yyjson_mut_obj_add_int(doc, obj, "width", config.width);
            yyjson_mut_obj_add_int(doc, obj, "height", config.height);
            yyjson_mut_obj_add_bool(doc, obj, "vsync", config.vsync);
            yyjson_mut_obj_add_bool(doc, obj, "fullscreen", config.fullscreen);

            return obj;
        }

        yyjson_mut_val *saveInputConfig (yyjson_mut_doc *doc, const InputConfig &config) {
            yyjson_mut_val *obj = yyjson_mut_obj(doc);
            yyjson_mut_val *bindings = yyjson_mut_obj(doc);
            
            for (const auto &buttonKeys : config.button_to_keys) {
                const char *buttonStr = BUTTON_TO_STRING.find(buttonKeys.first)->second.c_str();

                // check if single key
                if (buttonKeys.second.size() == 1) {
                    //const char *keyStr = KEY_TO_STRING.find(buttonKeys.second.front())->second.c_str();
                    const char *keyStr = KEY_TO_STRING.find(*buttonKeys.second.begin())->second.c_str();
                    yyjson_mut_obj_add_str(doc, bindings, buttonStr, keyStr);
                }
                // check if multiple keys
                else {
                    yyjson_mut_val *keys = yyjson_mut_arr(doc);
                    for (const auto &key : buttonKeys.second) {
                        const char *keyStr = KEY_TO_STRING.find(key)->second.c_str();
                        yyjson_mut_arr_add_str(doc, keys, keyStr);
                    }
                    yyjson_mut_obj_add_val(doc, bindings, buttonStr, keys);
                }
            }

            yyjson_mut_obj_add_val(doc, obj, "bindings", bindings);
            return obj;
        }
    }

    void loadConfigDefault (Config &config)
    {
        // Graphics
        config.graphics.width = 1280;
        config.graphics.height = 720;
        config.graphics.vsync = true;
        config.graphics.fullscreen = false;

        // Input
        config.input.setBinding(GLFW_KEY_A, Input::ButtonFlag::INPUT_MOVE_LEFT);
        config.input.setBinding(GLFW_KEY_D, Input::ButtonFlag::INPUT_MOVE_RIGHT);
        config.input.setBinding(GLFW_KEY_SPACE, Input::ButtonFlag::INPUT_JUMP);
        config.input.setBinding(GLFW_KEY_W, Input::ButtonFlag::INPUT_JUMP);
        config.input.setBinding(GLFW_KEY_E, Input::ButtonFlag::INPUT_SHOT);
    }

    bool loadConfig (Config &config, const char *path)
    {
        yyjson_doc *doc = yyjson_read_file(path, 0, NULL, NULL);
        
        if (!doc) {
            printf("Cannot read file: %s", path);
            return false;
        }

        yyjson_val *root = yyjson_doc_get_root(doc);

        yyjson_val *graphicsObj = yyjson_obj_get(root, "graphics");
        Internal::loadGraphicsConfig(config.graphics, graphicsObj);

        yyjson_val *inputObj = yyjson_obj_get(root, "input");
        Internal::loadInputConfig(config.input, inputObj);

        yyjson_doc_free(doc);

        return true;
    }

    bool saveConfig (Config &config, const char *path)
    {
        // first verify that we can write to the file
        FILE *f;
        fopen_s(&f, path, "w");
        if (!f) {
            printf("Cannot write to file: %s", path);
            fclose(f);
            return false;
        }

        yyjson_mut_doc *doc = yyjson_mut_doc_new(NULL);
        yyjson_mut_val *root = yyjson_mut_obj(doc);
        yyjson_mut_doc_set_root(doc, root);

        yyjson_mut_obj_add_val(doc, root, "graphics", Internal::saveGraphicsConfig(doc, config.graphics));
        yyjson_mut_obj_add_val(doc, root, "input", Internal::saveInputConfig(doc, config.input));
        
        const char *json = yyjson_mut_write(doc, YYJSON_WRITE_PRETTY, NULL);
        fwrite(json, strlen(json), 1, f);

        yyjson_mut_doc_free(doc);
        fclose(f);

        return true;
    }
}