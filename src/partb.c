//#include <avr/io.h>
//#include <avr/interrupt.h>
//
//void initialize() {
//    cli();
//    //set I/O pins
//    DDRB &= ~(1<<DDB0);
//    PORTB &= ~(1<<DDB0);
//    PORTB &= ~(1<<PORTB1);
//
//    TCCR1B &= ~(1<<WGM13);
//    TCCR1B &= ~(1<<WGM12);
//    TCCR1A &= ~(1<<WGM11);
//    TCCR1A &= ~(1<<WGM10);
//
//    TCCR1B |= (1<<CS12);
//    TCCR1B |= (1<<CS11);
//    TCCR1B |= (1<<CS10);
//
//    TCCR1B |= (1<<ICES1);
//    TIMSK1 |= (1<<ICIE1);
//
//    sei();
//}
//
//ISR(TIMER1_CAPT_vect) {
//    if (PINB & (1<<PINB0)) {
//        PORTB |= (1<<PORTB1);
//        TIFR1 |= (1<<ICF1);
//        TCCR1B &= ~(1<<ICES1);
//    } else {
//        PORTB &= ~(1<<PORTB1);
//        TIFR1 |= (1<<ICF1);
//        TCCR1B |= (1<<ICES1);
//    }
//}
//
//int main(void) {
//    initialize();
//    while (1) {}
//    return 0;
//}