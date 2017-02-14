package cn.ac.ict.myblockly;

import android.os.Bundle;
import android.support.annotation.NonNull;

import com.google.blockly.android.AbstractBlocklyActivity;
import com.google.blockly.android.codegen.CodeGenerationRequest;
import com.google.blockly.android.ui.BlockViewFactory;
import com.google.blockly.android.ui.WorkspaceHelper;

import java.util.List;

public class MainActivity extends AbstractBlocklyActivity {
    @Override
    public BlockViewFactory onCreateBlockViewFactory(WorkspaceHelper workspaceHelper) {
        return null;
    }

    @NonNull
    @Override
    protected String getToolboxContentsXmlPath() {
        return null;
    }

    @NonNull
    @Override
    protected List<String> getBlockDefinitionsJsonPaths() {
        return null;
    }

    @NonNull
    @Override
    protected List<String> getGeneratorsJsPaths() {
        return null;
    }

    @NonNull
    @Override
    protected CodeGenerationRequest.CodeGeneratorCallback getCodeGenerationCallback() {
        return null;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
}
