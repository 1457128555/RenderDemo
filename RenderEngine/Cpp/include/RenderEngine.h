#ifndef RenderEngine_h
#define RenderEngine_h

#ifdef __cplusplus
extern "C" {
#endif

void initRenderEngine(const char* assetPath);
void renderOneFrame();
void quitRenderEngine();

void setScreenSize(int width, int height);

void onPlayBottom();
void setLutIntensity(float value);

#ifdef __cplusplus
}
#endif

#endif /* RenderEngine_h */
