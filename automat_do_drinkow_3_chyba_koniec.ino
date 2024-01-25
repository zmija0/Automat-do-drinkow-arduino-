#include <LCD_I2C.h>

//Przypisanie pinów:
// sterowanie silnikami
#define Dir_X 22
#define Step_X 23
#define Dir_Y 24
#define Step_Y 25
#define Dir_Z 26
#define Step_Z 27
#define Enable 28

// czujniki krańcowe
#define KX 29
#define KY 30
#define KZ 31

// czujnik odległości
#define Echo 32
#define Trig 33

// przyciski
#define Up 34
#define Down 35
#define Ok 36 

//pompka
#define Rain 37

// zmienne do czujnika odległości
long CM;        //odległość w cm
long CZAS;     //długość powrotnego impulsu w uS
int steps;  // ilość kroków
int delayTime = 2;  //odstęp między krokami silnika
int Time = 20;  //długość impulsu cz. ruchu
int i;
int Number=0;   //numer w tabeli drinkow
int Size;   // rozmiar tabeli drinkow
int next_X; // kolejna współrzędna X
int next_Y; // kolejna współrzędna Y
int current_X = 0; // obecna współrzędna X
int current_Y = 0; // obecna współrzędna Y
int ms_rain;
int ms_after;
int ml;


// adresacja wyświetlacza
LCD_I2C lcd(0x27, 16, 2);

// opcje wyświetlane na wyświetlaczu

String Write[] = {"czyszczenie", "Test", "Chryzantema", "Rum Cranberry", "Californication",
"Cowboy_Roy", "Sex on the beach", "Cuba Libre", "Wodka Zurawina", "Tonic Limonka",
"Szarlotka cynamo", "Cytrynowka", "Gibson", "Cosmopolitan", "Wodka z Cola", 
"Gin z Tonikiem", "Cape Codder", "Vodka_Sunrise", "Fierro_Tonic", "Gimlet", "Knickerbocker",
"Gin Daisy", "Bianco mix", "El_Presidente", "Bacardi Coctail", "Mohito"};

void setup() 
{
   // sterowanie silnikami
  pinMode(Dir_X, OUTPUT);
  pinMode(Step_X, OUTPUT);
  pinMode(Dir_Y, OUTPUT);
  pinMode(Step_Y, OUTPUT);
  pinMode(Dir_Z, OUTPUT);
  pinMode(Step_Z, OUTPUT);
  pinMode(Enable, OUTPUT);
  // czujniki krańcowe
  pinMode(KX, INPUT_PULLUP);
  pinMode(KY, INPUT_PULLUP);
  pinMode(KZ, INPUT_PULLUP);
  // czujnik odległości
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  // przyciski
  pinMode(Up, INPUT_PULLUP);
  pinMode(Down, INPUT_PULLUP);
  pinMode(Ok, INPUT_PULLUP);
  // pompka
  pinMode(Rain, OUTPUT);

  // stany początkowe
  //digitalWrite(Enable, HIGH); wyjścia sterowników wyłączone
  digitalWrite(Dir_X, LOW);
  digitalWrite(Step_X, LOW);
  digitalWrite(Dir_Y, LOW);
  digitalWrite(Step_Y, LOW);
  digitalWrite(Dir_Z, LOW);
  digitalWrite(Step_Z, LOW);
  digitalWrite(Enable, HIGH);
  digitalWrite(Echo, LOW);
  digitalWrite(Rain, LOW);

  //  uruchomienie wyświetlacza
  lcd.begin();
  lcd.backlight();
  lenght_of_screen_tab();
  screen();
  Back_To_Start();

  //monitor szeregowy
 // Serial.begin(9600); 
}
void loop() 
{
  buttons();
}
/////////////////////////////////////////////////////////////////
// drinki

