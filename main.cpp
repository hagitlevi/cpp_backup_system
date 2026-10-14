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
        std::uintmax_t bytes_num = 0;
        int files_num = 0;
        if (!fs::exists(p)) {
            std::cerr << "Error: " << p << " The path does not exist\n";
            continue;
        }
        if (fs::is_directory(p)) {
            std::cout << "Scanning: " << p <<"\n";
            try {

                for (const fs::directory_entry& element : fs::recursive_directory_iterator(p, fs::directory_options::skip_permission_denied)) {
                    if (element.is_directory()) {
                        std::cout << "   [DIR] " << element.path() << "\n";
                        std::error_code ec;
                        fs::directory_iterator probe(element.path(), ec);
                        if (ec) {
                            std::cerr << "Warning: skipped: " << element.path() << " " << ec.message() << '\n';
                        }
                    }else if (element.is_regular_file()) {
                        files_num++;
                        std::uintmax_t size = element.file_size();
                        std::cout << "   [FILE] " << element.path() << " " << size << " bytes\n";
                        bytes_num += size;
                    }else {
                        std::cout << "   [OTHER] " << element.path() << "\n";
                    }
                }
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Error: cannot read directory: " << e.what() << "\n";
            }
            std::cout << "Total: " << files_num << " files, " << bytes_num << " bytes\n";
        } else {
            std::cerr << "Error: " << p << " is not a directory\n";
        }
        std::cout << "\n";
    }

    return 0;
}