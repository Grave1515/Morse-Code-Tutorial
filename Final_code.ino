#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,16,2);


const int but_easy = 4;
const int but_med = 3;
const int but_hard = 2;
const int but_gener  = 5;
const int aud =6;
//int bg_st = 1;
int lastButtonState = 1; // previous state of the button
unsigned long startPressed = 0;    // the moment the button was pressed
unsigned long endPressed = 0;      // the moment the button was released
unsigned long holdTime = 0;        // how long the button was hold
unsigned long idleTime = 0;        // how long the button was idle


char easy[9] = {' ','A','E','I','M','N','O','S','T'};
char medium[9] = {' ','C','D','G','H','K','R','U','W'};
char hard[11]= {' ','B','F','J','L','P','Q','V','X','Y','Z'};

String easyMorse[9] = { "", ".-", ".", "..", "--", "-.", "---", "...", "-" };
String mediumMorse[9] = { "", "-.-.", "-..", "--.", "....", "-.-", ".-.", "..-", ".--" };
String hardMorse[11] = { "", "-...", "..-.", ".---", ".-..", "--.-", ".--.", "...-", "-..-", "-.--", "--.." };



int e = 0;
int m =0;
int h =0;

int e_tr = 0;
int m_tr = 0;
int h_tr = 0;
int incorrectCount = 0;
int correctCount = 0;

String input_morse = "";


