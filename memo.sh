Note:

1. make sure there is an error msg if there are not enough arguments.
2. outfile should be created anyway, whether comand is valid or not.
3. if infile does not exisit, programme should return an erro and no commands should be executed.
4. if commands are not valide, the error msg should be printed out.
5. ./pipex infile "grep 8" "grep 0" outfile


test cases:


./pipex mains.c "grepp exit" "wc -l" outfile
# Fail to open infile: No such file or directory.
# returns a output file showing 0.
./pipex mains.c "grepp exit" "wcc -l" outfile
#Fail to open infile: No such file or directory
#Cannot execute the second command: Bad address
./pipex mains.c "grep exit" "wcc -l" outfile
#Fail to open infile: No such file or directory
#Cannot execute the second command: Bad address
./pipex mains.c "grep exit" "wc -l" outfile/tst
#Fail to create or open outfile: No such file or directory
#Fail to open infile: No such file or directory

< mains.c grep exit | wc -l > outfile
# bash: mains.c: No such file or directory
< mains.c greep exit | wcc -l > outfile
#bash: wcc: command not found
#bash: mains.c: No such file or directory

< mains.c grep exit | wc -l > outfile/tes
#bash: mains.c: No such file or directory
#bash: outfile/tes: Not a directory

# conclusion: mine pass the test. If the infile does not exisit, cmd1 not run, cmd2 runs.




