#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;


int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cerr << "Usage: " << argv[0] << " <directory>...\n";
        return 1;
    }

    for (int i=1; i<argc; i++) {
        fs::path p = argv[i];
        if (!exists(p)) {
            std::cerr << "Error: " << p << " The path does not exist\n";
            continue;
        }
        if (is_directory(p)) {
            std::cout << "Scanning: " << p <<"\n";
        } else {
            std::cerr << "Error: " << p << " is not a directory\n";
        }
    }

    return 0;
}