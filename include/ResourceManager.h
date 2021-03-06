#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <map>
#include <vector>
#ifdef __linux__
    #include <SDL2/SDL_ttf.h>
#else
#ifndef __APPLE__
    #include <TTF/SDL_ttf.h>
#else
    #include <SDL2_ttf/SDL_ttf.h>
#endif
#endif

#include <string>

using namespace std;

    class SDL_Texture;
    class SDL_Rect;
    class SDL_Renderer;

namespace SDL
{
    class TextureHandle;
    class Music;
    class Sound;

    class ResourceManager
    {
        public:
            ResourceManager(SDL_Renderer* renderer);
            virtual ~ResourceManager();

            TextureHandle* loadTexture(const std::string& file,const SDL_Color* colorKey = nullptr);
            TTF_Font* loadFont(const std::string& file,const int size);
            Music* loadMusic(const std::string& file);
            Sound* loadSound(const std::string& file);
            

            void clearFonts();
            void deleteFont(TTF_Font*);
            void clearTextures();
            void deleteTexture(TextureHandle*);
            void clearMusics();
            void deleteMusic(Music*);
            void clearSounds();
            void deleteSound(Sound*);
            
            bool isLoaded(TextureHandle*);
            bool isLoaded(TTF_Font*);
            bool isLoaded(Music*);
            bool isLoaded(Sound*);
            
            void clear();


        protected:

        private:
            map<std::string,TextureHandle*> m_textures;
            map<pair<std::string,int>,TTF_Font*> m_fonts;
            map<std::string,Music*> m_musics;
            map<std::string,Sound*> m_sounds;
            SDL_Renderer* m_renderer = nullptr;

    };
}



#endif // RESOURCEMANAGER_H
