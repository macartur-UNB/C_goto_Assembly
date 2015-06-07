# Compiler C to Assembly

### Introduction
This repository is a simple compiler from C to Assembly (nasm x86).


### Dependencies
```sh
$ sudo apt-get install bison
$ sudo apt-get install flex
```
### Installation
```sh
$ git clone https://github.com/macartur/C_goto_Assembly
$ cd C_goto_Assembly
$ make
```

### Running
```sh
    $ make run
```

### COMPLE ASSEMBLY
```sh
    $ nasm -f elf32 <program>.asm
    $ gcc -m32 <program>.o -o <program>
```
