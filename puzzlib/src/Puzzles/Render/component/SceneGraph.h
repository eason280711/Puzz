#pragma once

#include  "Event/Event.h"
#include "Core/ref_ptr.h"
#include "Puzzles/Render/component/render.h"

namespace puzz
{
    typedef SceneGraph::Object<SceneGraph::TranslationRotationScalingTransformation2D> Object2D;
    typedef SceneGraph::Scene<SceneGraph::TranslationRotationScalingTransformation2D> Scene2D;

    struct InstanceData {
        Matrix3 transformation;
        Color3 color;
    };

    class RenderStuffHolder {
    public:
        RenderStuffHolder();
        ~RenderStuffHolder();

        void draw();

        void onMouseEvent(Array<double> &info);

        GL::Texture2D& getTexture() { return tex; }

    private:
        b2Body* createBody(Object2D& object, const Vector2& size, b2BodyType type, const DualComplex& transformation, Float density = 1.0f);

        GL::Mesh _mesh{NoCreate};
        GL::Buffer _instanceBuffer{NoCreate};
        Shaders::FlatGL2D _shader{NoCreate};
        Containers::Array<InstanceData> _instanceData;

        Scene2D _scene;
        Object2D* _cameraObject;
        SceneGraph::Camera2D* _camera;
        SceneGraph::DrawableGroup2D _drawables;
        Containers::Optional<b2World> _world;
        GL::Framebuffer fbo;
        GL::Texture2D tex;
    };

    class BoxDrawable : public SceneGraph::Drawable2D {
    public:
        explicit BoxDrawable(Object2D& object, Containers::Array<InstanceData>& instanceData, const Color3& color, SceneGraph::DrawableGroup2D& drawables) : SceneGraph::Drawable2D{ object, &drawables }, _instanceData(instanceData), _color{ color } {}

    private:
        void draw(const Matrix3& transformation, SceneGraph::Camera2D&) override {
            arrayAppend(_instanceData, InPlaceInit, transformation, _color);
        }

        Containers::Array<InstanceData>& _instanceData;
        Color3 _color;
    };

    RenderStuffHolder::RenderStuffHolder():fbo(GL::defaultFramebuffer.viewport())
    {
        tex.setMagnificationFilter(GL::SamplerFilter::Linear)
            .setMinificationFilter(GL::SamplerFilter::Linear, GL::SamplerMipmap::Linear)
            .setWrapping(GL::SamplerWrapping::ClampToEdge)
            .setStorage(1, GL::TextureFormat::RGBA8, Vector2i(1920, 1080));  // 假設你的紋理大小為 800x600

        fbo.attachTexture(GL::Framebuffer::ColorAttachment{0}, tex, 0)
            .mapForDraw({ {0, GL::Framebuffer::ColorAttachment{0}} });

        const DualComplex globalTransformation = DualComplex::fromMatrix(Matrix3{}).normalized();

        /* Configure camera */
        _cameraObject = new Object2D{ &_scene };
        _camera = new SceneGraph::Camera2D{ *_cameraObject };
        _camera->setAspectRatioPolicy(SceneGraph::AspectRatioPolicy::Extend)
            .setProjectionMatrix(Matrix3::projection({ 20.0f * 16.0f / 9.0f, 20.0f }));

        /* Create the Box2D world with the usual gravity vector */
        _world.emplace(b2Vec2{ 0.0f, -9.81f });

        /* Create an instanced shader */
        _shader = Shaders::FlatGL2D{ Shaders::FlatGL2D::Configuration{}
            .setFlags(Shaders::FlatGL2D::Flag::VertexColor |
                      Shaders::FlatGL2D::Flag::InstancedTransformation) };

        /* Box mesh with an (initially empty) instance buffer */
        _mesh = MeshTools::compile(Primitives::squareSolid());
        _instanceBuffer = GL::Buffer{};
        _mesh.addVertexBufferInstanced(_instanceBuffer, 1, 0,
            Shaders::FlatGL2D::TransformationMatrix{},
            Shaders::FlatGL2D::Color3{});

        /* Create the ground */
        auto ground = new Object2D{ &_scene };
        createBody(*ground, { 11.0f, 0.5f }, b2_staticBody, DualComplex::translation(Vector2::yAxis(-8.0f)));
        new BoxDrawable{ *ground, _instanceData, 0xa5c9ea_rgbf, _drawables };

        /* Create a pyramid of boxes */
        for (std::size_t row = 0; row != 15; ++row) {
            for (std::size_t item = 0; item != 15 - row; ++item) {
                auto box = new Object2D{ &_scene };
                const DualComplex transformation = globalTransformation * DualComplex::translation(
                    { Float(row) * 0.6f + Float(item) * 1.2f - 8.5f, Float(row) * 1.0f - 6.0f });
                createBody(*box, { 0.5f, 0.5f }, b2_dynamicBody, transformation);
                new BoxDrawable{ *box, _instanceData, 0x2f83cc_rgbf, _drawables };
            }
        }
    }



