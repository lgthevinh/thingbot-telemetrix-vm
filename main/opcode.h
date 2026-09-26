#ifndef OPCODE_H
#define OPCODE_H

// Stack-base vm opcode
typedef enum
{
    HLT,
    PSH,
    ADD,
    SUB,
    MUL
} OpCode;

#endif // OPCODE_H