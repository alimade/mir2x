// convert monster graphics res to png files, usage:
//
//      monsterwil2png fileIndex            # index for monster files, 0 ~ 19
//                     path-to-package      #
//                     bodyFileName         # body file
//                     bodyFileNameExt      # body file
//                     shadowFileName       # shadow file
//                     shadowFileNameExt    # shadow file
//                     out-dir              # output file path
//                     prefix-width         # add prefix for easier view in file manger, 0 means no prefix
//
// for one decoding, following two files should exist
//      path-to-package/bodyFileName.bodyFileNameExt
//      path-to-package/shadowFileName.shadowFileNameExt
//
// i.e.
//      monsterwil2png 13 /home/you Mon-14 wil MonS-14 wil /home/you/out 4
//
// otherwise get error
//
// this command will try to find shadow images in shadow files
// if not find it will dynamically create one

#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <cinttypes>
#include <algorithm>

#include "imgf.hpp"
#include "alphaf.hpp"
#include "totype.hpp"
#include "filesys.hpp"
#include "wilimagepackage.hpp"

int g_MonWilFileIndex []
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void printUsage()
{
    const char *szUsage =
        "Usage: convert monster graphics res to png files, usage:\n"
        "\n"
        "                  monsterwil2png fileIndex            # index for monster files, 0 ~ 19\n"
        "                                 path-to-package      # \n"
        "                                 bodyFileName         # body file\n"
        "                                 bodyFileNameExt      # body file\n"
        "                                 shadowFileName       # shadow file\n"
        "                                 shadowFileNameExt    # shadow file\n"
        "                                 out-dir              # output file path\n"
        "\n"
        "              for one decoding, following two files should exist\n"
        "                  path-to-package/bodyFileName.bodyFileNameExt\n"
        "                  path-to-package/shadowFileName.shadowFileNameExt\n"
        "\n"
        "              i.e.\n"
        "                  monsterwil2png 13 /home/you Mon-14 wil MonS-14 wil /home/you/out\n"
        "\n"
        "              otherwise get error\n"
        "\n"
        "              this command will try to find shadow images in shadow files\n"
        "              if not find it will dynamically create one\n";
    std::printf("%s", szUsage);
}

const char *createOffsetFileName(char *szFileName,
        const char *szOutDir,
        bool bShadow,
        int  nLookID,
        int  nMotion,
        int  nDirection,
        int  nFrame,
        int  nDX,
        int  nDY,
        int  nImgCount,
        int  nPrefixWidth)
{
    if(szFileName){
        // refer to client/src/monster.cpp to get encoding strategy
        uint32_t nEncodeShadow    = bShadow    ? 0X0001 : 0X0000;
        uint32_t nEncodeLookID    = nLookID    & 0X07FF;
        uint32_t nEncodeMotion    = nMotion    & 0X000F;
        uint32_t nEncodeDirection = nDirection & 0X0007;
        uint32_t nEncodeFrame     = nFrame     & 0X001F;
        uint32_t nEncode = 0
            | (nEncodeShadow    << 23)
            | (nEncodeLookID    << 12)
            | (nEncodeMotion    <<  8)
            | (nEncodeDirection <<  5)
            | (nEncodeFrame     <<  0);

        char prefixBuf[64];
        if(nPrefixWidth > 0){
            std::sprintf(prefixBuf, "%0*d_", nPrefixWidth, nImgCount);
        }
        else{
            prefixBuf[0] = '\0';
        }

        std::sprintf(szFileName, "%s/%s%08llX%s%s%04X%04X.PNG",
                szOutDir,
                prefixBuf,
                to_llu(nEncode),
                ((nDX > 0) ? "1" : "0"),
                ((nDY > 0) ? "1" : "0"),
                std::abs(nDX),
                std::abs(nDY));
    }
    return szFileName;
}

