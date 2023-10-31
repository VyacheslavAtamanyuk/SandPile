#include "SandPile.h"
#include "BMP_READER.h"
#include <limits>
#include <string>
#include <filesystem>


void SandPile(Arguments args) {
    std::ifstream file(args.input, std::ios::binary);
    if (file) {
        char data;
        const int enough = 30;
        int count_for_x = 0;
        int count_for_y = 0;
        char buffer_for_x[enough];
        char buffer_for_y[enough];
        char* numbers;
        bool x_already_done = false;
        bool y_already_done = false;
        int16_t max_x = std::numeric_limits<int16_t>::min();
        int16_t min_x = std::numeric_limits<int16_t>::max();
        int16_t max_y = std::numeric_limits<int16_t>::min();
        int16_t min_y = std::numeric_limits<int16_t>::max();
        while (file.get(data)) {
            if (data == '\n') {
                buffer_for_x[count_for_x] = '\0';
                buffer_for_y[count_for_y] = '\0';
                numbers = buffer_for_x;
                max_x = std::max(max_x,static_cast<int16_t>(std::atoi(numbers)));
                min_x = std::min(min_x,static_cast<int16_t>(std::atoi(numbers)));
                numbers = buffer_for_y;
                max_y = std::max(max_y,static_cast<int16_t>(std::atoi(numbers)));
                min_y = std::min(min_y,static_cast<int16_t>(std::atoi(numbers)));
                numbers = nullptr;
                count_for_x = 0;
                count_for_y = 0;
                x_already_done = false;
                y_already_done = false;
                memset(buffer_for_x, 0, sizeof(buffer_for_x));
                memset(buffer_for_y, 0, sizeof(buffer_for_y));
            } else if (data != '\t') {
                if (!x_already_done) {
                    buffer_for_x[count_for_x++] = data;
                } else if (!y_already_done) {
                    buffer_for_y[count_for_y++] = data;
                }
            } else {
                if (!x_already_done) {
                    x_already_done = true;
                } else if (!y_already_done) {
                    y_already_done = true;
                }
            }
        }
        count_for_x = 0;
        count_for_y = 0;
        numbers = nullptr;
        x_already_done = false;
        y_already_done = false;
        memset(buffer_for_x, 0, sizeof(buffer_for_x));
        memset(buffer_for_y, 0, sizeof(buffer_for_y));
        int16_t x_size = std::max(abs(max_x),abs(min_x));
        int16_t y_size = std::max(abs(max_y),abs(min_y));
        uint64_t** array = new uint64_t*[2*y_size+1];
        for (int i = 0; i < 2*y_size + 1; ++i) {
            array[i] = new uint64_t[2*x_size+1];
        }
        for (int i = 0; i < 2*y_size + 1; ++i) {
            for (int j = 0; j < 2*x_size + 1; ++j) {
                array[i][j] = 0;
            }
        }
        std::ifstream file(args.input, std::ios::binary);
        int count_for_sand = 0;
        char buffer_for_sand[enough];
        while (file.get(data)) {
            if (data == '\n') {
                buffer_for_x[count_for_x] = '\0';
                buffer_for_y[count_for_y] = '\0';
                buffer_for_sand[count_for_sand] = '\0';
                numbers = buffer_for_x;
                int16_t x_coord = static_cast<int16_t>(std::atoi(numbers));
                numbers = buffer_for_y;
                int16_t y_coord = static_cast<int16_t>(std::atoi(numbers));
                numbers = buffer_for_sand;
                uint64_t num_of_sand = static_cast<uint64_t>(std::atoi(numbers));
                numbers = nullptr;
                count_for_x = 0;
                count_for_y = 0;
                count_for_sand = 0;
                x_already_done = false;
                y_already_done = false;
                memset(buffer_for_x, 0, sizeof(buffer_for_x));
                memset(buffer_for_y, 0, sizeof(buffer_for_y));
                memset(buffer_for_sand, 0, sizeof(buffer_for_sand));
                if (x_coord > 0 && y_coord >= 0) {
                    array[y_size - y_coord][x_size + x_coord] = num_of_sand;
                } else if (x_coord > 0 && y_coord < 0) {
                    array[y_size + abs(y_coord)][x_size + x_coord] = num_of_sand;
                } else if (x_coord <= 0 && y_coord >= 0) {
                    array[y_size - y_coord][x_size - abs(x_coord)] = num_of_sand;
                } else if (x_coord <= 0 && y_coord < 0) {
                    array[y_size + abs(y_coord)][x_size - abs(x_coord)] = num_of_sand;
                }
            } else if (data == '\t') {
                if (!x_already_done) {
                    x_already_done = true;
                } else if (!y_already_done) {
                    y_already_done = true;
                }
            } else{
                if (!x_already_done) {
                    buffer_for_x[count_for_x++] = data;
                } else if (!y_already_done) {
                    buffer_for_y[count_for_y++] = data;
                } else {
                    buffer_for_sand[count_for_sand++] = data;
                }
            }
        }
        y_size = 2*y_size + 1;
        x_size = 2*x_size + 1;
        for (int i = 0; i < args.max_iter; i++) {

            uint64_t** array_copy = new uint64_t*[y_size];
            for (int j = 0; j < y_size; ++j) {
                array_copy[j] = new uint64_t[x_size];
            }
            for(int j = 0; j < y_size; ++j) {
                for (int k = 0; k < x_size; ++k) {
                    array_copy[j][k] = array[j][k];
                }
            }

            bool left = false;
            bool up = false;
            bool right = false;
            bool down = false;
            for (int j = 0; j < x_size; ++j) {
                if (array[0][j] >= 4) {
                    up = true;
                }
                if (array[y_size - 1][j] >= 4) {
                    down = true;
                }
            }
            for (int j = 0; j < y_size; ++j) {
                if (array[j][0] >= 4) {
                    left = true;
                }
                if (array[j][x_size - 1] >= 4) {
                    right = true;
                }
            }

            int16_t old_y_size = y_size;
            int16_t old_x_size = x_size;
            //мб здесь по 1+1 лучше будет 1?
            y_size += up+down;
            x_size += left+right;


            // удаляем массив со старым размером
            for (int j = 0; j < old_y_size; ++j) {
                delete[] array[j];
            }
            delete[] array;

            // создаем массив с новым размером
            array = new uint64_t*[y_size];
            for (int j = 0; j < y_size; ++j) {
                array[j] = new uint64_t[x_size];
            }

            //инициализируем нулями
            for (int j = 0; j < y_size; ++j) {
                for (int k = 0; k < x_size; ++k) {
                    array[j][k] = 0;
                }
            }

            //заполняем
            for(int j = 0; j < old_y_size; ++j) {
                for (int k = 0; k < old_x_size; ++k) {
                    array[j + up][k + left] = array_copy[j][k];
                }
            }

            // удаляем копию старого массива
            for (int j = 0; j < old_y_size; ++j) {
                delete[] array_copy[j];
            }
            delete[] array_copy;

            // сделаем копию обновленного array, чтобы отслеживать актуальность песчинки на ее рассыпание
            uint64_t** array_copy1 = new uint64_t*[y_size];
            for (int j = 0; j < y_size; ++j) {
                array_copy1[j] = new uint64_t[x_size];
            }
            for (int j = 0; j < y_size; ++j) {
                for (int k = 0; k < x_size; ++k) {
                    array_copy1[j][k] = array[j][k];
                }
            }

            for (int j = 0; j < y_size; ++j) {
                for (int k = 0;  k < x_size; ++k) {
                    if (array[j][k] >= 4 && array_copy1[j][k] >= 4) {
                        array[j][k] -= 4;
                        array[j-1][k] += 1;
                        array[j+1][k] += 1;
                        array[j][k+1] += 1;
                        array[j][k-1] += 1;
                    }
                }
            }

            // удалим копию обновленного массива
            for (int j = 0; j < y_size; ++j) {
                delete[] array_copy1[j];
            }
            delete[] array_copy1;

            //засовываем в bmp при необходимости
            if ((args.freq == 0 && i == args.max_iter - 1) || (((i+1) % args.freq == 0) && (args.freq != 0))) {

                std::filesystem::path folder_path = args.output;
                char buffer[enough];
                std::sprintf(buffer, "%d.bmp", i+1);
                std::filesystem::path file_path = folder_path / buffer;
                std::cout << file_path << '\n';
                std::ofstream bmp_file(file_path, std::ios::out | std::ios::binary);
                SetBMPFile(bmp_file, array, args.output, x_size, y_size);
            }
        }
    }
}