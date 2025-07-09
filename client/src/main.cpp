#include <cstdio>
#include "log.hpp"
#include "client.hpp"
#include "pngtexdb.hpp"
#include "fontexdb.hpp"
#include "mapbindb.hpp"
#include "emojidb.hpp"
#include "imeboard.hpp"
#include "bgmusicdb.hpp"
#include "soundeffectdb.hpp"
#include "notifyboard.hpp"
#include "pngtexoffdb.hpp"
#include "clientargparser.hpp"

// global variables, decide to follow pattern in MapEditor
// put all global in one place and create them togother

ClientArgParser *g_clientArgParser = nullptr;
Log             *g_log             = nullptr; // log information handler, must be inited first
PNGTexDB        *g_progUseDB       = nullptr; // database for all PNG texture only
PNGTexDB        *g_itemDB          = nullptr; // database for all PNG texture only
PNGTexDB        *g_mapDB           = nullptr;
PNGTexOffDB     *g_heroDB          = nullptr; // database for hero
PNGTexOffDB     *g_hairDB          = nullptr; // database for hair
PNGTexOffDB     *g_monsterDB       = nullptr; // database for monster
PNGTexOffDB     *g_weaponDB        = nullptr; // database for weapon
PNGTexOffDB     *g_helmetDB        = nullptr; // database for helmet
PNGTexOffDB     *g_equipDB         = nullptr; // database for equipment in player status board
PNGTexOffDB     *g_magicDB         = nullptr; // database for magic
PNGTexOffDB     *g_standNPCDB      = nullptr; // database for NPC
PNGTexOffDB     *g_selectCharDB    = nullptr; // database for chars in ProcessSelectChar and ProcessCreateChar
EmojiDB         *g_emojiDB         = nullptr; // database for emoticons
BGMusicDB       *g_bgmDB           = nullptr; // database for bgm, contains .MP3/.WAV
SoundEffectDB   *g_seffDB          = nullptr; // database for sound effect, contains .WAV
MapBinDB        *g_mapBinDB        = nullptr;
FontexDB        *g_fontexDB        = nullptr;
SDLDevice       *g_sdlDevice       = nullptr; // for SDL hardware device
IMEBoard        *g_imeBoard        = nullptr; //
NotifyBoard     *g_notifyBoard     = nullptr;
Client          *g_client          = nullptr; // gobal instance

int main(int argc, char *argv[])
{
    std::srand((unsigned int)std::time(nullptr));
    try{
        argf::parser cmdParser(argc, argv);
        g_clientArgParser = new ClientArgParser(cmdParser);

        if(g_clientArgParser->disableProfiler){
            logDisableProfiler();
        }
        g_log = new Log("mir2x-client-v0.1");

    }
    catch(const std::exception &e){
        std::fprintf(stderr, "Caught exception: %s\n", e.what());
        return -1;
    }
    catch(...){
        std::fprintf(stderr, "Caught unknown exception, exit...\n");
        return -1;
    }

    try{
        g_sdlDevice       = new SDLDevice();
        g_progUseDB       = new PNGTexDB(1024);
        g_itemDB          = new PNGTexDB(1024);
        g_mapDB           = new PNGTexDB(8192);
        g_heroDB          = new PNGTexOffDB(1024);
        g_hairDB          = new PNGTexOffDB(1024);
        g_monsterDB       = new PNGTexOffDB(1024);
        g_weaponDB        = new PNGTexOffDB(1024);
        g_helmetDB        = new PNGTexOffDB(1024);
        g_equipDB         = new PNGTexOffDB(1024);
        g_magicDB         = new PNGTexOffDB(1024);
        g_standNPCDB      = new PNGTexOffDB(1024);
        g_selectCharDB    = new PNGTexOffDB(512);
        g_fontexDB        = new FontexDB(1024);
        g_mapBinDB        = new MapBinDB();
        g_emojiDB         = new EmojiDB();
        g_bgmDB           = new BGMusicDB(5);
        g_seffDB          = new SoundEffectDB(128);
        g_client          = new Client();       // loads fontex resource

        if(!g_clientArgParser->disableIME){
            g_imeBoard = new IMEBoard(DIR_UPLEFT, 0, 0);
        }

        g_notifyBoard = new NotifyBoard(DIR_UPLEFT, 0, 0, 10240, 0, 15, 0, colorf::RED + colorf::A_SHF(255), 0, 5);
        g_client->mainLoop();
    }
    catch(const std::exception &e){
        g_log->addLog(LOGTYPE_FATAL, "Caught exception: %s", e.what());
    }
    catch(...){
        g_log->addLog(LOGTYPE_FATAL, "Caught unknown exception");
    }
    return 0;
}
