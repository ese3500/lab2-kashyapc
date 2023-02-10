#include <stddef.h>
#include "tree.h"

char decodeMorse(node* curr, char* String, unsigned int count, int idx) {
    if (count == 0) {
        return curr->val;
    } else if (String[idx] == '.') {
        if (curr->dot == NULL) {
            return '?';
        }
        return decodeMorse(curr->dot, String, count-1, idx+1);
    } else if (String[idx] == '-') {
        if (curr->dash == NULL) {
            return '?';
        }
        return decodeMorse(curr->dash , String, count-1, idx+1);
    }
    return '#';
}