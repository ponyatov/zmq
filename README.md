# MultithreadedGeneratorUDP
## генератор высокоскоростного UDP-трафика
### zmq: cppzmq + pcpp (DPDK)

task: https://tracker.yandex.ru/ECOLITESOFTT-150

git remote add flic git@gitflic.ru:dponyatov/zmq.git

- поток до 100...200 Gbit
- UDP трафик на порты 40000..40024

## servers

- generator: dev01@10.110.1.106
- server   : dev01@10.110.1.105
