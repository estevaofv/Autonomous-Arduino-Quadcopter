void serverPoll() {
  currentClient = gs_server.available(); // get the next client
  
  if(currentClient != null){
    // read packet and convert data to variables;
    readPacket();
    // write pertinent data to the current client
    if(packetReceived == true){
    currentClient.write("I hear you bro!\n");
    packetReceived = false;
    }
  }
}

void disconnectEvent(Client theClient){
  connected = false;
  println(theClient.ip() + " disconnected");
}