void setup()
{
  pinMode(but_easy,INPUT_PULLUP);
  pinMode(but_med,INPUT_PULLUP);
  pinMode(but_hard,INPUT_PULLUP);
  pinMode(but_gener,INPUT_PULLUP);
  pinMode(aud,OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Morse Code");
  lcd.setCursor(6,1);
  lcd.print("Tutorial");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Buttons to press");
  //delay(1000);
  lcd.setCursor(0,1);
  scrollMessage("1 for easy 2 for medium 3 for hard ",1,0,350);

}

void loop()
{
  int be_st = digitalRead(but_easy);
  int bm_st = digitalRead(but_med);
  int bh_st = digitalRead(but_hard);
  int bg_st = digitalRead(but_gener);
 
 if (be_st == LOW)
 {
  if(e>=0 && e<=9)
  {
    easy_mode();
  }
  else if(e>9)
  {
    if(e_tr==0)
    {
      lcd.clear();
      lcd.print("Test Time:");
      //lcd.setCursor(0,1);
      scrollMessage("Here are some rules:",1,0,350);
      //delay(100);
      delay(2200);
      scrollMessage("Short Press 4 for Dot, Long Press 4 for Dash",1,0,325);
      //delay(2200);
      //scrollMessage("After entering complete morse code of the letter, press button 3 to register your input",0,0,325);
      delay(2000);
      scrollMessage("Press Button 1 when done. ",1,0,325);
      delay(100);
      incorrectCount = 0;
      correctCount = 0;
      e_tr++;
    }
    else if(e_tr==10)
    {
      lcd.clear();
      lcd.print("Test Results:");
      lcd.setCursor(0,1);
      scrollMessage("Correct="+String(correctCount)+"and Incorrect="+String(incorrectCount),1,0,350);
    }
    else if(e_tr>=1 && e_tr<=9)
    {
      if(e_tr>1 && e_tr<=9)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Your Input:");
        lcd.setCursor(6,1);
        lcd.print(input_morse);
        delay(1000);
        if(input_morse == easyMorse[e_tr-1])
        {
          correctCount++;
          lcd.clear();
          lcd.print("Correct Input");
          delay(500);
        }
        else
        {
          incorrectCount++;
          lcd.clear();
          lcd.print("Incorrect Input");
          delay(500);
        }
        input_morse="";
      }
      if(e_tr<=8)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Enter Morse code");
        lcd.setCursor(5,1);
        lcd.print("of");
        lcd.setCursor(8, 1);
        lcd.print(easy[e_tr]);
      //test = input_morse;
        delay(500);
      }
      e_tr++;
    }
  }
 }
 if (bm_st == LOW)
 {
  if(m>=0 && m<=9)
  {
    medium_mode();
  }
  else if(m>9){
      
    if(m_tr==0)
    {
      lcd.clear();
      lcd.print("Test Time:");
      lcd.setCursor(0,1);
      scrollMessage("Here is some info regarding test:",1,0,325);
      delay(2200);
      lcd.clear();
      //scrollMessage("Press Button 4 to input the Morse Code of the letter shown.",0,0,325);
      delay(2200);
      scrollMessage("Short Press 4 for Dot, Long Press 4 for Dash",0,0,325);
      //delay(2200);
      //scrollMessage("After entering complete morse code of the letter, press button 3 to register your input",0,0,325);
      delay(2000);
      scrollMessage("Press Button 2 when done",1,0,325);
      delay(100);
      incorrectCount = 0;
      correctCount = 0;
      m_tr++;
    }
    else if(m_tr==10)
    {
      lcd.clear();
      lcd.print("Test Results:");
      lcd.setCursor(0,1);
      scrollMessage("Correct="+String(correctCount)+"and Incorrect="+String(incorrectCount),1,0,350);
    }
    else if(m_tr>=1 && m_tr<=9)
    {
      if(m_tr>1 && m_tr<=9)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Your Input:");
        lcd.setCursor(6,1);
        lcd.print(input_morse);
        delay(1000);
        if(input_morse == mediumMorse[m_tr-1])
        {
          correctCount++;
          lcd.clear();
          lcd.print("Correct Input");
          delay(500);
        }
        else
        {
          incorrectCount++;
          lcd.clear();
          lcd.print("Incorrect Input");
          delay(500);
        }
        input_morse=""; // Reseeting the input taken by user
      }
      if(m_tr<=8)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Enter Morse Code");
        lcd.setCursor(5,1);
        lcd.print("Of");
        lcd.setCursor(8, 1);
        lcd.print(medium[m_tr]);
      //test = input_morse;
        delay(500);
      }
      m_tr++;
    }
  }
 }
 if (bh_st == LOW)
 {
  if(h>=0 && h<=11)
  {
  if(h==0)
  {
    lcd.clear();
    scrollMessage("Hard Mode Selected",0,0,350);
    lcd.setCursor(0,1);
    lcd.print("Press 3 for next");
    h++;
  }
  else if(h==11)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Train mode ends");
    scrollMessage("Press 3 to Continue",1,0,400);
    h++;
  }
  else if(h>=1 && h<12)
  {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HardMode:");
  //lcd.setCursor(0,0);
  //lcd.print("MorseCode-");
  lcd.setCursor(10,0);
  lcd.print(hard[h]);
  GetCode(hard[h]);
  lcd.setCursor(0,1);
  lcd.print("Press 3 for next");
  //scrollMessage("Press button 3 for next",1,0,350);
  delay(100);
  h++;
  }
  }
  else if(h>11){
    if(h_tr==0)
    {
      lcd.clear();
      lcd.print("Test Time:");
      lcd.setCursor(0,1);
      scrollMessage("Here are some rules:",1,0,350);
      delay(1000);
      //scrollMessage("Press Button 4 to input the Morse Code of the letter shown.",1,0,350);
      //delay(1200);
      scrollMessage("Short Press 4 for Dot, Long Press 4 for Dash",1,0,350);
      //delay(1200);
      //scrollMessage("After entering complete morse code of the letter, press button 3 to register your input",1,0,350);
      delay(2000);
      scrollMessage("Press Button 3 when done",1,0,350);
      incorrectCount = 0;
      correctCount = 0;
      h_tr++;
    }
    else if(h_tr==12)
    {
      lcd.clear();
      lcd.print("Test Results:");
      lcd.setCursor(0,1);
      scrollMessage("Correct="+String(correctCount)+"and Incorrect="+String(incorrectCount),1,0,350);
    }
    else if(h_tr>=1 && h_tr<=11)
    {
      if(h_tr>1 && h_tr<=11)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Your Input:");
        lcd.setCursor(6,1);
        lcd.print(input_morse);
        delay(1000);
        if(input_morse == hardMorse[h_tr-1])
        {
          correctCount++;
          lcd.clear();
          lcd.print("Correct Input");
          delay(1000);
        }
        else
        {
          incorrectCount++;
          lcd.clear();
          lcd.print("Incorrect Input");
          delay(1000);
        }
        input_morse="";
      }
      if(h_tr<=10)
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Enter Morse Code");
        lcd.setCursor(5,1);
        lcd.print("Of");
        lcd.setCursor(8, 1);
        lcd.print(hard[h_tr]);
      //test = input_morse;
        delay(500);
      }
      h_tr++;
    }
  }

 }

 if (bg_st != lastButtonState) 
  { 
     //updateState();
  if (bg_st == LOW) 
  {
      startPressed = millis();
  } 
    else if(bg_st == HIGH) 
    {
      endPressed = millis();
      holdTime = endPressed - startPressed;
      if (holdTime >= 100 && holdTime < 250) 
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Dot Registered"); 
        input_morse += ".";
        tone(aud,500,150);
        delay(350);
        noTone(aud);
    }
    else if (holdTime >= 250) 
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Dash Registered"); 
      input_morse += "-";
      tone(aud,500,450);
      delay(350);
      noTone(aud);
    }
  }
  }
 lastButtonState = bg_st;
}

