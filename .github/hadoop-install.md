links see [here...](http://www.powerxing.com/install-hadoop/)

## Normal Question List
- JAVA_HOME not found: add `export JAVA_HOME=/usr/lib/jvm/java-7-openjdk-amd64` to `hadoop-env.sh yarn-env.sh mapred-env.sh`
- WARN util.NativeCodeLoader: Unable to load native-hadoop library for your platform... using builtin-java classes where applicable. see [here...](http://stackoverflow.com/questions/19943766/hadoop-unable-to-load-native-hadoop-library-for-your-platform-warning) By adding to ~/.bashrc ` export HADOOP_OPTS="$HADOOP_OPTS -Djava.library.path=/usr/local/hadoop/lib/native" `
- `./sbin/start-dfs.sh` then `jps` has no DataNode process, see [here...](http://blog.csdn.net/lulongzhou_llz/article/details/40590427) By changing datanode's VERSION file of `clusterID` be consist with namenode's VERSION file.

### Hadoop Eclipse install
- [intsall eclipse plugin links](http://blog.csdn.net/young_kim1/article/details/50208837)
- [attach source link ](http://blog.csdn.net/lifuxiangcaohui/article/details/25218287)
- modify the plugins by the following cmd `./eclipse clean`
