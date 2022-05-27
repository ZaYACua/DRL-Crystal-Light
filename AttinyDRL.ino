const int leftOut = 0;  
const int RightOut = 1;
const int leftIn = 4;
const int RightIn = 3;
const int Analog = A1;
const int off = 450; //0.4459 V - 12.76V
const int on = 480; //0.4753 V - 13.6V
int c = 0;

void setup() {
  pinMode(leftOut, OUTPUT);
  pinMode(RightOut, OUTPUT);
  pinMode(leftIn, INPUT);
  pinMode(RightIn, INPUT);
  pinMode(Analog, INPUT);
  analogReference(INTERNAL); //використовую внутрішню опорну напругу 1.1 В

}


void loop() {
  do{
    if (analogRead(Analog)>=on){ //Перевіряю яка напруга. Якщо >= on продовжую перевірку.
      if (digitalRead(leftIn) == LOW) { //Якщо лівий покажчик повороту ОФФ змінюю константу з 0 на 1
        c = 1; 
       }
      if (digitalRead(RightIn) == LOW) { //Якщо лівий покажчик повороту ОФФ змінюю константу з 0 чи 1 на 2 чи 3
        c += 2; 
      }
    }
  }while(c==0); //Якщо хоч 1 потрібно вмикати - виходжу з циклу
  swtch(); //Переходжу до функції нижче, котра в залежності від змінної "c" вмикає праве чи ліве чи праве + ліве ДХО
  while (analogRead(Analog)>off){ //Цикл який працює після першого ввімкнення. Якщо напруга вище напруги OFF та не включене ближнє, чи покажчики повороту.
    if (digitalRead(leftIn) == HIGH) { //Вимикаю лівий, якщо вмикаю лівий покажчик повороту ( або ближнє світло)
      digitalWrite(leftOut, LOW); 
    }
    else if (digitalRead(leftOut)!=HIGH){ //В інакшому випадку перевіряю, чи зараз ввімкнений лівий. Якщо ні - змінюю константу "с" з 0 на 1
        c = 1;
    }
     if (digitalRead(RightIn) == HIGH) { //Вимикаю правий, якщо вмикаю правий покажчик повороту ( або ближнє світло)
      digitalWrite(RightOut, LOW);
    }
    else if (digitalRead(RightOut)!=HIGH){//В інакшому випадку перевіряю, чи зараз ввімкнений правий. Якщо ні - змінюю константу "с" додаю до змінної 2 ( отримую або 2, або 3).
        c += 2;
    }
    swtch(); //Переходжу до функції нижче, котра в залежності від змінної "c" вмикає праве чи ліве чи праве + ліве ДХО
  }
  delay(500); //Чекаю 0.5 секунди 
  digitalWrite(leftOut, LOW); //Вимикаю ліве ДХО
  digitalWrite(RightOut, LOW); //Вимикаю праве ДХО
}

void swtch(){ //В залежності від змінної "с" вмикаю ліве, праве або обидва ДХО з затримкою перед ввімкненням у 2 секунди.
  switch(c){ 
    case 1: 
        delay(2000);
        digitalWrite(leftOut, HIGH);
        break;
    case 2:
        delay(2000);
        digitalWrite(RightOut, HIGH);
        break;
    case 3:
        delay(2000);
        digitalWrite(leftOut, HIGH);
        digitalWrite(RightOut, HIGH);
        break;
  }
  c = 0; //Обнулюю після виконання функції switch
}