/*
void updateState() 
{
  // the button has been just pressed
  if (bg_st == LOW) 
  {
      startPressed = millis();
  } 
  else 
  {
    endPressed = millis();
    holdTime = endPressed - startPressed;

    if (holdTime >= 100 && holdTime < 250) 
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Dot Registered"); 
      input_morse += ".";
      tone(aud,500,150);
      delay(350);
      noTone(aud);
    }
    else if (holdTime >= 250) 
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Dash Registered"); 
      input_morse += "-";
      tone(aud,500,450);
      delay(350);
      noTone(aud);
    }
  }
}
*/

void MorseDot()
{
  tone(aud,500,200);
  delay(200);
}

void MorseDash()
{
  tone(aud,500,600);
  delay(600);
}

void Toneoff()
{
  noTone(aud);
  delay(200);
}


void GetCode(char ch)
{
	switch (ch) {
	  case 'A':	
		MorseDot();
		Toneoff();
		MorseDash();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print(".-");
		break;
	  case 'B':
		MorseDash();
		Toneoff();
		MorseDot();
		Toneoff();
		MorseDot();
		Toneoff();
		MorseDot();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print("-...");
		break;
	  case 'C':
	  MorseDash();
		Toneoff();
		MorseDot();
		Toneoff();
		MorseDash();
		Toneoff();
		MorseDot();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print("-.-.");
		break;
	  case 'D':
		MorseDash();
		Toneoff();
		MorseDot();
		Toneoff();
		MorseDot();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print("-..");
		break;
	  case 'E':
		MorseDot();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print(".");
		break;
	  case 'F':
	  MorseDot();
		Toneoff();
		MorseDot();
		Toneoff();
		MorseDash();
		Toneoff();
		MorseDot();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print("..-.");
		break;
	  case 'G':
		MorseDash();
		Toneoff();
		MorseDash();
		Toneoff();
		MorseDot();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print("--.");
		break;
	  case 'H':
	  MorseDot();
		Toneoff();
		MorseDot();
		Toneoff();
		MorseDot();
		Toneoff();
		MorseDot();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print("....");
		break;
	  case 'I':
	  MorseDot();
		Toneoff();
		MorseDot();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print("..");
		break;
	  case 'J':
	  MorseDot();
		Toneoff();
		MorseDash();
		Toneoff();
		MorseDash();
		Toneoff();
		MorseDash();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print(".---");
		break;
    case 'K':
	  MorseDash();
		Toneoff();
		MorseDot();
		Toneoff();
		MorseDash();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print("-.-");
		break;
	  case 'L':
	  MorseDot();
		Toneoff();
		MorseDash();
		Toneoff();
		MorseDot();
		Toneoff();
		MorseDot();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print(".-..");
		break;
    case 'M':
	  MorseDash();
		Toneoff();
		MorseDash();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print("--");
		break;
	  case 'N':
	  MorseDash();
		Toneoff();
		MorseDot();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print("-.");
		break;
	  case 'O':
	  MorseDash();
		Toneoff();
		MorseDash();
		Toneoff();
		MorseDash();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print("---");
		break;
	  case 'P':
	  MorseDot();
		Toneoff();
		MorseDash();
		Toneoff();
		MorseDash();
		Toneoff();
		MorseDot();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print(".--.");
		break;
	  case 'Q':
	  MorseDash();
		Toneoff();
		MorseDash();
		Toneoff();
		MorseDot();
		Toneoff();
		MorseDash();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print("--.-");
		break;
	  case 'R':
	  MorseDot();
		Toneoff();
		MorseDash();
		Toneoff();
		MorseDot();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print(".-.");
		break;
	  case 'S':
	  MorseDot();
		Toneoff();
		MorseDot();
		Toneoff();
		MorseDot();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print("...");
		break;
	  case 'T':
	  MorseDash();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print("-");
		break;
	  case 'U':
	  MorseDot();
		Toneoff();
		MorseDot();
		Toneoff();
		MorseDash();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print("..-");
		break;
	  case 'V':
	  MorseDot();
		Toneoff();
		MorseDot();
		Toneoff();
		MorseDot();
		Toneoff();
		MorseDash();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print("...-");
		break;
	  case 'W':
	  MorseDot();
		Toneoff();
		MorseDash();
		Toneoff();
		MorseDash();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print(".--");
		break;
	  case 'X':
	  MorseDash();
		Toneoff();
		MorseDot();
		Toneoff();
		MorseDot();
		Toneoff();
		MorseDash();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print("-..-");
		break;
	  case 'Y':
	  MorseDash();
		Toneoff();
		MorseDot();
		Toneoff();
		MorseDash();
		Toneoff();
		MorseDash();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print("-.--");
		break;
	  case 'Z':
	  MorseDash();
		Toneoff();
		MorseDash();
		Toneoff();
		MorseDot();
		Toneoff();
		MorseDot();
		Toneoff();
    lcd.setCursor(12,0);
    lcd.print("--..");
		break;
	  default: 
		Toneoff();
    break;		
	}
}


