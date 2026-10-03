#ifndef BEULE_H
#define BEULE_H


#include "list.h"

struct Stack;

Stack* stack_create();
void stack_delete(Stack* stack);

void stack_push(Stack* stack, Data data);
Data stack_pop(Stack* stack);
bool stack_is_empty(const Stack* stack);

void stack_dup(Stack* stack);
void stack_drop(Stack* stack);
void stack_swap(Stack* stack);
void stack_over(Stack* stack);
void stack_rot(Stack* stack);

#endif