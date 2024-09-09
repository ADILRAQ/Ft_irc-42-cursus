# IRC Server Project
## Summary
This project involves creating your own IRC (Internet Relay Chat) server. You will use an actual IRC client to connect to your server and test its functionality. IRC is a text-based communication protocol that enables real-time messaging, which can be public or private, and allows users to exchange direct messages and join group channels.

## Mandatory Features
* __Program name:__ `ircserv`
* __Arguments:__ `<port>` (the port on which your IRC server will listen), `<password>` (the connection password for clients).
* __Requirements:__
  * Handle multiple clients simultaneously without hanging.
  * Use non-blocking I/O operations with only one poll() (or equivalent).
  * No forking allowed.
  * Communication must be done via TCP/IP (IPv4 or IPv6).
  * The following IRC commands must be implemented:
      * Authenticate, set a nickname, set a username, join a channel, send/receive private messages.
      * Forward channel messages to all clients in the channel.
      * Implement operator-specific commands:
        * __KICK:__ Eject a client from the channel.
        * __INVITE:__ Invite a client to the channel.
        * __TOPIC:__ Change or view the channel's topic.
        * __MODE:__ Modify the channel's modes (i, t, k, o, l).

## How to Run the Project

* __Clone the Repository:__

  ```bash
   git clone git@github.com:ADILRAQ/Ft_irc-42-cursus.git
   cd Ft_irc-42-cursus
  ```
* __Compile the Project:__

  > Run the Makefile to compile the source code:
    ```bash
     make
    ```
* __Run the IRC Server:__

  > Launch the IRC server with the following command:

    ```bash
      ./ircserv <port> <password>
    ```
     > Replace <port> with the desired port number and <password> with the connection password for clients.

* __Test the Server:__

   Use an IRC client of your choice to connect to the server, but preferable to use `LimeChat`:

    ```bash
    /connect 127.0.0.1 <port>
    /pass <password>
    ```
* __Testing with `nc` (Netcat):__

* A simple test can be done using nc:

   ```bash
    nc 127.0.0.1 <port>
   ```
* Send partial data commands using `ctrl+D` to simulate various scenarios:

   ```
    com^Dman^Dd
   ```