void scrollMessage(String message,int r,int c,int tx_sp) {
  //  delay(400);
  for (int i=0; i < 16; i++)
  {
    message = " " + message;  
  } 
   message = message + " "; 

  //  delay(500);
  for (int position = 0; position < message.length(); position++) 
    {
    lcd.setCursor(c, r);
    lcd.print(message.substring(position, position + 16));
    delay(tx_sp);
    }
}

void easy_mode()
{
  if(e==0)
  {
    lcd.clear();
    scrollMessage("Easy Mode Selected",0,0,350);
    //scrollMessage("Press button 1 for viewing next letters",1,0,350);
    lcd.setCursor(0,1);
    lcd.print("Press 1 for next");
    e++;
  }
  else if(e==9)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Train mode ends");
    delay(100);
    scrollMessage("Press 1 to Continue",1,0,400);
    e++;
  }
  else if(e>=1 && e<10)
  {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("EasyMode:");
  //lcd.setCursor(0,0);
  //lcd.print("MorseCode-");
  lcd.setCursor(10,0);
  lcd.print(easy[e]);
  GetCode(easy[e]);
  lcd.setCursor(0,1);
  lcd.print("Press 1 for next");
  delay(100);
  e++;
  }
}

void medium_mode(){
  if(m==0)
  {
    lcd.clear();
    scrollMessage("Medium Mode Selected",0,0,350);
    lcd.setCursor(0,1);
    lcd.print("Press 2 for next");
    m++;
  }
  else if(m==9)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Train mode ends");
    lcd.setCursor(0, 1);
    scrollMessage("Press 2 to Continue",1,0,400);
    m++;
  }
  else if(m>=1 && m<10)
  {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MidMode: ");
  //lcd.setCursor(0,0);
  //lcd.print("MorseCode-");
  lcd.setCursor(10,0);
  lcd.print(medium[m]);
  GetCode(medium[m]);
  lcd.setCursor(0,1);
  lcd.print("Press 2 for next");
  //scrollMessage("Press button 2 for next",1,0,350);
  delay(100);
  m++;
  }
}