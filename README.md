# ft_sh1
minishell 1 project at 42

The goal is to build a small shell in C, that gets uses the system's environment, has a few builtins (env, printenv, setenv, unsetenv, cd, exit) and runs the standard commands from $(PATH).

-It should have a prompt ("$>") and show it everytime after the previous commands are done running, not before.
-Errors must be managed without errno
-as always no globals

Allowed functions:

◦ opendir ◦ readdir ◦ closedir ◦ malloc

◦ free

◦ exit

◦ getcwd ◦ chdir ◦ fork

◦ stat

◦ lstat

◦ fstat

◦ open

◦ close

◦ read

◦ write

◦ execve ◦ access ◦ wait

◦ waitpid ◦ wait3

◦ wait4

◦ signal ◦ kill
