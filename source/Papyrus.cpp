#include <Papyrus.h>

namespace DeviousMimicClothes {
    constexpr std::string_view PapyrusClass = "dmcNativeCalls";

    bool IsActorValid(RE::Actor* actor) {
        // no valid actor given
        if (actor == nullptr) {
            return false
        }

        // actor is not loaded, dead or busy
        if (!actor->Is3DLoaded() || actor->IsDead() || actor->IsDisabled() || actor->GetCurrentScene())
        {
            return false;
        }
        
        return true;
    }

    bool RegisterFunctions(RE::BSScript::IVirtualMachine* vm) {
        vm->RegisterFunction("IsActorValid", PapyrusClass, IsActorValid, false);

        return true;
    }
}