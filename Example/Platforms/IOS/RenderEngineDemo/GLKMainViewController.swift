import UIKit
import GLKit
import OpenGLES

class GLKMainViewController: GLKViewController {

    private var glContext: EAGLContext!

    override func viewDidLoad() {
        super.viewDidLoad()
        setupGL()
        setupUI()
    }
    
    private func setupGL() {
        
        // 创建 OpenGL ES 3.0 上下文
        glContext = EAGLContext(api: .openGLES3)
        EAGLContext.setCurrent(glContext)
        // 设置视图为 GLKView
        guard let glkView = self.view as? GLKView else {
            fatalError("视图不是 GLKView 类型")
        }
        
        glkView.context = glContext
        glkView.drawableColorFormat = .RGBA8888
        glkView.drawableDepthFormat = .format24
        
        RenderEngineWrapper.initRenderEngine()
    }
    
    private func setupUI(){
        // MARK: - 添加标签
        let lutLabel = UILabel()
        lutLabel.text = "Lut强度"
        lutLabel.textColor = .white
        lutLabel.font = UIFont.systemFont(ofSize: 14)
        lutLabel.setContentHuggingPriority(.required, for: .horizontal)
        lutLabel.translatesAutoresizingMaskIntoConstraints = false
        // MARK: - 添加滑动条
        let lutSlider = UISlider()
        lutSlider.minimumValue = 0
        lutSlider.maximumValue = 1
        lutSlider.value = 0.5
        lutSlider.addTarget(self, action: #selector(sliderChanged(_:)), for: .valueChanged)
        lutSlider.translatesAutoresizingMaskIntoConstraints = false
        // MARK: - 水平：标签 + 滑条
        let lutSliderRow = UIStackView(arrangedSubviews: [lutLabel, lutSlider])
        lutSliderRow.axis = .horizontal
        lutSliderRow.spacing = 8
        lutSliderRow.alignment = .center
        lutSliderRow.translatesAutoresizingMaskIntoConstraints = false

        // MARK: - 添加点击按钮
        let applyButton = UIButton(type: .system)
        applyButton.setTitle("播放/暂停", for: .normal)
        applyButton.titleLabel?.font = UIFont.boldSystemFont(ofSize: 16)
        applyButton.translatesAutoresizingMaskIntoConstraints = false
        applyButton.addTarget(self, action: #selector(buttonTapped), for: .touchUpInside)
        // MARK: - 垂直：滑条 + 按钮
        let stack = UIStackView(arrangedSubviews: [lutSliderRow, applyButton])
        stack.axis = .vertical
        stack.spacing = 16
        stack.translatesAutoresizingMaskIntoConstraints = false
        
        view.addSubview(stack)
        
        // MARK: - 自动布局
        NSLayoutConstraint.activate([
            // 靠底部显示
            stack.leadingAnchor.constraint(equalTo: view.leadingAnchor, constant: 20),
            stack.trailingAnchor.constraint(equalTo: view.trailingAnchor, constant: -20),
            stack.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor, constant: -30)
        ])
    }
    
    @objc func buttonTapped() {
       // RenderEngineWrapper.onPlayBottom()
       RenderEngineWrapper.onPlayBottom(in: self.view)
    }

    @objc func sliderChanged(_ sender: UISlider) {
        let lutIntensity = sender.value
        RenderEngineWrapper.setLutIntensity(lutIntensity)
    }
    
    override func glkView(_ view: GLKView, drawIn rect: CGRect) {
        RenderEngineWrapper.renderOneFrame()
    }
    
    deinit {
        if EAGLContext.current() === glContext {
            EAGLContext.setCurrent(nil)
        }
        RenderEngineWrapper.quitRenderEngine()
    }
}
