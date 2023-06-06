/*
 * errors.c -- error reporting
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

#include "errors.h"

_Noreturn void error(char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    fprintf(stderr, "An error occurred: ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);

    exit(1);
}

_Noreturn void notImplemented() {
    error("You have not implemented this operation yet!");
}

_Noreturn void internalError() {
    error("Internal error!");
}

static _Noreturn void splError(int errorCode, Position position, const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    fprintf(stderr, "An error occurred:\n");
    if (position.line >= 0) fprintf(stderr, "Line %d, Column %d: ", position.line, position.column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);

    exit(errorCode);
}

_Noreturn void syntaxError(Position position, char *token) {
    splError(100, position, "syntax error. Unexpected token '%s'", token);
}

_Noreturn void undefinedType(Position position, Identifier *name) {
    splError(101, position, "undefined type %s", name->string);
}

_Noreturn void notAType(Position position, Identifier *name) {
    splError(102, position, "%s is not a type", name->string);
}

_Noreturn void redeclarationAsType(Position position, Identifier *name) {
    splError(103, position, "redeclaration of %s as type", name->string);
}

_Noreturn void mustBeAReferenceParameter(Position position, Identifier *name) {
    splError(104, position, "parameter %s must be a reference parameter", name->string);
}

_Noreturn void redeclarationAsProcedure(Position position, Identifier *name) {
    splError(105, position, "redeclaration of %s as procedure", name->string);
}

_Noreturn void redeclarationAsParameter(Position position, Identifier *name) {
    splError(106, position, "redeclaration of %s as parameter", name->string);
}

_Noreturn void redeclarationAsVariable(Position position, Identifier *name) {
    splError(107, position, "redeclaration of %s as variable", name->string);
}

_Noreturn void illegalAssignment(Position position, Type *left, Type *right) {
    char leftBuffer[1024];
    char rightBuffer[1024];
    typeAsString(leftBuffer, sizeof leftBuffer, left);
    typeAsString(rightBuffer, sizeof rightBuffer, right);
    splError(108, position, "illegal assignment '<%s> := <%s>'", leftBuffer, rightBuffer);
}

_Noreturn void illegalAssignmentToArray(Position position) {
    splError(109, position, "illegal assignment to array.");
}

_Noreturn void ifConditionMustBeBoolean(Position position, Type *actual) {
    char buffer[1024];
    typeAsString(buffer, sizeof buffer, actual);
    splError(110, position, "'if' test expression must be of type boolean: actual = %s", buffer);
}

_Noreturn void whileConditionMustBeBoolean(Position position, Type *actual) {
    char buffer[1024];
    typeAsString(buffer, sizeof buffer, actual);
    splError(111, position, "'while' test expression must be of type boolean: actual = %s", buffer);
}

_Noreturn void undefinedProcedure(Position position, Identifier *name) {
    splError(112, position, "undefined procedure %s", name->string);
}

_Noreturn void callOfNonProcedure(Position position, Identifier *name) {
    splError(113, position, "call of non-procedure %s", name->string);
}

_Noreturn void argumentTypeMismatch(Position position, Identifier *name, int argumentIndex, Type *expected, Type *actual) {
    char expectedBuffer[1024];
    char actualBuffer[1024];
    typeAsString(expectedBuffer, sizeof expectedBuffer, expected);
    typeAsString(actualBuffer, sizeof actualBuffer, actual);
    splError(114, position, "procedure %s argument %d type mismatch: expected = %s, actual = %s", name->string, argumentIndex, expectedBuffer, actualBuffer);
}

_Noreturn void argumentMustBeAVariable(Position position, Identifier *name, int argumentIndex) {
    splError(115, position, "procedure %s argument %d must be a variable", name->string, argumentIndex);
}

_Noreturn void tooFewArguments(Position position, Identifier *name) {
    splError(116, position, "procedure %s called with too few arguments", name->string);
}

_Noreturn void tooManyArguments(Position position, Identifier *name) {
    splError(117, position, "procedure %s called with too many arguments", name->string);
}

_Noreturn void undefinedVariable(Position position, Identifier *name) {
    splError(121, position, "undefined variable %s", name->string);
}

_Noreturn void notAVariable(Position position, Identifier *name) {
    splError(122, position, "%s is not a variable", name->string);
}

_Noreturn void indexingNonArray(Position position) {
    splError(123, position, "illegal indexing a non-array");
}

_Noreturn void indexingWithNonInteger(Position position) {
    splError(124, position, "illegal indexing with a non-integer");
}

_Noreturn void mainIsMissing() {
    splError(125, ERROR_POSITION, "procedure 'main' is missing");
}

_Noreturn void mainIsNotAProcedure() {
    splError(126, ERROR_POSITION, "'main' is not a procedure");
}

_Noreturn void mainMustNotHaveParameters() {
    splError(127, ERROR_POSITION, "procedure 'main' must not have any parameters");
}

_Noreturn void illegalApostrophe(Position position) {
    splError(99, position, "illegal use of apostrophe");
}

_Noreturn void illegalCharacter(Position position, char character) {
    if (iscntrl(character))splError(99, position, "Illegal character 0x%02x", (unsigned char) character);
    else splError(99, position, "Illegal character '%c'", character);
}

_Noreturn void registerOverflow() {
    splError(140, ERROR_POSITION, "There are not enough registers to run this program!");
}

static char const *binaryOperatorTostring(BinaryOperator operator) {
    switch (operator) {
        case ABSYN_OP_EQU:
            return "=";
        case ABSYN_OP_NEQ:
            return "#";
        case ABSYN_OP_LST:
            return "<";
        case ABSYN_OP_LSE:
            return "<=";
        case ABSYN_OP_GRT:
            return ">";
        case ABSYN_OP_GRE:
            return ">=";
        case ABSYN_OP_ADD:
            return "+";
        case ABSYN_OP_SUB:
            return "-";
        case ABSYN_OP_MUL:
            return "*";
        case ABSYN_OP_DIV:
            return "/";
    }
}

static char const *unaryOperatorTostring(UnaryOperator operator) {
    switch (operator) {
        case ABSYN_OP_UNARY_MINUS:
            return "-";
    }
}


_Noreturn void noSuchBinaryOperator(Position position, BinaryOperator operator, Type *left, Type *right) {
    char leftBuffer[1024];
    char rightBuffer[1024];
    typeAsString(leftBuffer, sizeof leftBuffer, left);
    typeAsString(rightBuffer, sizeof rightBuffer, right);

    splError(118, position, "There is no binary operator '<%s> %s <%s>'.", leftBuffer, binaryOperatorTostring(operator), rightBuffer);
}

_Noreturn void noSuchUnaryOperator(Position position, UnaryOperator operator, Type *right) {
    char rightBuffer[1024];
    typeAsString(rightBuffer, sizeof rightBuffer, right);

    splError(119, position, "There is no unary operator '%s <%s>'.", unaryOperatorTostring(operator), rightBuffer);
}