
dup2 -> to set standart output (in pipex)
fork -> to share data between processes


./pipex file1 cmd1 cmd2 file2

- set file1 as standart input 0
- execute command (cmd1) (it will be writen in file1)
- read file1 (get command (cmd1) from file1)
- share data between the two processes !!! (pid)
- 1s proc output => 2n proc input
- execute commad (cmd2)
- read file1 (get command (cmd2) from file1)
- and write the output file2
