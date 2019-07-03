const int led = 11;
String networkName;
String pswd;

void setup() {
 Serial.begin(9600);
 Serial1.begin(9600);
 pinMode(led, OUTPUT);
 digitalWrite(led, LOW);


 
}

void loop() {
  frWifi();//from wifi
  toWifi();//to wifi
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
 if (Serial.available()>0){ //ifReadFromPC
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
      Serial1.println("AT+CIFSR=1"); //show IP address
     break;
    case '3':
      //Serial.println("AT+CWMODE=3");
     break;
    case '4':
      Serial1.println("AT+CIPMUX=1"); //enable multiple connections
     break;
    case '5':
      Serial1.println("AT+CIPSERVER=1,80"); //start tcp server
     break;
     
    case 'c':
    case 'C':
      Serial.println("turn off line ending and enter SSID:");
       while (Serial.available()==0){delay(5000);}//While serial buffer is empty, do nothing
       networkName = Serial.readString();
      Serial.println("enter password:");
       while (Serial.available()==0){delay(5000);}
       pswd =  Serial.readString();
      Serial.println("power on esp...");
      while (Serial.available()==0){delay(1000);}
      String cmnd = "AT+CWJAP=\"";
      cmnd += networkName;
      cmnd += "\",\"";
      cmnd += pswd;
      cmnd += "\"";
      Serial.println(cmnd); //changing this to Serial1 will send the generated command to the esp
            
     break;
    }
  
        
  }
} 










  
