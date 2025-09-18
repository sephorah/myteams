# MyTeams

The goal of this project is to create a server and a CLI client. The server can handle multiple clients at the same time.

Commands available:

- `/help`
- `/login`
- `/logout`
- `/users`
- `/user`
- `/send`
- `/messages`

Read the RFC in `/doc` to learn more about commands.

## Getting started

Run this command to help the server and client find the `libteams.so` library.
```
export LD_LIBRARY_PATH=$PWD/libs/myteams:$LD_LIBRARY_PATH
```

### Server 
```
USAGE: ./myteams_server port
	port is the port number on which the server socket listens
```

Example: `./myteams_server 5555`

### Client

```
USAGE: ./myteams_cli ip port

	ip is the server ip address on which the server socket listens
	port is the port number on which the server socket listens
```

Example: `./myteams_cli 127.0.0.1 5555`

## Developers

| [<img src="https://github.com/moonia.png?size=85" width=85><br><sub>Mounia ARJDAL</sub>](https://github.com/moonia) | [<img src="https://github.com/sephorah.png?size=85" width=85><br><sub>Séphorah ANIAMBOSSOU</sub>](https://github.com/sephorah)
| :---: | :---: |