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

- generator.js�Ǵ���� List<String> ���Լ��ض����ֻҪ��ÿһ��block��һ����Ӧ�Ĵ����߼��ͻ����ɶ�Ӧ�Ĵ���

�޸ĵķ��������⣬����ֱ����ӣ������漰��getBlockDefinitionsJsonPaths()��getToolboxContentsXmlPath()�ĵط�����Ҫ��ӶԶ���Ŀ¼�Ĵ���e.g.  AbstractBlocklyActivity.java:269-273
public BlocklyActivityHelper onCreateActivityHelper() {
        return new BlocklyActivityHelper(this,
                getBlockDefinitionsJsonPaths(),
                getToolboxContentsXmlPath());
    }

BlocklyActivityHelper.java:85 ���췽����Ҫ�����޸�
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

���Ե�ʱ�����ֱ����simpleactivity���޸ģ����⸴�ӵĲ�������