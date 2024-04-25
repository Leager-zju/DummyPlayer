#include "controller.h"

#include <vector>

#include "exception.h"

Controller::Controller()
    : userInfoManager_(new UserInfoManager("userInfo")),
      currentPlayer_(nullptr) {}

void Controller::run() {
  std::string command;
  for (;;) {
    std::cout << (currentPlayer_ ? "[" + currentPlayer_->getName() + "] > "
                                 : "(Not logged in) > ");
    try {
      if (execute()) {
        return;
      }
    } catch (std::exception& e) {
      std::cerr << e.what() << std::endl;
    }
  }
};

/**
 * true for exit
 */
bool Controller::execute() {
  auto&& tokens = getTokens();
  bool exit = false;
  if (!tokens.empty()) {
    if (tokens[0] == "show") {
      showUsers(tokens);
    } else if (tokens[0] == "login") {
      login(tokens);
    } else if (tokens[0] == "set-name") {
      setName(tokens);
    } else if (tokens[0] == "get-name") {
      getName(tokens);
    } else if (tokens[0] == "add-money") {
      addMoney(tokens);
    } else if (tokens[0] == "get-money") {
      getMoney(tokens);
    } else if (tokens[0] == "add-item") {
      addItem(tokens);
    } else if (tokens[0] == "sub-item") {
      subItem(tokens);
    } else if (tokens[0] == "get-item") {
      getItem(tokens);
    } else if (tokens[0] == "logout") {
      logout(tokens);
    } else if (tokens[0] == "quit") {
      quit(tokens, exit);
    } else {
      throw RuntimeException("Undefined command.");
    }
  }

  return exit;
}

std::vector<std::string> Controller::getTokens() {
  std::vector<std::string> tokens;
  std::string token;
  char ch;
  while ((ch = getchar()) != '\n') {
    if (ch == ' ') {
      if (!token.empty()) {
        tokens.emplace_back(token);
        token.clear();
      }
      continue;
    }
    token.push_back(ch);
  }
  tokens.emplace_back(token);
  return tokens;
}

bool Controller::isNumber(const std::string& token) {
  for (char ch : token) {
    if (!isdigit(ch)) {
      return false;
    }
  }
  return true;
}

void Controller::showUsers(const std::vector<std::string>& tokens) {
  if (tokens.size() != 1) {
    throw RuntimeException("Usage: showUsers");
  }
  userInfoManager_->show();
}

void Controller::login(const std::vector<std::string>& tokens) {
  if (tokens.size() != 2) {
    throw RuntimeException("Usage: login <userId>");
  }
  currentPlayer_ = userInfoManager_->login(tokens[1]);
}

void Controller::setName(const std::vector<std::string>& tokens) {
  if (tokens.size() != 2) {
    throw RuntimeException("Usage: set-name <name>");
  }
  currentPlayer_->setName(tokens[1]);
}

void Controller::getName(const std::vector<std::string>& tokens) {
  if (tokens.size() != 1) {
    throw RuntimeException("Usage: get-name");
  }
  std::cout << currentPlayer_->getName() << std::endl;
}

void Controller::addMoney(const std::vector<std::string>& tokens) {
  if (tokens.size() != 2) {
    throw RuntimeException("Usage: add-money <cnt>");
  }
  if (!isNumber(tokens[1])) {
    throw RuntimeException("cnt must be an integer");
  }
  currentPlayer_->addMoney(std::stoi(tokens[1]));
}

void Controller::getMoney(const std::vector<std::string>& tokens) {
  if (tokens.size() != 1) {
    throw RuntimeException("Usage: get-money");
  }
  std::cout << currentPlayer_->getMoney() << std::endl;
}

void Controller::addItem(const std::vector<std::string>& tokens) {
  if (tokens.size() != 3) {
    throw RuntimeException("Usage: add-item <item-id> <item-cnt>");
  }
  if (!isNumber(tokens[1])) {
    throw RuntimeException("item-id must be an integer");
  }
  if (!isNumber(tokens[2])) {
    throw RuntimeException("item-cnt must be an integer");
  }
  currentPlayer_->addItem(std::stoi(tokens[1]), std::stoi(tokens[2]));
}

void Controller::subItem(const std::vector<std::string>& tokens) {
  if (tokens.size() != 3) {
    throw RuntimeException("Usage: sub-item <item-id> <item-cnt>");
  }
  if (!isNumber(tokens[1])) {
    throw RuntimeException("item-id must be an integer");
  }
  if (!isNumber(tokens[2])) {
    throw RuntimeException("item-cnt must be an integer");
  }
  currentPlayer_->subItem(std::stoi(tokens[1]), std::stoi(tokens[2]));
}

void Controller::getItem(const std::vector<std::string>& tokens) {
  if (tokens.size() != 2) {
    throw RuntimeException("Usage: get-item <item-id>");
  }
  if (!isNumber(tokens[1])) {
    throw RuntimeException("item-id must be an integer");
  }
  std::cout << currentPlayer_->getItem(std::stoi(tokens[1])) << std::endl;
}

void Controller::logout(const std::vector<std::string>& tokens) {
  currentPlayer_ = nullptr;
}

void Controller::quit(const std::vector<std::string>& tokens, bool& exit) {
  if (currentPlayer_ == nullptr) {
    exit = true;
  } else {
    throw RuntimeException("You must logout before quit.");
  }
}