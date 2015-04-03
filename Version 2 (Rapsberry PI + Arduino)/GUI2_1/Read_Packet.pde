void readPacket() {
  byte[] type = currentClient.readBytesUntil(10);
  if (type != null) {
    switch((char)type[0]) {
    case 'a':
      String message = currentClient.readString();
      String stringVals[] = split(message, ",");
      if(message.length() > 30){
      pitch = Float.parseFloat(stringVals[0]);
      roll = Float.parseFloat(stringVals[1]);
      yaw = Float.parseFloat(stringVals[2]);
      odomx = Float.parseFloat(stringVals[3]);
      odomy = Float.parseFloat(stringVals[4]);
      relalt = Float.parseFloat(stringVals[5]);
      }
      packetReceived = true;
      //println(message);
      break;

    default:
      println("unrecognized type");
      currentClient.clear();
      packetReceived = true;
    }
  }
}

