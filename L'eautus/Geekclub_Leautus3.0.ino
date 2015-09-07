#include <AFMotor.h>

// Declaration moteur
const int stepsPerRevolution = 200; // Nb de pas par tour
const int maxRevolution = 30; // Nb de tours pour une course complète
const int motorSpeed = 30; // Vitesse de rotation tr/min
AF_Stepper motor(stepsPerRevolution, 2);

// Declaration capteurs
const char capteur_pluie = A1; // pin connecté au capteur extérieur
int val_pluie = 0; //la valeur recue
const char capteur_reserv = A2; // pin connecté au capteur de réservoir
int val_reserv = 0; // la valeur du réservoir
int seuil = 700; //Détermine le seuil de détection de la tension du capteur

// Variables fonctionnement
bool isDown = true;

void setup() {
  
  Serial.begin(9600);
  Serial.println("Initialisation!");

  // Init moteur
  motor.setSpeed(motorSpeed);   
  motor.release();
  
  delay(1000);
}

void loop() {
  
  val_pluie = analogRead(capteur_pluie); 
  Serial.println(val_pluie);
  
  if (val_pluie<seuil) {                   // S'il y a de l'eau sur le capteur
    Serial.println("Pluie detectee!");
  
    if (isDown) {                         // Et que le parapluie est plié
    
      Serial.println("Deploiement!");
      motor.step(maxRevolution*stepsPerRevolution, FORWARD, SINGLE);   // Fais monter le moteur 
      motor.release();
      isDown = false;                     // Et indique que le moteur est maintenant en haut
      
    } else {                              //Et que le moteur est en haut 
    
      val_reserv = analogRead(capteur_reserv); // On lit la valeur de remplissage de la cuve
      Serial.println(val_reserv);
      if (val_reserv<seuil) { // Si le réservoir est plein
        Serial.println("Reservoir plein, on se replie!");
        motor.step(maxRevolution*stepsPerRevolution, BACKWARD, SINGLE); // Fais descendre le moteur
        motor.release();
        isDown = true;  // Et indique que le récupérateur est maintenant en bas
      }
      
    }
    
   } else { // S'il n'y a pas d'eau sur le capteur
   
      if (isDown) {}
                                                //Insérer ici le watchdog et sleepmode
      else {                                   // Et que le moteur est en haut
        Serial.println("Plus de pluie, on se replie!");
        motor.step(maxRevolution*stepsPerRevolution, BACKWARD, SINGLE); // Fais descendre le moteur
        motor.release();
        isDown = true;                        // Et indique que le récupérateur est maintenant en bas
      } 
   }
  
}
