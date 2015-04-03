class posGraph {
  //vars
  int x, y, dimX, dimY;
  int odomX, odomY;
  //functions
  posGraph (int _x, int _y, int _dimX, int _dimY) {
    x = _x;
    y = _y;
    dimX = _dimX;
    dimY = _dimY;
  }

  void updateValues(float _odomX, float _odomY) {
    //setup data
    odomX = int(_odomX * 100);
    odomY = int(_odomY * 100);
    //draw graphics
    fill(0);
    strokeWeight(0);
    rect(x, y, dimX, dimY);
    stroke(255);
    
    if (abs(odomX) <= 500 && abs(odomY) <= 500) {
      strokeWeight(3);
      line(x + (dimX / 2), y, x + (dimX / 2), y + dimY);
      line(x, y + (dimY / 2), x + dimX, y+ (dimY / 2));
      fill(255, 0, 0);
      strokeWeight(0);
      ellipse(x + map(odomX, -500, 500, 0, dimX), y + map(odomY, 500, -500, 0, dimY), 10, 10);
    } 
    else {
    }
  }
}

