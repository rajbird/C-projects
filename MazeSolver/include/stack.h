/**
 * Rajbir Deol
 * 0918139
 */
#ifndef __RDEOL_STACK__
#define __RDEOL_STACK__

typedef struct StackType {
  Node * top;
} Stack;

/**
 * Pre-conditions: none
 * Post-conditions: A stack is created and initialized to empty
 */
Stack * create();

/**
 * Pre-conditions: An initialized stack
 * Post-conditions: The stack is destroyed and all associated memory is freed.
 */
void destroy(Stack * theStack);

/**
 * Pre-conditions: The stack is not full
 * Post-conditions: An element is added to the stack, the length is increased by one, 
 * the top of the stack points to the newly added element
 */
void push(Stack * theStack, int xCoor, int yCoor, char type);

/**
 * Pre-conditions: The stack is not empty
 * Post-conditions:The first (top) element of the stack is removed and returned.
 * The top of the stack is set to the successor of the removed element,
 * the length of the stack is decremented by one.
 */
void pop(Stack * theStack);

/**
 * it from the stack.
 * Pre-conditions: The stack is not empty
 * Post-conditions: Returns the element that is at the top of the stack but
 * does not remove that element from the stack.
 */
char peek(Stack * theStack);

#endif