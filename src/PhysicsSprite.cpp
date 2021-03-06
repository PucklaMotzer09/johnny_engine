#include <PhysicsSprite.h>
#include <LogManager.h>
#include <MainClass.h>
#include <Physics.h>
#include <iostream>

namespace SDL
{
    PhysicsSprite::PhysicsSprite(b2Body* body,int order) : Sprite(order),
        m_body(body)
    {
        setName("PhysicsSprite");
    }
    PhysicsSprite::PhysicsSprite(const char* file,const SDL_Color* colorKey,b2Body* body,int order) : Sprite(file,colorKey,order),
        m_body(body)
    {
        setName("PhysicsSprite");
    }
    PhysicsSprite::PhysicsSprite(TextureHandle* tex,b2Body* body,int order) : Sprite(tex,order),
        m_body(body)
    {
        setName("PhysicsSprite");
    }
    PhysicsSprite::~PhysicsSprite()
    {
        
    }
    
    bool PhysicsSprite::init()
    {
        if(!Sprite::init())
            return false;

        if(m_body)
        {
        	m_body->SetUserData(this);
        }
            
        return true;
    }
    bool PhysicsSprite::m_update()
    {
        if(!Sprite::m_update())
            return false;
        
        if(m_mainClass->getPhysics())
        {
            m_position = m_mainClass->getPhysics()->coordsWorldToPixel(m_body->GetPosition()) - (m_size/2.0) + m_offset;
            m_rotation = -m_body->GetAngle() / MATH_PI * 180.0;
        }
        else
        {
            LogManager::log("You need to activate the physics");
        }
        
        if(m_automaticDestroy)
        {
            Vector2 worldSize = m_mainClass->getPhysics()->getWorldSize();            if(m_position.getX() + m_size.getX()*2.0 < 0 || m_position.getY() + m_size.getY()*2.0 < 0 ||
               m_position.getX()-m_size.getX() > worldSize.getX() || m_position.getY()-m_size.getY() > worldSize.getY())
            {
                getParent()->removeChild(this);
            }
        }
        
        
        return true;
    }
    void PhysicsSprite::m_quit()
    {
        Sprite::m_quit();
        m_mainClass->getPhysics()->getWorld()->DestroyBody(m_body);
    }

    void PhysicsSprite::BeginContact(b2Contact* contact,b2Fixture* self,b2Fixture* other)
    {

    }
	void PhysicsSprite::EndContact(b2Contact* contact,b2Fixture* self,b2Fixture* other)
	{

	}
	void PhysicsSprite::PreSolve(b2Contact* contact,b2Fixture* self,b2Fixture* other,const b2Manifold* oldManifold)
	{

	}
	void PhysicsSprite::PostSolve(b2Contact* contact,b2Fixture* self,b2Fixture* other,const b2ContactImpulse* impulse)
	{

	}
}
