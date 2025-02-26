// Definim els pins dels LEDs.
int led1 = 3;    
int led2 = 5;
int led3 = 6;
int potenciometre = A0;                                              //Defineixo l'entrada analògica del potenciòmetre.
int temps = 1000;                                                    //Variable del temps.
int ValorPot;                                                        //Variable del potenciòmetre d'A0 que varia la velocitat.
int interruptor = 7;
int ValorInterruptor;                                                //Variable del interruptor que guarda el valor de 1(engegat) o 0(apagat). 
int ValorSentit= 8;
int sentit;                                                          //Variable que guarda el valor del sentit, 0(sentit original) 0 1(sentit contrari).
int potenciometre2 = A1;                                             //Defineixo l'entrada analògica del potenciòmetre.
int ValorPot2;                                                       //Variable del potenciòmetre d'A2.
int lluminositat;                                                    //Variable que hem guarda el valor de la intensitat dels LED's.

void setup() {
  // put your setup code here, to run once:
  // Configuració dels pins com a Sortida i Entrades.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(potenciometre, INPUT);
  pinMode(potenciometre2, INPUT);
  pinMode(interruptor, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  ValorInterruptor = digitalRead(interruptor);                    //Aqui li dono un valor a la variable del interruptor d'engegat o apagat.
  sentit = digitalRead(ValorSentit);                              //Aqui li dono un valor a la variable del sentit de gir.
  if (ValorInterruptor == HIGH){                                  //Aqui si el interruptor que engega el circuit està encés, el circuit funciona.
     ValorPot = analogRead(potenciometre);                        //Aqui llegeixo el valor del potenciòmetre que regula la velocitat.
     temps = map(ValorPot, 0, 1023, 200, 2000);                   //Mapeig de la variable del temps, amb el valor del potenciòmetre per variar el la velocitat.
     ValorPot2 = analogRead(potenciometre2);                      //Aqui llegeixo el valor del potenciòmetre que regula la lluminositat.
     lluminositat = map(ValorPot2, 0, 1024, 0,255);               //Mapeig de la variable de la lluminositat, amb el valor del potenciòmetre per variar el la intensitat dels LED's.

    if (sentit == HIGH){                                          //Aqui quan el interruptor de canvi de sentit està engegat, la direcció de la intensitat comança per el 3r LED.
       analogWrite(led3, lluminositat);                           //L'arduino modifica analògicament la intansitat dels LED's.
       delay(temps);
       analogWrite(led3, 0);                                      //L'arduino modifica analògicament la intansitat dels LED's a 0 perquè s'apagui.
       analogWrite(led2, lluminositat);                           //L'arduino modifica analògicament la intansitat dels LED's.
       delay(temps);
       analogWrite(led2, 0);                                      //L'arduino modifica analògicament la intansitat dels LED's a 0 perquè s'apagui.
       analogWrite(led1, lluminositat);                           //L'arduino modifica analògicament la intansitat dels LED's.
       delay(temps);
       analogWrite(led1, 0);                                      //L'arduino modifica analògicament la intansitat dels LED's a 0 perquè s'apagui.
       
    }
    else {                                                        //Aqui quan el interruptor de canvi de sentit està apagat(else), la direcció de la intensitat comança per el 1r LED.
      analogWrite(led1, lluminositat);
      delay(temps);
      analogWrite(led1, 0);
      analogWrite(led2, lluminositat);
      delay(temps);
      analogWrite(led2, 0);
      analogWrite(led3, lluminositat);
      delay(temps);
      analogWrite(led3, 0);
      
    }
 
  }
  else {                                                        //Aqui, el else fa referència al intrruptor d'engegat o apagat, que si no està engegat faci que el circuit no fuincioni.
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }

}
