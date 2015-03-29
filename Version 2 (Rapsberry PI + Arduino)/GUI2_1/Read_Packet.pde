void readPacket() {
  int byteCount = currentClient.available();
  
  if (currentClient != null) {

    switch(byteCount) {
    case 100:
      byte[] dataIn = new byte[100];
      dataIn = currentClient.readBytes(); // load bytes
      //-=-=-=-=-=-=-=
      pitch = get4ByteFloat(dataIn, 0);
      roll = get4ByteFloat(dataIn, 4);
      yaw = get4ByteFloat(dataIn, 8);
      
      //=-=-=-=-=-=-=-=
      currentClient.clear(); // clear receive buffer
      packetReceived = true; // ready to send data
      break;

      //-------------------------------------------------------

    default:
      packetReceived = false;
      println(byteCount);
      break;

      //--------------------------------------------------------
    }
  } 
}

