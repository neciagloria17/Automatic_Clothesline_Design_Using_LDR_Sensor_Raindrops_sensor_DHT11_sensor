//Inisialisasi DHT11
#include <DHT.h>
#define DHTPIN 13          // pin data DHT11 dihubungkan ke pin digital 13
#define DHTTYPE DHT11     // tipe sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

//Motor Stepper
int in1=8, in2=9, in3=10, in4=11;
int delaytime=3;
int lamaputaran=2000;

//Sensor Hujan
int sensorValueHujan = 3;
int cuaca = 0 ;

//Sensor LDR
int sensorPin = A5;
int sensorValueLDR = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  dht.begin();
  pinMode (sensorValueHujan, INPUT); 

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  float t = dht.readTemperature(); //Suhu
  Serial.println("Suhu");
  Serial.println(t);

  cuaca = digitalRead(sensorValueHujan);   //Baca sensor
  Serial.println("Cuaca");
  Serial.println(cuaca);

  sensorValueLDR=analogRead(sensorPin); //Membaca nilai analog dari pin A5
  float voltage = sensorValueLDR * (5.0/1023.0);
  Serial.println("Keterangan");
  Serial.println(voltage);

  // LDR
float total = (t - voltage );
Serial.println(total);

  if(cuaca == 0){
    Serial.println("Jemuran Masuk");
    for (int j=0; j<lamaputaran; j++ ){
        maju(); 
        }
  }
  else if ( total > 24.5 && total <= 25 ){
  
  }
  else if(total > 25 ){
     Serial.println("Jemuran Keluar");
        for (int j=0; j<lamaputaran; j++ ){
        mundur();
        }
  }else if(total <= 24.5 ){
        Serial.println("Jemuran Masuk");
         for (int i=0; i<lamaputaran; i++){
         maju(); 
     } 
  }
  
   delay(1000);
}

void mundur(){
  step1(); delay(delaytime);
  step2(); delay(delaytime);
  step3(); delay(delaytime);
  step4(); delay(delaytime);
}

void maju(){
  step4(); delay(2);
  step3(); delay(2);
  step2(); delay(2);
  step1(); delay(2);
}

void step1(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
}
void step2(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void step3(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
void step4(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
