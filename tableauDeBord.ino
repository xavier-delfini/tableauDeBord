#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN A0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  //pinMode(0,OUTPUT);  
  pinMode(1,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  }
void temperature_display (){
  float temperature = dht.readTemperature();  
  temperature =12;
  lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");    
    if(temperature >= 10 && temperature <= 18) {
      digitalWrite(6,HIGH);
      digitalWrite(7,LOW);
      /*digitalWrite(8,HIGH);
      digitalWrite(9,HIGH);*/
      digitalWrite(13,LOW);
      //digitalWrite(LOW,,8,9,)
    }
    else if(temperature >= 19 && temperature <= 21){
      digitalWrite(6,LOW);
      digitalWrite(7,HIGH);
      digitalWrite(13,LOW);
    }
    else if (temperature>=22){
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      digitalWrite(13,HIGH);      
    }
    
  
}
void humidity_display(){
  int humidity = dht.readHumidity();
  //humidity=45;  
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");  
  if(humidity >= 40 && humidity <= 70) {
      digitalWrite(8,HIGH);
      digitalWrite(9,LOW);
    }
    else{
      digitalWrite(8,LOW);
      digitalWrite(9,HIGH);
    }
  
}
void brigtness_display(){
  int brigtness = analogRead(A1);//*100)/2048
  lcd.setCursor(0, 1);
  lcd.print("Luminosité: ");
  lcd.print(brigtness);
  lcd.print(" %");  
}
void test(){
  //digitalWrite(8, HIGH);
  digitalWrite(1, LOW);
  delayMicroseconds(2);
  digitalWrite(1, HIGH);
  delayMicroseconds(10);
  digitalWrite(1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(A3, HIGH);
  // Calculating the distance
  int distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor 
  lcd.setCursor(0, 1);
  lcd.print("Distance: ");
  lcd.println(distance);

  if (distance<10){
    digitalWrite(8, HIGH);
    delay(20);
    digitalWrite(8, LOW);
    delay(50);    
  }
  else if (distance>=10 &&distance <=30){
    digitalWrite(8, HIGH);
    delay(40);
    digitalWrite(8, LOW);
    delay(200);    
  }
  else if (distance>=31 &&distance <=100){
    digitalWrite(8, HIGH);
    delay(20);
    digitalWrite(8, LOW);
    delay(2000);     
  }
}
void loop() {
  //temperature_display();
  //humidity_display();
  test();
  delay(1);
  //brigtness_display();
}