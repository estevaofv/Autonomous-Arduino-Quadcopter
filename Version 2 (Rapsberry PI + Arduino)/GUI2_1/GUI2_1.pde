import ddf.minim.spi.*;
import ddf.minim.signals.*;
import ddf.minim.*;
import ddf.minim.analysis.*;
import ddf.minim.ugens.*;
import ddf.minim.effects.*;

import controlP5.*;

import org.gamecontrolplus.gui.*;
import org.gamecontrolplus.*;
import net.java.games.input.*;

import processing.net.*;

//SERVER VARIABLES----------------------------------------------
Server gs_server;
int port = 10002;
Client currentClient;
boolean packetReceived = false;
int comCounter = 0;
//GUI VARIABLES----------------------------------------------------
//gamepad

ControlIO control;
ControlDevice gpad;

//controlp5

ControlP5 cp5;
Textarea myTextarea;
Println console;
DropdownList d1;
//-------------------------------------------------------------------
//GUI Varialbles
int arm = 0;
boolean connected = false;

float tp,ti,td;
float p, i, d;

short pitch_lock, roll_lock, yaw_lock;
float pitch,roll,yaw;
float relalt;
float odomx, odomy;

void setup() {
  size(displayWidth - 50, displayHeight - 50); //start window
  //frame.setResizable(true);

  gs_server = new Server(this, port); // Initialize server object

  controlP5Init(); // initialize cp5

  //control = ControlIO.getInstance(this); 
  //gpad = control.getMatchedDevice("fs_config"); //initialize game pad

  frameRate(30);
}


void draw() {
  background(75);
  
  drawGUI();
  
  serverPoll();
}