void Chryzantema()
{
  ml = 50;
  Rum();
  ml = 100;
  Zurawina();
  ml = 50;
  Granat();
  After_Raining();
}
void Rum_Cranberry()
{
  ml = 60;
  Rum();
  ml = 60;
  Pomarancza();
  ml = 60;
  Zurawina();
  After_Raining();
}
void Californication()
{
  ml = 20;
  Wodka();
  ml = 20;
  Gin();
  ml = 20;
  Rum();
  ml = 40;
  Limonka();
  ml = 80;
  Pomarancza();
  After_Raining();
}
void Cowboy_Roy()
{
  ml = 40;
  Rum();
  ml = 40;
  Wodka();
  ml = 120;
  Pomarancza();
  After_Raining();
}
void Sex_on_the_beach()
{
  ml = 40;
  Wodka();
  ml = 40;
  Pomarancza();
  ml = 40;
  Zurawina();
  ml = 40;
  After_Raining();
}
void Cuba_Libre()
{
  ml = 50;
  Rum();
  ml = 120;
  Cola();
  ml = 30;
  Limonka();
  After_Raining();
}
void Wodka_Zurawina()
{
  ml = 50;
  Wodka();
  ml = 40;
  Limonka();
  ml = 110;
  Zurawina();
  After_Raining();
}
void Tonic_Limonka()
{
  ml = 50;
  Wodka();
  ml = 30;
  Limonka();
  ml = 120;
  Tonic();
  After_Raining();
}
void Szarlotka() // dodac cynamon
{
  ml = 50;
  Wodka();
  ml = 120;
  Jablko();
  After_Raining();
}
void Cytrynowka()
{
  ml = 60;
  Wodka();
  ml = 100; 
  Sprite();
  ml = 40;
  Limonka();
  After_Raining();
}
void Gibson()
{
  ml = 90;
  Gin();
  ml = 30;
  Bianco();
  After_Raining();
}
void Cosmopolitan()
{
  ml = 40;
  Wodka();
  ml = 20;
  Pomarancza();
  ml = 20;
  Limonka();
  ml = 40;
  Zurawina();
  After_Raining();
}
void Wodka_Cola()
{
  ml = 50;
  Wodka();
  ml = 150;
  Cola();
  After_Raining();
}
void Gin_Tonic()
{
  ml = 50;
  Gin();
  ml = 150;
  Tonic();
  After_Raining();
}
void Cape_Codder()
{
  ml = 50;
  Wodka();
  ml = 50;
  Limonka();
  ml = 100;
  Zurawina();
  After_Raining();
}
void Vodka_Sunrise()
{
  ml = 50;
  Wodka();
  ml = 150;
  Pomarancza();
  ml = 30;
  Malina();
  After_Raining();
}
void Fierro_Tonic()
{
  ml = 50;
  Fierro();
  ml = 150;
  Tonic();
  After_Raining();
}
void Gimlet()
{
  ml = 50; 
  Gin();
  ml = 50;
  Limonka();
  After_Raining();
}
void Knickerbocker()
{
  ml = 60;
  Gin();
  ml = 30;
  Bianco();
  ml = 30;
  Fierro();
  After_Raining();
}
void Gin_Daisy()
{
  ml = 50;
  Gin();
  ml = 50;
  Granat();
  ml = 50;
  Limonka();
  ml = 50;
  Gazowana();
  After_Raining();
}
void Bianco_mix()
{
  ml = 75;
  Bianco();
  ml = 75;
  Sprite();
  ml = 50;
  Limonka();
  After_Raining();
}
void El_Presidente()
{
  ml = 60;
  Rum();
  ml = 30;
  Bianco();
  ml = 30;
  Granat();
  ml = 30;
  Pomarancza();
  After_Raining();
}
void Bacardi_Coctail()
{
  ml = 40;
  Rum();
  ml = 40;
  Granat();
  ml = 40;
  Limonka();
  After_Raining();
}
void Mohito()
{
  ml = 40;
  Rum();
  ml = 80;
  Limonka();
  ml = 60;
  Gazowana();
  After_Raining();
}

