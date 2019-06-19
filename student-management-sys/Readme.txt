--------------------------
Student management program
--------------------------

This program allows you to save students and their information
inside a file.

--------------------------
How to use it
--------------------------

Open a terminal inside the base folder where the Makefile is
stored. Then, type the following command to build the project:

make all

This command will build our executable files. Now execute the
newly build project with the following command:

./output/exe/student_management_sys -f "fileName"

This will start the interactive mode where you'll be prompted
to write the next command: append (to append a new student to the
file), list (to list all the students inside the file), or
quit (to quit the program).

Specify other arguments to enter other modes:

E.g.:
./output/exe/student_management_sys -f "fileName" -a

Where you'll be prompted immediately to append a new student.
OR

./output/exe/student_management_sys -f "fileName" -l

To immediately list all the students.
