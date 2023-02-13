// for any type of bits, reverse bits
// eg: input: "00111010"
// output: "01011100"
#include <stdio.h>

short rev_bit(short input) {
    short output = 0;
    short i = 0;

    for (i = 1; i != 0; i <<= 1) {
        output <<= 1;
        if (input & 1) {
            output |= 1;
        }
        input >>= 1;
    }
    return output;
}

int main() {
    short input = 0b0100001001000010;
    short output = rev_bit(input);

    printf("intput = %d, output = %d\n", input, output);
    return 0;
}
