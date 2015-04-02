byte[] writePacket() {
  byte[] dataOut = new byte[23]; // initialize array
  //convert and load data
  dataOut[0] = (byte)(pitch_lock & 0xFF);
  dataOut[1] = (byte)((pitch_lock << 8) & 0xFF);

  dataOut[2] = (byte)(roll_lock & 0xFF);
  dataOut[3] = (byte)((roll_lock << 8) & 0xFF);

  dataOut[4] = (byte)(yaw_lock & 0xFF);
  dataOut[5] = (byte)((yaw_lock << 8) & 0xFF);

  dataOut[6] = (byte)(throttle & 0xFF);
  dataOut[7] = (byte)((throttle << 8) & 0xFF);

  float2bytes(p);
  dataOut[8] = FB[0];
  dataOut[9] = FB[1];
  dataOut[10] = FB[2];
  dataOut[11] = FB[3];
  
  float2bytes(i);
  dataOut[12] = FB[0];
  dataOut[13] = FB[1];
  dataOut[14] = FB[2];
  dataOut[15] = FB[3];
  
  float2bytes(d);
  dataOut[16] = FB[0];
  dataOut[17] = FB[1];
  dataOut[18] = FB[2];
  dataOut[19] = FB[3];
  
  dataOut[20] = mode;
  dataOut[21] = pid_mode;
  dataOut[22] = pid_sync;
  //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  //send data
  return dataOut;
}

