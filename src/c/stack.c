#include "../header/stack.h"

void CreateEmptyStack(Stack *s){
    s->top=-1;
}

bool IsStackEmpty(Stack s){
    return s.top==-1;
}

bool IsStackFull(Stack s){
    return s.top==MAX_STACK_SIZE-1;
}

void PrintStackObat(Stack s){
    for(int i=0; i<=s.top; i++){
        printf("%s", s.obat[i]);
        if(i<s.top){
            printf(" -> ");
        }
    }
    printf("\n");
}

void Push(Stack *s, Obat val){
    if(!isStackFull(*s)){
        s->top++;
        strncpy(s->obat[s->top], val, MAX_OBAT_LENGTH);
    }
}

void Pop(Stack *s, Obat *val){
    if(!isStackEmpty(*s)){
        strncpy(*val, s->obat[s->top], MAX_OBAT_LENGTH);
        s->top--;
    }
}