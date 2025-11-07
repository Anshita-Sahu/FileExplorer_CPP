#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

using namespace std;

void listFiles(const fs::path& path) {
    cout << "\nFiles in directory: " << path << "\n";
    for (const auto& entry : fs::directory_iterator(path)) {
        cout << (entry.is_directory() ? "[DIR] " : "      ");
        cout << entry.path().filename().string() << "\n";
    }
}

void createFile(const string& filename) {
    ofstream file(filename);
    if (file) {
        cout << "File created successfully: " << filename << "\n";
    } else {
        cout << "Error creating file!\n";
    }
}

void deleteFile(const string& filename) {
    if (fs::remove(filename))
        cout << "File deleted: " << filename << "\n";
    else
        cout << "Error deleting file!\n";
}

void renameFile(const string& oldName, const string& newName) {
    try {
        fs::rename(oldName, newName);
        cout << "File renamed successfully.\n";
    } catch (fs::filesystem_error& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

int main() {
    fs::path currentPath = fs::current_path();
    int choice;
    string name, newname;

    while (true) {
        cout << "\n========= Simple File Explorer (C++) =========\n";
        cout << "Current Directory: " << currentPath << "\n";
        cout << "1. List files\n";
        cout << "2. Create file\n";
        cout << "3. Delete file\n";
        cout << "4. Rename file\n";
        cout << "5. Change directory\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                listFiles(currentPath);
                break;
            case 2:
                cout << "Enter file name: ";
                cin >> name;
                createFile((currentPath / name).string());
                break;
            case 3:
                cout << "Enter file name to delete: ";
                cin >> name;
                deleteFile((currentPath / name).string());
                break;
            case 4:
                cout << "Enter current file name: ";
                cin >> name;
                cout << "Enter new file name: ";
                cin >> newname;
                renameFile((currentPath / name).string(), (currentPath / newname).string());
                break;
            case 5:
                cout << "Enter new directory path: ";
                cin >> name;
                if (fs::exists(name) && fs::is_directory(name)) {
                    currentPath = fs::path(name);
                    fs::current_path(currentPath);
                    cout << "Changed directory to: " << currentPath << "\n";
                } else {
                    cout << "Invalid directory!\n";
                }
                break;
            case 6:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
}