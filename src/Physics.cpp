#include <Physics.h>
#include <MainClass.h>
#include <Box2DDebugDrawer.h>

namespace SDL
{
    Physics::Physics(MainClass* mainClass,const Vector2& gravity,const Vector2& worldSize)
    {
        m_world = new b2World(b2Vec2(gravity.getX(),gravity.getY()));
        m_mainClass = mainClass;
        m_worldSize = worldSize;
        m_world->SetDebugDraw(new Box2DDebugDrawer(m_mainClass));
    }

    Physics::~Physics()
    {

    }

    void Physics::update()
    {
        m_world->Step(m_mainClass->getDeltaTimeInSeconds(),6,2);
    }

    void Physics::quit()
    {
        delete m_world;
    }
    
    b2Vec2 Physics::coordsPixelToWorld(const Vector2& pos)
    {
        b2Vec2 worldPos(pos.getX(),pos.getY());
        
        worldPos.x -= m_worldSize.getX()/2.0;
        worldPos.y -= m_worldSize.getY()/2.0;
        
        worldPos.y *= -1.0;
        
        worldPos.x /= m_pixelsPerMetre;
        worldPos.y /= m_pixelsPerMetre;
        
        return worldPos;
    }
    
    Vector2 Physics::coordsWorldToPixel(const b2Vec2& pos)
    {
        Vector2 pixelPos(pos.x,pos.y);
        
        pixelPos *= m_pixelsPerMetre;
        
        pixelPos.setY(pixelPos.getY()*-1.0);
        
        pixelPos += m_worldSize/2.0;
        
        return pixelPos;
    }
    
    Vector2 Physics::toVector2(const b2Vec2& vec)
    {
        return Vector2(vec.x,vec.y);
    }
    
    double Physics::scalarPixelToWorld(double d)
    {
        return d/m_pixelsPerMetre;
    }
    
    double Physics::scalarWorldToPixel(double d)
    {
        return d * m_pixelsPerMetre;
    }
    
    b2Body* Physics::createBOX(const Vector2& pos,double w,double h,float32 friction,float32 restitution,float32 density,b2BodyType type)
    {
        b2BodyDef bdef;
        b2FixtureDef fdef;
        b2PolygonShape shape;
        b2Body* body;
        
        bdef.type = type;
        bdef.position = coordsPixelToWorld(pos);
        
        fdef.density = density;
        fdef.friction = friction;
        fdef.restitution = restitution;
        
        shape.SetAsBox(scalarPixelToWorld(w/2.0),scalarPixelToWorld(h/2.0));
        
        fdef.shape = &shape;
        
        body = m_world->CreateBody(&bdef);
        body->CreateFixture(&fdef);
        
        return body;
    }
    
    b2Body* Physics::createBOX(const Vector2& pos,double w,double h,b2BodyDef& bdef,b2FixtureDef& fdef)
    {
        b2PolygonShape shape;
        b2Body* body;
        
        bdef.position = coordsPixelToWorld(pos);
        
        shape.SetAsBox(scalarPixelToWorld(w/2.0),scalarPixelToWorld(h/2.0));
        
        fdef.shape = &shape;
        
        body = m_world->CreateBody(&bdef);
        body->CreateFixture(&fdef);
        
        return body;
    }
    
    b2Body* Physics::createCIRCLE(const Vector2& pos,double radius,float32 friction,float32 restitution,float32 density,b2BodyType type)
    {
        b2BodyDef bdef;
        b2FixtureDef fdef;
        b2CircleShape shape;
        b2Body* body;
        
        bdef.type = type;
        bdef.position = coordsPixelToWorld(pos);
        
        fdef.density = density;
        fdef.friction = friction;
        fdef.restitution = restitution;
        
        shape.m_radius = scalarPixelToWorld(radius);
        
        fdef.shape = &shape;
        
        body = m_world->CreateBody(&bdef);
        body->CreateFixture(&fdef);
        
        return body;
    }
    
    b2Body* Physics::createCIRCLE(const Vector2& pos,double radius,b2BodyDef& bdef,b2FixtureDef& fdef)
    {
        b2CircleShape shape;
        b2Body* body;
        
        bdef.position = coordsPixelToWorld(pos);
        
        shape.m_radius = scalarPixelToWorld(radius);
        fdef.shape = &shape;
        
        body = m_world->CreateBody(&bdef);
        body->CreateFixture(&fdef);
        
        return body;
    }

    b2Body* Physics::createCAPSULE(const Vector2& pos,double w,double h,float32 friction,float32 restitution,float32 density,b2BodyType type)
    {
    	b2BodyDef bdef;
    	b2FixtureDef fdef;
    	b2PolygonShape boxShape;
    	b2CircleShape cShape1,cShape2;
    	b2Body* body;

    	bdef.type = type;
    	bdef.position = coordsPixelToWorld(pos);

    	fdef.friction = friction;
    	fdef.restitution = restitution;
    	fdef.density = density;


    	boxShape.SetAsBox(w/2.0,h/2.0/2.0);
    	cShape1.m_p = vectorPixelToWorld(Vector2(0.0,-h/2.0));
    	cShape1.m_radius = scalarPixelToWorld(w/2.0);
    	cShape2.m_p = vectorPixelToWorld(Vector2(0.0,h/2.0));
    	cShape2.m_radius = scalarPixelToWorld(w/2.0);


    	fdef.shape = &boxShape;
    	body = m_world->CreateBody(&bdef);
    	body->CreateFixture(&fdef);

    	fdef.shape = &cShape1;
    	body->CreateFixture(&fdef);

    	fdef.shape = &cShape2;
    	body->CreateFixture(&fdef);

    	return body;

    }
    b2Body* Physics::createCAPSULE(const Vector2& pos,double w,double h,b2BodyDef& bdef,b2FixtureDef& fdef)
    {
    	b2PolygonShape boxShape;
    	b2CircleShape cShape1,cShape2;
    	b2Body* body;

    	bdef.position = coordsPixelToWorld(pos);

    	boxShape.SetAsBox(w/2.0,h/2.0/2.0);
		cShape1.m_p = vectorPixelToWorld(Vector2(0.0,-h/4.0));
		cShape1.m_radius = scalarPixelToWorld(w/2.0);
		cShape2.m_p = vectorPixelToWorld(Vector2(0.0,h/4.0));
		cShape2.m_radius = scalarPixelToWorld(w/2.0);

		fdef.shape = &boxShape;
		body = m_world->CreateBody(&bdef);
		body->CreateFixture(&fdef);

		fdef.shape = &cShape1;
		body->CreateFixture(&fdef);

		fdef.shape = &cShape2;
		body->CreateFixture(&fdef);

		return body;
    }

    b2Vec2 Physics::vectorPixelToWorld(const Vector2& v)
    {
    	return b2Vec2(v.getX()/m_pixelsPerMetre,-v.getY()/m_pixelsPerMetre);
    }

    Vector2 Physics::vectorWorldToPixel(const b2Vec2& v)
    {
    	return Vector2(v.x*m_pixelsPerMetre,-v.y*m_pixelsPerMetre);
    }
}
