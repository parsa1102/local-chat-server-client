1. run an instance of server and choose a port for it to bind to

2. from there you can open as many instances of client as you want choose the server Ip and port it is binded to so you would connect to the server

description:
as you hit sent on the client ui the message you had typed will be trnasmitted  to the server ui. the server will recieve your message and the time it was sent

the server has the ability to write a message and cast it. as the cast button is
 hit the written message will be displayed on the ui of all instances of client

as a client instance is opened and connected the server will recieve a message 
with the client number that has connected

and as a client instance is closed the server will be notified with a similar message

you can run multiple instances of server and open each of them on a diferrent port and connect each client to the server of your choice


QT version : Desktop QT 5.14.2 GCC 64bit


update notes 2.0:
1.connect button turns into disconnect button when connected in client
2.added input mask in client
3.enter key sends messages in client

update notes 3.0:
  features added:
     1.added entrer key shortcut for server as well
     2.added input mask for server
     3.added cutom username selection for clients
     
  bug fixes:
   1.port changes on server are now working as desired
   2.empty messages won't be sent anymore on both client and server
   
