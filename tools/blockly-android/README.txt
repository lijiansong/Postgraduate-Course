modify blockly-android to change its dir to store the json and jar files.
methods need to be changed contain...
for the AbstractBlocklyActivity:
- onLoadWorkspace..
  - loadWorkspaceFromAppDir
- getBlockDefinitionsJsonPaths
- getToolboxContentsXmlPath

/**
     * @return The path to the saved workspace file on the local device. By default,
     *         "workspace.xml".
     */
    @NonNull
    protected String getWorkspaceSavePath() {
        return "workspace.xml";
    }

need to change function contains:
- reloadToolbox
- reloadBlockDefinitions

codegen need to be modified:
CodeGeneratorService.java : 210/270
- loadAssetAsUtf8
- getBlockDefinitions

- generator.js是存放在 List<String> 可以加载多个，只要对每一个block有一个对应的处理逻辑就会生成对应的代码

//获取getFilesDir()的父目录
File dataDir = getFilesDir().getParentFile();
File mydir = new File(dataDir, "aaa");
mydir.mkdir();
File file = new File(mydir, "test.txt");
BufferedWriter fw = null;
try {
    file.createNewFile();
    fw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file, true), "UTF-8"));
    fw.append("测试内容");
    fw.flush();
    fw.close();
} catch (Exception e) {
    e.printStackTrace();
}