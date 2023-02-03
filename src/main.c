//#include <avr/io.h>
//#include <util/delay.h>
//
//void setup() {
//// write your initialization code here
//    DDRD &= ~(1<<DDD7);
//    PORTD |= (1<<PORTD7);
//}
//
//int main() {
//    setup();
//    char state = 0;
//    while (1) {
//        if (PIND & (1<<PIND7)) {
//            if (state == 0) {
//                PORTB &= ~(1 << PORTB4);
//                PORTB |= (1 << PORTB1);
//                state = 1;
//                _delay_ms(1000);
//            } else if (state == 1) {
//                PORTB &= ~(1 << PORTB1);
//                PORTB |= (1 << PORTB2);
//                state = 2;
//                _delay_ms(1000);
//            } else if (state == 2) {
//                PORTB &= ~(1 << PORTB2);
//                PORTB |= (1 << PORTB3);
//                state = 3;
//                _delay_ms(1000);
//            } else if (state == 3) {
//                PORTB &= ~(1 << PORTB3);
//                PORTB |= (1 << PORTB4);
//                state = 0;
//                _delay_ms(1000);
//            }
//        }
//    }
//    return 1;
//}
