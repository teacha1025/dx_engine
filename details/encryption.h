#pragma once
#include <stdio.h>
#include <string>

namespace MELON_LZSS {
    struct LZSS_ENCODE_INFO
    {
        int OriginalSize;
        int PressSize;
        int EncodeCode;
    };

    int LZSS_Encode(void* Src, int SrcSize, void* Dest)
    {
        int i;
        unsigned char* SrcPoint, * DestPoint;
        int PressSizeCounter, SrcSizeCounter;
        LZSS_ENCODE_INFO EncodeInfo;
        int EncodeCode;

        SrcPoint = (unsigned char*)Src;
        DestPoint = (unsigned char*)Dest;

        {
            int NumCounter[256];
            int MinNum;

            for (i = 0; i < 256; i++)
            {
                NumCounter[i] = 0;
            }

            for (i = 0; i < SrcSize; i++)
            {
                NumCounter[SrcPoint[i]] ++;
            }

            {
                EncodeCode = 0;
                MinNum = NumCounter[0];
                for (i = 1; i < 256; i++)
                {
                    if (MinNum > NumCounter[i])
                    {
                        MinNum = NumCounter[i];
                        EncodeCode = i;
                    }
                }
            }
        }

        {
            int Index, EqualNum, MaxEqualNum, MaxIndex;
            unsigned char* PressData;

            PressData = DestPoint + sizeof(LZSS_ENCODE_INFO);

            SrcSizeCounter = 0;

            PressSizeCounter = 0;

            while (SrcSizeCounter < SrcSize)
            {
                {
                    MaxEqualNum = -1;
                    MaxIndex = -1;

                    for (Index = 1; Index <= 254; Index++)
                    {
                        if (SrcSizeCounter - Index < 0) break;

                        for (EqualNum = 0; EqualNum < Index; EqualNum++)
                        {
                            if (EqualNum + SrcSizeCounter >= SrcSize) break;

                            if (SrcPoint[SrcSizeCounter + EqualNum] != SrcPoint[SrcSizeCounter - Index + EqualNum]) break;
                        }

                        if (EqualNum >= 4 && MaxEqualNum < EqualNum)
                        {
                            MaxEqualNum = EqualNum;
                            MaxIndex = Index;
                        }
                    }
                }

                if (MaxIndex == -1)
                {
                    if (Dest != NULL) PressData[PressSizeCounter] = SrcPoint[SrcSizeCounter];
                    PressSizeCounter++;

                    if (SrcPoint[SrcSizeCounter] == EncodeCode)
                    {
                        if (Dest != NULL) PressData[PressSizeCounter] = SrcPoint[SrcSizeCounter];
                        PressSizeCounter++;
                    }
                    SrcSizeCounter++;
                }
                else
                {
                    if (Dest != NULL) PressData[PressSizeCounter] = (unsigned char)EncodeCode;
                    PressSizeCounter++;

                    {
                        if (Dest != NULL) PressData[PressSizeCounter] = (unsigned char)MaxIndex;

                        if (Dest != NULL && PressData[PressSizeCounter] >= EncodeCode)
                            PressData[PressSizeCounter] ++;

                        PressSizeCounter++;
                    }

                    if (Dest != NULL) PressData[PressSizeCounter] = (unsigned char)MaxEqualNum;
                    PressSizeCounter++;

                    SrcSizeCounter += MaxEqualNum;
                }
            }
        }

        {
            EncodeInfo.OriginalSize = SrcSize;

            EncodeInfo.PressSize = PressSizeCounter + sizeof(LZSS_ENCODE_INFO);

            EncodeInfo.EncodeCode = EncodeCode;
        }

        if (Dest != NULL) memcpy(DestPoint, &EncodeInfo, sizeof(LZSS_ENCODE_INFO));

        return EncodeInfo.PressSize;
    }

    int LZSS_Decode(void* Press, void* Dest)
    {
        int PressSize, PressSizeCounter, DestSizeCounter;
        unsigned char* PressPoint, * DestPoint;
        LZSS_ENCODE_INFO EncodeInfo;

        PressPoint = (unsigned char*)Press;
        DestPoint = (unsigned char*)Dest;

        memcpy(&EncodeInfo, Press, sizeof(LZSS_ENCODE_INFO));

        if (Dest == NULL)
            return EncodeInfo.OriginalSize;

        PressSize = EncodeInfo.PressSize - sizeof(LZSS_ENCODE_INFO);

        {
            int Index, EqualNum;
            unsigned char* PressData;

            PressData = PressPoint + sizeof(LZSS_ENCODE_INFO);

            DestSizeCounter = 0;

            PressSizeCounter = 0;

            while (PressSizeCounter < PressSize)
            {
                if (PressData[PressSizeCounter] == EncodeInfo.EncodeCode)
                {
                    PressSizeCounter++;

                    if (PressData[PressSizeCounter] == EncodeInfo.EncodeCode)
                    {
                        DestPoint[DestSizeCounter] = (unsigned char)EncodeInfo.EncodeCode;
                        DestSizeCounter++;

                        PressSizeCounter++;
                    }
                    else
                    {

                        {
                            Index = PressData[PressSizeCounter];
                            PressSizeCounter++;

                            if (Index > EncodeInfo.EncodeCode) Index--;
                        }

                        EqualNum = PressData[PressSizeCounter];
                        PressSizeCounter++;

                        memcpy(&DestPoint[DestSizeCounter], &DestPoint[DestSizeCounter - Index], EqualNum);
                        DestSizeCounter += EqualNum;
                    }
                }
                else
                {
                    DestPoint[DestSizeCounter] = PressData[PressSizeCounter];

                    DestSizeCounter++;
                    PressSizeCounter++;
                }
            }
        }

        return EncodeInfo.OriginalSize;
    }
}

namespace MELON_ENCRYPT {
    char* makesalt(int key) {
        static char salt[10];
        static char saltchar[] = {
          "./0123456789"
          "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
          "abcdefghijklmnopqrstuvwxyz"
        };

        srand(key);

        for (int i = 0; i < 8; i++) {
            salt[i] = saltchar[(rand() >> 6) & 0x3f];
        }

        return salt;
    }

    std::string encode(std::string plane) {
        int count = 0, length = 0;
        char* salt = makesalt(0);
        for (auto&& d : plane) {
            if (count == 8) {
                count = 0;
                length++;
                salt = makesalt(length);
            }
            d ^= salt[count];
            count++;
        }
        return plane;
    }

    std::string decode(std::string press) {
        int count = 0, length = 0;
        char* salt = makesalt(0);
        for (auto&& d : press) {
            if (count == 8) {
                count = 0;
                length++;
                salt = makesalt(length);
            }
            d ^= salt[count];
            count++;
        }
        return press;
    }
}