#include "player.h"

Player::Player(const std::string& id, bool newRegister) {
  if (newRegister) {
    player_.set_id(id);
  } else {
    std::ifstream fread(id, std::ios::in);
    player_.ParseFromIstream(&fread);
    fread.close();
  }
}

Player::~Player() {
  std::ofstream fwrite("./" + player_.id(), std::ios::trunc);
  fwrite << player_.SerializeAsString();
  fwrite.close();
}