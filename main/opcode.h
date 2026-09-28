#ifndef OPCODE_H
#define OPCODE_H

// Stack-base vm opcode
typedef enum
{
    HLT,
    PSH,
    ADD,
    SUB,
    MUL,
    PUT_LOCL,
    GET_LOCL,
    JMP,
    JNZ,
} OpCode;

#endif // OPCODE_H