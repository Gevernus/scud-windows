#pragma once
#include <string>
#include <windows.h>

class QRGenerator
{
public:
    static HBITMAP GenerateQRCode(const std::wstring &data, int width, int height);
};