//
void cleaning ()
{
  ml = 100;
  Woda();
  After_Raining();
  Back_To_Start();
}
//////////////////// 
// składniki 
void Woda()
{
  next_X = 2175;
  next_Y = 2275;
  engines();
}
void Wodka()
{
  next_X = 4675;
  next_Y = 2275;
  engines();
}
void Fierro()
{
  next_X = 7175;
  next_Y = 2275;
  engines();
}
void Gin()
{
  next_X = 9675;
  next_Y = 2275;
  engines();
}
void Bianco()
{
  next_X = 2175;
  next_Y = 4775;
  engines();
}
void Rum()
{
  next_X = 4675;
  next_Y = 4775;
  engines();
}
void Pomarancza()
{
  next_X = 7175;
  next_Y = 4775;
  engines();
}
void Jablko()
{
  next_X = 9675;
  next_Y = 4775;
  engines();
}
void Limonka()
{
  next_X = 2175;
  next_Y = 7275;
  engines();
}
void Granat()
{
  next_X = 4675;
  next_Y = 7275;
  engines();
}
void Zurawina()
{
  next_X = 7175;
  next_Y = 7275;
  engines();
}
void Cola()
{
  next_X = 9675;
  next_Y = 7275;
  engines();
}
void Sprite()
{
  next_X = 2175;
  next_Y = 9775;
  engines();
}
void Gazowana()
{
  next_X = 4675;
  next_Y = 9775;
  engines();
}
void Tonic()
{
  next_X = 7175;
  next_Y = 9775;
  engines();
}
void Malina()
{
  next_X = 9675;
  next_Y = 9775;
  engines();
}
/////////////////////////////////
//reszta
//ruch w kazda pozycje xy
void Test()
{
  //
  next_X = 2175;
  next_Y = 2275;
  enginest_test();
  delay(10000);
  next_X = 4675;
  next_Y = 2275;
  enginest_test();
  next_X = 7175;
  next_Y = 2275;
  enginest_test();
  next_X = 9675;
  next_Y = 2275;
  enginest_test();
  //
  next_X = 2175;
  next_Y = 4775;
  enginest_test();
  next_X = 4675;
  next_Y = 4775;
  enginest_test();
  delay(10000);
  next_X = 7175;
  next_Y = 4775;
  enginest_test();
  next_X = 9675;
  next_Y = 4775;
  enginest_test();
  //
  next_X = 2175;
  next_Y = 7275;
  enginest_test();
  next_X = 4675;
  next_Y = 7275;
  enginest_test();
  delay(10000);
  next_X = 7175;
  next_Y = 7275;
  enginest_test();
  delay(10000);
  next_X = 9675;
  next_Y = 7275;
  enginest_test();
  //
  next_X = 2175;
  next_Y = 9775;
  enginest_test();
  next_X = 4675;
  next_Y = 9775;
  enginest_test();
  next_X = 7175;
  next_Y = 9775;
  enginest_test();
  next_X = 9675;
  next_Y = 9775;
  enginest_test();
  Back_To_Start();
}

