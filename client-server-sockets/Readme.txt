--------------------------
Client-Server program
--------------------------

This client/server program is used for logging warnings & errors in
a file. The sistem is made of two components: 
i) Server, 
ii) Client/s

--------------------------
How to use it
--------------------------

Open a terminal inside the base folder where the Makefile is
stored. Then, type the following command to build the project:

make all

This command will build our executable files.

If you want to execute the server, you can do so with the following
command:

./output/exe/server -f "fileName"

The server will create a message queue, and read if a client sends
a new message.

And if you want to execute the client, you can do so with the following
command:

./output/exe/client -f "fileName" -t "number of seconds"

The client will create a message queue and send the name of a named 
pipe to the server.