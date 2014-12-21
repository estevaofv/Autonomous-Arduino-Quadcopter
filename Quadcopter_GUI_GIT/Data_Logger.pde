void logData(float data1, float data2, float data3, float data4){
 if(logMode != 0){
  if(logMode == 1){
    dataLog.println(data1 + ", " + data2 + ", " + data3 + ", "  + data4 + ", " + hour() + ":" + minute() + ":" + second());
  }
 } 
}
