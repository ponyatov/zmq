- generator: dev01@10.110.1.106
  - dpdk01
  - old    :       10.120.100.39
- server   : dev01@10.110.1.105
  - server2
  - old    :       10.120.100.51

## `~/.ssh/config`

```
Host server2
  HostName 10.110.1.105
  User dev01
  IdentityFile ~/.ssh/id_ed25519
  ServerAliveInterval 60
  TCPKeepAlive yes

Host dpdk01
  HostName 10.110.1.106
  User dev01
  IdentityFile ~/.ssh/id_ed25519
  ServerAliveInterval 60
  TCPKeepAlive yes
```
