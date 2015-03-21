void displayData() {
  pushMatrix();
  lights();
  strokeWeight(0);
  fill(#B4AF04);
  translate((xPos * posMult), (relAlt * -1), (yPos * posMult));
  rotateX(radians(pitch));
  rotateY(radians(yaw * -1));
  rotateZ(radians(roll));
  box(30,5,30);
  popMatrix();
  
  //display point cloud
  for(int i = 0; i < pointCount; i++){
    stroke(255,0,0);
    strokeWeight(3);
    point(Xpoint[i], Ypoint[i], Zpoint[i]);
  }
  //display position history
  stroke(#FFF700);
  strokeWeight(1);
  for(int i = 0; i < quadX.length - 1; i++){
    line(quadX[i], quadY[i], quadZ[i], quadX[i + 1], quadY[i + 1], quadZ[i + 1]);
  }
}
