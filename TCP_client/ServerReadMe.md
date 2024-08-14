This is the process followed to make a bare bones TCP Client application on linux 

General process to follow:

//Create a socket
//create a hint structure for the server we are connecting to 

// Logic for what the client does:
                        runs a while loop:
                        	read/stdin the lines of text we wanna send
                        	sent to server
                        	wait for response from server
                        	display the response
                        	
                        	exits the loop if Keyboard Ctrl+C happens
                        close the socket
                       
