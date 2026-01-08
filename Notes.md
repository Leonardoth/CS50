# Week 1 - C
## [Official Notes](https://cs50.harvard.edu/x/notes/1)

1.Razão para o #include <stdio.h>?
    -> stdio.h é uma 'header file', funcionalidade que veio com o sistema/linguagem.
    Caso esqueça essa header file, você não tem acesso a 'biblioteca'(libraries) de códigos que ja foram escritos para a linguagem por exemplo.
    NÃO É studio.h, é STANDARD IO, então stdio.h

2.Onde está a documentação de C?
    https://manual.cs50.io/ -> Lá está um modo simplificado (com direito a pesquisa)


3.Quando se refere a um unico character, utiliza-se apenas ' ao invés de " (que é utilizado para string)

4. Prototype of a function
    Quando você precisa utilizar uma função antes dela ser declarada, você pode colocar a primeira linha dela no inicio do arquivo.
    ex:
        void meow(void);
        função que utilizará a função meow
        definição da função meow.

5. Why functions start with int?
    ex:
        int main (void)

        Significa que o OUTPUT será INT e o input sera VOID

6. Correctness, design, style.
    Correctness -> The code works.
    Design -> The code works and is done in a smart way, good performance etc.
    Style -> The code is easy to read and is good to.

    check50 ->
    design50 ->
    style50 ->


7. Magic Numbers
    Não é boa pratica usar o mesmo numero repetidamente no seu codigo, caso um numero vá ser usado mais de uma vez pode ser interessante criar uma variável com ele
    Se alguém olhar rapidamente seu código, a pessoa vai saber o porquê você escolheu aquele número específico? É óbvio? Se não, provavelmente ele é um numero mágico.
    O ideal é evitar números sem explicação explicita, ex:
        Se no nosso código vamos falar sobre baralho, provavelmente usaremos 52 como o limite máximo de cartas, porém é considerado boa prática colocar esse numero numa variável,
        principalmente pois em outras situações caso esse numero mudasse, mudariamos apenas em um lugar, evitando bugs.




8. Declaration, assignment and initialization of variables
    Declaração é o ato de declarar uma variável. ex: int row;
    Assignment é designar um valor a uma variavel. ex: row = 3;
    Inicializar uma variável é quando se designa um valor na sua declaração. ex: int row = 3;

9. #define
    Define é um 'preprocessor directive' ou 'macro' para criar constantes simbolicas

    #define NAME REPLACEMENT

    Na hora que o programa é compilado #define substitui todos os NAME com REPLACEMENT.
    Se #include é similar a copy/paste, #define é similar a find/replace.
    Não se usa ";" no final da linha de #define
    É uma convenção usar ALL CAPS para as constantes simbolicas, para diferenciá-las de variáveis.


# Week 2 - Arrays
## [Official Notes](https://cs50.harvard.edu/x/notes/2)


What "compiling" actually is:
    Preprocessing - Anything that starts with #, is a 'pre-process directive'
    something that is in another file and we want on this one. Basically it 'copies and paste' the library at the top of your code.

    in a simples get input + print, after preprocessing:
        #include <cs50.h>
        #include <stdio.h>
        is replaced by:
        string get_string(string prompt);
        int printf(string format, ...);

    Compiling - Gets translated from c to assembly code
    Assembling - Converts assembly code to binary
    Linking - Adds the files together (i.e: hello.c, cs50.c, stdio.c)

Decompile - The act of trying to reverse the compiling

Debugging - Act of fingind errors and fixing them in your code.
    Common way is to print to debug, but a proper way is to use a debugging tool.
    For this course is debug50.
        When debugging is possible to see variables with strange values before execution ou assignment of value,
        that just means that is a 'garbage value', that variable may be using a space in the memory that was being
        used by another program and that value was used.


Arrays - A list of values of the same type. "Sequence of values contiguos in memory."

                ↱ size of array (3 elements)
    int scores[3];
    |     ↳ name of array
    type of valeus

scores[0] = 72; -> assign position and value inside the array

Const -> make a constant so nobody can change the variable later

    const int N = 3;

    It's common to name constant with CAPITAL LETTERS so it jumps to the reader. Similar to #define.
    It is a good idea to put your constants OUTSIDE the function so if you want to change it somewhere, its obvious
    where to change it.


Arrays as input in function -> In C, passing an array as input to a function, you also have to pass it's length in
another argument.

    e.g: float average (int length, int array[])

    array is in [] but it's length comes in another argument.

What if we try to access an array index that doesn't exist?

    In a string (an array of chars), the 'last' element is \0 (NUL), if our string has 3 characters, the string[3] (4th element)
    would be 0. It's how the machine understands that the string stops there.
    If we try to go further, we start to see 'garbage values' that could belong to the same program or be residue of
    other programs in the memory. The 'double quotes' imply the \0. That's why we do not use double quotes for a single
    char.

Declaring two variables at once in a loop

        for (int i = 0; i < strlen(s); i++)

    This way, everytime we loop, it'll call strlen again, even if the length of the string is not changing.

    A better way to do it would be:

        for (int i = 0, n = strlen(s); i < n; i++)

    This way strlen is called only once and used throughout the loop.
    As long as the variables are the same type, it can be done this way.

Command Line Arguments

    in the main function we can give it parameters instead of (void)

        int main(int argc, string argv[])

    that means argc (argument count) and argv (argument vector)

    Argv[0] will always be the name of the program.
    Argv[1] will be the first argument

Status codes

    0 means sucessfull execution
    Positive numbers means failure/error

See status code of last execution

    we can type in the command line
        echo $?
    this will print the status code of the last execution

# Week 3 - Algorithm
## [Official Notes](https://cs50.harvard.edu/x/notes/3)

### BIG O NOTATION - ASYMPTOTIC NOTATION

    The best way to measure the efficiency of an algorithm is not by time, but through STEPS count. How many steps does it take to get to the expected result.

        The "Big O notation":

        1. Constant Time (O(1))
            The algorithm's runtime remains the same regardless of the input size.
            Example: Accessing an element in an array by its index.
            Example: A function that always performs a fixed number of operations.

        2. Logarithmic Time (O(log n))
            The runtime grows logarithmically with the input size.
            Example: Binary search in a sorted array.
            This means the algorithm divides the problem size by two in each step.

        3. Linear Time (O(n))
            The runtime grows directly proportional to the input size.
            Example: Iterating through all elements in an array.
            Example: Finding the maximum value in an unsorted array.

        4. Linearithmic Time (O(n log n))
            The runtime grows slightly faster than linear time.
            Example: Merge sort, Quick sort (average case).
            This is a common complexity for efficient sorting algorithms.

        5. Quadratic Time (O(n²))
            The runtime grows proportionally to the square of the input size.
            Example: Nested loops iterating through all pairs of elements in an array.
            Example: Simple sorting algorithms like bubble sort or insertion sort.

        6. Exponential Time (O(2ⁿ))

            The runtime grows exponentially with the input size.
            Example: Recursive algorithms that explore all possible subsets of an input.
            This is generally considered inefficient for larger input sizes.

        7. Factorial Time (O(n!))
            The runtime grows very rapidly with the input size.
            Example: Algorithms that explore all possible permutations of an input.
            This is the least efficient complexity.


### Comparing strings

"==" Is not good for comparing strings, for that there's a function called **strcmp(s1,s2)** (<string.h>) where it compares two strings and returns:

    less than 0 if the s1 comes ASCII-tically(alphabetically but with ascii values) before the s2.

    0 if they're equal

    greater than 0 if the s1 comes after s2.


### Data structures
We can create data structures to be used through our code

Example:

    typedef struct
    {
            string name;
            string number;
    }
    person;

    int main(void)
    {
        person people[3];

        <!-- Hardcoded just for example purposes -->
        people[0].name = "David";
        people[0].number = "+1-617-495-1000";

        people[1].name = "John";
        people[1].number = "+1-949-468-2750";

        people[2].name = "Yuliia";
        people[2].number = "+1-949-617-495-1000";

        string name = get_string("Name ");

        <!-- This hardcoded 3 will be solved later -->
        for (int i = 0; i < 3; i++)
        {
            if (strcmp(people[i]name, name) == 0)
            {
                printf("Found: %s\n", people[i].number);
                return 0;
            }
        }
        printf("Not Found!\n");
        return 1;
    }

### Sorting
Sorting values of an array so it makes it possible to use binary search in an array. Good to sort an array, that will be searched multiple times.

Visualization:
https://www.cs.usfca.edu/~galles/visualization/ComparisonSort.html

0 -> first element

n - 1 -> last element

#### Selecion sort

    For i from 0 to n-1
        Find smallest number between numbers[i] and numbers[n-1]
        Swap smallest number with numbers[i]

n(n-1)/2 -> (n² - n)/2 -> n²/2 - n/2 -> n²/2 is the highest, has more impact in the algorithm.

**Complexity:**

**O(n²)** - We only care about the highest order, what really impacts the algorithm

Even in the lower bound an the theta bound, it would have same complexity because the algorithm doesn't count for already sorted arrays.


### Bubble Sort

    Repeat n-1 times
        <!-- n-2 is necessary so the 'left' side won't go to n-1 and look beyond the array -->
        For i from 0 to n-2
            If numbers[i] and numbers [i+1] out of order
                swap them

- Complexity


        Repeat n-1 times (n-1)
            <!-- n-2 is necessary so the 'left' side won't go to n-1 and look beyond the array -->
            For i from 0 to n-2 (n-1)
                If numbers[i] and numbers [i+1] out of order
                    swap them
                <!-- If there are no swaps on this pass, means that it's already sorted  -->
                If no swaps
                    Quit

