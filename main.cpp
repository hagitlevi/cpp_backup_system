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
        if (!fs::exists(p)) {
            std::cerr << "Error: " << p << " The path does not exist\n";
            continue;
        }
        if (fs::is_directory(p)) {
            std::cout << "Scanning: " << p <<"\n";
            try {

                for (const fs::directory_entry& element : fs::directory_iterator(p)) {
                    if (element.is_directory()) {
                        std::cout << "   [DIR] " << element.path().filename() << "\n";
                    }else if (element.is_regular_file()) {
                        std::cout << "   [FILE] " << element.path().filename() << "\n";
                    }else {
                        std::cout << "   [OTHER] " << element.path().filename() << "\n";
                    }
                }
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Error: cannot read directory: " << e.what() << "\n";
            }
        } else {
            std::cerr << "Error: " << p << " is not a directory\n";
        }
    }

    return 0;
}