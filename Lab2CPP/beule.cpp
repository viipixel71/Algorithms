#include "beule.h"

struct Stack
{
    List* list;
};

Stack* stack_create()
{
    return new Stack{ list_create() };
}

void stack_delete(Stack* stack)
{
    if (!stack) return;
    list_delete(stack->list);
    delete stack;
}

void stack_push(Stack* stack, Data data)
{
    if (stack) list_insert(stack->list, data);
}

Data stack_pop(Stack* stack)
{
    if (!stack || stack_is_empty(stack)) return (Data)0;
    Data val = list_item_data(list_first(stack->list));
    list_erase_first(stack->list);
    return val;
}

bool stack_is_empty(const Stack* stack)
{
    return !stack || (list_first(stack->list) == nullptr);
}

void stack_dup(Stack* stack)
{
    if (!stack_is_empty(stack))
    {
        stack_push(stack, list_item_data(list_first(stack->list)));
    }
}

void stack_drop(Stack* stack)
{
    stack_pop(stack);
}

static int pop_n(Stack* stack, Data* items, int count)
{
    int popped = 0;
    for (int i = 0; i < count; ++i)
    {
        if (stack_is_empty(stack)) break;
        items[i] = stack_pop(stack);
        popped++;
    }
    return popped;
}

void stack_swap(Stack* stack)
{
    Data items[2];
    int n = pop_n(stack, items, 2);
    if (n < 2)
    {
        for (int i = n - 1; i >= 0; --i) stack_push(stack, items[i]);
        return;
    }
    stack_push(stack, items[0]);
    stack_push(stack, items[1]);
}

void stack_over(Stack* stack)
{
    Data items[2];
    int n = pop_n(stack, items, 2);
    if (n < 2)
    {
        for (int i = n - 1; i >= 0; --i) stack_push(stack, items[i]);
        return;
    }
    stack_push(stack, items[1]);
    stack_push(stack, items[0]);
    stack_push(stack, items[1]);
}

void stack_rot(Stack* stack)
{
    Data items[3];
    int n = pop_n(stack, items, 3);
    if (n < 3)
    {
        for (int i = n - 1; i >= 0; --i) stack_push(stack, items[i]);
        return;
    }
    stack_push(stack, items[1]);
    stack_push(stack, items[0]);
    stack_push(stack, items[2]);
}