//wywolanie funkcji ruchu xy
void enginest_test()
{
  direction_X();
  direction_Y();
  delay(2000);
}
//wywołanie funkcji ruchu xyz
void engines ()
{
  direction_X();
  direction_Y();
  move_Z();
}
//określanie kierunku ruchu x
void direction_X()		// ustalanie kierunku ruchu
{
	if (current_X <=next_X) 
	{
		digitalWrite(Dir_X, HIGH);
	}
	else 
	{
		digitalWrite(Dir_X, LOW);
	}
	move_X();
}
//określanie kierunku ruchu y
void direction_Y()		// ustalanie kierunku ruchu
{
	if (current_Y <=next_Y) 
	{
		digitalWrite(Dir_Y, HIGH);
	}
	else 
	{
		digitalWrite(Dir_Y, LOW);
	}
	move_Y();
}
//ruch w pozycjach x y
void move_X()			// ruch o steps_X kroków 
{		
	steps = abs(current_X - next_X);	// obliczanie liczby kroków

	digitalWrite(Enable, LOW);	// odblokowanie sterownika

	for (i=0; i<steps; i++)	// ruch
	{
		digitalWrite(Step_X, HIGH);
		delay(delayTime);
		digitalWrite(Step_X, LOW);
		delay(delayTime);	
	}
	
	digitalWrite(Enable, HIGH);	// zablokowanie sterownika
	
	current_X = next_X;	// zmiana widzianej lokalizacji	
}
void move_Y()			// ruch o steps_X kroków 
{		
	steps = abs(current_Y - next_Y);	// obliczanie liczby kroków

	digitalWrite(Enable, LOW);	// odblokowanie sterownika

	for (i=0; i<steps; i++)	// ruch
	{
		digitalWrite(Step_Y, HIGH);
		delay(delayTime);
		digitalWrite(Step_Y, LOW);
		delay(delayTime);	
	}
	
	digitalWrite(Enable, HIGH);	// zablokowanie sterownika
	
	current_Y = next_Y;	// zmiana widzianej lokalizacji	
}
// ruch w kierunku z i właczenie pompki
void move_Z()
{	
	digitalWrite(Enable, LOW);
	digitalWrite(Dir_Z, HIGH);
  delayTime = 1;
	for (i=0; i<7200; i++)
	{
		digitalWrite(Step_Z, HIGH);
		delay(delayTime);
		digitalWrite(Step_Z, LOW);
		delay(delayTime);
	}
  Raining(); // załączenie nalewania 
  // podnoszenie rurki
	//digitalWrite(Rain, HIGH);
	//delay(1000);
	//digitalWrite(Rain, LOW);
	digitalWrite(Dir_Z, LOW);
	for (i=0; i<7200; i++)
	{
		digitalWrite(Step_Z, HIGH);
		delay(delayTime);
		digitalWrite(Step_Z, LOW);
		delay(delayTime);
	}
  delayTime = 2;
	digitalWrite(Enable, HIGH);
  // załączenie pompki na 1sek w powietrzu żeby się nie cofało 
  ml = 30;
  Raining();
}
//powrót na współrzędne 0 0 0 
void Back_To_Start()
{
  digitalWrite(Enable, LOW);
  digitalWrite(Dir_X, LOW);
  digitalWrite(Dir_Y, LOW);
  digitalWrite(Dir_Z, LOW);
  for (;;)//oś Z
  {
    digitalWrite(Step_Z, HIGH);
		delay(delayTime);
		digitalWrite(Step_Z, LOW);
		delay(delayTime);	
    if ((digitalRead(KZ) == LOW))
    {
      break;
    }
  }
  for (;;)  //oś X
  {
    digitalWrite(Step_X, HIGH);
		delay(delayTime);
		digitalWrite(Step_X, LOW);
		delay(delayTime);	
    if ((digitalRead(KX) == LOW))
    {
      break;
    }
  }
  for (;;) //oś Y
  {
    digitalWrite(Step_Y, HIGH);
		delay(delayTime);
		digitalWrite(Step_Y, LOW);
		delay(delayTime);
    if ((digitalRead(KY) == LOW))
    {
      break;
    }	
  }
  current_Y = 0;
  current_X = 0;
  digitalWrite(Enable, HIGH);
}
//tabela funkcji
void (*drinkTab[])() = {cleaning, Test, Chryzantema, Rum_Cranberry, Californication, 
Cowboy_Roy, Sex_on_the_beach, Cuba_Libre, Wodka_Zurawina, Tonic_Limonka, 
Szarlotka, Cytrynowka, Gibson, Cosmopolitan, Wodka_Cola, Gin_Tonic, 
Cape_Codder, Vodka_Sunrise, Fierro_Tonic, Gimlet, Knickerbocker, Gin_Daisy,
Bianco_mix, El_Presidente, Bacardi_Coctail, Mohito};
//obsługa przycisków
void buttons()
{
  
  //obsługa przewijania w góre
  if (digitalRead(Up) == LOW)
  {
    delay(Time);
    if (digitalRead(Up) == LOW)
    {
      if (Number == 0)
      {
        Number = Size;
      } 
      else
      {
        Number = Number - 1;
      }
      screen();
      delay(500);
    }
  }
  //obsługa przewijania w dół
  if (digitalRead(Down) == LOW)
  {
    delay(Time);
    if (digitalRead(Down) == LOW)
    {
      if (Number == Size)
      {
        Number = 0;
      } 
      else
      {
        Number = Number + 1;
      }
      screen();
      delay(500);
    }
  }
  //obsługa zatwierdzenia;
  if (digitalRead(Ok) == LOW)
  {
    delay(Time);
    if (digitalRead(Ok) == LOW)
    {
      if(analogRead(A0)>=550)
      {
        pomiar_odleglosci();
        if(CM < 6)
        {
          drinkTab[Number]();
        }
        else
        {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("wsadz szklanke");
        }
      }
      else
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("wylej wode");
      }

    }
    delay(500);
  }
}
//obsługa wyświetlacza
void screen()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(Write[Number]);
}
//określenie długości tablicy drinków (ilości opcji)
void lenght_of_screen_tab()
{
  Size = sizeof(Write)/sizeof(Write[0]);
  Size = Size - 1;
}

void Raining()  // funkcja od 'zaciągania' z butelki
{
  ms_rain = ml * 125;
  digitalWrite(Rain, HIGH);
  delay(ms_rain);
  digitalWrite(Rain, LOW);
}

void After_Raining() // funkcja od 'wypychania' reszty płynu z rurki
{
  digitalWrite(Rain, HIGH);
  delay(15000);
  digitalWrite(Rain, LOW);
  delay(10000);
  Back_To_Start();
}

// funkcja odpowiedzalna za pomiar odległości
void pomiar_odleglosci ()
{
  digitalWrite(Trig, LOW);        
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);         
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  digitalWrite(Echo, HIGH); 
  CZAS = pulseIn(Echo, HIGH);
  CM = CZAS / 58;                
}
