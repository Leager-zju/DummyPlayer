#pragma once

#include <fstream>
#include <string>

#include "info.pb.h"

class Player;
class UserInfoManager {
 public:
  UserInfoManager(const std::string& path);
  ~UserInfoManager();

  dummyPlayer::Users& getUsers();

  std::unique_ptr<Player> login(const std::string& userId);

  void show() {
    auto&& ids = getUsers().id();
    for (auto&& id : ids) {
      std::cout << id << std::endl;
    }
  }

 private:
  std::string path_;
  bool isDirty_;
};