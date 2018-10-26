# Creating a program in 64 bit Linux

## Objectives
* Create a 100% from scratch program in assembly without using the C runtime
* Utilize system calls 
* Ensure program enters and exits without any errors


### Sections
* We will have two sections. One section for our code, the other section for where we are going to store data
* To define a section, use the section keyword followed by the section name. In our case:
    * section .data
    * section .text
* Under each of the sections, you will place the appropiate code/data. So under section .text, place your code, etc

### Globals
* Globals are global functions
* We NEED a _start function since we do not have anywhere for our program to start. 
* To create a global, use the global keyword followed by the global name, with an underscore. 
* We will create this global under the .text section
* ex: global _start
* After you define your global, we need to utilize the global, a couple lines down you simply call the globals name: 
* _start:
* Under start, is where all of our actual asm code will be

### Data
* We need a string don't we? It would be a pain if we had to create a string byte by byte. Fear not! We can create a string. 
* to do so, we need to give the string a name followed by a size, we will use msg 
* Following the msg variable name, we need to define a size of each character... 
* db tells the compiler to allocate a byte space for a variable, while dw allocates two bytes. 
* Characters are generally always db while most numbers are dw
* ex: msg       db      "This is a string"
* After the string itself, we can also define additional things such as a nul, newline, etc (refer to ascii table for values)
* ex, string with newline:      msg     db      "Another string", 0xa
* You can also store other variables here



### Compiling and Building
* After you have created your .nasm file... you need to compile it to an object
* To do this:
    * run: nasm -f elf64 -o hello.o hello.nasm
    * nasm is the executable
    * -f is the format, in this case: elf64. Which stands for linux 64
    * -o is the output, you can name this whatever you like. The .o at the end is the file type (an object)
    * Finally you input the name of your asm file. In this case, it's hello.nasm
* Once you have done the above steps, you'll be presented with a object file (extension .o)
* You need to build this into an executable: 
    * run: ld -o hello hello.o
    * ld is the gnu linker
    * -o specifies the executable name
    * hello.o is the object we are linking and building into a executable 


# Instructions
1. Use all of your knowledge up to this point to see if you can build hello world
2. If you succeed in that, build some more complicated programs... experiment!
