
char state;

int PinMa=4;
int PWMa=5;
int PinMb=7;
int PWMb=6;

const int ldr1 = A0;
const int ldr2 = A1;
const int ldr3 = A2;
const int ldr4 = A3;
const int ldr5 = A4;

int DS_1=0;
int DS_2=0;
int DS_3=0;
int DS_4=0;
int DS_5=0;

void move (int x, int y){
  digitalWrite (PinMa,HIGH);
  analogWrite(PWMa,y);
  digitalWrite (PinMb,HIGH);
  analogWrite(PWMb,x);
}
void backward (int x, int y){
  digitalWrite (PinMa,LOW);
  analogWrite(PWMa,y);
  digitalWrite (PinMb,LOW);
  analogWrite(PWMb,x);
}

void LineTrack(){
  do{
  DS_1 = digitalRead(ldr1);
DS_2 = digitalRead(ldr2);
DS_3 = digitalRead(ldr3);
DS_4 = digitalRead(ldr4);
DS_5 = digitalRead(ldr5);

if (DS_1 == 0 &&DS_2 == 1 && DS_3 == 1 && DS_4 == 1 && DS_5 == 0||DS_1 == 0 &&DS_2 == 0 && DS_3 == 1 && DS_4 == 0 && DS_5 == 0){
  move(120,120);
}

else if (DS_2 == 0 && DS_3 == 0 && DS_4 == 0 && DS_1 == 0 && DS_5 == 0) { // semicircule

  while(DS_2 == 0 && DS_3 == 0 && DS_4 == 0 && DS_1 == 0 && DS_5 == 0){  
  move(120,120);
  DS_1 = digitalRead(ldr1);
DS_2 = digitalRead(ldr2);
DS_3 = digitalRead(ldr3);
DS_4 = digitalRead(ldr4);
DS_5 = digitalRead(ldr5);
}


}

/*else if (DS_2 == 1 && DS_3 == 1 && DS_4 == 1 && DS_1 == 1 && DS_5 == 1) { // semicircule

  /*while(DS_1==1 && DS_5==1){  
  move(80,80);
  DS_1 = digitalRead(ldr1);
  DS_5 = digitalRead(ldr5);
} 
if (DS_1==0 &&DS_5==1){
  move(100,50);
  }
  else if (DS_1==1 &&DS_5==0){
  move(50,100);
  }
  else {
  move(120,120);
  }
}*/

else if (DS_2 == 1 && DS_3 == 1 && DS_4 == 0){
  move(115,120);
}

else if (DS_2 == 0 && DS_3 == 1 && DS_4 == 1){
  move (120,115);
}

else if (DS_2 == 0 && DS_3 == 0 && DS_4 == 1) { // elf 4mal
while(DS_3==0){
  move(120,15);
  DS_3 = digitalRead(ldr3);
  if(DS_4==0){
    break;
  }
} 
}
else if (DS_2 == 1 && DS_3 == 0 && DS_4 == 0) { // elf emen
while(DS_3==0){
  move(15,120);
  DS_3 = digitalRead(ldr3);
  if(DS_2==0){
    break;
  }
}
}
  } while(state == 'n'||state == '0');
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);

  
pinMode(PinMa, OUTPUT);
pinMode(PWMa, OUTPUT);
pinMode(PinMb, OUTPUT);
pinMode(PWMb, OUTPUT);

pinMode(ldr1, INPUT);
pinMode(ldr2, INPUT);
pinMode(ldr3, INPUT);
pinMode(ldr4, INPUT);
pinMode(ldr5, INPUT);

}

void loop()
{
  
if (Serial.available() > 0){ 
state = Serial.read();
Serial.println(state);
  }

if (state == 'f') { 
move(200, 200);
}
else if (state == 'b') { 
backward(200, 200);
}
else if (state == 'l') { 
move(20, 155);
}
else if (state == 'r') { 
move(155, 20);
}

else if (state == 'm'||state == '0'){
move(0, 0);
}
else if (state == 'n'){ 
  
    LineTrack();
    state = Serial.read();
    Serial.println(DS_1);
    Serial.print(DS_2);
    Serial.print(DS_3);
    Serial.print(DS_4);
    Serial.print(DS_5);
  }


}
