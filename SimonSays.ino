long randNumber;
int colors[110];

#define L1 4
#define L2 6
#define L3 8
#define L4 10
#define B1 5
#define B2 7
#define B3 9
#define B4 11
#define buzzer 13


void setup(){  
  Serial.begin(9600);
  randomSeed(analogRead(0));

  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);

  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT);
  pinMode(B4, INPUT);
 

  pinMode(buzzer, OUTPUT);
  
  for(int i = 0; i <= 100; i++)
  colors[i] = random(0, 4);

}


void printSequence(int level){
  for(int i = 0; i <= level; i++){
    digitalWrite(L1 + colors[i] * 2, HIGH);
    tone(buzzer,200+(L1 + colors[i] * 2)*100,500);
    delay(300);
    digitalWrite(L1 + colors[i] * 2, LOW);
    delay(300);    
  }
}

int level = 0;
void readAnswer(){
  int a1 = 0;
  int a2 = 0;
  int a3 = 0;
  int a4 = 0;
  for(int i = 0; i <= level; i++){
    while(a1 == 0 && a2 == 0 && a3 == 0 && a4 == 0){
      a1 = digitalRead(B1);
      a2 = digitalRead(B2);
      a3 = digitalRead(B3);
      a4 = digitalRead(B4);
    }
    
  int led = B1;
    if(a1 != 0)
    {
      led = L1;
      tone(buzzer,200+(L1 + colors[i] * 2)*100,500);
    }
    
    if(a2 != 0) 
    {
      led = L2;
       tone(buzzer,200+(L1 + colors[i] * 2)*100,500);
    }
    
    if(a3 != 0) 
    {
      led = L3;
       tone(buzzer,200+(L1 + colors[i] * 2)*100,500);
    }
    if(a4 != 0) 
    {
      led = L4;
      tone(buzzer,200+(L1 + colors[i] * 2)*100,500);
    }

    digitalWrite(led, HIGH);
    delay(200);
    digitalWrite(led, LOW);
    delay(200);

    
    switch(colors[i]){
      case 0:{
        if(a1 == 0){
          flicker();
          level = -1;
          delay(500);
          return;
        }
      }break;
      case 1:{
        if(a2 == 0){
          flicker();
          level = -1;
          delay(500);
          return;
        }
      }break;
      case 2:{
        if(a3 == 0){
           flicker();
          level = -1;
          delay(500);
          return;
        }
      }break;
      case 3:{
        if(a4 == 0){
           flicker();
          level = -1;
          delay(500);
          return;
        }
      }break;
    }
    
    a1 = a2 = a3 = a4 = 0;
    delay(500);
     
  }
}

void flicker()
{
   
 
  for(int j=1;j<=3;j++)
  {  tone(buzzer, 300-j*23);
    for(int i=0;i<=6 ;i+=2)
    {
      digitalWrite(L1+i, HIGH);
      delay(50);
      digitalWrite(L1+i, LOW);
      delay(50);
      
    }
    noTone(buzzer);
    delay(50);
  }
  
  delay(200);

}

void loop() {
   
  printSequence(level);
  readAnswer();
  level++;
}
