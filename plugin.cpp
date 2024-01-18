#include <Dragon.h>

using namespace SKSE;

namespace DeviousMimicClothes {
    void MessageHandler(MessagingInterface::Message* a_msg) {
        switch (a_msg->type) {
            // Descriptions are taken from the original skse64 library
            // See:
            // https://github.com/ianpatt/skse64/blob/09f520a2433747f33ae7d7c15b1164ca198932c3/skse64/PluginAPI.h#L193-L212
            case SKSE::MessagingInterface::kPostLoad:
                logger::info("kPostLoad: sent to registered plugins once all plugins have been loaded");
                break;
            case SKSE::MessagingInterface::kPostPostLoad:
                logger::info(
                    "kPostPostLoad: sent right after kPostLoad to facilitate the correct dispatching/registering of "
                    "messages/listeners");
                break;
            case SKSE::MessagingInterface::kPreLoadGame:
                // message->dataLen: length of file path, data: char* file path of .ess savegame file
                logger::info("kPreLoadGame: sent immediately before savegame is read");
                break;
            case SKSE::MessagingInterface::kPostLoadGame:
                // You will probably want to handle this event if your plugin uses a Preload callback
                // as there is a chance that after that callback is invoked the game will encounter an error
                // while loading the saved game (eg. corrupted save) which may require you to reset some of your
                // plugin state.
                logger::info("kPostLoadGame: sent after an attempt to load a saved game has finished");
                break;
            case SKSE::MessagingInterface::kSaveGame:
                logger::info("kSaveGame");
                break;
            case SKSE::MessagingInterface::kDeleteGame:
                // message->dataLen: length of file path, data: char* file path of .ess savegame file
                logger::info("kDeleteGame: sent right before deleting the .skse cosave and the .ess save");
                break;
            case SKSE::MessagingInterface::kInputLoaded:
                logger::info("kInputLoaded: sent right after game input is loaded, right before the main menu initializes");
                break;
            case SKSE::MessagingInterface::kNewGame:
                // message-data: CharGen TESQuest pointer (Note: I haven't confirmed the usefulness of this yet!)
                logger::info("kNewGame: sent after a new game is created, before the game has loaded");
                break;
            case SKSE::MessagingInterface::kDataLoaded:
                logger::info("kDataLoaded: sent after the data handler has loaded all its forms");
                break;
            default:
                logger::info("Unknown system message of type: {}", a_msg->type);
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

        return true;
    }
}