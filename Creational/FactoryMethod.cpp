/* This example will implement the Factory Method pattern such that the factory
 * will produce 2d game objects that each have a sprite and collider (more
 * attributes can be added later).
 */

#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>

class Sprite {
  public:
    virtual ~Sprite() = default;
    virtual void draw() = 0;
};

class Collider {
  public:
    virtual ~Collider() = default;
    virtual void collide() = 0;
};

class BasicSprite : public Sprite {
  public:
    void draw() override {
      std::cout << "Drawing a basic sprite...\n";
    }
};

class BasicCollider : public Collider {
  public:
    void collide() override {
      std::cout << "Colliding basic collider...\n";
    }
};

class GameObject {
  public:
    virtual ~GameObject() = default;

    virtual void draw() = 0;
    virtual void collide() = 0;
};

class Circle : public GameObject {
    std::unique_ptr<Sprite> sprite;
    std::unique_ptr<Collider> collider;

    double radius;

  public:
    explicit Circle(double r)
      : radius(r),
        sprite(std::make_unique<BasicSprite>()),
        collider(std::make_unique<BasicCollider>()) {}

    [[nodiscard]] double getArea() const {
      return M_PI * radius * radius;
    }

    [[nodiscard]] double getCircumference() const {
      return 2 * M_PI * radius;
    }

    void draw() override {
      sprite->draw();
    }

    void collide() override {
      collider->collide();
    }
};

class Square : public GameObject {
    std::unique_ptr<Sprite> sprite;
    std::unique_ptr<Collider> collider;

    double sideLength;

  public:
    explicit Square(double length)
      : sideLength(length),
        sprite(std::make_unique<BasicSprite>()),
        collider(std::make_unique<BasicCollider>()) {}

    [[nodiscard]] double getArea() const {
      return sideLength * sideLength;
    }

    [[nodiscard]] double getPerimeter() const {
      return 4 * sideLength;
    }

    void draw() override {
      sprite->draw();
    }

    void collide() override {
      collider->collide();
    }
};

class Rectangle : public GameObject {
    std::unique_ptr<Sprite> sprite;
    std::unique_ptr<Collider> collider;

    double sideLength;
    double sideHeight;

  public:
    Rectangle(double length, double height)
      : sideLength(length),
        sideHeight(height),
        sprite(std::make_unique<BasicSprite>()),
        collider(std::make_unique<BasicCollider>()) {}

    [[nodiscard]] double getArea() const {
      return sideLength * sideHeight;
    }

    [[nodiscard]] double getPerimeter() const {
      return 2 * (sideLength + sideHeight);
    }

    void draw() override {
      sprite->draw();
    }

    void collide() override {
      collider->collide();
    }
};

class Triangle : public GameObject {
    std::unique_ptr<Sprite> sprite;
    std::unique_ptr<Collider> collider;

    double sideLength;

  public:
    explicit Triangle(double length)
      : sideLength(length),
        sprite(std::make_unique<BasicSprite>()),
        collider(std::make_unique<BasicCollider>()) {}

    [[nodiscard]] double getArea() const {
      return std::sqrt(3) * 0.5 * sideLength;
    }

    [[nodiscard]] double getCircumference() const {
      return 3 * sideLength;
    }

    void draw() override {
      sprite->draw();
    }

    void collide() override {
      collider->collide();
    }
};

class Obround : public GameObject {
    std::unique_ptr<Sprite> sprite;
    std::unique_ptr<Collider> collider;

    double sideLength;
    double sideHeight;

  public:
    Obround(double length, double height)
      : sideLength(length),
        sideHeight(height),
        sprite(std::make_unique<BasicSprite>()),
        collider(std::make_unique<BasicCollider>()) {
      if (length < height) {
        throw std::invalid_argument("Length cannot be less than height for an obround");
      }
    }

    [[nodiscard]] double getArea() const {  // (PI * r ^ 2) * (l x h of rectangle between the semicircles)
      return M_PI * 0.5 * sideHeight * 0.5 * sideHeight * (sideLength - sideHeight) * (sideHeight);
    }

    [[nodiscard]] double getPerimeter() const {
      return M_PI * sideHeight * 2 * (sideLength - sideHeight);
    }

    void draw() override {
      sprite->draw();
    }

    void collide() override {
      collider->collide();
    }
};

enum class ObjectType { Circle, Square, Rectangle, Triangle, Obround };

class GameObjectFactory {
  public:
    static std::unique_ptr<GameObject> createObject(ObjectType type, double size) {
      switch (type) {
        case ObjectType::Circle:
          return std::make_unique<Circle>(size);
        case ObjectType::Square:
          return std::make_unique<Square>(size);
        case ObjectType::Triangle:
          return std::make_unique<Triangle>(size);
        default:
          return nullptr;
      }
    }

    static std::unique_ptr<GameObject> createObject(ObjectType type, double size1, double size2) {
      switch (type) {
        case ObjectType::Rectangle:
          return std::make_unique<Rectangle>(size1, size2);
        case ObjectType::Obround:
          return std::make_unique<Obround>(size1, size2);
        default:
          return nullptr;
      }
    }
};

int main() {
  std::unique_ptr<GameObject> obround;

  std::unique_ptr<GameObject> circle = GameObjectFactory::createObject(ObjectType::Circle, 5.0);
  std::unique_ptr<GameObject> square = GameObjectFactory::createObject(ObjectType::Square, 5.0);
  std::unique_ptr<GameObject> triangle = GameObjectFactory::createObject(ObjectType::Triangle, 5.0);

  std::unique_ptr<GameObject> rectangle = GameObjectFactory::createObject(ObjectType::Rectangle, 10.0, 2.0);
  try {
    obround = GameObjectFactory::createObject(ObjectType::Obround, 9.0, 2.0);
  } catch (const std::invalid_argument& e) {
    std::cerr << "Failed to create obround: " << e.what() << std::endl;
  }

  circle->draw();
  circle->collide();
  triangle->draw();
  triangle->collide();
  square->draw();
  square->collide();
  rectangle->draw();
  rectangle->collide();

  if (obround) {
    obround->draw();
    obround->collide();
  }

  return 0;
}
