## Hadoop Install
- install links see [here...](http://www.powerxing.com/install-hadoop/)

## Normal Question List
- JAVA_HOME not found: add `export JAVA_HOME=/usr/lib/jvm/java-7-openjdk-amd64` to `hadoop-env.sh yarn-env.sh mapred-env.sh`
- WARN util.NativeCodeLoader: Unable to load native-hadoop library for your platform... using builtin-java classes where applicable. see [here...](http://stackoverflow.com/questions/19943766/hadoop-unable-to-load-native-hadoop-library-for-your-platform-warning) By adding to ~/.bashrc ` export HADOOP_OPTS="$HADOOP_OPTS -Djava.library.path=/usr/local/hadoop/lib/native" `
- `./sbin/start-dfs.sh` then `jps` has no DataNode process, see [here...](http://blog.csdn.net/lulongzhou_llz/article/details/40590427) By changing datanode's VERSION file of `clusterID` be consist with namenode's VERSION file.
- close Eclipse first, then stop hbase and stop hdfs, otherwise something unexpected may happen...
- before sleep computer, must remember stop hdfs & hbase...
- the Eclipse IDE(NEON1) is very fucking, even if the variable is not declared `final`, you can also access it from within inner class, you can run your program without any warnings or errors. What a fucking bug!(found from my homework)

### Hadoop Eclipse install
- intsall eclipse plugin links, see [here](http://blog.csdn.net/young_kim1/article/details/50208837) or [here](http://www.powerxing.com/hadoop-build-project-using-eclipse/)
- [attach source link ](http://blog.csdn.net/lifuxiangcaohui/article/details/25218287)
- modify the plugins by the following cmd `./eclipse clean`

### HBase Install
- hbase install see this [page](http://blog.csdn.net/flyfish111222/article/details/51893096)

### HBase Eclipse Plugins
- HBase Eclipse config see this [page](http://blog.csdn.net/liuxiangke0210/article/details/53787223) and this [page](http://blog.csdn.net/nengyu/article/details/51779395)

