const int led = 13;
String networkName;
String pswd;
String cmnd;
bool passthru;

void setup() {
 Serial.begin(9600);
 Serial1.begin(9600);
 pinMode(led, OUTPUT);
 digitalWrite(led, LOW);
 passthru = false;


 
}

void loop() {
  frWifi();//from wifi
  if (passthru = true){     
  toWifi();//to wifi
  }
  else{
    if (Serial.available())
      Serial1.write(Serial.read());
  }
}

void frWifi(){
 if (Serial1.available()){ //ifReadFromESP...
 /* if (Serial1.find("+IPD,")){ //if it detects an external connection
    digitalWrite(led, !digitalRead(led));//just toggle the led at this point idc
  }
 else*/
  Serial.write(Serial1.read()); //...writeToPcFromESP
 }
}

void toWifi(){
 if (Serial.available()>0){ //if there is input from the pc
  char command = Serial.read();
/**/
  switch (command){
    case '0':
      Serial1.println("AT");
     break;
    case '1':
      digitalWrite(led, !digitalRead(led));
     break;
    case '2':
      Serial1.println("AT+CIFSR"); //show IP address
      if (Serial1.available()>0){
        Serial.write(Serial1.read());
      }
     break;
    case '3':
      Serial.println("AT+CWMODE=3");
     break;
    case '4':
      Serial1.println("AT+CIPMUX=1"); //enable multiple connections
     break;
    case '5':
      Serial1.println("AT+CIPSERVER=1,80"); //start tcp server
     break;
    case '6':
      Serial1.println("AT+CIPSERVER=1,1336"); //start tcp server
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

    default:
      
     break;
    }        
  }
} 










  
