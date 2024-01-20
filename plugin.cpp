#include <Papyrus.h>
#include <logger.h>

using namespace SKSE;

namespace DeviousMimicClothes {
    void InitializePapyrus() {
        logger::trace("Initializing Papyrus binding...");
        if (GetPapyrusInterface()->Register(DeviousMimicClothes::RegisterFunctions)) {
            logger::trace("Papyrus functions bound.");
        } else {
            stl::report_and_fail("Failure to register Papyrus bindings.");
        }
    }

    void MessageHandler(MessagingInterface::Message* a_msg) {
        switch (a_msg->type) {
            // Descriptions are taken from the original skse64 library
            // See:
            // https://github.com/ianpatt/skse64/blob/09f520a2433747f33ae7d7c15b1164ca198932c3/skse64/PluginAPI.h#L193-L212
            case MessagingInterface::kPostLoad:
                logger::trace("kPostLoad: sent to registered plugins once all plugins have been loaded");
                break;
            case MessagingInterface::kPostPostLoad:
                logger::trace(
                    "kPostPostLoad: sent right after kPostLoad to facilitate the correct dispatching/registering of "
                    "messages/listeners");
                InitializePapyrus();
                break;
            case MessagingInterface::kPreLoadGame:
                // message->dataLen: length of file path, data: char* file path of .ess savegame file
                logger::trace("kPreLoadGame: sent immediately before savegame is read");
                break;
            case MessagingInterface::kPostLoadGame:
                // You will probably want to handle this event if your plugin uses a Preload callback
                // as there is a chance that after that callback is invoked the game will encounter an error
                // while loading the saved game (eg. corrupted save) which may require you to reset some of your
                // plugin state.
                logger::trace("kPostLoadGame: sent after an attempt to load a saved game has finished");
                break;
            case MessagingInterface::kSaveGame:
                logger::trace("kSaveGame");
                break;
            case MessagingInterface::kDeleteGame:
                // message->dataLen: length of file path, data: char* file path of .ess savegame file
                logger::trace("kDeleteGame: sent right before deleting the .skse cosave and the .ess save");
                break;
            case MessagingInterface::kInputLoaded:
                logger::trace("kInputLoaded: sent right after game input is loaded, right before the main menu initializes");
                break;
            case MessagingInterface::kNewGame:
                // message-data: CharGen TESQuest pointer (Note: I haven't confirmed the usefulness of this yet!)
                logger::trace("kNewGame: sent after a new game is created, before the game has loaded");
                break;
            case MessagingInterface::kDataLoaded:
                logger::trace("kDataLoaded: sent after the data handler has loaded all its forms");
                break;
            default:
                logger::trace("Unknown system message of type: {}", a_msg->type);
                break;
        }
    }

    SKSEPluginLoad(const LoadInterface* skse) {
        Init(skse);

        // Setup logging (e.g. using spdlog)
        SetupLog();
        auto* plugin = PluginDeclaration::GetSingleton();
        auto version = plugin->GetVersion();
        
        logger::info("{} {} is loading...", plugin->GetName(), version);

        GetMessagingInterface()->RegisterListener("SKSE", MessageHandler);

        logger::info("{} has finished loading.", plugin->GetName());

        return true;
    }
}