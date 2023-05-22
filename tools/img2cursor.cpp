
/*******************************************************************************
 * Copyright (c) 2023.
 * This file is part of The WhiteGear Studio software property.
 * If you get unexpected access to this file, or part ot whole codebase, you should
 * report this source code leak and delete all copies of source code from all your machines.
 ******************************************************************************/

#include <math/color.hpp>

/*******************************************************************************

     /$$$$$$ /$$      /$$  /$$$$$$   /$$$$$$   /$$$$$$  /$$   /$$ /$$$$$$$
    |_  $$_/| $$$    /$$$ /$$__  $$ /$$__  $$ /$$__  $$| $$  | $$| $$__  $$
      | $$  | $$$$  /$$$$| $$  \__/|__/  \ $$| $$  \__/| $$  | $$| $$  \ $$
      | $$  | $$ $$/$$ $$| $$ /$$$$  /$$$$$$/| $$      | $$  | $$| $$$$$$$/
      | $$  | $$  $$$| $$| $$|_  $$ /$$____/ | $$      | $$  | $$| $$__  $$
      | $$  | $$\  $ | $$| $$  \ $$| $$      | $$    $$| $$  | $$| $$  \ $$
     /$$$$$$| $$ \/  | $$|  $$$$$$/| $$$$$$$$|  $$$$$$/|  $$$$$$/| $$  | $$
    |______/|__/     |__/ \______/ |________/ \______/  \______/ |__/  |__/

    Simple utility tool for converting every input RGBA image into array of
    statically allocated pixels in format of R8G8B8A8_UNORM.

 ******************************************************************************/

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.hpp>

namespace {
    void usage() {
        fprintf(stdout, "usage:\n");
        fprintf(stdout, "img2cur <input_file> <output_file>\n");
    }

    const char* header = {
            "#ifndef _CONVIMAGE_DATA_HEADER_\n"
            "#define _CONVIMAGE_DATA_HEADER_\n\n"
            "#include <math/color.hpp>\n\n"
            "namespace wg {\n"
            "\tinline static const bounded_array<color32, "
    };
    const char* ending = {
            "\r\t};\n"
            "}\n"
            "\n#endif\n"
    };
}

auto main(int argc, char** argv) -> int {
    using namespace wg;

    if (argc < 3) {
        usage();
        return -1;
    }

    char* image_filename = argv[1];
    char* converted_filename = argv[2];

    int w, h, c;
    unsigned char* pixels = stbi_load(image_filename, &w, &h, &c, 4);
    if (pixels) {
        fprintf(stdout, "image '%s' has been loaded.\n", image_filename);
    }
    else {
        fprintf(stderr, "failed to load image!: %s", stbi_failure_reason());
        return -1;
    }

#ifdef WG_UNIX
    FILE* fd = fopen(converted_filename, "w+");
#elif WG_WINDOWS
    FILE* fd = nullptr;
    fopen_s(&fd, converted_filename, "w+");
#endif

    image_filename[strlen(image_filename) - 4] = 0;

    fprintf(fd, "%s%d> %s = {\n\t\t", header, int(w*h), image_filename);

    const uint pixel_count = w * h;

    uint counter = 0;
    for (uint i = 0; i < pixel_count; ++i) {
        const u8* raw = pixels + (i * 4);
        fprintf(fd, "{ 0x%02x, 0x%02x, 0x%02x, 0x%02x }, ",
                *(raw + 2), *(raw + 1), *(raw + 0), *(raw + 3));

        ++counter;
        if ((counter % 4) == 0) {
            fprintf(fd, "\n\t\t");
        }
    }

    fprintf(fd, "%s", ending);
    fclose(fd);

    return 0;
}
