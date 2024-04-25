#pragma once

#include <exception>
#include <string>

class RuntimeException : public std::exception {
 public:
  RuntimeException(const std::string& errMsg) : errMsg_(errMsg) {}
  const char* what() const noexcept override { return errMsg_.c_str(); }

 private:
  std::string errMsg_;
};