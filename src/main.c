#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include <stdlib.h>
#include "tree.h"
#include "uart.h"

#define F_CPU 16000000UL
#define PRESCALE 9600
#define MAX_COUNT 65536

volatile unsigned int edge1 = 0;
volatile unsigned int edge2 = 0;
volatile unsigned int count = 0;
volatile char String[25];
node root;

void setupInterrupts(void) {
    cli();
    //set I/O pins
    DDRB &= ~(1<<DDB0);
    PORTB &= ~(1<<DDB0);
    PORTB &= ~(1<<PORTB1);

    TCCR1B &= ~(1<<WGM13);
    TCCR1B &= ~(1<<WGM12);
    TCCR1A &= ~(1<<WGM11);
    TCCR1A &= ~(1<<WGM10);

    //pre-scaling set to 1024
    TCCR1B |= (1<<CS12);
    TCCR1B &= ~(1<<CS11);
    TCCR1B |= (1<<CS10);

    TCCR1B |= (1<<ICES1);
    TCCR1B |= (1<<ICNC1);
    TIMSK1 |= (1<<ICIE1);
    TIMSK1 |= (1<<TOIE1);

    sei();
    UART_init((F_CPU/(PRESCALE*16UL))-1);
}

void createTree(void) {
    node* Z = (node*) malloc(sizeof(node));
    Z->val = 'Z';
    Z->dot = NULL;
    Z->dash = NULL;
    node* Y = (node*) malloc(sizeof(node));
    Y->val = 'Y';
    Y->dot = NULL;
    Y->dash = NULL;
    node* X = (node*) malloc(sizeof(node));
    X->val = 'X';
    X->dot = NULL;
    X->dash = NULL;
    node* V = (node*) malloc(sizeof(node));
    V->val = 'V';
    V->dot = NULL;
    V->dash = NULL;
    node* Q = (node*) malloc(sizeof(node));
    Q->val = 'Q';
    Q->dot = NULL;
    Q->dash = NULL;
    node* P = (node*) malloc(sizeof(node));
    P->val = 'P';
    P->dot = NULL;
    P->dash = NULL;
    node* L = (node*) malloc(sizeof(node));
    L->val = 'L';
    L->dot = NULL;
    L->dash = NULL;
    node* J = (node*) malloc(sizeof(node));
    J->val = 'J';
    J->dot = NULL;
    J->dash = NULL;
    node* H = (node*) malloc(sizeof(node));
    H->val = 'H';
    H->dot = NULL;
    H->dash = NULL;
    node* F = (node*) malloc(sizeof(node));
    F->val = 'F';
    F->dot = NULL;
    F->dash = NULL;
    node* C = (node*) malloc(sizeof(node));
    C->val = 'C';
    C->dot = NULL;
    C->dash = NULL;
    node* B = (node*) malloc(sizeof(node));
    B->val = 'B';
    B->dot = NULL;
    B->dash = NULL;
    node* W = (node*) malloc(sizeof(node));
    W->val = 'W';
    W->dot = P;
    W->dash = J;
    node* D = (node*) malloc(sizeof(node));
    D->val = 'D';
    D->dot = B;
    D->dash = X;
    node* K = (node*) malloc(sizeof(node));
    K->val = 'K';
    K->dot = C;
    K->dash = Y;
    node* R = (node*) malloc(sizeof(node));
    R->val = 'R';
    R->dot = L;
    R->dash = NULL;
    node* S = (node*) malloc(sizeof(node));
    S->val = 'S';
    S->dot = H;
    S->dash = V;
    node* G = (node*) malloc(sizeof(node));
    G->val = 'G';
    G->dot = Z;
    G->dash = Q;
    node* O = (node*) malloc(sizeof(node));
    O->val = 'O';
    O->dot = NULL;
    O->dash = O;
    node* U = (node*) malloc(sizeof(node));
    U->val = 'U';
    U->dot = F;
    U->dash = NULL;
    node* A = (node*) malloc(sizeof(node));
    A->val = 'A';
    A->dot = R;
    A->dash = W;
    node* I = (node*) malloc(sizeof(node));
    I->val = 'I';
    I->dot = S;
    I->dash = U;
    node* N = (node*) malloc(sizeof(node));
    N->val = 'N';
    N->dot = D;
    N->dash = K;
    node* M = (node*) malloc(sizeof(node));
    M->val = 'M';
    M->dot = G;
    M->dash = O;
    node* T = (node*) malloc(sizeof(node));
    T->val = 'T';
    T->dot = N;
    T->dash = M;
    node* E = (node*) malloc(sizeof(node));
    E->val = 'E';
    E->dot = I;
    E->dash = A;
    root.dot = E;
    root.dash = T;
    root.val = '!';
}

ISR(TIMER1_CAPT_vect) {
    char Morse[8];
    if (PINB & (1<<PINB0)) {
        edge1 = (unsigned) TCNT1;
        TIFR1 |= (1<<ICF1);
        TCCR1B &= ~(1<<ICES1);
    } else {
        edge2 = (unsigned) TCNT1;
        PORTB &= ~(1<<PORTB1);
        TIFR1 |= (1<<ICF1);
        TCCR1B |= (1<<ICES1);
        unsigned int out = edge2 - edge1;
        if (out > 500 && out < 3000) {
            String[count] = '.';
            count += 1;
            sprintf(Morse, ".");
            UART_putstring(Morse);
            PORTB |= (1<<PORTB1);
            _delay_ms(50);
            PORTB &= ~(1<<PORTB1);
        } else if (out >= 3000 && out < 8000) {
            String[count] = '-';
            count += 1;
            sprintf(Morse, "-");
            UART_putstring(Morse);
            PORTB |= (1<<PORTB2);
            _delay_ms(50);
            PORTB &= ~(1<<PORTB2);
        } else if (out >= 8000 && out < 30000) {
            char Out[32];
            String[count] = '\0';
            sprintf(Morse, "\n");
            UART_putstring(Morse);
            char decoded = decodeMorse(&root, String, count, 0);
            sprintf(Out, "%c\n", decoded);
            UART_putstring(Out);
            count = 0;
        }
        edge1 = 0;
        edge2 = 0;
    }
}

ISR(TIMER1_OVF_vect) {
    edge2 = 0;
    edge1 = 0;
}

int main(void) {
    setupInterrupts();
    createTree();
    while (1) {}
    return 0;
}