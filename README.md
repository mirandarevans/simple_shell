# Simple Shell

This is a simple shell. It executes commands, including those with arguments.
It follows the [betty style guide](https://github.com/holbertonschool/Betty/wiki)
It can be used with or without a full path name.
It can be used to execute standard commands in the PATH such as ls and pwd.

## Directions for Use
Compile with this command:
```
gcc -Wall -Werror -Wextra -pedantic *.c -o <shell name here>
```
Invoke shell by typing its path name
```
old_shell$ ./shell
$
```

## Built-ins
* cd - change directory
```
$ cd /home
$ pwd
home
```
* exit - exit shell
```
$ exit 99
old_shell$ echo $?
99
```
* alias - create an alias
```
$ alias pwd=ls
$ pwd
hello_world.txt
```
* setenv - set an environmental variable
```
$ setenv HELLO world
$ echo $HELLO
world
```
* unsetenv - unset an env
```
$ unsetenv HELLO
$ echo $HELLO

$
```
* env - list all environmental variables
```
$ env
XDG_SESSION_ID=4
TERM=xterm-256color
...
```

## Other Features:
* && and || logical operators
```
$ ls
hello_world.txt
$ asgdnja || ls
./shell: 1: asgdnja: not found
hello_world.txt
```
* semicolon separator
```
$ ls; pwd
hello_world.txt
/home
```
* limited variable expansion
```
$ echo ~
/home/vagrant
```

## Blog Post
Check it out [here](https://medium.com/simple-shell-project/what-happens-when-you-type-ls-l-in-the-shell-e6430f1e6671)