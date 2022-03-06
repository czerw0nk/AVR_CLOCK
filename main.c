#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <main.h>

/*Prototypes
static void Init_Time(struct time* CurrentTime);
static void Init_7seg(void);
static void Init_Button(void);
static void Init_Port(void);
static void Init_Clock(void);
static void Init_ADC(void);

static void readADC(uint8_t channel);
static void clockTick(struct time* CurrentTime);
*/
volatile uint8_t cnt=0;   

/*for set time*/
uint8_t pressed_number = 0;
uint8_t cursor = 0;
uint8_t temp1=0;
uint8_t temp2=0;

uint8_t h=0;
uint8_t m=0;
uint8_t s=0;

/*--------------Init section begin---------------- */
static void Init_Port(void){


}

static void Init_ADC_CH(uint8_t channel){

	switch(channel) {
	case 0:
		ADMUX &= ~((1<<MUX0) | (1<<MUX1) | (1<<MUX2) | (1<<MUX3) | (1<<MUX4));
		break;
		
	case 1:
		ADMUX &= ~((1<<MUX1) | (1<<MUX2) | (1<<MUX3) | (1<<MUX4));
		ADMUX |= (1<<MUX0);
		break;
		
	case 2:
		ADMUX &= ~((1<<MUX0) | (1<<MUX2) | (1<<MUX3) | (1<<MUX4));
		ADMUX |= (1<<MUX1);
		break;
	
	case 3:
		ADMUX &= ~((1<<MUX2) | (1<<MUX3) | (1<<MUX4));
		ADMUX |= (1<<MUX0) | (1<<MUX1);
		break;
	
	case 4:
		ADMUX &= ~((1<<MUX1) | (1<<MUX0) | (1<<MUX3) | (1<<MUX4));
		ADMUX |= (1<<MUX2);
		break;
	
	case 5:
		ADMUX &= ~((1<<MUX1) | (1<<MUX3) | (1<<MUX4));
		ADMUX |= (1<<MUX2) | (1<<MUX0);
		break;
	
	case 6:
		ADMUX &= ~((1<<MUX3) | (1<<MUX0) |(1<<MUX4));
		ADMUX |=  (1<<MUX1) | (1<<MUX2);
		break;
	
	case 7:
		ADMUX &= ~((1<<MUX3) | (1<<MUX4));
		ADMUX |= (1<<MUX0) | (1<<MUX1) | (1<<MUX2);
		break;
	}
}

static void Init_Time(struct time* CurrentTime){
	CurrentTime->second = 0;
	CurrentTime->minute = 0;
	CurrentTime->hour = 22;
	CurrentTime->hoursFormat = 24;
	INIT_LED_FORMAT;
}

static void Init_7seg(void){
	/*Init all ports*/
	INIT_PB;
	INIT_PD0; 
	INIT_PD1; 
	INIT_C7; 
	INIT_PA7; 
	INIT_PD4; 
	INIT_PD5;  
	INIT_PD6; 

	/*Off all segments*/
	OFF_A;  
	OFF_B;  
	OFF_C;  
	OFF_D;  
	OFF_E;  
	OFF_F;  
	OFF_G;

	/*Off all display*/
	OFF_DISPLAY_H1;
	OFF_DISPLAY_H2;
	OFF_DISPLAY_M1;
	OFF_DISPLAY_M2;
	OFF_DISPLAY_S1;
	OFF_DISPLAY_S2;
}

static void Init_Button(void){
	INIT_SW_PD2;
	INIT_SW_PC0;
	PULLUP_SW_PC0;
	INIT_PD7;
}

static void Init_Interupt(void){
	MCUCR |= ((1<<ISC01) | (1<<ISC00) | (1<<ISC10) | (1<<ISC11));
	GICR  |= (1<<INT0) | (1<<INT1);
}

static void Init_NumPad(void){
	INIT_PC1;
	INIT_PC2;
	INIT_PC3;
	INIT_PC4;
	INIT_PC5;
	INIT_PC6;
	PULLUP_SW_PC1;
	PULLUP_SW_PC2;
	PULLUP_SW_PC3;
	PULLUP_SW_PC4;
	PULLUP_SW_PC5;
	PULLUP_SW_PC6;
}

