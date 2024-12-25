#include <iostream>
#include <vector>
#include <string>

class ModularHouse
{
public:
    std::vector<std::string> parts;

    void ListParts() const
    {
        std::cout << "House parts: ";
        for (const auto &part : parts)
        {
            std::cout << part << " ";
        }
        std::cout << std::endl;
    }
};

class Documentation
{
public:
    std::vector<std::string> pages;

    void ListPages() const
    {
        std::cout << "Documentation pages: ";
        for (const auto &page : pages)
        {
            std::cout << page << " ";
        }
        std::cout << std::endl;
    }
};

class Builder
{
public:
    virtual ~Builder() {}

    virtual void BuildWalls() = 0;
    virtual void BuildFloor() = 0;
    virtual void BuildRoof() = 0;

    virtual ModularHouse *GetHouse() = 0;

    virtual Documentation *GetDocumentation() = 0;
};

class WoodHouseBuilder : public Builder
{
private:
    ModularHouse *house;
    Documentation *documentation;

public:
    WoodHouseBuilder()
    {
        Reset();
    }

    ~WoodHouseBuilder()
    {
        delete house;
        delete documentation;
    }

    void Reset()
    {
        house = new ModularHouse();
        documentation = new Documentation();
    }

    void BuildWalls() override
    {
        house->parts.push_back("Wooden Walls");
        documentation->pages.push_back("Wooden Walls Description");
    }

    void BuildFloor() override
    {
        house->parts.push_back("Wooden Floor");
        documentation->pages.push_back("Wooden Floor Description");
    }

    void BuildRoof() override
    {
        house->parts.push_back("Wooden Roof");
        documentation->pages.push_back("Wooden Roof Description");
    }

    ModularHouse *GetHouse() override
    {
        ModularHouse *result = house;
        house = new ModularHouse();
        return result;
    }

    Documentation *GetDocumentation() override
    {
        Documentation *result = documentation;
        documentation = new Documentation();
        return result;
    }
};

/**
 * Конкретный строитель для кирпичного дома.
 */
class BrickHouseBuilder : public Builder
{
private:
    ModularHouse *house;
    Documentation *documentation;

public:
    BrickHouseBuilder()
    {
        Reset();
    }

    ~BrickHouseBuilder()
    {
        delete house;
        delete documentation;
    }

    void Reset()
    {
        house = new ModularHouse();
        documentation = new Documentation();
    }

    void BuildWalls() override
    {
        house->parts.push_back("Brick Walls");
        documentation->pages.push_back("Brick Walls Description");
    }

    void BuildFloor() override
    {
        house->parts.push_back("Concrete Floor");
        documentation->pages.push_back("Concrete Floor Description");
    }

    void BuildRoof() override
    {
        house->parts.push_back("Brick Roof");
        documentation->pages.push_back("Brick Roof Description");
    }

    ModularHouse *GetHouse() override
    {
        ModularHouse *result = house;
        house = new ModularHouse();
        return result;
    }

    Documentation *GetDocumentation() override
    {
        Documentation *result = documentation;
        documentation = new Documentation();
        return result;
    }
};

/**
 * Класс Директора управляет процессом построения.
 */
class Director
{
private:
    Builder *builder;

public:
    void SetBuilder(Builder *builder)
    {
        this->builder = builder;
    }

    // Построение минимального дома
    void BuildMinimalHouse()
    {
        builder->BuildWalls();
    }

    // Построение полного дома
    void BuildFullHouse()
    {
        builder->BuildWalls();
        builder->BuildFloor();
        builder->BuildRoof();
    }
};

/**
 * Клиентский код.
 */
void ClientCode()
{
    Director director;

    // Пример 1: Деревянный дом
    WoodHouseBuilder woodBuilder;
    director.SetBuilder(&woodBuilder);

    std::cout << "Building Wooden House:\n";
    director.BuildFullHouse();
    ModularHouse *woodenHouse = woodBuilder.GetHouse();
    woodenHouse->ListParts();
    Documentation *woodenDocs = woodBuilder.GetDocumentation();
    woodenDocs->ListPages();
    delete woodenHouse;
    delete woodenDocs;

    // Пример 2: Кирпичный дом
    BrickHouseBuilder brickBuilder;
    director.SetBuilder(&brickBuilder);

    std::cout << "\nBuilding Brick House:\n";
    director.BuildFullHouse();
    ModularHouse *brickHouse = brickBuilder.GetHouse();
    brickHouse->ListParts();
    Documentation *brickDocs = brickBuilder.GetDocumentation();
    brickDocs->ListPages();
    delete brickHouse;
    delete brickDocs;

    // Пример 3: Минимальный деревянный дом
    std::cout << "\nBuilding Minimal Wooden House:\n";
    director.SetBuilder(&woodBuilder);
    director.BuildMinimalHouse();
    ModularHouse *minimalWoodenHouse = woodBuilder.GetHouse();
    minimalWoodenHouse->ListParts();
    Documentation *minimalWoodenDocs = woodBuilder.GetDocumentation();
    minimalWoodenDocs->ListPages();
    delete minimalWoodenHouse;
    delete minimalWoodenDocs;
}

/**
 * Основной метод программы.
 */
int main()
{
    ClientCode();
    return 0;
}
