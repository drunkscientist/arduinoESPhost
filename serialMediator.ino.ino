const int led = 13;
String networkName;
String pswd;
String cmnd;
bool passthru = false;
bool networkListen = false;
const int baud[]={300,1200,2400,4800,9600,19200,38400,57600,74880,115200,230400,250000,500000,1000000,2000000};



void setup() {
 Serial.begin(9600);
 Serial1.begin(9600);
 pinMode(led, OUTPUT);
 digitalWrite(led, LOW);
 passthru = false;
 networkListen = false;


 
}

void loop() {
  if (passthru == true){      
    if (Serial.available()) //ifRead from pc...
      Serial1.write(Serial.read());//...write to esp
    if (Serial1.available()) //ifReadFromESP...
      Serial.write(Serial1.read()); //...writeToPcFromESP
    }
   else{
    toWifi();//to wifi
    if (networkListen == true)
      frWifi();//from wifi
     else{
       if (Serial1.available()) //ifReadFromESP...
      Serial.write(Serial1.read()); //...writeToPcFromESP
      }
      
 }
}

void espReturn(){
   delay(100);
      if (Serial1.available()>0){
        delay(10);
        Serial.write(Serial1.read());
      }
}

void frWifi(){
 if (Serial1.available()){ //ifReadFromESP...
   char inbound;
   inbound = Serial1.read();
   if (inbound == '+'){ 
    digitalWrite(led, !digitalRead(led));//just toggle the led at this point idc
  }
   else{
    String returned = "";
    while (Serial1.available()>0){      
     char d = Serial1.read();
     returned += d;          
    }
    Serial.print(returned);
   }
 }
}

void toWifi(){
 if (Serial.available()>0){ //if input from the pc
  char command = Serial.read();

  switch (command){
    case '0':
      Serial1.println("AT");
     break;
    case '1':
      digitalWrite(led, !digitalRead(led));
     break;
    case '2':
      Serial1.println("AT+CIFSR"); //show IP address
      espReturn();
     break;
    case '3':
      Serial1.println("AT+CWMODE=3");
     break;
    case '4':
      Serial1.println("AT+CIPMUX=1"); //enable multiple connections
     break;
    case '5':
      Serial1.println("AT+CIPSERVER=1,80"); //start tcp server
      networkListen = true;
     break;
    case '6':
      Serial1.println("AT+CIPSERVER=1,1336"); //start tcp server
     break;
    case '7':

     break;
    case '8':
      networkListen = false;
     break;
    case '9':
      passthru = true;
      Serial.println("entering passthrough mode, turn on line ending+carrige return. the only way back is to reset");
      
     break;


     
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/     
    
    
    case 'c':
    case 'C':
    Serial.println("turn off line ending");
    delay(7000);
    if (Serial.available()>0){
      char z = Serial.read();
      delay(10);
    }
      Serial.println("enter SSID:");
       while (Serial.available()==0){delay(5000);}//While serial buffer is empty, do nothing
       networkName = Serial.readString();
      Serial.println("enter password:");
       while (Serial.available()==0){delay(5000);}
       pswd =  Serial.readString();
      Serial.println("power on esp...");
      while (Serial.available()==0){delay(1000);}
      cmnd = "AT+CWJAP_CUR=\""; //change CUR to DEF to make network permanant
      cmnd += networkName;
      cmnd += "\",\"";
      cmnd += pswd;
      cmnd += "\"";
      Serial.println(cmnd); //changing this to Serial1 will send the generated command to the esp
            
     break;

    case 'r':
    case 'R':
      Serial1.println("AT+RST");
     break;

    case 'B':
    case 'b':
    for (int i = 0; i < 14; i++){ //iterate baud rates
      Serial1.end(); //end current connection
      Serial1.begin(baud[i]); //begin new connection at iterated baud rate
      Serial1.println("AT+UART_DEF=9600"); //attempt to set new default baud rate
    }
    Serial1.end(); //end the obscene 2000000 baud connection
    Serial1.begin(9600); //restart to our default
     break;
    case 'l':
      networkListen = false;
     break;
    case 'L':
      networkListen = true;
     break;
    

/*************************************************************/

    default:
      Serial.println("that is an unrecognized command");
    case '/n':
    
     break;
    }        
  }
} 










  
