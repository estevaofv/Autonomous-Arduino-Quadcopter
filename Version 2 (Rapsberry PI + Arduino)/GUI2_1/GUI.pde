void drawGUI(){
  fill(0,0,0,100);
  rect(width - 290, height - 460, 290, 230);
  fill(255);
  
  overlayText();
  
  odomGraph.updateValues(1, 1);
  
  cp5.draw();
}
