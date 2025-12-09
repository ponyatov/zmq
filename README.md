# MultithreadedGeneratorUDP
## генератор высокоскоростного UDP-трафика
### zmq: cppzmq + pcpp (DPDK)

task: https://tracker.yandex.ru/ECOLITESOFTT-150

git remote add flic git@gitflic.ru:dponyatov/zmq.git

- поток до 100...200 Gbit
- UDP трафик на порты 40000..40024

## servers

- generator: dev01@10.110.1.106
  - dpdk01
  - 100g   :       10.120.100.39
- server2  : dev01@10.110.1.105
  - old    :       10.120.100.51
  - 100g   :       10.120.100.51
