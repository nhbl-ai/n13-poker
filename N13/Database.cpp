#include "Database.h"
#include <fstream>
#include <iostream>
std::unordered_map<std::string, std::string> loadUsers(const std::string& filename) {
	std::unordered_map<std::string, std::string> users;
	std::ifstream file(filename);
	std::string username, password;
	while (file >> username >> password) {
		users[username] = password;
	}
	return users;
}

void saveUsers(const std::unordered_map<std::string, std::string>& users, const std::string& filename) {
	std::ofstream file(filename);
	for (const auto& user : users) {
		file << user.first << " " << user.second << std::endl;
	}
}

//void saveUsernames(const std::unordered_map<std::string, std::string>& users, const std::string& filename) {
//    std::ofstream file(filename);
//    for (const auto& user : users) {
//        file << user.first << std::endl;
//    }
//}

void saveUsername(const std::string& username, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << username << "\n"; // Ghi tên người dùng hiện tại
        file.close();
    }
}