    b2Body* RenderStuffHolder::createBody(Object2D& object, const Vector2& halfSize, const b2BodyType type, const DualComplex& transformation, const Float density) {
        b2BodyDef bodyDefinition;
        bodyDefinition.position.Set(transformation.translation().x(), transformation.translation().y());
        bodyDefinition.angle = Float(transformation.rotation().angle());
        bodyDefinition.type = type;
        b2Body* body = _world->CreateBody(&bodyDefinition);

        b2PolygonShape shape;
        shape.SetAsBox(halfSize.x(), halfSize.y());

        b2FixtureDef fixture;
        fixture.friction = 0.8f;
        fixture.density = density;
        fixture.shape = &shape;
        body->CreateFixture(&fixture);
        body->GetUserData().pointer = reinterpret_cast<std::uintptr_t>(&object);
        object.setScaling(halfSize);

        return body;
    }

    inline void RenderStuffHolder::draw()
    {
        fbo.bind();
        fbo.clear(GL::FramebufferClear::Color);

        /* Step the world and update all object positions */
        _world->Step(1.0f / 60.0f, 6, 2);
        for (b2Body* body = _world->GetBodyList(); body; body = body->GetNext()) {
            (*reinterpret_cast<Object2D*>(body->GetUserData().pointer))
                .setTranslation({ body->GetPosition().x, body->GetPosition().y })
                .setRotation(Complex::rotation(Rad(body->GetAngle())));
        }

        /* Populate instance data with transformations and colors */
        arrayResize(_instanceData, 0);
        _camera->draw(_drawables);

        /* Upload instance data to the GPU and draw everything in a single call */
        _instanceBuffer.setData(_instanceData, GL::BufferUsage::DynamicDraw);
        _mesh.setInstanceCount(_instanceData.size());
        _shader.setTransformationProjectionMatrix(_camera->projectionMatrix())
            .draw(_mesh);

        GL::defaultFramebuffer.bind();
    }

    inline void RenderStuffHolder::onMouseEvent(Array<double> &info)
    {
        double xpos = info[0], ypos = info[1];
        int windowWidth = info[2], windowHeight = info[3];
        const auto position = _camera->projectionSize() * Vector2::yScale(-1.0f) * (Vector2{ float(xpos), float(ypos) } / Vector2{ float(windowWidth), float(windowHeight) } *Vector2{ 16.0f / 9.0f, 1.0f } - Vector2{ 0.5f });


        auto destroyer = new Object2D{ &_scene };
        createBody(*destroyer, { 0.5f, 0.5f }, b2_dynamicBody, DualComplex::translation(position), 2.0f);
        new BoxDrawable{ *destroyer, _instanceData, 0xffff66_rgbf, _drawables };
    }

    inline RenderStuffHolder::~RenderStuffHolder()
    {
    }

}