./pipex file1 cmd1 cmd2 file2

- set file1 as standart input 0
- execute command (cmd1) (it will be writen in file1)
- read file1 (get command (cmd1) from file1)
- share data between the two processes !!! (pid)
- 1s proc output => 2n proc input
- execute commad (cmd2)
- read file1 (get command (cmd2) from file1)
- and write the output in file2

---------------------------------------------
- in two process they can have same file descriptor value but with different files
- unique in current process

fork
- create a second process (child process) and return positive value in main process
- in child process fork return 0
- the main (parent) process run first then the child
- return -1 if error
- memory get copied from one process o new one

wait(NULL) (parent process wait for child process)
- check the children of the currwnt process not main (original)
- run child process first then parent process // wait(NULL)
- to secure your process from having memeory leaks add this line wait(NULL) // it make sure that all child process are finished
- return 0 if there is no children process
- return positive number (children process pid) if there is children process

pipe
- take an array , assign first element  to 3 and second to 4  // we will use those values as file descriptors
- the values assigned follow order of opened files descriptor

execlp
- execute command
- is better to use them in child process because in cause something went wrong they don't block the main process
- return -1 if error
- "execl" execute program / "p" (stand for path varibale) look for path 
- "execvp" take arguments as array
- "execvpe" e stands for environment varibale
- exec functions run executable file / not run command lines

dup -> (file) //take the files as paramater
- create a copy of my current file descriptor

dup2 -> (files,fd) //take file and the file descriptor too copy in 
- create a copy of my current file descriptor
- so the two files descriptor will be pointed on same file

signals
- SIGKILL: termnate the process
- SIGSTOP: stop the process
- SIGCONT: continue the process




















