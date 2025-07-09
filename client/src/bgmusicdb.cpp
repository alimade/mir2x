#include "clientargparser.hpp"
#include "bgmusicdb.hpp"
#include "hexstr.hpp"

extern ClientArgParser *g_clientArgParser;
std::optional<std::tuple<BGMusicElement, size_t>> BGMusicDB::loadResource(uint32_t key)
{
    if(g_clientArgParser->disableAudio){
        return {};
    }

    char bgmIndexString[16];
    std::vector<uint8_t> bgmDataBuf;

    if(!m_zsdbPtr->decomp(hexstr::to_string<uint32_t, 4>(key, bgmIndexString, true), 8, &bgmDataBuf)){
        return {};
    }

    if(bgmDataBuf.empty()){
        return {};
    }

    Mix_Music *musicPtr = nullptr;
    if(auto rwOpsPtr = SDL_RWFromConstMem(bgmDataBuf.data(), bgmDataBuf.size())){
        musicPtr = Mix_LoadMUS_RW(rwOpsPtr, SDL_TRUE);
    }

    if(!musicPtr){
        return {};
    }

    return std::make_tuple(BGMusicElement
    {
        .music = musicPtr,
        .musicFileData = std::move(bgmDataBuf), // vector class guarantees .data() get preserved
    }, 1);
}

void BGMusicDB::freeResource(BGMusicElement &element)
{
    // check SDL_mixer docmument
    // Mix_FreeMusic() stops music if it's playing, this is blocking when music doing fading out

    if(g_clientArgParser->disableAudio){
        return;
    }

    if(element.music){
        Mix_FreeMusic(element.music);
        element.music = nullptr;
        std::vector<uint8_t>().swap(element.musicFileData);
    }
}