bool monsterWil2PNG(int nMonsterFileIndex,
        const char *szPath,
        const char *szBodyFileBaseName,
        const char *,
        const char *szShadowFileBaseName,
        const char *,
        const char *szOutDir,
        const char *szPrefixWidth)
{
    WilImagePackage stPackageBody(szPath, szBodyFileBaseName);
    WilImagePackage stPackageShadow(szPath, szShadowFileBaseName);

    std::vector<uint32_t> stPNGBufShadow;

    int imgCount = 0;
    const int prefixWidth = std::stoi(szPrefixWidth);

    for(int nInnMonID = 0; nInnMonID < 10; ++nInnMonID){
        for(int nMotion = 0; nMotion < 10; ++nMotion){
            for(int nDirection = 0; nDirection < 8; ++nDirection){

                // terrible here
                // different monsters have different frame count

                int nMaxFrameCount = 10;
                int nGlobalMonID = nMonsterFileIndex * 10 + nInnMonID;

                // list monster IDs which need specification
                // only need to handle here if frameCount > 10 because it can cause overflow

                // I checked for Mon-1 ~ Mon-12
                // only these two needs special handling

                // if a motion has frameCount > 10
                // then this motion should only be one direction valid
                // otherwise it causes next direction accessing current frame array

                switch(nGlobalMonID){
                    case 104:
                        {
                            if(nMotion == 4){
                                nMaxFrameCount = (nDirection == 0) ? 20 : 0;
                            }
                            break;
                        }
                    case 85:
                        {
                            if(nMotion == 8){
                                nMaxFrameCount = (nDirection == 0) ? 20 : 0;
                            }
                            break;
                        }
                    default:
                        {
                            nMaxFrameCount = 10;
                            break;
                        }
                }

                for(int nFrame = 0; nFrame < nMaxFrameCount; ++nFrame){
                    int nBaseIndex = nInnMonID * 1000 + nMotion * 80 + nDirection * 10 + nFrame + g_MonWilFileIndex[nMonsterFileIndex];

                    // For taoist dog, nInnMonID = 0, file = Mon-10.wil
                    // arrangement:
                    //
                    // Mon-10:
                    // TMP000000.PNG ~ TMP000399.PNG taodog motions                   <-------+
                    // TMP000400.PNG ~ TMP000639.PNG invalid index or unknown images          |
                    // TMP000640.PNG ~ TMP000719.PNG taodog transform motions         <----+  |
                    //                                                                     |  |
                    // MonS-10:                                                            |  |
                    // TMP000000.PNG ~ TMP000399.PNG taodog motion shadows-----------------+--+
                    // TMP000400.PNG ~ TMP000479.PNG taodog transform motion shadows ------+

                    int alterShadowBaseIndex = -1;
                    if(nGlobalMonID == 90){
                        if(nBaseIndex >= 400 && nBaseIndex <= 639){
                            continue;
                        }
                        else if(nBaseIndex >= 640 && nBaseIndex <= 719){
                            alterShadowBaseIndex = (nBaseIndex - 640) + 400;
                        }
                    }

                    if(const auto bodyImgInfo = stPackageBody.setIndex(nBaseIndex)){
                        const auto layer = stPackageBody.decode(true, false, false);

                        // export for MonsterDBN
                        char szSaveFileName[128];
                        createOffsetFileName(szSaveFileName,
                                szOutDir,
                                false,
                                nGlobalMonID,
                                nMotion,
                                nDirection,
                                nFrame,
                                bodyImgInfo->px,
                                bodyImgInfo->py,
                                imgCount++,
                                prefixWidth);

                        if(!imgf::saveImageBuffer((uint8_t *)(layer[0]), bodyImgInfo->width, bodyImgInfo->height, szSaveFileName)){
                            std::printf("save PNG failed: %s", szSaveFileName);
                            return false;
                        }

                        // to save shadow png file
                        // try shadow file first, failed then try to make a dynamically one

                        if(alterShadowBaseIndex >= 0){
                            nBaseIndex = alterShadowBaseIndex;
                        }

                        if(const auto shadowImgInfo = stPackageShadow.setIndex(nBaseIndex)){
                            const auto shadowLayer = stPackageShadow.decode(true, false, false);

                            // export for MonsterDBN
                            char szSaveShadowFileName[128];
                            createOffsetFileName(szSaveShadowFileName,
                                    szOutDir,
                                    true,
                                    nGlobalMonID,
                                    nMotion,
                                    nDirection,
                                    nFrame,
                                    shadowImgInfo->px,
                                    shadowImgInfo->py,
                                    imgCount++,
                                    prefixWidth);

                            if(!imgf::saveImageBuffer(shadowLayer[0],  shadowImgInfo->width, shadowImgInfo->height, szSaveShadowFileName)){
                                std::printf("save PNG failed: %s", szSaveShadowFileName);
                                return false;
                            }

                        }
                        else{

                            // dynamically create one

                            // make a big buffer to hold the shadow as needed
                            // shadow buffer size depends on do project or not
                            //
                            //  project :  (nW + nH / 2) x (nH / 2 + 1)
                            //          :  (nW x nH)
                            //

                            bool bProject = true;
                            if(nMotion == 4){
                                switch(nGlobalMonID){
                                    case 30:
                                        {
                                            if(nFrame == 3){
                                                bProject = false;
                                            }
                                            break;
                                        }
                                    case 104:
                                        {
                                            if(nFrame == 19){
                                                bProject = false;
                                            }
                                            break;
                                        }
                                    default:
                                        {
                                            if(nFrame == 9){
                                                bProject = false;
                                            }
                                            break;
                                        }
                                }
                            }

                            const auto [bufShadow, nShadowW, nShadowH] = alphaf::createShadow(stPNGBufShadow, bProject, layer[0], bodyImgInfo->width, bodyImgInfo->height, colorf::A_SHF(0XFF));
                            if(true
                                    && nShadowW > 0
                                    && nShadowH > 0){

                                char szSaveShadowFileName[128];
                                createOffsetFileName(szSaveShadowFileName,
                                        szOutDir,
                                        true,
                                        nGlobalMonID,
                                        nMotion,
                                        nDirection,
                                        nFrame,
                                        bProject ? bodyImgInfo->shadowPX : (bodyImgInfo->px + 3),
                                        bProject ? bodyImgInfo->shadowPY : (bodyImgInfo->py + 2),
                                        imgCount++,
                                        prefixWidth);

                                if(!imgf::saveImageBuffer(bufShadow, nShadowW, nShadowH, szSaveShadowFileName)){
                                    std::printf("save shadow PNG failed: %s", szSaveShadowFileName);
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    // check arguments
    if(argc != 9){
        printUsage();
        return 1;
    }

    if(true
            && std::strcmp(argv[1],  "0")
            && std::strcmp(argv[1],  "1")
            && std::strcmp(argv[1],  "2")
            && std::strcmp(argv[1],  "3")
            && std::strcmp(argv[1],  "4")
            && std::strcmp(argv[1],  "5")
            && std::strcmp(argv[1],  "6")
            && std::strcmp(argv[1],  "7")
            && std::strcmp(argv[1],  "8")
            && std::strcmp(argv[1],  "9")
            && std::strcmp(argv[1], "10")
            && std::strcmp(argv[1], "11")
            && std::strcmp(argv[1], "12")
            && std::strcmp(argv[1], "13")
            && std::strcmp(argv[1], "14")
            && std::strcmp(argv[1], "15")
            && std::strcmp(argv[1], "16")
            && std::strcmp(argv[1], "17")
            && std::strcmp(argv[1], "18")
            && std::strcmp(argv[1], "19")){
        std::printf("Invlid argv[1] : %s\n", argv[1]);
        printUsage();
        return 1;
    }

    return monsterWil2PNG(std::atoi(argv[1]), argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8]);
}
