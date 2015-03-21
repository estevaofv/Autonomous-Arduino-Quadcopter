public void controlEvent(ControlEvent Event) {
  String ENAME = Event.name();

  if (ENAME == "arm") {
    arm = round(Event.value());
    if (arm == 1) {
      println("System Armed");
    } else {
      println("System DISArmed");
    }
  }
  
  else if(ENAME == "proportional"){
    float tfloat = float(Event.getStringValue());
    tp = tfloat;
  }
  
  else if(ENAME == "integral"){
    float tfloat = float(Event.getStringValue());
    ti = tfloat;
  }
  
  else if(ENAME == "derivative"){
    float tfloat = float(Event.getStringValue());
    td = tfloat;
  }
  
  else if(ENAME == "pid_apply"){
    
  }
  
  else if(ENAME == "pitch_lock"){
    
  }
  
  else if(ENAME == "roll_lock"){
    
  }
  
  else if(ENAME == "yaw_lock"){
    
  }
  
  else {
    println("UNKNOWN: " + Event);
  }
}

