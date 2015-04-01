#include<iostream>    //cout
#include<stdio.h> //printf
#include<string.h>    //strlen
#include<string>  //string
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<netdb.h> //hostent

#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/String.h"

#include <sstream>
 
using namespace std;
 
/**
    TCP Client class
*/
class tcp_client
{
private:
    int sock;
    std::string address;
    int port;
    struct sockaddr_in server;
     
public:
    tcp_client();
    bool conn(string, int);
    bool send_data(string data);
    string receive(int);
};
 
tcp_client::tcp_client()
{
    sock = -1;
    port = 0;
    address = "";
}
 
/**
    Connect to a host on a certain port number
*/
bool tcp_client::conn(string address , int port)
{
    //create socket if it is not already created
    if(sock == -1)
    {
        //Create socket
        sock = socket(AF_INET , SOCK_STREAM , 0);
        if (sock == -1)
        {
            perror("Could not create socket");
        }
         
        cout<<"Socket created\n";
    }
    else    {   /* OK , nothing */  }
     
    //setup address structure
    if(inet_addr(address.c_str()) == -1)
    {
        struct hostent *he;
        struct in_addr **addr_list;
         
        //resolve the hostname, its not an ip address
        if ( (he = gethostbyname( address.c_str() ) ) == NULL)
        {
            //gethostbyname failed
            herror("gethostbyname");
            cout<<"Failed to resolve hostname\n";
             
            return false;
        }
         
        //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
        addr_list = (struct in_addr **) he->h_addr_list;
 
        for(int i = 0; addr_list[i] != NULL; i++)
        {
            //strcpy(ip , inet_ntoa(*addr_list[i]) );
            server.sin_addr = *addr_list[i];
             
            cout<<address<<" resolved to "<<inet_ntoa(*addr_list[i])<<endl;
             
            break;
        }
    }
     
    //plain ip address
    else
    {
        server.sin_addr.s_addr = inet_addr( address.c_str() );
    }
     
    server.sin_family = AF_INET;
    server.sin_port = htons( port );
     
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }
     
    cout<<"Connected\n";
    return true;
}
 
/**
    Send data to the connected host
*/
bool tcp_client::send_data(string data)
{
    //Send some data
    if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
    {
        perror("Send failed : ");
        return false;
    }
    
    //cout<<"Data send\n";
     
    return true;
}
 
/**
    Receive data from the connected host
*/
string tcp_client::receive(int size=512)
{
    char buffer[size];
    string reply;
     
    //Receive a reply from the server
    if( recv(sock , buffer , sizeof(buffer) , 0) < 0)
    {
        puts("recv failed");
    }
     
    reply = buffer;
    return reply;
}

//--------------initialize variables-------------------------
bool connectionVerified = false;
const int numSerialFloats = 6;
float serialFloats[numSerialFloats];
unsigned char serialRawChars[numSerialFloats * 4];
//-----------------------------------------------------------

void serialInCallback(const std_msgs::Float32MultiArray::ConstPtr& array){
	int i = 0;
	for(std::vector<float>::const_iterator it = array->data.begin(); it != array->data.end(); ++it){
		serialFloats[i] = *it;
		i++;
	}
	//used for converting from floats to chars
	char* convPointer;
	convPointer = (char*) & serialFloats[0];
	serialRawChars[0] = convPointer[0];
	serialRawChars[1] = convPointer[1];
	serialRawChars[2] = convPointer[2];
	serialRawChars[3] = convPointer[3];
}

string sendPacket(char mode){
	//intitialize variables
	string dataString; // initialize the string	
	// main logic
	if(mode == 'a'){ // base variable mode
		// initialization variables
		unsigned char data[100]; // size of transmit buffer
		//---------------------------
		//Fill the buffer with gibberish first
		for(int i = 0; i < 100; i++){
			data[i] = 'x';
		}
		//---------------------------
		for (int i = 0; i < (numSerialFloats * 4); i++){
			data[i] = serialRawChars[i];
		}
		//--------------------------------
		for(int i = 0; i < 100; i++){ //convert my char array to a string
	
			dataString += data[i];
	
		}
	}
	//-----------send out data
	
	return(dataString);
}
 
int main(int argc , char *argv[])
{
    tcp_client c;
    string host;
    
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	ros::init(argc, argv, "wifi_client"); // initializes ros
  	
  	ros::NodeHandle n; // neccesary for ros
  	
  	//ros::Publisher wifi_pub = n.advertise<std_msgs::String>("wifi_cmd", 1000); //creates a publisher for the recieved information (currently of type string)
  	ros::Subscriber serial_sub = n.subscribe("serial_in", 1000, serialInCallback);
  	
  	ros::Rate loop_rate(10); // used to keep polling at constant rate
  	//-=-=-=-=-=-=-=-=-=-=-=-=-
  	
  	//temporary, finds host ip
    cout<<"Enter hostname : ";
    cin>>host;
     
    //connect to host
    c.conn(host , 10002);

	//-=-=-=-=--=-=-=-=-=-=-=-=-	
		
	while(ros::ok()){ //checks health of ros node
		//initialize variables
    	
    	
    	string recvVal;
  
    	//send some data
    	c.send_data(sendPacket('a'));
     	//received 100 bytes
    	recvVal = c.receive(100);
    	
		
		ros::spinOnce(); 
		loop_rate.sleep(); // maintains constant loop speed while freeing up cpu time
	}

    //done
    return 0;
}
