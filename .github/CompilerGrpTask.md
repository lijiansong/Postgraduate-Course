## I am task-driven
2017/04/24, communication with teacher, three tasks:
- [x] ToDo: project integration, add augmented reality module to the project.
- [x] ToDo: add a module to implement android device control, i.e. one android device end can control another android device end, e.g. send a request to it and etc. the implement mainly hooks into RPC, daemon process and something like server process.
- [x] ToDo: program slice, separate android event from the arduino device, e.g. when the connection is interrupted, the program on the android device such as UI ought to run normally although device is shutdown.
- [x] ToDo: AI about automatical chess playing.

- follow this [giude](http://blog.csdn.net/u013831198/article/details/70215925) to install opencv3.2 on ubuntu 14.04...
- ubuntu 14.04 kernel 4.8.2 driver [usb/serial/ch341](http://elixir.free-electrons.com/linux/v4.8.2/source/drivers/usb/serial/ch341.c)
- change the chown and group of the usb serial port by `$ sudo usermod -aG dialout whoami[user_name]` & `chmod 777 /dev/ttyUSB0`

- [x] ToDo: 实现ElasticActor的论文实验，使之支持
  - dispatcher.c: 位置无关的移动
  - actor station： scheduler的实现，使之支持actor数目的动态调节，即论文中的数学模型
  - build step: cd KVStore/app/Driver `$ make` will get *.so and *.c files, execute `$ moloader -F config/all.conf`, if you get the error msg that `No route to host` it means the zookeeper server has been down.
  - 实现思路：
    - 看懂KVStore例子的含义，跑通一个简单的例子，弄清分布式数据的传递和处理流程
    - 弄清楚mola的相关接口含义
    - 再考虑如何实现dispather和scheduler
- [ ] ToDo: ElasticActor msg dispatcher, scheduler & asynchronous communication
