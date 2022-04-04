# minitalk

A project of the 42 curriculum, with as general goal to learn more about unix signals. We had to create both a server and client program, where the client will send a string, that the server has to print if the client adressed it's PID.

Restrictions for this project:

• only write, signal, sigemptyset, sigaddset, sigaction, kill, getpid, malloc, free, pause, sleep, usleep, exit

• one global variable allowed (I used none).

• The server has to display the string pretty quickly. 

• Your server should be able to receive strings from several clients in a row without
needing to restart.

• The communication between your client and your server has to be done only using
UNIX signals.

• You can only use these two signals: SIGUSR1 and SIGUSR2.

Was created as a project for the 19 coding school (part of the 42 network) and passed with 100%.

# Norme

Code was written in a style to be in accordance with the [normev3](https://github.com/42School/norminette) rules.

# Usage

Clone the repository, run make to compile both the server and client.

Start the server first, it will print it's own PID.

Run the client, followed by server PID, followed by string the server should print. ASCI characters are supported.

# Logic

A very quick rundown of how this works, when launching the server it will get it's pid and start looping indefinitly while waiting for signals from the client.

The client will translate the string into 1s and 0s, according to the value of the char in the string we are reading. Sending SIGUSR1 and SIGUSR2 repectively to represent either a 1 or 0.
Once all characters in the string have been sent it will send a null character (00000000) to let the server know the string has been fully sent.

The client will add all the SIGUSRS he recieves until he has revcieved 8, which he will then calculate back to the character value and print it. It send a signal after to let the client know to send the next element of the string.
Upon recieving the terminator it send a signal to the client to let it shut down.
