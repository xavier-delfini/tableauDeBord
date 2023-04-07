#include <LiquidCrystal.h>//Importation de la librairie LiquidCrystal, utilisé pour l'affichage sur le LCD
#include <DHT.h>//Importation de la librairie DHT utile pour le capteur de température et d'humidité

#define DHTPIN A2//Capteur température
#define DHTTYPE DHT11//Déclaration du modèle type de capteur utilisé

DHT dht(DHTPIN, DHTTYPE);//Déclaration du pin utilisé par le capteur du nom de DHTTYPE(DHT11)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//Déclaration des pins utilisé pour les Data du LCD
int mode=0;
void setup() {
  lcd.begin(16, 1);//Démmarage du LCD sur une seul ligne avec une capacité d'affichage de 16 caractère * 1
  dht.begin();
  pinMode(6,OUTPUT);  //Led Bleu
  pinMode(7,OUTPUT);  //Led Rouge
  pinMode(8,OUTPUT);  //Buzzer
  pinMode(9,OUTPUT);  //Led Jaune
  pinMode(10,OUTPUT); //Trigger Ultrason  
  pinMode(13,OUTPUT); //Ventilateur
  pinMode(18,OUTPUT); //Led Verte
  pinMode(19,INPUT);  //Bouton Poussoir
  pinMode(A1,INPUT);  //Capteur Luminosité
  pinMode(A3,INPUT);  //Echo Ultrason
  }
void temperature_display (){
  float temperature = dht.readTemperature(); //Récupération de la température 
  //temperature =12;
  lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C ");    
    if(temperature >= 10 && temperature <= 18) {
      digitalWrite(6,HIGH);//Led Rouge allumée
      digitalWrite(7,LOW);
      digitalWrite(13,LOW);
    }
    else if(temperature >= 19 && temperature <= 21){
      digitalWrite(6,LOW);
      digitalWrite(7,HIGH);//Led Bleu allumée
      digitalWrite(13,LOW);
    }
    else if (temperature>=22){
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      digitalWrite(13,HIGH);//Ventilateur allumé
    }
    
  
}
void reset_states(){//Réinitialisation de tous les états des composants actif 
     digitalWrite(18,LOW);
      digitalWrite(9,LOW);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      digitalWrite(13,LOW); 
      digitalWrite(10, LOW);
      digitalWrite(8, LOW);
      lcd.clear();
}
void humidity_display(){//Humidité
  int humidity = dht.readHumidity();//Lecture de la valeur d'humidité reçu (en %)
  //humidity=45;  
  lcd.setCursor(0, 0);
  lcd.print("Humidite: ");
  lcd.print(humidity);
  lcd.print(" %");  
  if(humidity >= 40 && humidity <= 70) {
      digitalWrite(18,HIGH);//Led Verte allumée
      digitalWrite(9,LOW);
    }
    else{
      digitalWrite(18,LOW);
      digitalWrite(9,HIGH);//Led Jaune allumée
    }
  
}
void brigtness_display(){//Capteur luminosité
  int brigtness = analogRead(A1);//Lecture de la valeur reçu
  lcd.setCursor(0, 0);
  lcd.print("Luminosite: ");
  lcd.print(brigtness);
  lcd.print(" %");  
}
void radar_recul(){
  digitalWrite(10, LOW);
  delayMicroseconds(2);//temps d'attente de 2 microsecondes obligatoire
  digitalWrite(10, HIGH);//Démarrage de l'envoie des ultrasons
  delayMicroseconds(10);
  digitalWrite(10, LOW);//Arret de l'envoie
  long duration = pulseIn(A3, HIGH);//Mesure du temps de retour des ultrasons
  int distance = duration * 0.034 / 2;//Calcul de la distance en utilisant le calcul de la vitesse du son dans l'air a 20 degrets (0.034km/s)
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Distance: ");
  lcd.print(distance);

  if (distance<10){
    digitalWrite(8, HIGH);//Buzzer
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
  distance=0;
}
void loop() {
  switch (mode)
  {
    case 0:
      temperature_display();
      break;
    case 1:
      humidity_display(); 
      break; 
    case 2:
      brigtness_display();
      break; 
    case 3:
      radar_recul();
      break;                 
  }  
  if (digitalRead(19)==1 && mode>=3){
    
    mode=0;
  }
  else if(digitalRead(19)==1){
    reset_states();
    mode++;    
  }
  delay(500);
}