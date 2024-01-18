#include <Dragon.h>

namespace DeviousMimicClothes {

    void Dragon::PrintName() {
        auto console = RE::ConsoleLog::GetSingleton();
        if (console) console->Print(this->_name.c_str());
    }
}