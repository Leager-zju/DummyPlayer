#pragma once

#include <memory>
#include <string>
#include <vector>

#include "player.h"
#include "userInfoManager.h"
#include "log.h"
class Controller {
 public:
  Controller();
  ~Controller() = default;

  void run();

 private:
  /**
   * true for exit
   */
  bool execute();

  std::vector<std::string> getTokens();
  bool isNumber(const std::string& token);

  void showUsers(const std::vector<std::string>& tokens);
  void login(const std::vector<std::string>& tokens);
  void setName(const std::vector<std::string>& tokens);
  void getName(const std::vector<std::string>& tokens);
  void addMoney(const std::vector<std::string>& tokens);
  void getMoney(const std::vector<std::string>& tokens);
  void addItem(const std::vector<std::string>& tokens);
  void subItem(const std::vector<std::string>& tokens);
  void getItem(const std::vector<std::string>& tokens);
  void logout(const std::vector<std::string>& tokens);
  void quit(const std::vector<std::string>& tokens, bool& exit);

  template<class ...Args>
  void log(Args&& ...args) { logManager_->log(__TIME__, args...); }

  std::unique_ptr<UserInfoManager> userInfoManager_;
  std::unique_ptr<Player> currentPlayer_;
  std::unique_ptr<LogManager> logManager_;
};