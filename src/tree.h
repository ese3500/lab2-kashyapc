typedef struct Tree_Node {
     struct Tree_Node* dot;
     struct Tree_Node* dash;
     char val;
} node;

char decodeMorse(node* curr, char* String, unsigned int count, int idx);