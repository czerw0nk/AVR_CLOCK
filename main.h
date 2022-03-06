/*-------------Globals begin------------- */
struct time{
uint8_t hour;
uint8_t minute;
uint8_t second;
uint8_t hoursFormat;
}CurrentTime;

uint8_t buffor = 0; /* For adjustment of 12h format*/
/*--------------Globals end------------- */

 

/* -------7seg display begin---------*/
#define INIT_PD0 DDRD |= (1<<PD0)
#define INIT_PD1 DDRD |= (1<<PD1)
//#define INIT_PD2 DDRD |= (1<<PD2) INTx
#define INIT_C7 DDRC |= (1<<PC7)
#define INIT_PA7 DDRA |= (1<<PA7)
#define INIT_PD4 DDRD |= (1<<PD4)
#define INIT_PD5 DDRD |= (1<<PD5)
#define INIT_PD6 DDRD |= (1<<PD6)
#define INIT_PB DDRB |= 0b11111111;
 
#define ON_A PORTB  |= (1<<PB0)
#define ON_B PORTB  |= (1<<PB1)
#define ON_C PORTB  |= (1<<PB2)
#define ON_D PORTB  |= (1<<PB3)
#define ON_E PORTB  |= (1<<PB4)
#define ON_F PORTB  |= (1<<PB5)
#define ON_G PORTB  |= (1<<PB6)
#define ON_H PORTB  |= (1<<PB7)

#define OFF_A PORTB  &= ~(1<<PB0)
#define OFF_B PORTB  &= ~(1<<PB1)
#define OFF_C PORTB  &= ~(1<<PB2)
#define OFF_D PORTB  &= ~(1<<PB3)
#define OFF_E PORTB  &= ~(1<<PB4)
#define OFF_F PORTB  &= ~(1<<PB5)
#define OFF_G PORTB  &= ~(1<<PB6)
#define OFF_H PORTB  &= ~(1<<PB7)



/*hour*/
#define ON_DISPLAY_H1 PORTD |= (1<<PD0)
#define ON_DISPLAY_H2 PORTD |= (1<<PD1)

/*minute*/
#define ON_DISPLAY_M1 PORTC |= (1<<PC7)
#define ON_DISPLAY_M2 PORTA |= (1<<PA7)

/*second*/
#define ON_DISPLAY_S1 PORTD |= (1<<PD4)
#define ON_DISPLAY_S2 PORTD |= (1<<PD5)

/*hour*/
#define OFF_DISPLAY_H1 PORTD &= ~(1<<PD0)
#define OFF_DISPLAY_H2 PORTD &= ~(1<<PD1)

/*minute*/
#define OFF_DISPLAY_M1 PORTC &= ~(1<<PC7)
#define OFF_DISPLAY_M2 PORTA &= ~(1<<PA7)

/*second*/
#define OFF_DISPLAY_S1 PORTD &= ~(1<<PD4)
#define OFF_DISPLAY_S2 PORTD &= ~(1<<PD5)

/* -------7seg display end---------*/

/* -------LED segment begin---------*/
#define INIT_LED_FORMAT DDRD  |= (1<<PD6)
#define LED_FORMAT_OFF PORTD  &= ~(1<<PD6);
#define LED_FORMAT_ON PORTD  |= (1<<PD6);
/* -------LED segment end---------*/
  
/* -------NumPad segment begin---------*/
#define INIT_PC1 DDRC &= ~(1<<PC1)
#define INIT_PC2 DDRC &= ~(1<<PC2)
#define INIT_PC3 DDRC &= ~(1<<PC3)
#define INIT_PC4 DDRC |= (1<<PC4)
#define INIT_PC5 DDRC |= (1<<PC5)
#define INIT_PC6 DDRC |= (1<<PC6)

#define ON_PC1 PORTC |= (1<<PC1)
#define ON_PC2 PORTC |= (1<<PC2)
#define ON_PC3 PORTC |= (1<<PC3)
#define ON_PC4 PORTC |= (1<<PC4)
#define ON_PC5 PORTC |= (1<<PC5)
#define ON_PC6 PORTC |= (1<<PC6)

#define OFF_PC1 PORTC &= ~(1<<PC1)
#define OFF_PC2 PORTC &= ~(1<<PC2)
#define OFF_PC3 PORTC &= ~(1<<PC3)
#define OFF_PC4 PORTC &= ~(1<<PC4)
#define OFF_PC5 PORTC &= ~(1<<PC5)
#define OFF_PC6 PORTC &= ~(1<<PC6)

#define PULLUP_SW_PC1 PORTC |= (1<<PC1)
#define PULLUP_SW_PC2 PORTC |= (1<<PC2)
#define PULLUP_SW_PC3 PORTC |= (1<<PC3)
#define PULLUP_SW_PC4 PORTC |= (1<<PC4)
#define PULLUP_SW_PC5 PORTC |= (1<<PC5)
#define PULLUP_SW_PC6 PORTC |= (1<<PC6)

#define IS_SW_PC1   !(PINC & (1<<PC1))
#define IS_SW_PC2   !(PINC & (1<<PC2))
#define IS_SW_PC3   !(PINC & (1<<PC3))
#define IS_SW_PC4   !(PINC & (1<<PC4))
#define IS_SW_PC5   !(PINC & (1<<PC5))
#define IS_SW_PC6   !(PINC & (1<<PC6))

/* -------NumPad segment end---------*/


/*----------Interupt button begin-----*/
#define INIT_SW_PD2 DDRD &= ~(1<<PD2)
#define PULLDOWN_PD2 PORTD &= ~(1<<PD2)
#define INIT_PD7 DDRD |= (1<<PD7)
#define ON_PD7 PORTD |= (1<<PD7)
#define OFF_PD7 PORTD  &= ~(1<<PD7)
#define INIT_SW_PC0 DDRC &= ~(1<<PC0)
#define PULLUP_SW_PC0 PORTC |= (1<<PC0)
#define IS_SW_PC0   !(PINC & (1<<PC0))
/*----------Interupt button end-------*/