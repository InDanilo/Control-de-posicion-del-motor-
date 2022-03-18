const int EchoPin = 5;
const int TriggerPin = 6;
const int En = 12;
const int Rt = 11;
const int Av = 10;
const unsigned int Ts=60000;
unsigned int t,t0;

int pwm=0;
void setup() {
 
   Serial.begin(115200);
   pinMode(TriggerPin, OUTPUT);
   pinMode(EchoPin, INPUT);
   pinMode(En, OUTPUT);
   pinMode(Av, OUTPUT);
   pinMode(Rt ,OUTPUT);
}

void loop() {

   t=micros();

  if(t-t0 >= Ts){
   printSerial();
  t0=t;  
  
   int cm = ping(TriggerPin, EchoPin);
   Serial.print("D: ");
   Serial.print(cm);
   Serial.println("  ");
   
//Rango del pwm de 70 a 255//
int ref = 100;
pwm=255;

if (cm > ref){
    //pwm=int((cm))*1;
  if (pwm>255) pwm=255;  
      digitalWrite(En, HIGH); 
      analogWrite(Rt, 0);
      analogWrite(Av, pwm);
     

      delay(50);
      //digitalWrite(En, LOW);
      //analogWrite(Av, 0);
      
}
 
  if ( cm < ref){
  
    //pwm=int((200-cm)*1);
    
    if (pwm>255) pwm=255;  
      digitalWrite(En, HIGH); 
      analogWrite(Av, 0);
      analogWrite(Rt, pwm);
      
       
     delay(50);
     //digitalWrite(En, LOW);
     //analogWrite(Av, 0);
    }
    if (cm==ref)pwm=0;
    // digitalWrite(En, LOW); 
     analogWrite(Av, pwm);
      analogWrite(Rt, 0);

     // Serial.print("  pwm= ");
     // Serial.println(pwm);
  }
  
}


int ping(int TriggerPin, int EchoPin) {
   double duration, distanceCm;
   
   digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(TriggerPin, LOW);
   
   duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
   
   distanceCm = (duration * 10 / 292)/2*10;   //convertimos a distancia, en cm
   return distanceCm;
}

void printSerial(){
  Serial.print("Ts:[ms] -> ");
  Serial.print((t-t0)/1000);
  Serial.print(" ");
  }
