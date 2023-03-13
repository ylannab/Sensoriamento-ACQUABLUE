#include <SoftwareSerial.h>


//Entradas Sensor Condutividade
String inputstring_EC = "";
String sensorstring_EC = "";
boolean input_string_complete_EC = false;
boolean sensor_string_complete_EC = false;

//Entradas Sensor Oxigênio Dissolvido
String inputstring_DO = "";
String sensorstring_DO = "";
boolean input_string_complete_DO = false;
boolean sensor_string_complete_DO = false; 
float DO; 

//Entradas Sensor pH
String inputstring_pH = "";                              
String sensorstring_pH = "";                             
boolean input_string_complete_pH = false;                
boolean sensor_string_complete_pH = false;               
float pH; 

//Entradas apc220
int pinoRX = 6;
int pinoTX = 7;



SoftwareSerial apc220(pinoRX, pinoTX);


void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600); 
  apc220.begin(9600);

  inputstring_EC.reserve(10);
  sensorstring_EC.reserve(30);

  inputstring_DO.reserve(10);
  sensorstring_DO.reserve(30);

  inputstring_pH.reserve(10); 
  sensorstring_pH.reserve(30);
}

void serialEvent() {
  inputstring_EC = Serial.readStringUntil(13);
  input_string_complete_EC = true;

  inputstring_DO = Serial.readStringUntil(13);
  input_string_complete_DO = true;   

  inputstring_pH = Serial.readStringUntil(13);           
  input_string_complete_pH = true;
}

void serialEvent1() {
  sensorstring_EC = Serial1.readStringUntil(13);
  sensor_string_complete_EC = true;
}

void serialEvent2() {  
sensorstring_DO = Serial2.readStringUntil(13);
sensor_string_complete_DO = true;     
}

void serialEvent3() {                                 
  sensorstring_pH = Serial3.readStringUntil(13);         
  sensor_string_complete_pH = true;                     
}

void loop() 
 {
  if (apc220.available()) {
    Serial.write(apc220.read());
  }
  if (Serial.available()) {
    apc220.write(Serial.read());
  }
  if (input_string_complete_EC == true) {
    Serial1.print(inputstring_EC);
    Serial1.print('\r');
    inputstring_EC = "";
    input_string_complete_EC = false;
  }
  if (sensor_string_complete_EC == true) {
    if (isdigit(sensorstring_EC[0]) == false) {
      Serial.println(sensorstring_EC);
    }
    else
    {
      print_EC_data();
    }
    sensorstring_EC = "";
    sensor_string_complete_EC = false;
  }
if (input_string_complete_DO == true) {
 Serial2.print(inputstring_DO); 
 Serial2.print('\r');
 inputstring_DO = "";  
 input_string_complete_DO = false; 
}

if (sensor_string_complete_DO == true) {
     if (isdigit(sensorstring_DO[0]) == false) { 
      Serial.println(sensorstring_DO);
      }
    else
    {
       print_DO_data();
    }
//Serial.println(sensorstring_DO);
/*                                                 // descomente esta seção para ver como converter o D.O. lendo de uma corda para um flutuador
    if (isdigit(sensorstring[0])) {                   /// se o primeiro caractere da string for um dígito
      DO = sensorstring.toFloat();                    // converte a string em um número de ponto flutuante para que possa ser avaliada pelo Arduino
      if (DO >= 6.0) {                                // se o DO for maior ou igual a 6,0
        Serial.println("high");                       // imprima "high" isso está demonstrando que o Arduino está avaliando o DO como um número e não como uma string
      }
      if (DO <= 5.99) {                               // se o DO for menor ou igual a 5,99
        Serial.println("low");                        // imprime "baixo" isso está demonstrando que o Arduino está avaliando o DO como um número e não como uma string
      }
    }
  */
}
sensorstring_DO = "";
sensor_string_complete_DO = false;

  if (input_string_complete_pH == true) {                
    Serial3.print(inputstring_pH);                       
    Serial3.print('\r');                              
    inputstring_pH = "";                                 
    input_string_complete_pH = false;                    
  }
  
if (sensor_string_complete_pH == true) {               //if a string from the Atlas Scientific product has been received in its entirety
   
if (isdigit(sensorstring_pH[0]) == false) { 
     Serial.println(sensorstring_pH);;
    }
    else
    {
      print_pH();
    }                        //send that string to the PC's serial monitor
   /*                                                 //uncomment this section to see how to convert the pH reading from a string to a float 
    if (isdigit(sensorstring[0])) {                   //if the first character in the string is a digit
      pH = sensorstring.toFloat();                    //convert the string to a floating point number so it can be evaluated by the Arduino
      if (pH >= 7.0) {                                //if the pH is greater than or equal to 7.0
        Serial.println("high");                       //print "high" this is demonstrating that the Arduino is evaluating the pH as a number and not as a string
      }
      if (pH <= 6.99) {                               //if the pH is less than or equal to 6.99
        Serial.println("low");                        //print "low" this is demonstrating that the Arduino is evaluating the pH as a number and not as a string
      }
    }
  */
  }
  sensorstring_pH = "";                                  //clear the string:
  sensor_string_complete_pH = false;   
    
}
void print_EC_data(void) {
  char sensorstring_EC_array[30];
  char *EC;
  //char *TDS;
  //char *SAL;
  //char *GRAV;
  //float f_ec;

  sensorstring_EC.toCharArray(sensorstring_EC_array, 30);
  EC = strtok(sensorstring_EC_array, ",");
  //TDS = strtok(NULL, ",");
  //SAL = strtok(NULL, ",");
  //GRAV = strtok(NULL, ",");

  apc220.print("#");
  apc220.print("a");
  apc220.print("#");
  apc220.print(EC);
  apc220.println("#");


  Serial.print("#");
  Serial.print("a");
  Serial.print("#");
  Serial.print(EC);
  Serial.println("#");

   
  //Serial.print("TDS:");
  //Serial.println(TDS);

  //Serial.print("SAL:");
  //Serial.println(SAL);

  //Serial.print("GRAV:");
  //Serial.println(GRAV);
  
  //f_ec= atof(EC);
}

void print_DO_data(void){
  char sensorstring_DO_array[30];
  char *DO;

  sensorstring_DO.toCharArray(sensorstring_DO_array, 30);
   DO = strtok(sensorstring_DO_array, ",");

  apc220.print("#");
  apc220.print("b");
  apc220.print("#");
  apc220.print(DO);
  apc220.println("#");


  Serial.print("#");
  Serial.print("b");
  Serial.print("#");
  Serial.print(DO);
  Serial.println("#");
}

void print_pH(void){
  char sensorstring_pH_array[30];
  char *pH;

  sensorstring_pH.toCharArray(sensorstring_pH_array, 30);
   pH = strtok(sensorstring_pH_array, ",");

  apc220.print("#");
  apc220.print("c");
  apc220.print("#");
  apc220.print(pH);
  apc220.println("#");


  Serial.print("#");
  Serial.print("c");
  Serial.print("#");
  Serial.print(pH);
  Serial.println("#");
} 