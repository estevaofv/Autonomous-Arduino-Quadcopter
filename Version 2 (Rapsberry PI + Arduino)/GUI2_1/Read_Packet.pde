void readPacket() {
  int byteCount = currentClient.available();
  switch(byteCount) {
  case 100:
    byte[] dataIn = new byte[100];
    dataIn = currentClient.readBytes(); // load bytes
    
    println(byteCount + "gotcha" + get4ByteFloat(dataIn, 0) + get4ByteFloat(dataIn, 4));
    
    currentClient.clear(); // clear receive buffer
    packetReceived = true; // ready to send data
    break;
  default:
    packetReceived = false;
    println(byteCount);
    break;
  }
}

