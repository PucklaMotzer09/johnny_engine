#ifndef MAINCLASS_H
#define MAINCLASS_H
#include "InputManager.h"
#include <SDL2/SDL_events.h>
#include "Actor.h"
#include "WindowHandle.h"
#include <chrono>
#include <SDL2_framerate.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_mixer.h>

#define NO_FPS_LOCK -1

using namespace std::chrono;

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;
class SDL_Rect;

#ifndef _WIN32
namespace cAudio
{
	class IAudioManager;
}
#endif


namespace SDL
{            
    class ResourceManager;
    class Physics;
    class Camera;
    class JoystickManager;
    class TextureHandle;
    class Sprite;
    class ContactListener;

    class MainClass : public Actor
    {
        public:
            MainClass(const char* title = "New Window",int width = NORM_W,int height = NORM_H);
            virtual ~MainClass();

            void run();

            void setTimeScale(double d){m_timeScale = d;}
            void setMaxFPS(int);
            void setAmbientLight(const SDL_Color&);
            void setNativeRes(const Vector2& v);
            void setBackgroundColor(const SDL_Color&);

            static MainClass* getInstance() {return instance;}

            InputManager* getInputManager() {return m_inputManager;}
            ResourceManager* getResourceManager() {return m_resourceManager;}
            SDL_Renderer* getRenderer() {return m_renderer;}
            WindowHandle* getWindow() {return m_window;}
            SDL_Texture* getBackBuffer() {return m_backBuffer;}
            JoystickManager* getJoystickManager() {return m_joystickManager;}
#ifndef _WIN32
            cAudio::IAudioManager* getAudioManager() {return m_audioManager;}
#endif
            Camera* getCamera();
            int getMaxFPS() {return m_maxFPS;}
            Physics* getPhysics();
            float getScaleW() const {return m_scaleW;}
            float getScaleH() const {return m_scaleH;}
            const Vector2& getNativeRes() const {return m_nativeResolution;}
            #ifdef _WIN32
            double getDeltaTimeInSeconds() const {return m_realDeltaTimeInSeconds*m_timeScale;}
            #else
            double getDeltaTimeInSeconds() const {return m_smoothDeltaTimeInSeconds*m_timeScale;}
            #endif
            double getFPS() const {return m_fps;}
            const SDL_Color& getAmbientLight() const {return m_ambientLight;}
            Sprite* getAmbientSprite();
            const SDL_Color& getBackgroundColor() const {return m_backgroundColor;}

            void activatePhysics(const Vector2& gravity = Vector2(0.0,-10.0),const Vector2& worldSize = Vector2(NORM_W,NORM_H));
#ifndef _WIN32
            void activateAudio(bool initializeDefault,const char* IFilePath);
#endif
            void activateAudio(int frequency = 44100,Uint16 format = MIX_DEFAULT_FORMAT,int channels = 2,int chunksize = 2048);
            void activateJoystick();
            
            virtual bool m_render() override;
            virtual bool render() override;
            virtual bool update() override;
            virtual bool m_update() override;

            virtual void onResize(int,int);
            virtual void onFullscreen(bool);

        protected:
            virtual void quit() = 0;
            virtual bool init() = 0;
            virtual bool pollEvents();
            virtual bool pollEvent(const SDL_Event& e);

            int m_maxFPS = 60;
            InputManager* m_inputManager = nullptr;
            ResourceManager* m_resourceManager = nullptr;
            WindowHandle* m_window = nullptr;
            Physics* m_physics = nullptr;
            Camera* m_camera = nullptr;
            JoystickManager* m_joystickManager = nullptr;
#ifndef _WIN32
            cAudio::IAudioManager* m_audioManager = nullptr;
#endif

            double m_timeScale = 1.0;
            bool m_scaleToResolution = true;

        private:
            static MainClass* instance;

            void m_quit();

            void startTimeMeasure();
            void mainLoop();
            int endTimeMeasure();
            void recreateBuffer();
            void resetViewport(SDL_Rect*);

            void m_init();

            const char* m_windowTitle;
            int m_windowWidth;
            int m_windowHeight;


            double calculateMeanDeltaTime();
            void takeAwayHighestAndLowestDts();
            void moveDeltaTimesOneIndexDown();
            int getDeltaTimesSize();
            void copyRealTimesToSmoothTimes();
            int m_realDeltaTimeSize = 0;
            void setNum(double&,int&);
            double m_realDeltaTimeInSeconds = 0.0;
            double m_smoothDeltaTimeInSeconds = 0.0;
            double m_realDeltaTimes[11] = {-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0};
            double m_smoothDeltaTimes[11] = {-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0};
            double m_FPSes[3];
            double m_fps = 0.0;
            int m_lastFrame = 0;

            TextureHandle* m_testTexture = nullptr;
            SDL_Rect* m_testRect = nullptr;
            SDL_Texture* m_backBuffer = nullptr;
            float m_scaleW;
            float m_scaleH;
            SDL_Rect m_backBufferDst;

            double m_time = 0.0;
            high_resolution_clock::time_point m_startTime;
            high_resolution_clock::time_point m_endTime;
            #ifdef MAX_FPS_LOCK
            double m_timeForMaxFPS = 0.0;
            high_resolution_clock::time_point m_startTimeForMaxFPS;
            high_resolution_clock::time_point m_endTimeForMaxFPS;
            duration<double,micro> m_deltaClockTimeForMaxFPS;
            #endif
            duration<double,micro> m_deltaClockTime;
            
            FPSmanager m_fpsManager;
            
            SDL_Color m_backgroundColor;
            SDL_Color m_ambientLight;
            Sprite* m_ambientSprite = nullptr;
        
            Vector2 m_nativeResolution;
            ContactListener* m_contactListener;

            bool m_audioOpened = false;
    };
}



#endif // MAINCLASS_H
