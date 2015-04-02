#include <stdio.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
#include <iostream>
#include <sys/ioctl.h>
// ROS STUFF
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32MultiArray.h>
#include "std_msgs/ByteMultiArray.h"
#include <sstream>
#include <string>
#include <string.h>

float char2Float(unsigned char data[], int offset);

//ROS variables
float serialInFloats[6];
//=-=-=-=-=-=-=
int uart0_filestream = -1;
bool bytesReceived = true;
const int wifiInCharNum = 25;
char wifiInChar[wifiInCharNum];

void wifiInCallback(const std_msgs::ByteMultiArray::ConstPtr& array){
	int i = 0;
	for(std::vector<signed char>::const_iterator it = array->data.begin(); it != array->data.end(); ++it){
		wifiInChar[i] = (char)*it;
		i++;
	}
}

void transferSerialData(){
	//----- CHECK FOR ANY RX BYTES -----
	if (uart0_filestream != -1)
	{
		// Read up to 255 characters from the port if they are there
		unsigned char rx_buffer[256];
		int rx_length = read(uart0_filestream, (void*)rx_buffer, 255);		//Filestream, buffer to store in, number of bytes to read (max)
		if (rx_length < 0)
		{
			//An error occured (will occur if there are no bytes)
		}
		else if (rx_length == 0)
		{
			//No data waiting
		}
		else //process data
		{
			//Bytes received
			rx_buffer[rx_length] = '\0';
			
			serialInFloats[0] = char2Float(rx_buffer, 0);
			serialInFloats[1] = char2Float(rx_buffer, 4);
			serialInFloats[2] = char2Float(rx_buffer, 8);
			serialInFloats[3] = char2Float(rx_buffer, 12);
			serialInFloats[4] = char2Float(rx_buffer, 16);
			serialInFloats[5] = char2Float(rx_buffer, 20);
			
			if(rx_length >= 4){ // check to see if the data is there
				bytesReceived = true;
			}
		}
	}
    //----- TX BYTES -----
    if(bytesReceived == true){
		unsigned char tx_buffer[25]; // the 53 bytes to send to the teensy
		unsigned char *p_tx_buffer;
	
		p_tx_buffer = &tx_buffer[0];
		//load data into the buffer for transmission
		for(int i = 0; i < wifiInCharNum; i++){
			if(wifiInChar[i] != NULL){
				*p_tx_buffer++ = wifiInChar[i];
			}
			else{
				*p_tx_buffer++ = 'p';
			}
		}
		//transmit
		if (uart0_filestream != -1)
		{
			int count = write(uart0_filestream, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0]));		//Filestream, bytes to write, number of bytes to write
			if (count < 0)
			{
				ROS_INFO("UART TX error\n");
			}
			count = write(uart0_filestream, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0]));		//Filestream, bytes to write, number of bytes to write
			if (count < 0)
			{
				ROS_INFO("UART TX error\n");
			}
			
			bytesReceived = false;
		}
		}
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
}


float char2Float(unsigned char data[], int offset){
	union {
		unsigned char c[4];
		float f;
	} u;
	u.c[0] = data[offset];
	u.c[1] = data[offset + 1];
	u.c[2] = data[offset + 2];
	u.c[3] = data[offset + 3];
	
	return u.f;
}

int main(int argc, char **argv){
	// INITIALIZE ROS
	ros::init(argc, argv, "serial_node");
	ros::NodeHandle n;
	ros::Rate loop_rate(10);
	
	ros::Publisher serial_pub = n.advertise<std_msgs::Float32MultiArray>("serial_in", 1000);
	ros::Subscriber wifi_sub = n.subscribe("wifi_cmd", 1000, wifiInCallback);
	
	// INITIALIZE THE UART SERIAL PORT
	uart0_filestream = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);		
	
	if (uart0_filestream == -1)
	{
		//ERROR - CAN'T OPEN SERIAL PORT
		ROS_INFO("Error - Unable to open UART.  Ensure it is not in use by another application\n");
	}
	
	struct termios options;
	tcgetattr(uart0_filestream, &options);
	options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(uart0_filestream, TCIFLUSH);
	tcsetattr(uart0_filestream, TCSANOW, &options);
	
	// main loop
	
	while(ros::ok()){
		
		transferSerialData();
		//Publishes data to the topic
		std_msgs::Float32MultiArray serialOutArray;
		serialOutArray.data.clear();
		for (int i = 0; i < 6; i++){
			serialOutArray.data.push_back(serialInFloats[i]);
		}
		serial_pub.publish(serialOutArray);
		
		ros::spinOnce(); // process callbacks
		
		loop_rate.sleep();	// keep 10 hertz loop rate
					
		//close(uart0_filestream);		
	}
}