(n-1) x (n-1)
n² - 1n - 1n + 1
n² - 2n + 1

**Complexity: O(n²)**

**Θ:**

**Ω:** O(n) -> needs at least one pass

### Recursive Algorithm

A function that calls itself.

Base cases -> Where the recursion stops, usually because we got the answer no matter what (example: true or false)

Recursive cases -> Where the function calls itself again (shrinking the problem each time)


Iteration:

        void draw(int n)
        {
            for (int i=0; i < n; i++)
            {
                for (int j = 0; j < i+1; j++)
                {
                    printf("#");
                }
                printf("\n");
            }
        }

Same function as recursive

    void draw(int n)
    {
        // base case
        if (n <= 0)
        {
            return;
        }
        draw(n-1);

        for (int i = 0; i < n; i++)
        {
            printf("#");
        }

        printf("\n");
    }

After reaching the 'base case', it'll rewind and do the other steps. As long as we 'take a bite' every step, and the problem gets smaller (to avoid infinite loops).

### Merge sort
Uses recursion to sort an array.

Pseudocode

    If only one number
        Quit
    Else
        Sort left half of numbers
        Sort right half of numbers
        Merge sorted halves


**Complexity: O(n log2 n)**

## Hexadecimal

Hexadecimal system, aka base-16, is a much more concise way to express the data on a computer's system.

    0 1 2 3 4 5 6 7 8 9 A B C D E F

Hexadecimal make this mapping easy because of a group of four binary digits (bits) is hable to have 16 different combinations, and each of those combinations maps to a single hexadecimal digit.

We can express long complex binary numbers in a more concise way with hexadecimal.

We usually distinguish hexadecimal to decimal with a 0x in front of it.

    Decimal     Binary      Hexadecimal
       0        0000            0x0
       1        0001            0x1
       2        0010            0x2
       3        0011            0x3
       4        0100            0x4
       5        0101            0x5
       6        0110            0x6
       7        0111            0x7
       8        1000            0x8
       9        1001            0x9
       10       1010            0xA
       11       1011            0xB
       12       1100            0xC
       13       1101            0xD
       14       1110            0xE
       15       1111            0xF

Hexadecimal numbers has place values much like binary(1,2,4,8...) and decimals (1,10,100,1000...) but they are in powers of 16.

               16² 16¹ 16^0
              256  16  1
    0x397 = 0x  3   9  7
    0xADC = 0x  A   D  C


To convert binary number to hexadecimal, group four binary digits (bits) together from right to left.

* Pad the leftmost group with extra 0 bits at the front if necessary.

Then use the chart above to convert those bits to something more concise.

Memory adresses in our system are usually represented in hexadecimals.


# Week 4 - Memory
## [Official Notes](https://cs50.harvard.edu/x/notes/4)

## RGB

    FFFFFF -> White
    000000 -> Black
    FF0000 -> Red (no blue, no green)
    00FF00 -> Green
    0000FF -> Blue

in hexadecimal F means 15, each color has 2 'digits'

      RED       GREEN       BLUE
    16¹ 16^0   16¹ 16^0    16¹ 16^0
     F   F      0    0      0    0

     16¹ * F -> 240
     16^0 * F -> 15
                255

     That sums 255, the max value achieved for a color in RGB.

## Symbols in C


    & -> Adress of operator
         Tells the adress of varible if used before it

    * -> Dereference operator
         Go to adress/location in memory


    int n = 50;

    this is the conventional way to write a pointer
         p is a pointer to the adress
    int *p = &n;
             get adress of n;


using it

    int main(void)
    {
        int n = 50;
        // here * means we are declaring the type of the variable p (pointer)
        int *p = &n;

        // This would give us the value stored in that adress
        // Here * means "go there"
        printf("%i\n", *p);

        // This would give us the adress
        printf("%p\n", p);

    }


## String

    // to use the 'string' type, we used #include <cs50.h> until now

    string s = "HI!";
    // in memory would look like
                H I ! \0

    s only stores the adress of the first character, the end being determined by \0.

    strings in C are called "char *" or "char star".

    char *s = "HI!";


## Defining Data types

You can create a shorthand ou rewrite names for data types

    // We used it like this
    typedef struct
    {
        string name;
        string number
    } person;

    // but it don't always have to be that complicated
    // under the hood string in <cs50.h> is like this:

    // typedef <old name> <new name>;
    typedef char *string;

    // this way we can create aliases for data types


    it is easier for structs too like

    struct car
    {
        int year;
        char model[10];
        char plate[7];
        int odometer;
        double engine_size;
    };

    // With this alias, we do not need to type struct car to create a car, we would need only car_t
    typedef struct car car_t;

    // the following code would have the same effect as calling typedef:
    struct car
    {
        int year;
        char model[10];
        char plate[7];
        int odometer;
        double engine_size;
    }
    car_t;

    // Above you can see the typedef after the struct, this creates the struct AND an alias for it. car_t being the alias.

    // before
    struct car newCar;

    // now
    car_t newCar;



## Point Arithmetic

    char *s = "HI!";
    printf("%c\n", *s);
    printf("%c\n", *(s+1));
    printf("%c\n", *(s+2));

This would print the same as

    char *s = "HI!";
    printf("%c\n", s[0]);
    printf("%c\n", s[1]);
    printf("%c\n", s[2]);

We can even use

    char *s = "HI!";
    // This would print I!
    printf("%s\n", s + 1);
    // This would print !
    printf("%s\n", s + 2);

    // Beyond the expected size, could bring HAVOC! Check next section!

Why we cant compare strings like int?

    void strcmp_example(void)
    {
        char *s = get_string("s: ");
        char *t = get_string("t: ");

        // because * is the adress of the first char, it compares the adresses
        if (s==t)
        {
            printf("Same\n");
        }
        else
        {
            printf("Different\n");
        }
    }

## Malloc (Dynamic Memory Allocation)


Malloc stands for Memory Allocation, it is useful to reserve space in memory but we'll have to free after using so we don't end up running out of memory.

To use Malloc we have to **#include <stdlib.h>**

**ALWAYS CHECK FOR NULL AFTER USING MALLOC!**

Example:

    void copy_example2(void)
    {
           // This will use malloc (memory allocation) to fix copy_example1

        char *s = get_string("s: ");

        // this will figure out the size of the string, add 1 for \0 and alloc memory
        char *t = malloc(strlen(s)+1);
        if (t == NULL)
        {
            // insuficcient memory
            return 1;
        }

        // we want to include the \0 so we'll use <= instead of <
        for (int i = 0, n = strlen(s); i <= n; i++)
        {
            t[i] = s[i];
        }

        // We avoid capitalizing if the user didn't type anything
        if(strlen(t) > 0)
        {
            t[0] = toupper(t[0]);
        }



        printf("s: %s\n", s);
        printf("t: %s\n", t);
        // You'll need to free the memory when you are not using it anymore
        free(t);
    }


when malloc doesn't have any memory available, it returns the ADRESS 0 (NULL) different from NUL(\0);




You can use malloc to allocate in heap memory or in stack memory

example:

    // #include <cs50.h>
    int x = get_int();

    // array of floats on the stack
    float stack_array[x];

    // array of floats on the heap
    float *heap_array = malloc(x * sizeof(float));

**Failing to return memory back to the system when you're finished with it results in a <u>memory leak</u>. You must free(  ) it.**

freeing memory allocated

    char *word = malloc(50 * sizeof(char));

    // do stuff with word

    // now we're done working with that block

    free(word);


**Important**

    for (int i = 0; i < 3; i++)
    {
        // Allocate node for number
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            // Important: Always free() previously alloc'd memory
            // n can be NULL in the third iteration, just closing
            // would leave the two previous memory allocated (memory leak)
            return 1;
        }
    ...




## **Three golden rules:**

1. Every Block of memory that you malloc() must subsequently be free()d.
2. Only memory that **you** malloc() should be free()d.
3. **Do not** free() a block of memory more than once.

## Tradeoff

  There is a tradeoff in being able to manipulate and access memory, you have to code defensively, trying to prevent any errors, checking the boundaries because you DO NOT want to touch memory that isn't yours. The computer WILL crash, freeze and so on.


## valgrind

Command Line program that allow you to look for memory related errors in your program.

in the following code we have a bug

    int main(void)
    {
        int *x = malloc(3 * sizeof(int));

        x[0] = 72;
        x[1] = 73;
        x[2] = 33;

        // You'll have to free the memory!
    }

so we'll use valgrind to detect it

    valgrind ./memory

result:

    ==32112== 12 bytes in 1 blocks are definitely lost in loss record 1 of 1
    ==32112==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==32112==    by 0x109151: main (memory.c:6)

It shows that we do not free memory in our code, memory leak.


fix:

    int main(void)
    {
        int *x = malloc(3 * sizeof(int));

        x[0] = 72;
        x[1] = 73;
        x[2] = 33;

        // You'll have to free the memory!
        free(x);
    }

after:

    valgrind ./memory

    ==34137== All heap blocks were freed -- no leaks are possible

## Garbage

Garbage values are values that are allocated but not set, for example you can have a

    int scores[1024];

 that will allocate 1024 values, but they'll all be garbage until you set them.


## Less

Useful tool for programs that have a large output, you can run

    // | is called "piping" you are piping the output of ./program to another program called less (linux)
    ./program | less

and the terminal will have only enough output to fill the screen, until you press space and it'll give another page of output.



