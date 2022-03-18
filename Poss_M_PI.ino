const int EchoPin = 5;
const int TriggerPin = 6;
const int En = 12;
const int Rt = 11;
const int Av = 10;
const unsigned int Ts=60000;
unsigned int t,t0;
int e, ref, pwm, cm;
float a= 1;
float b = -10.588;
float c= 0.542;  
float pwm1=0;
float e1=0;

void setup() {
 
   Serial.begin(115200);
   pinMode(TriggerPin, OUTPUT);
   pinMode(EchoPin, INPUT);
   pinMode(En, OUTPUT);
   pinMode(Av, OUTPUT);
   pinMode(Rt ,OUTPUT);
   digitalWrite(En, LOW); 
  
 //Inicializando variables.
 ref=100; // Referencia [mm]
   e=0;
   pwm=1;
   cm=100;

   
}

void loop() {

   t=micros();

  if(t-t0 >= Ts){
  // printSerial();
  t0=t;  
  }
  cm = ping(TriggerPin, EchoPin);
    e=(cm-ref);
//   Serial.print("D: ");
//   Serial.print(cm);
//   Serial.print("  ");
   Serial.print("Eror = ");
   Serial.print(e);

   

  
   e=(cm-ref); //Error
  
   pwm = abs(((a*pwm1 + b*e + c*e1)/6))*2;
   pwm1=pwm;
   e1=e;

   if (pwm >=(250)) 
   pwm = 250;
   if(pwm<=5)
   pwm=0; 
   
 if (e>=0){
      digitalWrite(En, HIGH); 
      analogWrite(Rt, 0);
      analogWrite(Av, pwm);
      delay(50); 
 }
 
 if (e <= 0){
      digitalWrite(En, HIGH);
      analogWrite(Rt, pwm);
      analogWrite(Av, 0);
      delay(50); 
 }
 

 if (e==0);{
   digitalWrite(En, LOW);
     analogWrite(Av, 0);
     analogWrite(Rt, 0);
     }

  
     
//Serial.print(" mm= ");
//Serial.print(cm);
//Serial.print("  pwm1= ");
//Serial.print(pwm1);
//Serial.print("  e1= ");
//Serial.print(e1);
Serial.print("  pwm= ");
Serial.println(pwm);

  
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
