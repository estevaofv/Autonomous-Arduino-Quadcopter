import ddf.minim.spi.*;
import ddf.minim.signals.*;
import ddf.minim.*;
import ddf.minim.analysis.*;
import ddf.minim.ugens.*;
import ddf.minim.effects.*;

import controlP5.*;

import processing.net.*;

//SERVER VARIABLES----------------------------------------------
Server gs_server;
int port = 10002;
Client currentClient;
boolean packetReceived = false;
int comCounter = 0;
//GUI VARIABLES----------------------------------------------------
//graphs
posGraph odomGraph = new posGraph(10, 500, 200, 200);
//gamepad

//controlp5

ControlP5 cp5;
Textarea myTextarea;
Println console;
DropdownList d1;
//-------------------------------------------------------------------
//GUI Varialbles
int arm = 0;
boolean connected = false;

float tp, ti, td;
float p, i, d;
byte mode, pid_mode;
boolean pid_sync = false;
byte[] FB = new byte[4];

int pitch_lock, roll_lock, yaw_lock;
int throttle;
float pitch, roll, yaw;
float relalt;
float odomx, odomy;


void setup() {
  size(displayWidth - 50, displayHeight - 50); //start window
  //frame.setResizable(true);

  gs_server = new Server(this, port); // Initialize server object

    controlP5Init(); // initialize cp5

  posGraph odomGraph = new posGraph(10, height - 210, 200, 200);
  
  pitch_lock = 4;
  roll_lock = 9;
  yaw_lock = 8;

  p = 12.9;
  i = 13.6;
  d = 8.7;

  mode = 4;
  pid_mode = 2;

  throttle = 9000;

  frameRate(30);
}


void draw() {
  background(75);

  drawGUI();

  serverPoll();
}