## Use of memory

The computer uses the memory in a certain way

            | machine code |
            |    globals   |
            |     heap     |
            |              |
            |              |
            |              |
            |     stack    |


machine code -> when you run a program the computer automatically loads the machine program

globals -> global variables defined outside of main

heap -> If you use malloc in your code, that's from where it gets the memory, filling top to bottom. **Anything you create dynamically while your program is running (malloc)**

stack -> the stack grows upward, everytime you call a function/has local variables, they use the memory in stack. **Anything you give a name to (function, variable)** you can also use stack memory with malloc check [Malloc (Dynamic Memory Allocation)](#malloc-dynamic-memory-allocation)

When we define local variables, they are in one 'frame of memory' in stack, if we call another function, passing those variables as arguments, the function will be placed in another stack, in a different 'frame of memory'. As soon as swap returns, it's frame of memory goes away, and the variables of the main function were never changed because swap never had access to them. The values in the stack WILL STAY, there as GARBAGE, if a malicious actor has access to the memory he can access those values.

To work we would like to pass reference (pass by adress)

instead of

    void swap(int a, int b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

if we wanted to make changes to those values, we would pass by reference (pass the adress)

    // we specify that a is not a int but a ADRESS of an int, same with b
    void swap(int *a, int *b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

and when calling we would use

    swap(&x, &y);


### Overflow

Heap Overflow

Calling malloc too much would cause the 'heap' to grow until it overflows on stack

Stack Overflow

Calling functions too much would cause 'stack' to grow until overflow as well where functions overflow  over heap or over eachother

Buffer Overflow

A chunk of memory overflowing over another, for example allocating an array of 4 chars and trying to print the 5th, 6th...


## Crowdstrike

Security related software that crashed taking down very important systems with it.

    Oficial statement

    "The Content Interpreter expected only20 values. Therefore, the attempt to access the 21st value produced an out-of-bounds
    memory read beyond the end of the input data array and resulted in a system crash."


[Full Analysis of incident](https://www.crowdstrike.com/wp-content/uploads/2024/08/Channel-File-291-Incident-Root-Cause-Analysis-08.06.2024.pdf)


It was caused by the overflow, by touching memory that they shouldn't have, and brought the system to a crash.

**Anytime that we use malloc or pointers, always check if the value is not NULL and everything went correctly.**

## File Manipulation

This code will open a file as append ("a"), write to it (if it exists) and save it.

    // FILE is the type
    FILE *file = fopen("phonebook.csv", "a");
    // IMPORTANT to check if it was sucessfull
    if (file == NULL)
    {
        return 1;
    }

    char *name = get_string("name: ");
    char *number = get_string("number: ");

    fprintf(file, "%s, %s\n", name, number);
    fclose(file);




This code will copy everything from argv[1] to argv[2]

    #include <stdio.h>
    #include <stdint.h>

    // this replicates how windows treat a BYTE
    typedef uint8_t BYTE;

    int main(int argc, char *argv[])
    {
        // the "b" means to do it in binary, because we want to copy them without changing anything
        FILE *src = fopen(argv[1], "rb");
        FILE *dst = fopen(argv[2], "wb");

        BYTE b;

        // while fread iterates over the file src byte by byte
        while(fread(&b, sizeof(b), 1, src) != 0)
        {
            fwrite(&b, sizeof(b), 1, dst);
        }

        fclose(dst);
        fclose(src);
    }


# Week 5 - Data Structure
## [Official Notes](https://cs50.harvard.edu/x/notes/5)


A Queue -> FIFO -> First in First Out

    enqueue -> put something in the queue
    dequeue -> remove something (first) of the queue

    const int CAPACITY = 50;

    typedef struct
    {
        person people[CAPACITY]; // maximum capacity
        int size; // current size of queue
    } queue;


A Stack -> LIFO -> Last in First Out

    push -> push something in the top of the stack
    pop -> remove something from the top of the stack

    const int CAPACITY = 50;

    typedef struct
    {
        person people[CAPACITY]; // maximum capacity
        int size; // current size of queue
    } stack;



## Resizing Array


### Old way
    int main(void)
    {
        int *list = malloc(3 * sizeof(int));
        if (list == NULL)
        {
            return 1;
        }

        list[0] = 1;
        list[1] = 2;
        list[2] = 3;


        // Time passes and i want to add another number to my list

        int *tmp = malloc(4 * sizeof(int));
        if(tmp == NULL)
        {
            free(list); // ALWAYS free memory that you allocate
            // even if its inside an error!
            return 1;
        }

        for (int = 0; i < 3; i++)
        {
            tmp[i] = list[i];
        }

        tmp[3] = 4;

        free(list);

        list = tmp;

        // i would have to copy list to tmp and recreate everytime

    }


### With realloc


    int *list = malloc(3 * sizeof(int));
    if (list == NULL)
    {
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;


    // Time passes and i want to add another number to my list

    int *tmp = realloc(list, 4 * sizeof(int));
    if(tmp == NULL)
    {
        free(list); // ALWAYS free memory that you allocate
        // even if its inside an error!
        return 1;
    }

    tmp[3] = 4;

    list = tmp;

    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }


    free(list);
    return 0;
    // i would have to copy list to tmp and recreate everytime



### With Linked List

In a [linked list](#linked-list), for each element (node) there is a pointer that points to the next element, that can be anywhere in the memory until the last element (that points to nothing 0x0 or NULL);

    //              we have to add "node" here
    typedef struct node
    {
        int number;
        // to use "struct node" before its definition
        struct node *next;
    } node;

    int usingLinkedList(void)
    {
        // Memory for numbers
        node *list = NULL;

        // Build list
        for (int i = 0; i < 3; i++)
        {
            // Allocate node for number
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                // Important: Always free() previously alloc'd memory
                // n can be NULL in the third iteration, just closing
                // would leave the two previous memory allocated (memory leak)
                return 1;
            }
            n->number = get_int("Number: ");
            n->next = NULL;

            // Prepend node to list
            n->next = list;
            list = n;
        }

        // Free memory
        node *ptr = list;
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
        return 0;
    }

## Linked List

For each element (node) there is a pointer that points to the next element, that can be anywhere in the memory until the last element (that points to nothing 0x0 or NULL);

### Appending to a linked list

    int main(void)
    {
        // Memory for numbers
        node *list = NULL;

        // Build list
        for (int i = 0; i < 3; i++)
        {
            // Allocate node for number
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                // Important: Always free() previously alloc'd memory
                // n can be NULL in the third iteration, just closing
                // would leave the two previous memory allocated (memory leak)
                return 1;
            }
            n->number = get_int("Number: ");
            n->next = NULL;

            // If list is empty
            if (list == NULL)
            {
                // This node is the whole list
                list = n;
            }

            // If list has numbers already
            else
            {
                // Iterate over nodes in list
                for (node *ptr = list; ptr != NULL; ptr = ptr->next)
                {
                    // If at end of list
                    if (ptr->next == NULL)
                    {
                        // Append node
                        ptr->next = n;
                        break;
                    }
                }
            }
        }

        // Print numbers
        for (node *ptr = list; ptr != NULL; ptr = ptr->next)
        {
            printf("%i\n", ptr->number);
        }

        // Free memory
        node *ptr = list;
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
        return 0;
    }

### Sort Inserting in linked lists

    void unload(node *list);

    int main(void)
    {
        // Memory for numbers
        node *list = NULL;

        // Build list
        for (int i = 0; i < 3; i++)
        {
            // Allocate node for number
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                unload(list);
                return 1;
            }
            n->number = get_int("Number: ");
            n->next = NULL;

            // If list is empty
            if (list == NULL)
            {
                list = n;
            }

            // If number belongs at beginning of list
            else if (n->number < list->number)
            {
                n->next = list;
                list = n;
            }

            // If number belongs later in list
            else
            {
                // Iterate over nodes in list
                for (node *ptr = list; ptr != NULL; ptr = ptr->next)
                {
                    // If at end of list
                    if (ptr->next == NULL)
                    {
                        // Append node
                        ptr->next = n;
                        break;
                    }

                    // If in middle of list
                    if (n->number < ptr->next->number)
                    {
                        n->next = ptr->next;
                        ptr->next = n;
                        break;
                    }
                }
            }
        }

        // Print numbers
        for (node *ptr = list; ptr != NULL; ptr = ptr->next)
        {
            printf("%i\n", ptr->number);
        }

        // Free memory
        unload(list);
        return 0;
    }

    void unload(node *list)
    {
        node *ptr = list;
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }



## Trees

A tree is a two dimensional data structure.

### Binary search tree

Every node left child is lesser than the root, the right child is larger.


### Searching in a binary tree

    bool search(node *tree, int number)
    {
        if (tree == NULL)
        {
            return false;
        }
        else if (number < tree->number)
        {
            return search(tree->left, number);
        }
        sle if (number > tree->number)
        {
            return search(tree->right, number);
        }
        else
        {
            return true;
        }
    }


### It has to stay balanced

If you keep it balanced, it'll stay O(log n), it needs to have clever algorithms to keep it balanced and not turn in to a linked list after apending more elements.


## Dictionaries

The ability to associate words with definitions (key with values) is super useful. Keys are often strings and values can be strings, numbers even structures (person) and so on.

## Hash function

Takes input and produces output like any other fuction, it allows you to decide where some value goes in memory.


### Bucketize

Go from a large/infinite domain to a very finite and well defined range of values.

    The example was taking 52 cards and to sort them, first BUCKETIZE (literally put them into buckets) spliting them between symbols (spade, hearts, clubs, diamons).

    This way is easier to sort 13 cards 4 times, than 52 cards once.

You can build [hashtables](#hash-tables) using this method.

### Hash Tables
It is one way to implement a [dictionary](#dictionaries)

It is essentially the offspring of a array ad linked list together, a combination of the two.

    The example creates 26 squares, each one representing one letter of the alphabet.

    They will be used to organize names in a phonebook for example.

    So if we add luigi, would be in the lth place.
    But what if we have Link as well?
    We would have a colision, where two values would be in the same place, to solve this we link them


we can create an array of 26 pointers


    typedef struct node
    {
        char *name;
        char *number;
        struct node *next;
    } node;

    node *table[26];

    // The best way to organize them would be to look at the first
    // three letters
    // This would increase the number of buckets to 17000+

    #include <ctype.h>

    // unsigned is an optimization because the number wont be negative (between 0 and 25)
    unsigned int hash(char *word)
    {
        return toupper(word[0] - 'A');
    }

    // we could use similar code to look at the first three letters
    // and come up with a number between 0 and 17000+ and get a much larger hashtable instead

### downside

You reserve much more space upfront
Theoretically speaking it still O(n), there are scenarios where all of the names you'll insert will have the same first three letters.

### appeal

Hashtables are tecnically O(n) (O(n/k)) but in practice if you are clever about the hash function you use you can probably create an ideal [hash function](#hash-function) that prevents colision most of the time, making it O(1).

## Tries

A Trie is tree of arrays.
Gives us a true constant time O(1) but with a downside.

To use it to save phonenumbers

    typedef struct node
    {
        struct node *children[26];
        // if number is not NULL, is someone's actual number
        char *number;
    } node;

they are by definition O(1), dependent only of the size of the name of the person


### downside

Uses a massive amount of memory because uses each letter of the person's name and for each letter, a new array of 26 is created.
It's a tradeoff that by increasing the number of memory used in this case, you significantly decrease time.

# Week 6 - Python
## [Official Notes](https://cs50.harvard.edu/x/notes/6)

Python is an interpreted language (doesn't need to compile first).

[Oficial Documentation](https://docs.python.org/3)



Speller(previous week) in python:s

```
# Words in dictionary
words = set()


def check(word):
    """Return true if word is in dictionary else false"""
    return word.lower() in words


def load(dictionary):
    """Load dictionary into memory, returning true if successful else false"""
    with open(dictionary) as file:
        words.update(file.read().splitlines())
    return True


def size():
    """Returns number of words in dictionary if loaded else 0 if not yet loaded"""
    return len(words)


def unload():
    """Unloads dictionary from memory, returning true if successful else false"""
    return True
```


BLUR in python

```
# Blurs an image

from PIL import Image, ImageFilter

# Blur image
before = Image.open("bridge.bmp")
after = before.filter(ImageFilter.BoxBlur(1))
after.save("out.bmp")
```

Ways of doing Whats your name? in python

```
1. Concatenation

answer = get_string("Whats your name?")
// By concatenation we just add it to the string.
print("hello, " + answer)

```


```
2. Comma separated

answer = get_string("Whats your name?")
// By default python will concatenate (witha space) every comma separated value inside the print function.
print("hello,", answer)

```

```
3. Formated (Variable Interpolation)

answer = get_string("Whats your name?")
// We can format a string with placeholders using f before it.
print(f"hello, {answer}")

```


## Positional Parameters

When the **ORDER** of the parameters matter.

The problem is that some functions can be confusing what would result in simple mistakes that could've been avoided.

## Named Parameters

Some languages support **Named Parameters** where you can specify the parameters when calling a function, avoiding confusion.

example with the print function:

```
// * in this case **does NOT** have anything to do with pointers it just means that we can have 0 or any number of objects.

// we can overwrite the separator (sep), the end of the print (end) and so on.
print(*objects, sep=' ', end='\n', file=None, flush=false)
```

In python there's no difference on using single or double quotes. If you want to use " for example, you would have to start the string with ' and vice-versa.

## Incrementing

Python **DOES NOT** support the **counter++ (neither --)** increment, instead we should use **counter += 1**.


## Input

Python supports user input with the input() function, that's the equivalent of get_string() function from cs50.

The input default is string.

```
// user inputs 2
x = input("x: ")
x = "2"

// user inputs 2
x = int(input("x: "))
x = 2
```

## Conditionals

**Indentation MATTERS**, style50 considers 4 spaces.
```
if x < y:
    print("x is less than y")
elif x > y:
    print("x is greater than y")
else:
    print("x is equal to y")
```

## Comparing two strings

In python you can compare functions easier than C

"==" doesn't compare memory adresses

The equivalent of "||" in python is **"or"**

```
s = input("Do you agree")

if s == "Y" or s == "y"
    print("Agreed")
elif s == "N" or s == "n"
    print("Don't Agree")

```

option 2

```
s = input("Do you agree")

// Problem
// This could get very messy because the user can type yEs for example, the solution could just be converting the string to uppercase
if s in ["Y", "y", "yes", "Yes"]
    print("Agreed")
elif s in ["N", "n", "no", "No"]
    print("Don't Agree")

```

## Operators

### (*) Operator
In python we can use the * operator to multiply some action, for example:
```
print("?" * 4, end="")

will print "????"
```

### (+) Operator
Also used to concatenate, it's more like append, it joins things together

It can also be used to add an item to a list
example:

```
fruits = []

fruits += [banana]
```


## OOP

Object Oriented Programing give us the possibility to have functions related to the object, inside it. Much like [structures](#data-structures) in C.

When the function is "inside" a data type is called methods


```
// you can chain methods like this
s = input("Do you agree").lower()

if s in ["y", "yes"]
    print("Agreed")
elif s in ["n", "no"]
    print("Don't Agree")
```


## Copying strings

```
s = input("s: ")

t = s.capitalize()

// They are different adresses
print(s)
print(t)
```

## Loops

```
i = 0
while i < 3:
    print("meow")
    i += 1
```

```
// since "i" is never used, by convention we use "_" instead
for _ in range(3):
    print("meow")
```

You can loop for every character of a string for example
```
before = input("Before: ")
print("After: ", end="")
for c in before:
    print(c.upper(), end="")
print()
```

### Infinite loops
Is not uncommon to see infinite loops on python, where it breaks out of the loop as soon as the condition is met.

```
import cs50

while True:
    n = cs50.get_int("Number")
    if n > 0:
        break
```

### Else

If you don't breakout of a for loop, you can use else keyword to execute some other code. Example:

```
// this can be simplified by using a simple if else statement
"if name in phonebook"

for name in phonebook:
    if name == n:
        print("Found!")
        break
else:
    print("Not found!")
```

## Importing Functions

There are two ways of using a imported function

```
example 1

from cs50 import get_int

x = get_int("Number: ")


example 2

import cs50

x = cs50.get_int("Number: ")

```

This way it's harder to have conflicts and you can keep them in the scope instead of turning it into a "global variable".

## Functions

Functions are defined by the def keyword

Much like C, in Python we cannot call functions before they are defined, but the solution is a little different.

```
// This would give us an error

for _ in range(3):
    meow()

def meow():
    print("Meow")
```

What we usually do is to define a main function

```
def main():
    meow(3)

def meow(n):
    for _ in range(n):
        print("Meow")

// We call main at the end of our code, so all the functions are defined
main()

// The conventional way to call main is

if __name__ == "__main__":
    main()
```


## Truncation

Truncation is not a problem in python but floating imprecision still exists, if you are dealing with scientific computing problemas or complex ones you should use libraries that adresses those issues.

You can specify a number of decimals, like in the example:

```
x = int(input("x: "))
y = int(input("y: "))

z = x/y

// This would show us floating imprecision 0.3333333333333314829...
print(f"{z:.50f}")
```



You can simply divide 1/3 and will result in 0.33333333, using // instead of / will result in 0.


## Exceptions

We can use try and catch for errors if

```

// Tries to do something that can give an error
try:
    n = int(input("Input: "))
// Conventionally we only put inside TRY what CAN give an error, since print won't fail, we'll move it to else
//  print("Integer")

// Conditional based on the error "code"
except ValueError:
    print("Not Integer.")

// If there's not an error
else:
    print("Integer.")

```


## Command Line Arguments

We can use command line arguments in python using a library called sys

```
from sys import argv

// Python puts every argument in a list

if len(argv) == 2:
    print (f"Hello, {argv[1]}")
else:
    print("Hello, World")
```


## Exit Status

The sys library enable us to use argv and exit status on our code

```
import sys

// Python puts every argument in a list

if len(sys.argv) != 2:
    print("Missing command-line argument)
    sys.exit(1)

print (f"Hello, {sys.argv[1]}")
sys.exit(0)
```

You can use `echo $?` to see the exit status from the last code run


## Installing libraries

You can use PIP to install libraries that other people have created


# Week 7 - SQL
## [Official Notes](https://cs50.harvard.edu/x/notes/7)

## Useful LINKS
Keywords - https://www. w3schools.com/sql/sql_ref_keywords.asp


C -> Create data in a database (CREATE, INSERT)
R -> Read data from a database (SELECT)
U -> Update data in a database (UPDATE)
D -> Delete data in a database (DELETE, DROP)

Datas in database are stored in what we call Tables. Tables are like sheets in Google Sheets for example (data stored in lines and columns)


sqlite3 -> Is used in web applications, mobile applications, store the data in a file (locally or cloud)

the common way for creating a new table in the terminal
```
<!-- Creates the database and starts sqlite3 -->
sqlite3 favorites.db
```

```
<!-- Changes the mode to csv -->
.mode csv
```

```
<!-- Import csv file to database -->
.import favorites.csv favorites
```

```
<!-- Close sqlite3 -->
.quit
```

```
<!-- Opens the database -->
sqlite3 favorites.db
<!-- Give us the schema of the database -->
.schema

<!-- result of previous command -->
CREATE TABLE IF NOT EXISTS "favorites"(
"Timestamp" TEXT, "language" TEXT, "problem" TEXT);
```

```
<!-- Shows everything thats on the table favorites, SQL commands have to end with ; -->
SELECT * FROM favorites;
```

```
<!-- Select only the language column -->
SELECT language FROM favorites;
```

```
<!-- Other Funcions -->
AVG
COUNT
DISTINCT
LOWER
MAX
MIN
UPPER
...
```

```
<!-- How many rows -->
SELECT COUNT(*) FROM favorites;

<!-- output -->
+----------+
| COUNT(*) |
+----------+
| 313      |
+----------+
```

```
<!-- Only different languages -->
SELECT DISTINCT language FROM favorites;

<!-- output -->
+----------+
| language |
+----------+
| Python   |
| C        |
| Scratch  |
+----------+
```

```
<!-- How many different languages have -->
SELECT COUNT(DISTINCT language) FROM favorites;

<!-- output -->
+--------------------------+
| COUNT(DISTINCT language) |
+--------------------------+
| 3                        |
+--------------------------+
```

```
<!-- Count every row that has C as language in favorites.db -->
SELECT COUNT(*) FROM favorites WHERE language = 'C';

<!-- output -->
+----------+
| COUNT(*) |
+----------+
| 59       |
+----------+
```

```
<!--  -->
SELECT COUNT(*) FROM favorites WHERE language = 'C' AND problem = 'Hello, World';

<!-- output -->
+----------+
| COUNT(*) |
+----------+
| 8        |
+----------+
```

## Conventions
Stylistic we CAPTALIZE every keyword on SQL, to distinguish from SQL code to the table.
The convention is to use single quotes ' instead of double quotes ".

```
<!-- In this case we have a ' inside "Hello, It's me", we would use two single quotes where we want only one -->
<!-- We used parantheses to ensure the operators are handled in the priority we intended -->
SELECT COUNT(*) FROM favorites WHERE language = 'C' and (problem = 'Hello, World' OR problem = 'Hello, It''s Me');

<!-- output -->
+----------+
| COUNT(*) |
+----------+
| 8        |
+----------+
```

## Like
```
<!-- LIKE keyworld looks for something that looks like it, in this case % is the wildcard -->
SELECT COUNT(*) FROM favorites WHERE language = 'C' AND problem LIKE 'Hello, %';

<!-- output -->
+----------+
| COUNT(*) |
+----------+
| 8        |
+----------+
```

## Group By
```
<!-- Group by value -->
SELECT language, COUNT(*) FROM favorites GROUP BY language;

<!-- output -->
+----------+----------+
| language | COUNT(*) |
+----------+----------+
| C        | 59       |
| Python   | 243      |
| Scratch  | 11       |
+----------+----------+

<!-- Order in ascending order by default -->
SELECT language, COUNT(*) FROM favorites GROUP BY language ORDER BY COUNT(*);

<!-- output  -->
+----------+----------+
| language | COUNT(*) |
+----------+----------+
| Scratch  | 11       |
| C        | 59       |
| Python   | 243      |
+----------+----------+

<!-- Order in descending order -->
SELECT language, COUNT(*) FROM favorites GROUP BY language ORDER BY COUNT(*) DESC;

<!-- output -->
+----------+----------+
| language | COUNT(*) |
+----------+----------+
| Python   | 243      |
| C        | 59       |
| Scratch  | 11       |
+----------+----------+
```

## Alias

```
<!-- Same thing as before but giving an Alias (n) to the column -->
SELECT language, COUNT(*) AS n FROM favorites GROUP BY language ORDER BY COUNT(*) DESC;

<!-- output -->
+----------+-----+
| language |  n  |
+----------+-----+
| Python   | 243 |
| C        | 59  |
| Scratch  | 11  |
+----------+-----+
```

## Limit

```
<!-- Using LIMIT we can limi the result to only the most favorited language for example -->
SELECT language, COUNT(*) AS n FROM favorites GROUP BY language ORDER BY COUNT(*) DESC LIMIT 1;

<!-- output -->
+----------+-----+
| language |  n  |
+----------+-----+
| Python   | 243 |
+----------+-----+

```

## Insert

```
<!-- Inserting into the favorites table (column,...) VALUES(value, ...) -->
INSERT INTO favorites (language, problem) VALUES('SQL', 'Fiftyville');

<!-- result -->

| 10/15/2024 10:32:52 | Python   | Starting from Scratch |
| 10/15/2024 10:32:53 | C        | Recover               |
| NULL                | SQL      | Fiftyville            | <-
+---------------------+----------+-----------------------+
```

## Delete

```
<!-- You should REALLY use WHERE condition unless you know what you are doing -->
DELETE FROM favorites WHERE Timestamp IS NULL;

<!-- result -->

| 10/15/2024 10:32:52 | Python   | Starting from Scratch |
| 10/15/2024 10:32:53 | C        | Recover               |
+---------------------+----------+-----------------------+
```

## Update

```
<!-- This would overwrite EVERYTHING from the favorites table -->
<!-- Highly destructive, only way to reverse it is if we have a backup of the database to restore -->
UPDATE favorites SET language = 'SQL', problem = 'Fiftyville';

```

## Databases

### **Primary Key** -> Usually its an ID, a unique number to identify some show, person or other element.
### **Foreign Key** -> Its the appearence of a Primary Key in another table for the purpose for relating the table to the other.(show_id for shows)

Ex:
```
shows
id      TITLE
37732   Some show

id -> Primary key

ratings
show_id rate votes
37732   6.7  347

show_id -> FOREIGN KEY REFERENCES TO shows(id)
```

### **Table data**

```
INTEGER -> Normal numbers used for sums and so on
REAL -> Equivalent to floats (floating points values with decimal points)
NUMERIC -> Used for numbers with purpose (like years, dates, time)
BLOB -> Binary large object (raw 0s and 1s)
TEXT -> Strings
NOT NULL -> When something CANNOT be NULL
UNIQUE -> Values that cannot repeat
NULL -> Ausence of data
```

### Nested QUERIES

```
<!-- Resolves everything from inside the parenthesis THEN it treats the result as another table -->

SELECT * FROM shows WHERE id IN (SELECT show_id FROM ratings WHERE rating >= 6.0) LIMIT 10;



<!-- Another example using = -->
SELECT genre FROM genres WHERE show_id = (SELECT id FROM shows WHERE title = 'Catweazle');

```

## Join

```
<!-- Joins two or more tables together -->
SELECT * FROM shows JOIN ratings ON shows.id = ratings.show_id WHERE rating >= 6.0 LIMIT 10;

<!-- If we only wanted two specific columns -->
SELECT title, rating FROM shows JOIN ratings ON shows.id = ratings.show_id WHERE rating >= 6.0 LIMIT 10;
```

## One-to-Many
Type of relationship where one key of a table can be present multiple times in another.
Joining tables where there's a one to many relationship would repeat the side of "one" to match the "many" rows.

## Many-to-Many

```
>SELECT name FROM people WHERE id IN
...>(SELECT person_id FROM stars WHERE show_id =
...>(SELECT id FROM shows WHERE title = 'The Office' AND year = 2005));

<!-- You can also JOIN all tables like (slower) -->
> SELECT title FROM shows
...> JOIN stars ON shows.id = stars.show_id
...> JOIN people ON stars.person_id = people.id
...> WHERE name = 'Steve Carell';

<!-- OR -->
>SELECT title FROM shows, stars, people
...> WHERE shows.id = stars.show_id
...> AND people.id = stars.person_id
...> AND name = 'Steve Carell';

```

## INDEXING

We can create index inside the memory of our database that speeds up common searches like titles.

ex:

```
CREATE INDEX title_index ON shows (title);
```

This creates a tree-like structure (B-Tree) that speeds up any search (at the cost of memory RAM or HD space) when we use commands like

```
SELECT * FROM shows WHERE title = 'The Office';
```


## SQL in Python

example:

```
from cs50 import SQL

db = SQL("sqlite:///favorites.db")

favorite = input("Favorite: ")

<!-- We use ? in SQL to avoid SQL injection DO NOT USE formatted strings -->
rows = db.execute("SELECT COUNT(*) AS n FROM favorites WHERE language = ?", favorite)
row = rows[0]

print(row["n"])

```

## Race conditions / TRANSACTIONS

To avoid multiple servers updating the table at the same time and risking updating the same row for example, we have TRANSACTIONS:

example for updating number of likes in a instagram post:

```
db.execute("BEGIN TRANSACTION")
rows = db.execute("SELECT likes FROM posts WHERE id = ?", id)
likes = rows[0]["likes"]
db.execute("UPDATE posts SET likes = ? WHERE id = ?", likes +1, id)
db.execute("COMMIT")

```

## SQL Injection

Similar to prompt injections (and came way before), someone uses the expected input to escape and execute commands/find vulnerabilities in the code.


example of vulnerable code for login
```
<!-- it checks if there is an user (username) with this password -->
rows = db.execute(f"SELECT * FROM users WHERE username='{username}' AND password = '{password}'")
if rows:
    login as username
    ...

<!-- The user with malicious intent can ESCAPE the password check as it follows
In this case '-- the first ' would end the email as expected and everything after -- would be ignored -->

rows = db.execute(f"SELECT * FROM users WHERE username='admin@truemail.com'--' AND password = '{password}'")

<!-- The query would run as it was like -->

rows = db.execute(f"SELECT * FROM users WHERE username='admin@truemail.com')

<!-- This would result in a row where username = admin@truemail.com and would login (if rows) -->
```

# Week 8 - HTML, CSS, JavaScript
## [Official Notes](https://cs50.harvard.edu/x/notes/8)

 ## IP
Protocol to handle adresses of computers in the internet (sender, receiver)
 ```
  0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |Version|  IHL  |Type of Service|          Total Length         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |         Identification        |Flags|      Fragment Offset    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |  Time to Live |    Protocol   |         Header Checksum       |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                       Source Address                          |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Destination Address                        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Options                    |    Padding    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                    Example Internet Datagram Header

 ```

 ## TCP
 Protocol to keep track of sequence numbers, where the receiver can know the order and if there's information missing (ex: 1 of 4, 2 of 4...)

It also define convention called "Ports".

## Ports
Unique numeric identifiers for specific internet service

```
Example:

 80 HTTP
443 HTTPS

```

```
  0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |          Source Port          |       Destination Port        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                        Sequence Number                        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Acknowledgment Number                      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |  Data |           |U|A|P|R|S|F|                               |
   | Offset| Reserved  |R|C|S|S|Y|I|            Window             |
   |       |           |G|K|H|T|N|N|                               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |           Checksum            |         Urgent Pointer        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Options                    |    Padding    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                             data                              |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

                            TCP Header Format

```

## DNS - Domain Name System

Domain Name System Servers -> Servers that translates domain names to ip adresses, so humans can type more user friendly versions of website names for example typing google.com instead of the IP adress

```

 What the user types         | What it gets translated to

 Fully Qualified Domain Name |  IP Address

```

## DHCP - Dynamic Host Configuration Protocol

Gives your computer an IP adress when it boots up.

Also tells your computer what DNS to use.
Also tells you the IP adress of your default gateway (router that you should use by default)

## HTTP - Hyper Text Transfer Protocol

Protocol that governs how web browsers and web servers comunicate

## HTTPS - Hyper Text Transfer Protocol Secure

Secure version of HTTP, uses encryption, scrambles the data to ensure that when you are visiting a webpage you and only you can see that webpage and no one in-between actually know what you are looking at beyond the name/ip adress of the website itself.

## Host Name
In the context of website adress, the host name is the "www" or "web" that comes before it's adress. Usually we don't need to type it anymore, the DNS finds the right host name.

## Top Level Domain

You'll pay to use it in your adress, for example .ai is a country code, usually used by websites that implicates the use of artificial intelligence.

.com - Comercial
.gov - Government
.org - Organization
.br  - Brazil
.jp  - Japan


## Curl
Connect URL

in the terminal `curl -I https://www.harvard.edu/`

output
```
HTTP/2 200
server: nginx
date: Sat, 27 Sep 2025 03:35:21 GMT
content-type: text/html; charset=UTF-8
vary: Accept-Encoding
host-header: a9130478a60e5f9135f765b23f26593b
link: <https://www.harvard.edu/wp-json/>; rel="https://api.w.org/"
link: <https://www.harvard.edu/wp-json/wp/v2/pages/6392>; rel="alternate"; title="JSON"; type="application/json"
link: <https://www.harvard.edu/>; rel=shortlink
x-rq: dca5 181 253 80
accept-ranges: bytes
x-cache: HIT
cache-control: max-age=300, must-revalidate
```

How does a website work when we **Do NOT** type www. for example.

in the terminal `curl -I http://harvard.edu/`

```
<!-- 301 means "moved permanently" -->
HTTP/1.1 301 Moved Permanently

Server: nginx
Date: Sat, 27 Sep 2025 03:40:09 GMT
Content-Type: text/html
Content-Length: 162
Connection: keep-alive

<!-- New location (https) -->
Location: https://harvard.edu/
```

in the terminal `curl -I https://harvard.edu/`

```
<!-- Still tell us 301 -->
HTTP/2 301

server: nginx
date: Sat, 27 Sep 2025 03:41:05 GMT
content-type: text/html; charset=utf-8

<!-- Final location -->
location: https://www.harvard.edu/
x-rq: dca5 181 253 80
x-cache: HI
```

in the terminal `curl -I https://www.harvard.edu/`
Then we'll get the 200.

```
HTTP/2 200
server: nginx
date: Sat, 27 Sep 2025 03:42:34 GMT
content-type: text/html; charset=UTF-8
vary: Accept-Encoding
host-header: a9130478a60e5f9135f765b23f26593b
link: <https://www.harvard.edu/wp-json/>; rel="https://api.w.org/"
link: <https://www.harvard.edu/wp-json/wp/v2/pages/6392>; rel="alternate"; title="JSON"; type="application/json"
link: <https://www.harvard.edu/>; rel=shortlink
cache-control: max-age=300, must-revalidate
accept-ranges: bytes
x-cache: HIT
x-rq: dca5 181 253 80

```


### Common Codes

```
200 - OK
301 - Moved Permanently
302 - Found
304 - Not Modified
307 - Temporary Redirect
401 - Unauthorized
403 - Forbidden
404 - File not found
418 - I'm a Teapot
500 - Internal Server Error
503 - Service Unavailable

```

## HTML Structure


```
<!-- Document type declaration -->
<!DOCTYPE html>


<!-- Beginning of html document (tag: html) and the page will be in english (lang="en"), the language helps in case where the user got translators enabled, google translate and so on -->
<html lang="en">

<!-- "Top of the page" -->
    <head>
    <!-- Title of page (Shows in tab name) -->
        <title>
        hello, title
        <!-- close tag/end tag to close the title -->
        </title>
    <!-- Ends the head of the page -->
    </head>
    <!-- Starts the body  -->
    <body>
        hello, body
    </body>

<!-- Closing of html, doesn't need to repeat properties in the opening tag -->
</html>
```

## HTML Tree
![HTML Tree](Images/htmlTree.png)

This is what called DOM (Document Object Model), this is what the browser is doing in memory to create nodes and pointers that somehow represents this and to know what to represent on the screen.

## Videos in a page

```
<body>
    <!-- video is the tag that wraps the <source> (media) -->
    <!-- some properties won't need a value, the simple fact that they are in the tag means that they are true -->
    <!-- controls property enables the showing of controls (pause, volume) for the user -->
    <!-- muted means that by default the video will be muted -->
    <video controls muted>
        <!-- Media is the src of the <source> tag with it's properties  -->
        <!-- src being the location of the media -->
        <!-- type defines the type of media being displayed by the source -->
        <source src="video.mp4" type="video/mp4">
    </video>
</body>
```

## Searching from our page!

```
<body>
    <!-- We determine which action the for will have -->
    <!-- in this case whe the user clicks submit we'll GET https://www.google.com/search -->
    <form action="https://www.google.com/search" method="get">

        <!-- Although there is no order for tag properties, it is smart to keep them in alphabetical order, so it's easier to check if something is missing -->
        <!-- autofocus makes so that on page loading the input box is already selected, the user can start typing right away -->
        <!-- the property "name" defines the KEY that will be sent to google in the get method the result will be https://www.google.com/search?q=VALUE_OF_INPUT -->
        <!-- type "search" is just one type of input where the user can type and have an X to delete the input -->
        <input autocomplete="off" autofocus placeholder="Query!" name="q" type="search">
        <!-- Value sets what's writen inside of it -->
        <!-- type "submit" means that when this button is clicked, the form will execute it's action -->
        <input type="submit" value="Google Search">
    </form>
    </body>
```


## Regex

A pattern that lets you match text/filter inputs

![alt text](Images/Regex.png)
![alt text](Images/Regex2.png)

### Valid email adress
```
<form>
    <!-- Patterne explained:

    Quick and dirty expression just to explain the basics

    . -> any character
    + -> one or more times
    . -> any character
    + -> one or more times
    \. -> literal "."
    edu -> together with the literal dot forms ".edu"

    Basically this is a regex to match any email that ends with .edu
    The best bet to check if the user is inputing an email is to use type="email".
     -->
    <input autocomplete="off" autofocus name="email" placeholder="Email" pattern=".+@.+\.edu" type="email">
    <button>Register</button>
</form>
```

### Valid phone number (US)


```
<!-- a pattern to match xxx-xxx-xxxx phone numbers -->
... pattern="\d{3}=\d{3}-d{4}"
```


### NEVER TRUST user input

The user can simply inspect elements and delete the 'pattern' expected, fill the form and send it anyway.


## LINK:  [Validate Your Html](validator.w3.org)


## CSS : Cascading Style Sheets

It's a language (not a programing one!) that let us stylize our page.

To link a stylesheet to our page, in our header we'll have to use

href refers to the name of the file

rel refers to the relationship to the file to the page

`<link href="styles.css" rel="stylesheet">`


## Frameworks

Frameworks are libraries writen by someone else that makes it easier to frame/structure your own project.

## Boostrap

Bootstrap is a popular framework that makes it easier to style your project.

To use Bootstrap in your page you'll have to link the file just like any other css file but the href will be the link that is provided by Bootstrap and use the rel="stylesheet" just like any other css file.

`<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap@4.1.3/dist/css/bootstrap.min.css"`

In this case "min" just means that white space was removed from the file to make it smaller.

Then you'll just add the classes that they put in their documentation.

[Link to Boostrap Documentation](https://getbootstrap.com/docs/4.1/getting-started/introduction)



## Javascript

A programing language, used by the page and executed in the browser to give the page/website funcitonalities and features.

Usually client-side but can be run in the server side too.

### Variables

```
let counter = 0

counter += 1;
<!-- or -->
counter++;

```


### Loops
```
for (let i = 0; i < 10; i++)
{

}
```

### Using javascript code

To use javascript in your page you'll have some options:

```
<!-- 1. using a script tag -->
<script>
    console.log("Hello World")
</script>

<!-- 2. Import from a file (even when used with source attribute you'll use a closing tag) -->
<!-- This can be done in the head or inside the body of the page after all the content (order of operations matter!) -->
<head>
    <script src="script.js"></script>
</head>

<!-- This can also be like -->

<head>
    <script src="https://somesite.com/script.js"></script>
</head>
```


### Events

In javascript you'll have a LOT of events that can be watched so they can trigger code execution, making your page/website react to the user input.

Some events are:

![alt text](Images/Events.png)



hello.html
```
<script>
        function greet(){
            <!-- uses the same selector as CSS -->
            let name = document.querySelector('#name').value;
            alert('hello, ' + name);
        }
    </script>
    <title>
        Hello
    </title>
    <body>
        <!-- on submit executes the function AND "return false" prevents default behaviour (sending to the server) -->
        <form onsubmit="greet(); return false;">
            <input autocomplete="off" autofocus id="name" name="name" placeholder="Name" type="Text">
            <input type="Submit">
        </form>
    </body>
```

the previous method mixes html with javascript, to keep them separated we can do the following:


```
    <body>
        <!-- on submit executes the function AND "return false" prevents default behaviour (sending to the server) -->

        <form onsubmit="greet(); return false;">
            <input autocomplete="off" autofocus id="name" name="name" placeholder="Name" type="Text">
            <input type="Submit">
        </form>

        <script>

            <!-- how to prevent behaviour? -->
            <!-- anytime a function is triggered by an event, the event is passed to the function -->

            function greet(event){
                let name = document.querySelector('#name').value;
                alert('hello, ' + name);
                event.preventDefault();
            }

            let form = document.querySelector('form');
            <!-- we add an event listener, be careful to not use () after the function, to not call it instantly -->

            form.addEventListener('submit', greet);


    </script>
    </body>
```


### Anonymous function

If a function will be used only in one place, there's no need to name them

example:

```
            <!-- We won't call greet anymore in our code, so the only time it appears can be a anonymous function, it'll have the same effect that it had above -->

            let form = document.querySelector('form');
            form.addEventListener('submit', function(event){
                <!-- we took out the name variable too! -->
                alert('hello, ' + document.querySelector('#name').value);
                event.preventDefault();
            });
```


### Order of operations

The code above if put inside the head, the javascript will try to add event listener way before the element "form" is created, giving us an error.

fixes:

1. Putting the script at the end of the body, so it'll load after the page is loaded.
2. If it's an external script (has src attribute) add a property "defer" to the script tag, making it wait to load the script only after the page is already loaded.
3. Add an event listener to wait until the page is loaded to add the form event listener

```
    document.addEventListener('DOMContentLoaded', function () {
        let form...
        ...
        ...
        ...
    })
```


# Week 9 - Flask

## [Official Notes](https://cs50.harvard.edu/x/notes/9)

## Routes

`https://www.example.com/route?key=value`


```
When you search cats on google you send it to the backend:

GET /search?q=cats HTTP/2
Host: www.google.com

```

Flask handles those requests on the serve side to know what to send


## Flask

Python microframework that handles the backend

we'll use `flask run` instead of http-server

we'll need two files

```
app.py
requirements.txt
```

simple flask application in app.py:

```
# Says hello to world by returning a string of text

from flask import Flask, render_template, request

app = Flask(__name__)


@app.route("/")
def index():
    return "hello, world"
```


requirements.txt
```
<!-- List of dependencies -->
Flask
```

So when someone is ruinning the flask app for the first time, they could simply

`pip install -r requirements.txt`


by simply running `flask run` i'll detect the app.py and when accessing the route '/' it'll give us a blank page with "hello, world".

We can also deliver HTML (simple example):

```
# Says hello to world by returning a string of HTML

from flask import Flask, render_template, request

app = Flask(__name__)


@app.route("/")
def index():
    return '<!DOCTYPE html><html lang="en"><head><title>hello title</title></head><body>hello, body</body></html>'
```


Improving our application, we can also serve HTML based upon templates by creating a folder called templates and creating a file called index.html with the following code within that folder:

```
<!DOCTYPE html>

<html lang="en">

    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>hello</title>
    </head>

    <body>
        hello, from file
    </body>

</html>
```

we would change the app.py as it follows:

```
# Says hello to world by returning a string of HTML

from flask import Flask, render_template

app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html")

```

This is exactly how a server can associate a route ("/") to a file "index.html", instead of using `/index.html`


## Using dynamic values

```
<!DOCTYPE html>

<html lang="en">

    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>hello</title>
    </head>

    <body>
        <!-- placeholder in this case is a variable that will be replaced by the server -->
        hello, {{ placeholder }}
    </body>

</html>
```

app.py
```
# Uses request.args.get

from flask import Flask, render_template, request

app = Flask(__name__)


@app.route("/")
def index():
<!-- the second parameter is a fallback/default value, in case the 'name' is missing, to avoid 'bad request' error -->
    name = request.args.get("name", "world")
    return render_template("index.html", placeholder=name)
```

by adding `/?name=Leo` to our base URL we get

```
hello, Leo
```


## Using forms to fill the request

index.html
```
<!DOCTYPE html>

<html lang="en">

    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>hello</title>
    </head>

    <body>
        <form action="/greet" method="get">
            <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
            <button type="submit">Greet</button>
        </form>
    </body>

</html>
```

greet.html
```
<!DOCTYPE html>

<html lang="en">

    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>hello</title>
    </head>

    <body>
        hello, {{ name }}
    </body>

</html>

```


app.py
```
from flask import Flask, render_template, request

app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html")

@app.route("/greet")
def greet():
    return render_template("greet.html", name=request.args.get("name", "world"))

```

## File tree

```
app.py
requirements.txt
<!-- conventionally static will hold javascript, images and so on -->
static/
templates/
```

## Avoiding Repetition

It's common that multiple pages would use the same data (title, icon, head tag...) and for that we have a solution so we won't keep repeating the same thing over and over:

templates/layout.html
```
<!DOCTYPE html>

<html lang="en">

    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>hello</title>
    </head>

    <body>
        {% block body%}{% endblock %}
    </body>

</html>

```

index.html
```
{% extends "layout.html" %}

{% block body %}

    <form action="/greet" method="get">
        <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
        <button type="submit">Greet</button>
    </form>

{% endblock %}
```

greet.html
```
{% extends "layout.html" %}

{% block body %}

    hello, {{ name }}

{% endblock %}

```


## Request Methods

You can imagine scenarios where it is not safe to utilize get, as usernames and passwords would show up in the URL.

To use POST requests we do the following changes:

index.html
```
<!-- in html the method is all lowercase -->
<form action="/greet" method="post">
```

app.py
```
<!-- methods can support more than one method -->
@app.route("/greet", methods=["POST"])
def greet():
    return render_template("greet.html", name=request.args.get("name", "world"))
```

### GET key/value pairs are stored in request.args
### POST key/value pairs are stored in request.form


## Using only one route

app.py

```

from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        return render_template("greet.html", name=request.form.get("name", "world"))
    return render_template("index.html")
```

index.html
```
<!-- replaces /greet with / -->
<form action="/" method="post">
```

## Conditions inside template


greet.html
```
{% extends "layout.html" %}

{% block body %}
<!-- normal HTML will collapse multiple white spaces into one for the user -->
    hello,
    {% if name %}
        {{ name }}
    {% else %}
        world
    {% endif %}


{% endblock %}

```

## Loops inside HTML

app.py
```
from flask import Flask, render_template, request

app = Flask(__name__)

SPORTS = [
    "Basketball",
    "Soccer",
    "Ultimate Frisbee",
]


@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)
```


index.html
```
{% extends "layout.html" %}

{% block body %}

<h1> Welcome! Register for Frosh IMs</h1>
<form action="/register" method="post">
    <input name="name" placeholder="Name" required type="text">
    <select name="sport" required>
        <option value="" disabled selected>Sport</option>
        {% for sport in sports %}
            <option value="{{sport}}">{{sport}}</option>
        {% endfor %}
    </select>
    <button type="submit">Register</button>

</form>
{% endblock %}
```

this can be done as other elements such as radial buttons

index.html
```
{% extends "layout.html" %}

{% block body %}

<h1> Welcome! Register for Frosh IMs</h1>
<form action="/register" method="post">
    <input name="name" placeholder="Name" required type="text">
    {% for sport in sports %}
        <input name="sport" type="radio" value="{{sport}}"> {{sport}}
    {% endfor %}
    <button type="submit">Register</button>
</form>
{% endblock %}
```


## Server-side validation

NEVER trust what the humans are sending to the server and never rely on client-side validation alone, anyone can disable those validations.

app.py
```
from flask import Flask, render_template, request

app = Flask(__name__)

SPORTS = [
    "Basketball",
    "Soccer",
    "Ultimate Frisbee",
]


@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register():
    if not request.form.get("name") or request.form.get("sport") not in SPORTS:
        return render_template("failure.html")
    return render_template("success.html")

```

## Errors

app.py
```
from flask import Flask, render_template, request

app = Flask(__name__)

SPORTS = [
    "Basketball",
    "Soccer",
    "Ultimate Frisbee",
]


@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register():
    name = request.form.get("name")
    if not name:
        return render_template("error.html", message= "Missing Name")
    sport = request.form.get("sport")
    if not sport:
        return render_template("error.html", message= "Missing Sport")
    if sport not in SPORTS:
        return render_template("error.html", message= "Invalid Sport")

    return render_template("success.html")
```


error.html
```
{% extends "layout.html" %}


{% block body %}
    <h1>Failed to register: {{message}}</h1>
{% endblock %}
```


## Saving in memory (server)

This is a simple way of doing it (and not a correct one!) since there could be multiple people with the same name (and they would overwrite each other) and it assumes that the server has enough memory and will keep running.


app.py
```

from flask import Flask, render_template, request

app = Flask(__name__)

SPORTS = [
    "Basketball",
    "Soccer",
    "Ultimate Frisbee",
]

REGISTRANTS = {}

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register():
    name = request.form.get("name")
    if not name:
        return render_template("error.html", message= "Missing Name")
    sport = request.form.get("sport")
    if not sport:
        return render_template("error.html", message= "Missing Sport")
    if sport not in SPORTS:
        return render_template("error.html", message= "Invalid Sport")

    REGISTRANTS[name] = sport

    return render_template("success.html")


@app.route("/registrants")
def registrants():
    return render_template("registrants.html", registrants=REGISTRANTS)
```


registrants.html
```
{% extends "layout.html" %}

{% block body %}
    <h1> Registrants </h1>
    <table>
        <thead>
            <tr>
                <th>Name</th>
                <th>Sport</th>
            </tr>
        </thead>
        <tbody>
        {% for registrant in registrants %}
        <tr>
            <td>{{registrant}}</td>
            <td>{{registrants[registrant]}}</td>
        </tr>
        {% endfor %}
        </tbody>
    </thead>

{% endblock %}
```

## Saving in a database

For this example we have a sqlite3 db empty with one table (registrants) and only 3 columns (id, name, sport):


appp.py
```
<!-- We import SQL -->
from cs50 import SQL
from flask import Flask, render_template, request

app = Flask(__name__)

<!-- We connect to the db -->
db = SQL("sqlite:///froshims.db")

SPORTS = [
    "Basketball",
    "Soccer",
    "Ultimate Frisbee",
]



@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register():
    name = request.form.get("name")
    if not name:
        return render_template("error.html", message= "Missing Name")
    sport = request.form.get("sport")
    if not sport:
        return render_template("error.html", message= "Missing Sport")
    if sport not in SPORTS:
        return render_template("error.html", message= "Invalid Sport")

<!-- We insert into the db after the validation using placeholders (?,?) -->
    db.execute("INSERT INTO registrants (name, sport) VALUES (?,?)", name, sport)

    return render_template("success.html")


@app.route("/registrants")
def registrants():
<!-- We get the result as list of dictionaries ex: 1 = {name: "david", sport: "soccer"}-->
    registrants = db.execute("SELECT name, sport FROM registrants")
    return render_template("registrants.html", registrants=registrants)
```


registrants.html
```
{% extends "layout.html" %}

{% block body %}
    <h1> Registrants </h1>
    <table>
        <thead>
            <tr>
                <th>Name</th>
                <th>Sport</th>
            </tr>
        </thead>
        <tbody>
        {% for registrant in registrants %}
        <tr>
            <td>{{registrant.name}}</td>
            <td>{{registrant.sport}}</td>
        </tr>
        {% endfor %}
        </tbody>
    </thead>

{% endblock %}

```

Now it's saved even if the server loses power!

## MVC (Architecture) - Model, View, Controller

* Controller -> app.py (controls everything about the application, contains the business logic)
* View -> What the users see (everything in the templates folder for example)
* Model -> How data is stored and manipulated (Database/storage of data)


## Cookies and Sessions

Cookies are small files that are stored on your computer such tath your computer can communicate with the server and effectively say, "I'm an authorized user that has already logged in". This authorization through this cookie is called a session.

when successfully logging in, the server can send a response like
```
HTTP/2 200
Content-Type: text/html
<!-- value in this case would be a random number/string of characters+numbers -->
Set-Cookie: session=value
```

with the cookie set, when the browser sends a request to the server it'll have the cookie on the header so the server knows it's already authorized
```
GET / HTTP/2
Host: accounts.google.com
Cookie: session=value
```

Cookies can be informations that the website uses to 'track' your clicks, such as username, email or even for advertisement purposes.

## Simple Login system

app.py
```
<!-- we imported session (to be used in session["name"] and session.clear() and redirect (to redirect (code 301 or so) after the login/logout) -->
from flask import Flask, render_template, request, session, redirect
from flask_session import Session

app = Flask(__name__)

<!-- This means that the session won't persist when the user quits the browser -->
app.config["SESSION_PERMANENT"] = False
<!-- this uses files locally on the server to keep track of sessions -->
app.config["SESSION_TYPE"] = "filesystem"

<!-- this initiates the session on server -->
Session(app)


@app.route("/")
def index():
    <!-- gets if theres a name on session -->
    return render_template("index.html", name=session.get("name"))

@app.route("/login", methods=["GET","POST"])
def login():
    if request.method == "POST":
        <!-- sets a name for session -->
        session["name"] = request.form.get("name")
        <!-- redirects to home page after login -->
        return redirect("/")
    return render_template("login.html")

@app.route("/logout")
def logout():
    <!-- clears the session -->
    session.clear()
    <!-- redirects to home page after logout -->
    return redirect("/")
```

index.html
```
{% extends "layout.html" %}

{% block body %}

    {% if name %}
        You are logged in as {{name}}. <a href="/logout">Log out</a>
    {% else %}
        You are NOT logged in. <a href="/login">Log In</a>
    {% endif %}

{% endblock %}
```

login.html
```
{% extends "layout.html" %}

{% block body %}
    <form action="/login" method="post">
        <input autocomplete="off" autofocus name="name" placeholder="Name" type="text">
        <button type="submit">Log In</button>
    </form>

{% endblock %}
```



## Shopping Cart


We examined the following code for store in app.py. The following code was shown:

app.py
```
from cs50 import SQL
from flask import Flask, redirect, render_template, request, session
from flask_session import Session

# Configure app
app = Flask(__name__)

# Connect to database
db = SQL("sqlite:///store.db")

# Configure session
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)


@app.route("/")
def index():
    books = db.execute("SELECT * FROM books")
    return render_template("books.html", books=books)


@app.route("/cart", methods=["GET", "POST"])
def cart():

    # Ensure cart exists
    if "cart" not in session:
        session["cart"] = []

    # POST
    if request.method == "POST":
        book_id = request.form.get("id")
        if book_id:
            session["cart"].append(book_id)
        return redirect("/cart")

    # GET
    books = db.execute("SELECT * FROM books WHERE id IN (?)", session["cart"])
    return render_template("cart.html", books=books)
```

Notice that cart is implemented using a list. Items can be added to this list using the Add to Cart buttons in books.html. When clicking such a button, the post method is invoked, where the id of the item is appended to the cart. When viewing the cart, invoking the get method, SQL is executed to display a list of the books in the cart.

We also saw the contents of books.html:
```
{% extends "layout.html" %}

{% block body %}

    <h1>Books</h1>
    {% for book in books %}
        <h2>{{ book["title"] }}</h2>
        <form action="/cart" method="post">
            <input name="id" type="hidden" value="{{ book['id'] }}">
            <button type="submit">Add to Cart</button>
        </form>
    {% endfor %}

{% endblock %}
```

Notice how this creates the ability to `Add to Cart` for each book using `for book in books`.


## Shows

We looked at a pre-designed program called shows, in app.py:

```
# Searches for shows using LIKE

from cs50 import SQL
from flask import Flask, render_template, request

app = Flask(__name__)

db = SQL("sqlite:///shows.db")


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/search")
def search():
    shows = db.execute("SELECT * FROM shows WHERE title LIKE ?", "%" + request.args.get("q") + "%")
    return render_template("search.html", shows=shows)
```

Notice how the search route allows for a way by which to search for a show. This search looks for titles LIKE the one provided by the user.

We also examined index.html:
```
<!DOCTYPE html>

<html lang="en">

    <head>
        <meta name="viewport" content="initial-scale=1, width=device-width">
        <title>shows</title>
    </head>

    <body>

        <input autocomplete="off" autofocus placeholder="Query" type="text">

        <ul></ul>

        <script>
            let input = document.querySelector('input');
            input.addEventListener('input', async function() {
                let response = await fetch('/search?q=' + input.value);
                let shows = await response.json();
                let html = '';
                for (let id in shows) {
                    let title = shows[id].title.replace('<', '&lt;').replace('&', '&amp;');
                    html += '<li>' + title + '</li>';
                }
                document.querySelector('ul').innerHTML = html;
            });
        </script>

    </body>

</html>
```

Notice that the JavaScript script creates an implementation of autocomplete, where titles that match the input are displayed.


## API

An application program interface or API is a series of specifications that allow you to interface with another service. For example, we could utilize IMDB’s API to interface with their database. We might even integrate APIs for handling specific types of data downloadable from a server.


# Week 10 - The end (Final Project)
