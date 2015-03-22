byte[] writePacket(){
  byte[] dataOut = new byte[100]; // initialize array
  //convert and load data
  dataOut[0] = 'D';
  dataOut[1] = '\n';
  //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  //send data
  return dataOut;
}
