package com.example.renderdemo

import android.widget.*
import android.view.Gravity
import android.view.ViewGroup
import android.os.Bundle
import android.opengl.GLSurfaceView
import android.view.View
import androidx.appcompat.app.AppCompatActivity


class MainActivity : AppCompatActivity() {

    private lateinit var glSurfaceView: GLSurfaceView
    private lateinit var myRenderer: MyGLRenderer

    private external fun initRenderEngine(filesDir: String, externalDir: String, packageName: String)
    private external fun renderOneFrame()
    private external fun quitRenderEngine()
    private external fun setViewport(width: Int, height: Int)
    private external fun onPlayBottom()
    private external fun setLutIntensity(value: Float)

    init {
        System.loadLibrary("renderdemo") // 加载 C++ 编写的本地库
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        glSurfaceView = GLSurfaceView(this)
        glSurfaceView.setEGLContextClientVersion(3)  // 使用 OpenGL ES 3.0
        myRenderer = MyGLRenderer(this)
        glSurfaceView.setRenderer(myRenderer)
        //setContentView(glSurfaceView)

        setupUI()
    }

    fun setupUI() {

        val rootLayout = FrameLayout(this)

        // 水平布局：标签 + 按钮
        val horizontalLayout = LinearLayout(this).apply {
            orientation = LinearLayout.HORIZONTAL
            gravity = Gravity.CENTER_VERTICAL
            setBackgroundColor(0x66_000000) // 半透明黑色，可选
        }

        val label = TextView(this).apply {
            text = "Lut强度"
            textSize = 16f
            setTextColor(0xFFFFFFFF.toInt())
        }

        // 拖拽条
        val seekBar = SeekBar(this).apply {
            max = 100
            progress = 50
            setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
                override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                    val value = progress / 100.0f
                    setLutIntensity(value)
                }
                override fun onStartTrackingTouch(seekBar: SeekBar?) {}
                override fun onStopTrackingTouch(seekBar: SeekBar?) {}
            })
        }

        val seekBarLayoutParams = LinearLayout.LayoutParams(
            0, // 宽度为0，配合weight使用
            LinearLayout.LayoutParams.WRAP_CONTENT,
            1f // 权重为1，占据剩余空间
        )
        horizontalLayout.addView(label)
        horizontalLayout.addView(seekBar, seekBarLayoutParams)

        val button = Button(this).apply {
            text = "播放/暂停"
            setOnClickListener {
                onPlayBottom()
            }
        }

        // 垂直布局：水平布局 + 拖拽条
        val verticalLayout = LinearLayout(this).apply {
            orientation = LinearLayout.VERTICAL
            setPadding(20, 0, 20, 0)
            addView(horizontalLayout)
            addView(button)
            setBackgroundColor(0x00FFFFFF) // 完全透明
        }

        // 4. 设置 UI 控件的布局参数，让其悬浮在底部
        val uiParams = FrameLayout.LayoutParams(
            FrameLayout.LayoutParams.MATCH_PARENT,
            FrameLayout.LayoutParams.WRAP_CONTENT,
            Gravity.BOTTOM
        )
        uiParams.bottomMargin = 100

        // 5. 组装
        rootLayout.addView(glSurfaceView)
        rootLayout.addView(verticalLayout, uiParams)

        setContentView(rootLayout)
    }

    override fun onDestroy() {
        super.onDestroy()
        myRenderer.release()
    }

    private class MyGLRenderer(val activity: MainActivity) : GLSurfaceView.Renderer {

        override fun onSurfaceCreated(gl: javax.microedition.khronos.opengles.GL10?, config: javax.microedition.khronos.egl.EGLConfig?) {

            val filesDir = activity.filesDir.absolutePath
            val externalDir = activity.getExternalFilesDir(null)?.absolutePath ?: ""
            val packageName = activity.packageName
            activity.initRenderEngine(filesDir, externalDir, packageName)
        }

        override fun onDrawFrame(gl: javax.microedition.khronos.opengles.GL10?) {
            activity.renderOneFrame()  // 渲染每一帧
        }

        override fun onSurfaceChanged(gl: javax.microedition.khronos.opengles.GL10?, width: Int, height: Int) {
            activity.setViewport(width, height)  // 设置视口
        }

        fun release() {
            activity.quitRenderEngine()
        }
    }
}