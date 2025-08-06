
Pod::Spec.new do |s|

  s.name         = 'RenderEngine'
  s.version      = '0.0.1'
  s.summary      = 'A cross-platform rendering engine using C++.'
  s.description  = 'C++ core + Objective-C++ wrapper, Swift friendly.'
  s.homepage     = 'https://techgit.meitu.com/sheng.chen/renderdemo'
  s.license      = { :type => 'MIT', :file => 'LICENSE' }
  s.author       = { 'ChenSheng' => 'sheng.chen@pixocial.com' }
  s.source       = { :git => 'https://techgit.meitu.com/sheng.chen/renderdemo.git', :tag => '0.0.1' }

  s.ios.deployment_target = '12.0'

  s.source_files = 'ObjC/**/*.{h,mm}', 'Cpp/**/*.{hpp,h,cpp,c}'
  s.public_header_files = 'ObjC/include/**/*.h'

  s.pod_target_xcconfig = {
    'CLANG_CXX_LANGUAGE_STANDARD' => 'c++17',
    'CLANG_CXX_LIBRARY' => 'libc++',
    'OTHER_CPLUSPLUSFLAGS' => '-std=c++17 -stdlib=libc++',
    'HEADER_SEARCH_PATHS' => '$(PODS_TARGET_SRCROOT)/Cpp/include'
  }
  
  s.requires_arc = true
  s.libraries = 'c++'

  s.dependency 'MBProgressHUD', '~> 1.2.0'
end