static void Init_Timmer(void){
	/* prescaler */
	TCCR0 |= (1<<CS02) | (1<<CS00);  
 	TIMSK |= (1<<TOIE0);
	TCNT0 =130;         
   	sei();  
}

static void Init_ADC(void)
{
	ADCSRA = (1<<ADEN) 
   |(1<<ADPS0)  
   |(1<<ADPS1)  
   |(1<<ADPS2);   

  ADMUX  =  (1<<REFS0); 
}
/*--------------Init section end------------------ */


/*-------------Function section begin------------- */
static void clockTick(struct time* CurrentTime){
	CurrentTime->second++;
	if(CurrentTime->second>59){
		CurrentTime->second=0;
		CurrentTime->minute++;
	}
	if(CurrentTime->minute > 59){
		CurrentTime->minute = 0;
		CurrentTime->hour++;
	}
	if(CurrentTime->hour > CurrentTime->hoursFormat-1)
	{
		CurrentTime->hour = 0;
		CurrentTime->minute = 0;
		CurrentTime->second = 0;
	}
}

static int readADC(uint8_t channel){
	Init_ADC_CH(channel);
	
	ADCSRA |= (1<<ADSC); 
   
    while(ADCSRA & (1<<ADSC));  

	return ADC;
}

static void displayNumber(uint8_t number){
		switch(number)
		{
			case 0: 
			{
			OFF_G;
			ON_A;
			ON_B;
			ON_C;
			ON_D;
			ON_E;	
			ON_F;
			break;
			}
			case 1: 
			{
			OFF_A;
			OFF_E;
			OFF_F;
			OFF_G;
			OFF_D;	
			ON_B;
			ON_C;	
			break;
			}
			case 2: 
			{
			OFF_C;
			OFF_F;
			ON_A;
			ON_B;
			ON_D;	
			ON_E;
			ON_G;	
			break;
			}
			case 3: 
			{
			OFF_E;
			OFF_F;
			ON_A;
			ON_B;
			ON_C;	
			ON_D;
			ON_G;	
			break;
			}
			case 4: 
			{
			OFF_A;
			OFF_D;
			OFF_E;
			ON_F;
			ON_G;	
			ON_B;
			ON_C;	
			break;
			}
			case 5: 
			{
			OFF_B;
			OFF_E;
			ON_A;
			ON_F;
			ON_G;	
			ON_C;
			ON_D;	
			break;
			}
			case 6: 
			{
			OFF_B;
			ON_A;
			ON_C;
			ON_D;
			ON_E;	
			ON_F;
			ON_G;	
			break;
			}
			case 7: 
			{
			OFF_F;
			OFF_G;
			OFF_E;
			OFF_D;
			ON_A;
			ON_B;
			ON_C;	
			break;
			}
			case 8: 
			{
			ON_A;
			ON_B;
			ON_C;
			ON_D;
			ON_E;
			ON_F;
			ON_G;	
			break;
			}
			case 9: 
			{
			OFF_E;
			ON_A;
			ON_B;
			ON_C;
			ON_D;
			ON_F;
			ON_G;	
			break;
			}
			default:
			{
			ON_E;
			ON_A;
			ON_B;
			ON_C;
			ON_D;
			ON_F;
			ON_G;
			ON_H;	
			break;	
			}		
		}
}

uint8_t check_NumPad()
{
	pressed_number = 0;
	while(pressed_number == 0){
		OFF_PC6;
		if(IS_SW_PC3)
			pressed_number = 1;
		else if(IS_SW_PC2)
			pressed_number =  2;
		else if(IS_SW_PC1)
			pressed_number =  3;
		ON_PC6;
		
		OFF_PC5;
		if(IS_SW_PC3)
			pressed_number = 4;
		else if(IS_SW_PC2)
			pressed_number =  5;
		else if(IS_SW_PC1)
			pressed_number =  6;
		ON_PC5;
		
		OFF_PC4;
		if(IS_SW_PC3)
			pressed_number = 7;
		else if(IS_SW_PC2)
			pressed_number =  8;
		else if(IS_SW_PC1)
			pressed_number =  9;
		ON_PC4;	
	}
return pressed_number;
}

