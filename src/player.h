#pragma once

#include <fstream>
#include <string>

#include "exception.h"
#include "info.pb.h"

class Player {
 public:
  Player(const std::string& id, bool newRegister);
  ~Player();

  inline void setName(const std::string& name) { player_.set_name(name); }

  inline const std::string& getName() { return player_.name(); }

  inline void addMoney(int n) { player_.set_money(getMoney() + n); }

  inline int getMoney() { return player_.money(); }

  inline void addItem(int itemId, int cnt) {
    if (player_.mutable_items()->count(itemId) == 0) {  // 不存在道具
      player_.mutable_items()->insert({itemId, cnt});
    } else {  // 存在道具
      player_.mutable_items()->at(itemId) += cnt;
    }
  }

  inline void subItem(int itemId, int cnt) {
    if (player_.mutable_items()->count(itemId) == 0) {  // 不存在道具
      return;
    }
    // 存在道具
    int& has = player_.mutable_items()->at(itemId);
    if (has >= cnt) {
      has -= cnt;
    } else {
      throw RuntimeException("Error: the item count is less than cnt.");
    }
  }

  inline int getItem(int itemId) {
    if (player_.mutable_items()->count(itemId) == 0) {  // 不存在道具
      throw RuntimeException("The item " + std::to_string(itemId) + " does not exist.");
    }
    return player_.mutable_items()->at(itemId);
  }

 private:
  dummyPlayer::Player player_;
};