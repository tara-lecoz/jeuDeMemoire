#include <LiquidCrystal.h>
#include <EEPROM.h>
#define buzzer 11
 
LiquidCrystal lcd(1, 2, 3, 4, 5, 6);  
int blueLED = A3;       
int redLED = A0;
int greenLED = A1;
int yellowLED = A2;
int leds;             

int blueButton = 7;     
int redButton = 10;
int greenButton = 9;
int yellowButton = 8;
int buttonState =12;   

bool continueGame = true;  
String simonInput;          
int highScore = 0;         
int address = 0;           
int score = 0;              

void setup() 
{
  pinMode(blueLED, OUTPUT); 
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(blueButton,INPUT);   
  pinMode(redButton,INPUT);
  pinMode(greenButton,INPUT);
  pinMode(yellowButton,INPUT);
  pinMode(buzzer, OUTPUT);

  highScore = EEPROM.read(address);  
  lcd.begin(16,2);                   
  lcd.print("High Score: " + String(highScore)); 
  lcd.setCursor(0,1);
  lcd.print("Score: " + String(score));         
  
  randomSeed(analogRead(0));               
}

void loop() 
{ 
  
  while(continueGame == true)   
  {
    lcd.setCursor(0,1);
    lcd.print("Score: " + String(score)); 
    continueGame = newRound();             
  }
  if(score > highScore)          
  {
    highScore = score;            
    EEPROM.update(address, highScore); 
    score = 00;             
    lcd.setCursor(0,0);           
    lcd.print("High Score: " + String(highScore)); 
  }
  score = 0;
  while(continueGame == false)    
  {
    leds = 0;           
    simonInput = "";            
    continueGame = beginNewGame();
    lcd.setCursor(0,1);
    lcd.print("Score: 00");
  }
}


bool newRound()
{ 
  delay(300);
  String userInput;
  bool buttonPressed = false;
  int newLED = random(4);   
  simonInput = simonInput + newLED; 
  leds++;
  
  for(int i = 0; i < leds; i++)  
  {
    displayPattern(simonInput.charAt(i)); 
    delay(300);
  }
  for(int i = 0; i < leds; i++)
  {
    while(buttonPressed == false)  
    {
      if(buttonPressed = digitalRead(blueButton) == true)   
      {
       
        digitalWrite(blueLED, HIGH); 
        delay(700);
        digitalWrite(blueLED, LOW);
        buttonPressed = true;         
        userInput = userInput + 0;     
        delay(400);
      }
      else if(buttonPressed = digitalRead(redButton) == true)
      {
        
        digitalWrite(redLED, HIGH);     
        delay(700);
        digitalWrite(redLED, LOW);
        buttonPressed = true;
        userInput = userInput + 1;   
        delay(400);
      }
      else if(buttonPressed = digitalRead(greenButton) == true)
      {
        
        digitalWrite(greenLED, HIGH);  
        delay(700);
        digitalWrite(greenLED, LOW);    
        buttonPressed = true;
        userInput = userInput + 2;   
        delay(400);
      }
      else if(buttonPressed = digitalRead(yellowButton) == true)
      {
        
        digitalWrite(yellowLED, HIGH);  
        delay(700);
        digitalWrite(yellowLED, LOW);
        buttonPressed = true;
        userInput = userInput + 3;      
        delay(400);
      }
    }
    if(userInput.charAt(i) != simonInput.charAt(i))  
      {  
        gameOver();                  
        return false;     
      }
    buttonPressed = false;            
  }
    
    score++;                          
    lcd.setCursor(0,1);
    lcd.print("Score: " + String(score));    
    return true;
    
}

void displayPattern(char led)           
{
  if(led == '0')     
  {
    digitalWrite(blueLED, HIGH);
    delay(700);
    digitalWrite(blueLED, LOW);
  }
  else if(led == '1')      
  {
    digitalWrite(redLED, HIGH);
    delay(700);
    digitalWrite(redLED, LOW);
  }
  else if(led == '2')     
  {
    digitalWrite(greenLED, HIGH);
    delay(700);
    digitalWrite(greenLED, LOW);
  }
  else if(led == '3')         
  {
    digitalWrite(yellowLED, HIGH);
    delay(700);
    digitalWrite(yellowLED, LOW);
  }
}

bool beginNewGame()
{
  bool buttonPressed = false;
  while(buttonPressed == false)
    {
      if(buttonState = digitalRead(blueButton) == true)
      {
        buttonPressed = true;
      }
      else if(buttonState = digitalRead(redButton) == true)
      {
        buttonPressed = true;
      }
      else if(buttonState = digitalRead(greenButton) == true)
      {
        buttonPressed = true;
      }
      else if(buttonState = digitalRead(yellowButton) == true)
      {
        buttonPressed = true;
      }
    }
  int count = 0;
  
  while(count < 3)
  {
    digitalWrite(blueLED,HIGH);
    digitalWrite(redLED,HIGH);
    digitalWrite(greenLED,HIGH);
    digitalWrite(yellowLED,HIGH);
    delay(200);
    digitalWrite(blueLED,LOW);
    digitalWrite(redLED,LOW);
    digitalWrite(greenLED,LOW);
    digitalWrite(yellowLED,LOW);
    delay(200);
    count++;
  }
  delay(300);
  return buttonPressed;
}

void gameOver()
{
  int count = 0;
  while(count < 3)
  {
    digitalWrite(blueLED,HIGH);
    digitalWrite(redLED,HIGH);
    digitalWrite(greenLED,HIGH);
    digitalWrite(yellowLED,HIGH);
    tone(buzzer, 1900);
    delay(300);
    digitalWrite(blueLED,LOW);
    digitalWrite(redLED,LOW);
    digitalWrite(greenLED,LOW);
    digitalWrite(yellowLED,LOW);
    tone(buzzer, 1900);
    delay(300);
    noTone(buzzer);
    count++;
  }

}