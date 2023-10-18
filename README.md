### Scripty Interpreter
A simple interpreter for a language I created titled Scripty.

### Functions
It has four core math functions, three printing, and three memory-based functions. A full list is available below.

<b>4 math functions</b>
- ADD
- SUB
- MULT
- DIV

<b>3 printing functions</b>
- PRINTS - Prints a string which is taken as an arg
- PRINTF - Prints the value of the line following it
-	PRINTV - Prints the value of a variable by name, which is taken as an arg
  
<b>3 memory functions</b>
-	MOV - Copies the value of a variable to another variable. If the variable exists, the value will be copied over. If it doesn't, it creates a new variable.
-	SETVAR - Sets a variable by name and has two args, a string of the name, and an integer as the value
-	SETVAR - Sets a variable by name to the value of the expression in the line following and has one arg, a string of the name

<b>1 misc function</b>
- REPEAT - Repeats a given number of times, taken as an arg.
