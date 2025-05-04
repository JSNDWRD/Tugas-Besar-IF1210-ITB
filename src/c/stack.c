#include "../header/stack.h"
#include "../header/kamus.h"

void CreateEmptyStack(Stack *S){
    S->top=-1;
}

boolean isStackEmpty(Stack S){
    return S.top==-1;
}

boolean isStackFull(Stack S){
    return S.top==MAX_STACK_SIZE-1;
}

void printStackObat(Stack S){
    for(int i=0; i<=S.top; i++){
        printf("%s", S.obat[i]);
        if(i<S.top){
            printf(" -> ");
        }
    }
    printf("\n");
}

boolean isStackEqual(Stack S1, Stack S2){
    if(S1.top!=S2.top){
        return false;
    }
    for(int i=0; i<S1.top; i++){
        if(strcmp(S1.obat[i],S2.obat[i])!=0){
            return false;
        }
    }
    return true;
}

void push(Stack *S, Obat val){
    if(!isStackFull(*S)){
        S->top++;
        strncpy(S->obat[S->top], val, MAX_OBAT_LENGTH);
    }
}

void pop(Stack *S, Obat *val){
    if(!isStackEmpty(*S)){
        strncpy(*val, S->obat[S->top], MAX_OBAT_LENGTH);
        S->top--;
    }
}