#ifndef LABWORK3_BMP_HEADER_H
#define LABWORK3_BMP_HEADER_H

#include <fstream>
#include <cstdint>

static const uint8_t kHeader1Size = 14;
static const uint8_t kHeader2Size = 40;
static const uint8_t kNumOfColors = 5;
static const uint8_t kSizeOfColorTable = 20;
static const uint8_t kBitsPerPixel = 4;
static const uint8_t kRGBPlusAlpha = 4;

void WriteHeader1ToBmp(std::ofstream& bmp_file, const uint32_t x_size, const uint32_t y_size, const uint8_t padding) {
    uint8_t header1[kHeader1Size] = {};
    uint32_t size = kHeader1Size + kHeader2Size + kSizeOfColorTable + ((x_size + 1) / 2 + padding) * y_size;
    uint8_t offset = kHeader1Size + kHeader2Size + kSizeOfColorTable;
    header1[0] = 'B';
    header1[1] = 'M';
    header1[2] = (size & 0xFF);
    header1[3] = ((size >> 8) & 0xFF);
    header1[4] = ((size >> 16) & 0xFF);
    header1[5] = ((size >> 24) & 0xFF);
    header1[10] = offset;
    bmp_file.write(reinterpret_cast<char*>(header1),kHeader1Size);
}

void WriteHeader2ToBmp(std::ofstream& bmp_file, const uint32_t x_size, const uint32_t y_size) {
    uint8_t header2[kHeader2Size] = {};
    header2[0] = kHeader2Size;
    header2[4] = (y_size & 0xFF);
    header2[5] = ((y_size >> 8) & 0xFF);
    header2[6] = ((y_size >> 16) & 0xFF);
    header2[7] = ((y_size >> 24) & 0xFF);
    header2[8] = (y_size & 0xFF);
    header2[9] = ((y_size >> 8) & 0xFF);
    header2[10] = ((y_size >> 16) & 0xFF);
    header2[11] = ((y_size >> 24) & 0xFF);
    header2[12] = 1;
    header2[14] = kBitsPerPixel;
    header2[32] = kNumOfColors;
    bmp_file.write(reinterpret_cast<char*>(header2), kHeader2Size);
}

void WriteColorTable(std::ofstream& bmp_file) {
    static const uint8_t white[kRGBPlusAlpha] = {255, 255, 255, 0};
    static const uint8_t green[kRGBPlusAlpha] = {0, 128, 0, 0};
    static const uint8_t yellow[kRGBPlusAlpha] = {0, 255, 255, 0};
    static const uint8_t purple[kRGBPlusAlpha] = {255, 0, 128, 0};
    static const uint8_t black[kRGBPlusAlpha] = {0, 0, 0, 0};
    static const uint8_t* colors[kNumOfColors] = {white, green, yellow, purple, black};

    for (int i = 0; i < kNumOfColors; ++i) {
        for (int j = 0; j < kRGBPlusAlpha; ++j) {
            bmp_file << colors[i][j];
        }
    }
}

void WritePadding(std::ofstream& bmp_file, const uint8_t padding) {
    for (int k = 0; k < padding; ++k) {
        bmp_file << 0;
    }
}

void WriteTwoPixels(std::ofstream& bmp_file, const uint8_t pixel1, const uint8_t pixel2) {
    uint8_t byte = 0;
    byte += pixel1 << kBitsPerPixel;
    byte += pixel2;
    bmp_file << byte;
}

void WritePixelsInBMP(std::ofstream& bmp_file, uint64_t** array, const uint8_t padding, const uint32_t x_size, const uint32_t y_size) {
    for (int row = 0; row < y_size; ++row) {
        int new_row = y_size - 1 - row;
        for (int col = 0; col < x_size; col += 2) {
            uint8_t pixel1 = kNumOfColors - 1;
            if (pixel1 > array[new_row][col]) {
                pixel1 = array[new_row][col];
            }
            if (col == x_size - 1) {
                WriteTwoPixels(bmp_file, pixel1, 0);
                continue;
            }

            uint8_t pixel2 = kNumOfColors - 1;
            if (pixel2 > array[new_row][col + 1]) {
                pixel2 = array[new_row][col + 1];
            }
            WriteTwoPixels(bmp_file, pixel1, pixel2);
        }
        WritePadding(bmp_file, padding);
    }
}

void SetBMPFile(std::ofstream& bmp_file, uint64_t** array, const char* output, const uint32_t x_size, const uint32_t y_size) {
    const uint8_t padding = (4 - ((x_size + 1) / 2) % 4) % 4;
    WriteHeader1ToBmp(bmp_file, x_size, y_size, padding);
    WriteHeader2ToBmp(bmp_file, x_size, y_size);
    WriteColorTable(bmp_file);
    WritePixelsInBMP(bmp_file, array, padding, x_size, y_size);
    bmp_file.close();
}
#endif //LABWORK3_BMP_HEADER_H
