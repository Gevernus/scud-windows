#include "QRGenerator.h"
#include <zxing/qrcode/QREncoder.h>
#include <zxing/BitMatrix.h>

HBITMAP QRGenerator::GenerateQRCode(const std::wstring &data, int width, int height)
{
    zxing::qrcode::QRCodeWriter writer;
    auto matrix = writer.encode(std::string(data.begin(), data.end()), width, height);

    HDC hdc = GetDC(NULL);
    HBITMAP hbm = CreateCompatibleBitmap(hdc, width, height);
    HDC hdcMem = CreateCompatibleDC(hdc);
    SelectObject(hdcMem, hbm);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            SetPixel(hdcMem, x, y, matrix->get(x, y) ? RGB(0, 0, 0) : RGB(255, 255, 255));
        }
    }

    DeleteDC(hdcMem);
    ReleaseDC(NULL, hdc);
    return hbm;
}