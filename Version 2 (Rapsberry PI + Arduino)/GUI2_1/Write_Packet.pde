void writePacket() {
  String dataOut = ""; // initialize array
  //convert and load data
  roll_lock++;
  dataOut += str(pitch_lock);
  dataOut += ',';
  dataOut += str(roll_lock);
  dataOut += ',';
  dataOut += str(yaw_lock);
  dataOut += ',';
  dataOut += str(throttle);
  dataOut += ',';
  dataOut += str(p);
  dataOut += ',';
  dataOut += str(i);
  dataOut += ',';
  dataOut += str(d);
  dataOut += ',';
  dataOut += str(mode);
  dataOut += ',';
  dataOut += str(pid_mode);
  dataOut += ',';
  dataOut += str(pid_sync);
  dataOut += ",end";
  //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  //send data
  //println(dataOut);
  currentClient.write(dataOut);  
}

