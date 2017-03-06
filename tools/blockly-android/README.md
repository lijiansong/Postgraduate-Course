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

修改的方法有问题，不能直接添加，凡是涉及到getBlockDefinitionsJsonPaths()和getToolboxContentsXmlPath()的地方都需要添加对额外目录的处理，e.g.  AbstractBlocklyActivity.java:269-273
public BlocklyActivityHelper onCreateActivityHelper() {
        return new BlocklyActivityHelper(this,
                getBlockDefinitionsJsonPaths(),
                getToolboxContentsXmlPath());
    }

BlocklyActivityHelper.java:85 构造方法需要继续修改
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

测试的时候可以直接在simpleactivity上修改，避免复杂的操作步骤

异步通信example or 《第一行代码》key words：AsyncTask
http://stackoverflow.com/questions/34607534/how-to-connect-android-with-httpsurlconnection
<br>see [here...](http://stackoverflow.com/questions/34607534/how-to-connect-android-with-httpsurlconnection)