static void logic(void){
	/* Clock */
	S2();
	S1();

	M2();
	M1();

	H2();
	H1();

	/* NumPad*/
	
	/* polling ADC */
	if(readADC(3) >= 512){
		if(buffor == 1){
			CurrentTime.hour+=12;
			buffor=0;
		}
		CurrentTime.hoursFormat = 24;
		LED_FORMAT_ON;
	}
	else
	{
		if(CurrentTime.hour > 12)
		{
			CurrentTime.hour -=12;
			buffor = 1;
		}
		CurrentTime.hoursFormat = 12;
		LED_FORMAT_OFF;
	}
}

void H1(){
	ON_DISPLAY_H1;
	_delay_ms(10);
	displayNumber(CurrentTime.hour/10);
	OFF_DISPLAY_H1;
	_delay_ms(1);
}

void H2(){
	ON_DISPLAY_H2;
	_delay_ms(10);
	displayNumber(CurrentTime.hour%10);
	OFF_DISPLAY_H2;
	_delay_ms(1);
}

void M1(){
	ON_DISPLAY_M1;
	_delay_ms(10);
	displayNumber(CurrentTime.minute/10);
	OFF_DISPLAY_M1;
	_delay_ms(1);
}

void M2(){
	ON_DISPLAY_M2;
	_delay_ms(10);
	displayNumber(CurrentTime.minute%10);
	OFF_DISPLAY_M2;
	_delay_ms(1);
}

void S1(){
	ON_DISPLAY_S1;
	_delay_ms(10);
	displayNumber(CurrentTime.second%10);
	OFF_DISPLAY_S1;
	_delay_ms(1);
}

void S2(){
	ON_DISPLAY_S2;
	_delay_ms(10);
	displayNumber(CurrentTime.second/10);
	OFF_DISPLAY_S2;
	_delay_ms(1);
}
/*-------------Function section end--------------- */

/* ------------Interupt handler begin------------- */
ISR(INT0_vect)
{	
	uint8_t cnt =0;
	cursor++; 
	if(cursor == 7)
	{
		CurrentTime.hour=h;
		CurrentTime.minute=m;
		CurrentTime.second=s;
		cursor=0;
		cli();
	}
	//while(!IS_SW_PC0){
		ON_PD7;	
		displayNumber(cursor);
		/*H1*/
		if(cursor == 1)
			temp1=check_NumPad();
			
		/*H2*/
		else if(cursor == 2){
			temp2=check_NumPad();
			temp1 *= 10;
			temp2 += temp1; 
			if(temp2>CurrentTime.hoursFormat)
				h=CurrentTime.hoursFormat;
			else
				h=temp2; 
		}
		
		/*M1*/
		else if(cursor == 3)
			temp1=check_NumPad();
		/*M2*/
		else if(cursor == 4){
			temp2=check_NumPad();
			temp1 *= 10;
			temp2 += temp1; 
			if(temp2>60)
				m=60;
			else
				m=temp2; 
		}

		/*S1*/
		else if(cursor == 5)
			temp1=check_NumPad();
		/*S2*/
		else if(cursor == 6){
			temp2=check_NumPad();
			temp1 *= 10;
			temp2 += temp1; 
			if(temp2>60)
				s=60;
			else
				s=temp2; 
		}
		
	//}
	OFF_PD7;
}

ISR(INT1_vect){
ON_PD7;
}

ISR(TIMER0_OVF_vect)   
{  
  TCNT0 = 130;      
  cnt++;
  /* 125*64us*125  = 1000ms */  
  if(cnt>125) 
  {  
    clockTick(&CurrentTime);
    cnt=0;  
  }  
}

/* ------------Interupt handler-end--------------- */

int main(void)
{
	Init_Time(&CurrentTime);
	Init_7seg();
	Init_Timmer();
	Init_ADC();
	Init_NumPad();
	Init_Interupt();
	Init_Button();

	while(1){
	logic();
	}
}