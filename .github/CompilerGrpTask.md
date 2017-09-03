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
- [x] ToDo: ~~ElasticActor msg dispatcher, scheduler & asynchronous communication~~
- [x] ToDo: two things, collect useful info to compute Ni-opt to determine the num of actor stations & granularity adjustment of scheduler
  - KVStore要实现这样一种功能见moloader.cpp源文件，该源文件是整个应用的entrance
  - 主要实现两个功能，一个是实时收集各类信息，定期地计算station的数目，另外一个就是scheduler，scheduler的调度单元是actor station，目前的版本也是基于此
  - scheduler以actor station为调度单位，actor迁移的策略。先弄清楚station和actor的关系？TODO查阅station的定义源码，从4个station扩展到8个station期间需要做哪些事情？
  - scheduler轮询计算的策略：每隔一段时间计算station的数目，根据给出的opt公式计算，首先先统计公式所需要的各个参数。e.g. K表示actor的种类，其值需要解析all.conf去统计；actor的到达率，在scheduler中设置时间窗口去统计...
  - all.conf 添加新的配置参数表征轮询计算的时间间隔，所以需要对应修改moloader的解析方法
  - 着手实现的时候先新建一个branch再开始写
  - context上下文是指actor的状态，此次实现不需要考虑actor的状态
  - 看懂dispatcher的实现思路，暂时`不考虑Scatter-Gather模型`，对应dispatch group
- [x] ToDo: 两件事情，实现师兄的论文代码和调试蛋疼的机械臂(在问题没解决之前还没有资格说自己不想做)。
  - actor 模型：
    - 实现actor的动态迁移
    - 实现actor
  - ~~机械臂：~~
    - ~~时间间隔有点久，先查看是否有硬件故障，如果有，故障出在哪里，为什么会出现，如何解决；~~
    - ~~考虑识别算法是否需要重现实现，如果重新实现，有哪些高效的方案，采用何种识别策略；~~


- [x] BackUp: for the servo you should give it enough time for it to rotate to the given angles, opencv camera calibration see [here](http://docs.opencv.org/2.4/doc/tutorials/calib3d/camera_calibration_square_chess/camera_calibration_square_chess.html), to detect [chessboard corners](https://dsp.stackexchange.com/questions/2805/how-does-opencv-find-chessboard-corners), [hand eye calibration](https://robotics.stackexchange.com/questions/7163/hand-eye-calibration)
- [x] BackUp: for the next semester, mainly focuses on Cambricon project, which is primarily about compiler tool-chain of Cambricon IPU & deep learning platform that is similar to Tensorflow, Caffe and MxNet based on clang & llvm, all these efforts output at least two papers. Months later, take up Huawei, Alibaba or Face++ project, mainly to solve deep learning and nlp problems. Later ph.d stage concentrates on nlp programming, distributed iot programming framework.
- [x] TODO: elastic actor的实验抓紧做（周一到周五的晚上和周末两天做这个），[PPoPP](http://conf.researchr.org/home/PPoPP-2018)的deadline在8月25号，based on the experimental result to decide...目前距离截止投稿还有一个月，争取在接下来的一周即31号之前有突破性的进展吧，近期先熟悉一下寒武纪的项目，弄清楚背后的流程，高温假回来后再好好搞。


