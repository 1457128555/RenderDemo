#include <jni.h>
#include <string>

#include "RenderEngine.h"

extern "C" JNIEXPORT void JNICALL
Java_com_example_renderdemo_MainActivity_initRenderEngine(JNIEnv* env, jobject /* this */,
    jstring filesDir, jstring externalDir, jstring packageName) {

    const char* filesDirPath = env->GetStringUTFChars(filesDir, nullptr);
    const char* externalDirPath = env->GetStringUTFChars(externalDir, nullptr);
    const char* packageNameStr = env->GetStringUTFChars(packageName, nullptr);

    const std::string assetPath = std::string(externalDirPath) + "/Asset";
    initRenderEngine(assetPath.c_str());
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_renderdemo_MainActivity_renderOneFrame(JNIEnv* env, jobject /* this */) {
    renderOneFrame();
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_renderdemo_MainActivity_quitRenderEngine(JNIEnv* env, jobject /* this */) {
    quitRenderEngine();
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_renderdemo_MainActivity_setViewport(JNIEnv* env, jobject /* this */, jint width, jint height) {
    setScreenSize(width, height);
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_renderdemo_MainActivity_onPlayBottom(JNIEnv* env, jobject /* this */) {
    onPlayBottom();
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_renderdemo_MainActivity_setLutIntensity(JNIEnv* env, jobject /* this */, jfloat value) {
    setLutIntensity(value);
}