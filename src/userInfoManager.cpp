#include "userInfoManager.h"

#include "player.h"

UserInfoManager::UserInfoManager(const std::string& path)
    : path_(path), isDirty_(false) {
  std::ifstream fread(path_, std::ios::in);
  getUsers().ParseFromIstream(&fread);
  fread.close();
}

UserInfoManager::~UserInfoManager() {
  if (isDirty_) {
    std::ofstream fwrite(path_, std::ios::trunc);
    fwrite << getUsers().SerializeAsString();
    fwrite.close();
  }
}

dummyPlayer::Users& UserInfoManager::getUsers() {
  static dummyPlayer::Users users;
  return users;
}

std::unique_ptr<Player> UserInfoManager::login(const std::string& userId) {
  bool exist = false;
  auto&& ids = getUsers().id();
  for (auto&& id : ids) {
    if (id == userId) {
      exist = true;
      break;
    }
  }

  if (!exist) {
    getUsers().add_id(userId);
    isDirty_ = true;
  }

  return std::make_unique<Player>(userId, !exist);
}