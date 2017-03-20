links see [here...](http://www.powerxing.com/install-hadoop/)

Normal Question List:
- JAVA_HOME not found: add `export JAVA_HOME=/usr/lib/jvm/java-7-openjdk-amd64` to `hadoop-env.sh yarn-env.sh mapred-env.sh`
- WARN util.NativeCodeLoader: Unable to load native-hadoop library for your platform... using builtin-java classes where applicable. see [here...](http://stackoverflow.com/questions/19943766/hadoop-unable-to-load-native-hadoop-library-for-your-platform-warning)
by adding to ~/.bashrc ` export HADOOP_OPTS="$HADOOP_OPTS -Djava.library.path=/usr/local/hadoop/lib/native" `
