#pragma
#include <unordered_map>
#include <string>

std::unordered_map<std::string, std::string> loadUsers(const std::string& filename);
void saveUsers(const std::unordered_map<std::string, std::string>& users, const std::string& filename);
void saveUsername(const std::string& username, const std::string& filename);



