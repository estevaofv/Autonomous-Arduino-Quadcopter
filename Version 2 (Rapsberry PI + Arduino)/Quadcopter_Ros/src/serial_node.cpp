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
std::string serialInString;
std::string wifiInString = "-----";
//=-=-=-=-=-=-=
int uart0_filestream = -1;
bool bytesReceived = true;


void wifiInCallback(const std_msgs::String::ConstPtr& msg){
	wifiInString = msg->data;
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
			std::string temp;
			for(int i = 0; i < rx_length; i++){
				temp += rx_buffer[i];
			}
			
			serialInString = temp;
			
			if(rx_length >= 4){ // check to see if the data is there
				bytesReceived = true;
			}
		}
	}
    //----- TX BYTES -----
    if(bytesReceived == true){
		unsigned char tx_buffer[25]; // the bytes to send to the teensy
		unsigned char *p_tx_buffer;
	
		p_tx_buffer = &tx_buffer[0];
		//load data into the buffer for transmission
		*p_tx_buffer++ = 'a';
		*p_tx_buffer++ = '\n';
		for(int i = 0; i < wifiInString.length(); i++){
			if(wifiInString[i] != NULL){
				*p_tx_buffer++ = wifiInString[i];
			}
			else{
				*p_tx_buffer++ = 'x';
			}
		}
		*p_tx_buffer++ = 'z';
		//std::cout << wifiInString << "\n";
		//transmit
		if (uart0_filestream != -1)
		{
			int count = write(uart0_filestream, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0]));		//Filestream, bytes to write, number of bytes to write
			if (count < 0)
			{
				ROS_INFO("UART TX error\n");
			}
			
			bytesReceived = false;
		}
		}
	//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
}


int main(int argc, char **argv){
	// INITIALIZE ROS
	ros::init(argc, argv, "serial_node");
	ros::NodeHandle n;
	ros::Rate loop_rate(10);
	
	ros::Publisher serial_pub = n.advertise<std_msgs::String>("serial_in", 1000);
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
		std_msgs::String serialIn_msg;
		serialIn_msg.data = serialInString;
		serial_pub.publish(serialIn_msg);
		
		ros::spinOnce(); // process callbacks
		
		loop_rate.sleep();	// keep 10 hertz loop rate
					
		//close(uart0_filestream);		
	}
}
