#include "cheats.hpp"

#include <3ds.h>

#include "Debugger/WP.hpp"
#include "Memory/MemManager.hpp"
#include "Render/Font.hpp"
#include "csvc.h"

#include FT_FREETYPE_H

namespace CTRPluginFramework {


extern "C" void svcSetWatchpoint(u32 addr, WatchMode mode, WatchOP opt, WatchSize size);
extern "C" void svcDisableWatchPoint(void);
extern "C" bool svcGetWatchpointInfo(WatchpointInfo* out);


void Watchpoint(MenuEntry* entry) {
    bool is_loop = true;
    static bool is_wp_enabled = false;
    Keyboard key("ダミー");
    std::string title;
    static u32 addr;
    Result res;

    auto enter_wp_addr = []() {
        WatchSize size;
        WatchOP type;
        int choice = -1;
        Keyboard keyboard_set_wp("ウォッチポイントを設定\nアドレスを入力");
        keyboard_set_wp.Open(addr);
        Keyboard keyboard_wp_type("ウォッチタイプを選択", {"Read", "Write", "Read/Write"});
        choice = keyboard_wp_type.Open();
        switch (choice) {
            case 0: {
                type = Read;
                break;
            }
            case 1: {
                type = Write;
                break;
            }
            case 2: {
                type = ReadWrite;
                break;
            }
            default:
                return false;
        }
        Keyboard keyboard_wp_size("サイズを選択", {"1Byte", "2Byte", "4Byte"});
        choice = keyboard_wp_size.Open();
        switch (choice) {
            case 0: {
                size = Byte;
                break;
            }
            case 1: {
                size = HalfW;
                break;
            }
            case 2: {
                size = Word;
                break;
            }
            default:
                return false;
        }
        svcSetWatchpoint(addr, User, type, size);
        return true;
    };

    while (is_loop) {
        StringVector list_option;
        title = "操作を選択\n";
        title.append("Bボタンで戻る\n");
        if (is_wp_enabled) {
            title.append(Utils::Format("設定中のアドレス:0x%08X\n", addr));
            list_option.emplace_back(Color::Red << "ウォッチポイント無効化");
            list_option.emplace_back(Color::Green << "ウォッチポイント変更");
        } else {
            title.append("ウォッチポイントを有効化\n");
            list_option.emplace_back(Color::Blue << "ウォッチポイント有効化");
        }
        key.GetMessage() = title;
        key.Populate(list_option);
        int choice = key.Open();
        if (Controller::IsKeysDown(B)) {
            is_loop = false;
        }
        if (is_wp_enabled) {
            if (choice == 0) {
                svcDisableWatchPoint();
                is_wp_enabled = false;
            }
            if (choice == 1) {
                svcDisableWatchPoint();
                is_wp_enabled = enter_wp_addr();
            }
        } else {
            if (choice == 0) {
                is_wp_enabled = enter_wp_addr();
            }
        }
    }

    entry->SetGameFunc([](MenuEntry* entry) {
        WatchpointInfo wp_info;
        if (!svcGetWatchpointInfo(&wp_info)) return;
        OSD::Notify(Utils::Format("far:%08X pc :%08X lr :%08X", wp_info.far, wp_info.pc, wp_info.lr));
    });
    return;
}

}  // namespace CTRPluginFramework