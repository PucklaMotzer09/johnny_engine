#ifndef PHYSICS_SPRITE_H
#define PHYSICS_SPRITE_H
#include <Sprite.h>
#include <Box2D/Box2D.h>

namespace SDL
{
    class TextureHandle;
    
    class PhysicsSprite : public SDL::Sprite
    {
    public:
        PhysicsSprite(b2Body* body = nullptr,int order = 0);
        PhysicsSprite(const char* file,const SDL_Color* colorKey = nullptr,b2Body* body = nullptr,int order = 0);
        PhysicsSprite(TextureHandle*,b2Body* body = nullptr,int order = 0);
        virtual ~PhysicsSprite();
        
        virtual bool init();
        virtual bool m_update();
        virtual void m_quit();
        
        b2Body* getBody() {return m_body;}
        bool getAutomaticDestroy() {return m_automaticDestroy;}
        const Vector2& getOffset() const {return m_offset;}
        
        void setBody(b2Body* body) {m_body = body; body->SetUserData(this);}
        void setAutomaticDestroy(bool b) {m_automaticDestroy = b;}
        void setOffset(const Vector2& v) {m_offset = v;}

        virtual void BeginContact(b2Contact*,b2Fixture*,b2Fixture*);
        virtual void EndContact(b2Contact*,b2Fixture*,b2Fixture*);
        virtual void PreSolve(b2Contact*,b2Fixture*,b2Fixture*,const b2Manifold*);
        virtual void PostSolve(b2Contact*,b2Fixture*,b2Fixture*,const b2ContactImpulse*);

    protected:
        bool m_automaticDestroy = true;
        Vector2 m_offset;
        
    private:
        b2Body* m_body = nullptr;
    };
}


#endif
