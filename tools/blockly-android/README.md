modify blockly-android to change its dir to store the json and jar files.

methods need to be changed contain...

for the AbstractBlocklyActivity:
- onLoadWorkspace..
  - loadWorkspaceFromAppDir
- getBlockDefinitionsJsonPaths
- getToolboxContentsXmlPath

```Java
/**
     * @return The path to the saved workspace file on the local device. By default,
     *         "workspace.xml".
     */
    @NonNull
    protected String getWorkspaceSavePath() {
        return "workspace.xml";
    }
```

need to change function contains:
- reloadToolbox
- reloadBlockDefinitions

codegen need to be modified:
CodeGeneratorService.java : 210/270
- loadAssetAsUtf8
- getBlockDefinitions

- generator.js是存放在 List<String> 可以加载多个，只要对每一个block有一个对应的处理逻辑就会生成对应的代码

修改的方法有问题，不能直接添加，凡是涉及到getBlockDefinitionsJsonPaths()和getToolboxContentsXmlPath()的地方都需要添加对额外目录的处理，e.g.  AbstractBlocklyActivity.java:269-273

```Java
public BlocklyActivityHelper onCreateActivityHelper() {
        return new BlocklyActivityHelper(this,
                getBlockDefinitionsJsonPaths(),
                getToolboxContentsXmlPath());
    }
```
AbstractBlocklyActivity.java:527-541
```
 /**
     * Runs the code generator. Called when user selects "Run" action.
     * <p/>
     * Gets the latest block definitions and generator code by calling
     * {@link #getBlockDefinitionsJsonPaths()} and {@link #getGeneratorsJsPaths()} just before
     * invoking generation.
     *
     * @see #getCodeGenerationCallback()
     */
    protected void onRunCode() {
        mBlockly.requestCodeGeneration(
            getBlockDefinitionsJsonPaths(),
            getGeneratorsJsPaths(),
            getCodeGenerationCallback());
}
```

BlocklyActivityHelper.java:85 构造方法需要继续修改

```Java
BlocklyController.Builder builder = new BlocklyController.Builder(activity)
                .setClipDataHelper(mClipDataHelper)
                .setWorkspaceHelper(mWorkspaceHelper)
                .setBlockViewFactory(mBlockViewFactory)
                .setWorkspaceFragment(mWorkspaceFragment)
                .addBlockDefinitionsFromAssets(blockDefinitionJsonPaths)
                .setToolboxConfigurationAsset(toolboxPath)
                .setTrashUi(mTrashBlockList)
                .setToolboxUi(mToolboxBlockList, mCategoryFragment);
        mController = builder.build();
```


测试的时候可以直接在simpleactivity上修改，避免复杂的操作步骤

异步通信example or 《第一行代码》key words：AsyncTask

http://stackoverflow.com/questions/34607534/how-to-connect-android-with-httpsurlconnection
<br>see [here...](http://stackoverflow.com/questions/34607534/how-to-connect-android-with-httpsurlconnection)
how to write pcm-formated audio data to file see [here...](http://stackoverflow.com/questions/13583827/audiorecord-writing-pcm-file)


- [x] Now I finished packaging cloud services e.g. Baidu Voice Recognition Service
- [ ] ToDo: define a description rule as easy as possible to describe the cloud service, then package them into a module. To integrate with Blockly, modify the source code of Blockly so that it can support dynamical generating blocks.

- [x] modify the source code of blockly, a time consuming task
- [x] design rules of the description file, and write a parser to parse it
- [x] learning to add an module to android blockly, and then add the dynamical module to Dongshouke, package the cloud service and write a simple parser to parse the description file...
- [ ] NLP module need to be learned and develop my own NLP lib...

### Notice
- openFileInput doesn't accept path separators, i.e. if you implement an Instance of InputStream like this `InputStream voiceInputStream=openFileInput(Environment.getExternalStorageDirectory().getPath()+AUDIO_NAME);` then your program will crash :-)
- project FileTest read & write is `assets`, and project RESTful read & write is `assets` directory again, while project RESTful_AudioRecord is the local directory...
- in google blockly source code, most of member variables are declared `final` for security, so it may be rediculious to modify the source code to support dynamical loading blocks. 

