void keyPressed() {
  if (cp5.controller("derivative").isActive() == false && cp5.controller("integral").isActive() == false 
    && cp5.controller("proportional").isActive() == false) {
    if (key == ENTER && stage == 1) {
      stage = 2;
    }
    if (key == ' ' && stage == 2 && start == true) {
      start = false;
    }
    if (key == '1' && mode != 1) {
      mode = 1;
    }
    if (key == '2' && mode != 2) {
      mode = 2;
    }
    if (key == '3' && mode != 3) {
      mode = 3;
    }
    if (key == '4' && mode != 4) {
      mode = 4;
    }
    if (key == 'c' && connected == false) {
      readPacket();
      readPacket();
      writePacket('a');
    }
    if (key == 's') {
      start = true;
    }
  }
}

