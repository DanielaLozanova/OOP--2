#pragma once
#include <iostream>
#include<fstream>
#include <assert.h>
using namespace std;
class Box
{
private:
	double x;
	double y;
	double z;
public:
	Box(double x = 0, double y = 0, double z = 0);

	void setX(double x);
	void setY(double y);
	void setZ(double z);
	double getX() const;
	double getY() const;
	double getZ() const;
	double volume() const;
	void print() const;
	void saveBox(ofstream& file) const;
};

class Material
{
private:
	char* name;
	bool breakable;
	void copy(const Material& other);
public:
	Material(const char* name = "", bool breakable = true);
	~Material();
	Material(const Material& other);
	Material& operator=(const Material& other);
	const char* getName() const;
	bool getBreakable() const;
	void print() const;
	void saveMaterial(ofstream& file) const;
};
const Material mat{ "",true };
class Element
{
private:
	Material material;
	double weight;
public:
	Element(const Material& material = mat, double weight = 0.0);
	bool breakableElement() const;
	void print() const;
	void saveElement(ofstream& file) const;
	double getWeight() const;
};
const Box b{ 0.0,0.0,0.0 };
class Item
{
private:
	Box box;
	char* address;
	double cost;
	unsigned int capacity;
	unsigned int size;
	Element* elements;
	void setAddress(const char* address);
	void copy(const Item& other);
	void saveElements(ofstream& file) const;
public:
	Item(const Box& box = b, const char* address = "", double cost = 0, unsigned int capacity = 4);
	virtual ~Item();
	Item(const Item& other);
	Item& operator=(const Item& other);
	virtual Item* clone() const = 0;
	bool addItem(const Element& element);
	double weightElements() const;
	virtual double costShip() const;
	void printElements() const;
	virtual void print() const;
	bool save(const char* path) const;
	Element* getElements() const;
	unsigned int getCapacity() const;
	double getCost() const;
	double getBoxVolume() const;
	bool breakableItem() const;
};
class Furniture : public Item
{
private:
	char* marka;
	void copy(const char* marka);
public:
	Furniture(const Box& box = b, const char* address = "", double cost = 0, unsigned int capacity = 4, const char* marka = "");
	virtual ~Furniture();
	Furniture(const Furniture& other);
	Furniture& operator=(const Furniture& other);
	virtual Item* clone() const;
	double weightFurniture() const;
	bool breakableFurniture() const;
	virtual double costShip() const;
	virtual void print() const;
};
class Shoes : public Item
{
private:
	bool tryS;
public:
	Shoes(const Box& box = b, const char* address = "", double cost = 0, unsigned int capacity = 4, bool tryS = false);
	virtual ~Shoes() {};
	virtual Item* clone() const;
	virtual double costShip() const;
	virtual void print() const;
};
class CourierCompany
{
	unsigned int numberItems;
	unsigned int pos;
	Item** items;
	void copy(const CourierCompany& other);
	void clear();
	void resize(int numberItems);
	void sort();
	bool addEl(unsigned int pos);
public:
	CourierCompany(unsigned int numberItems = 4);
	~CourierCompany();
	CourierCompany(const CourierCompany& other);
	CourierCompany& operator=(const CourierCompany& other);
	void addItemToCC(const Item* item);
	double income() const;
	double totalVolume() const;
	void printCC() const;
	void ranking();
};
