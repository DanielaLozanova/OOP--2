#include "Header3.h"
Box::Box(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Box::setX(double x)
{
	this->x = x;
}
void Box::setY(double y)
{
	this->y = y;
}
void Box::setZ(double z)
{
	this->z = z;
}
double Box::getX() const
{
	return x;
}
double Box::getY() const
{
	return y;
}
double Box::getZ() const
{
	return z;
}
double Box::volume() const
{
	return x * y * z;
}
void Box::print() const
{
	cout << "Width: " << getX() << endl;
	cout << "Lenght: " << getY() << endl;
	cout << "Height: " << getZ() << endl;
}
void Box::saveBox(ofstream& file) const
{
	file << "Width: " << getX() << endl;
	file << "Lenght: " << getY() << endl;
	file << "Height: " << getZ() << endl;
}

//Material

void Material::copy(const Material& other)
{
	this->name = new char[strlen(other.name) + 1];
	strcpy(this->name, other.name);
	this->breakable = other.breakable;
}
Material::Material(const char* name, bool breakable)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->breakable = breakable;
}
Material::~Material()
{
	delete[] name;
}
Material::Material(const Material& other)
{
	copy(other);
}
Material& Material::operator=(const Material& other)
{
	if (this != &other)
	{
		delete[]name;
		copy(other);
	}
	return *this;
}
const char* Material::getName() const
{
	return name;
}
bool Material::getBreakable() const
{
	return breakable;
}
void Material::print() const
{
	cout << "Name of material: " << getName() << endl;
	cout << "The material is ";
	if (getBreakable() == true)
	{
		cout << "breakable" << endl;
	}
	else
	{
		cout << "not breakable" << endl;
	}
}
void Material::saveMaterial(ofstream& file) const
{
	file << "Name of material: " << getName() << endl;
	file << "The material is ";
	if (getBreakable() == true)
	{
		file << "breakable." << endl;
	}
	else
	{
		file << "not breakable." << endl;
	}
}
//Element

Element::Element(const Material& material, double weight) : material(material.getName(), material.getBreakable())
{
	this->weight = weight;
}
bool Element::breakableElement() const
{
	return material.getBreakable();
}
void Element::print() const
{
	material.print();
	cout << "Weight of element: " << getWeight() << endl;
}
void Element::saveElement(ofstream& file) const
{
	material.saveMaterial(file);
	file << "Weight of element: " << getWeight();
}
double Element::getWeight() const
{
	return weight;
}

//Item

void Item::setAddress(const char* address)
{
	this->address = new char[strlen(address) + 1];
	assert(this->address != nullptr);
	strcpy(this->address, address);
}
void Item::copy(const Item& other)
{
	this->box = other.box;
	setAddress(other.address);
	this->cost = other.cost;
	this->capacity = other.capacity;
	this->elements = new Element[capacity];
	for (int i = 0; i < capacity; ++i)
	{
		this->elements[i] = other.elements[i];
	}
}
Item::Item(const Box& box, const char* address, double cost, unsigned int capacity)
{
	this->box = box;
	setAddress(address);
	this->cost = cost;
	this->capacity = capacity;
	this->size = 0;
	this->elements = new Element[capacity];
}
Item::~Item()
{
	delete[] address;
	delete[] elements;
}
Item::Item(const Item& other)
{
	copy(other);
}
Item& Item::operator=(const Item& other)
{
	if (this != &other)
	{
		delete[] address;
		delete[] elements;
		copy(other);
	}
	return *this;
}
bool Item::addItem(const Element& element)
{
	if (box.volume() < element.getWeight() + weightElements())
	{
		return false;
	}
	if (size < capacity)
	{
		elements[size++] = element;
	}
	else
	{
		Element* ptr = new Element[capacity + 1];
		for (int i = 0; i < capacity; ++i)
		{
			ptr[i] = elements[i];
		}
		ptr[capacity++] = element;
		delete[] elements;
		elements = ptr;
		++size;
	}
	return true;
}
double Item::weightElements() const
{
	double sum = 0.0;
	for (int i = 0; i < capacity; ++i)
	{
		sum = elements[i].getWeight() + sum;
	}
	return sum;
}
double Item::costShip() const
{
	return weightElements()*cost;
}
void Item::printElements() const
{
	for (int i = 0; i < capacity; ++i)
	{
		elements[i].print();
	}
}
void Item::print() const
{
	box.print();
	cout << "Address: " << address << endl;
	cout << "Cost: " << cost << endl;
	cout << "Number of elements: " << capacity << endl;
	printElements();
	cout << endl;
}
void Item::saveElements(ofstream& file) const
{
	for (int i = 0; i < capacity; ++i)
	{
		elements[i].saveElement(file);
	}
}
bool Item::save(const char* path) const
{
	ofstream file(path, ios::out | ios::app);
	if (!file)
	{
		cerr << "File cannot open " << endl;
		return false;
	}
	box.saveBox(file);
	file << "Address: " << address << endl;
	file << "Cost: " << cost << endl;
	file << "Number of elements: " << capacity << endl;
	saveElements(file);
	file.close();
	return true;
}
Element* Item::getElements() const
{
	return elements;
}
unsigned int Item::getCapacity() const
{
	return capacity;
}
double Item::getCost() const
{
	return cost;
}
double Item::getBoxVolume() const
{
	return box.volume();
}
bool Item::breakableItem() const
{
	for (int i = 0; i < capacity; ++i)
	{
		if (elements[i].breakableElement() == true)
		{
			return true;
		}
	}
	return false;
}

//Furniture

void Furniture::copy(const char* marka)
{
	this->marka = new char[strlen(marka) + 1];
	strcpy(this->marka, marka);
}

Furniture::Furniture(const Box& box, const char* address, double cost, unsigned int capacity, const char* marka)
	:Item(box, address, cost, capacity)
{
	copy(marka);
}
Furniture::Furniture(const Furniture& other) : Item(other)
{
	copy(other.marka);
}
Furniture& Furniture::operator=(const Furniture& other)
{
	if (this != &other)
	{
		Item::operator=(other);
		delete[] this->marka;
		copy(marka);
	}
	return *this;

}
Furniture::~Furniture()
{
	delete[] marka;
}
Item* Furniture::clone() const
{
	return new Furniture(*this);
}
double Furniture::weightFurniture() const
{
	return weightElements();
}
bool Furniture::breakableFurniture() const
{
	Element* elements = getElements();
	unsigned int cap = getCapacity();
	for (int i = 0; i < cap; ++i)
	{
		if (elements[i].breakableElement() == true)
		{
			return true;
		}
	}
	return false;
}
double Furniture::costShip() const
{
	Element* elements = getElements();
	unsigned int cap = getCapacity();
	double sum = 0.0;
	for (int i = 0; i < cap; ++i)
	{
		if (breakableItem() == true)
		{
			double t = 1.0;
			double temp = (1.5 / 100);
			t = Item::costShip()*temp;
			return Item::costShip() + t;
		}
	}
	return Item::costShip();
}
void Furniture::print() const
{
	Item::print();
	cout << "Marka: " << marka<< endl;
}
//Shoes

Shoes::Shoes(const Box& box, const char* address, double cost, unsigned int capacity, bool tryS)
	:Item(box, address, cost, capacity)
{
	this->tryS = tryS;
}
Item* Shoes::clone() const
{
	return new Shoes(*this);
}
double Shoes::costShip() const
{
	if (tryS == true)
	{
		double temp = (3 / 100) * getCost()* weightElements();
		return getCost() * weightElements() + temp;
	}
	return getCost() * weightElements();
}
void Shoes::print() const
{
	Item::print();
	if (tryS == true)
	{
		cout << "Shoes can be tryed on." << endl;
	}
	else
	{
		cout << "Shoes cannot be tryed on." << endl;
	}
}

// CourierCompany

void CourierCompany::copy(const CourierCompany& other)
{
	this->items = new Item*[other.numberItems];
	for (int i = 0; i < other.pos; ++i)
	{
		this->items[i] = other.items[i]->clone();
	}
	this->numberItems = other.numberItems;
	this->pos = other.pos;
}
CourierCompany::CourierCompany(unsigned int numberItems)
{
	this->numberItems = numberItems;
	this->pos = 0;
	this->items = new Item*[numberItems];
}
void CourierCompany::clear()
{
	for (int i = 0; i < pos; ++i)
	{
		delete[] items[i];
	}
	delete[] items;
}
CourierCompany::~CourierCompany()
{
	clear();
}
CourierCompany::CourierCompany(const CourierCompany& other)
{
	copy(other);
}
CourierCompany& CourierCompany::operator=(const CourierCompany& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}
void CourierCompany::resize(int numberItems)
{
	Item** temp;
	temp = new Item*[numberItems];
	for (int i = 0; i < this->pos; ++i)
	{
		temp[i] = items[i]->clone();
	}
	clear();
	items = temp;
	this->numberItems = numberItems;
}
bool CourierCompany::addEl(unsigned int pos)
{
	cout << "Enter element" <<endl;
	cout << "Enter Material name: ";
	char matName[65];
	char br[10];
	bool b;
	double wei;
	cin.get();
	cin.getline(matName, 64);
	cout << "Enter breakable: ";
	//cin.get();
	cin.getline(br, 10);
	if (!strcmp("Yes", br))
	{
		b = true;
	}
	else
	{
		b = false;
	}
	//cin.get();
	cout << "Enter weight: ";
	cin >> wei;
	Element temp({ matName,br }, wei);
	cout << endl;
	if (items[pos]->addItem(temp))
	{
		return true;
	}
	else
	{
		cout << "Element is too big"<<endl;
		return false;
	}

}
void CourierCompany::addItemToCC(const Item* item)
{
	if (pos == numberItems)
	{
		resize(numberItems + 1);
	}
	items[pos] = item->clone();
	for (int i = 0; i < items[pos]->getCapacity(); ++i)
	{
		if (!addEl(pos))
		{
			--i;
		}
	}
	++pos;
}
double CourierCompany::income() const
{
	double sum = 0.0;
	for (int i = 0; i < pos; ++i)
	{
		sum += items[i]->costShip();
	}
	return sum;
}
double CourierCompany::totalVolume() const
{
	double sum = 0.0;
	for (int i = 0; i < pos; ++i)
	{
		sum += items[i]->getBoxVolume();
	}
	return sum;
}
void CourierCompany::printCC() const
{
	for (int i = 0; i < pos; ++i)
	{
		items[i]->print();
	}
	cout << "The number of items is: " << pos << endl;
}
void CourierCompany::sort()
{
	Item* temp = nullptr;
	for (int i = 0; i < pos; ++i)
	{
		for (int j = 0; j < pos - 1; ++j)
		{
			if (items[j]->costShip() < items[j + 1]->costShip())
			{
				temp = items[j + 1];
				items[j + 1] = items[j];
				items[j] = temp;
			}
		}
	}
}
void CourierCompany::ranking()
{
	sort();
	int temp = 10;
	if (pos < 10)
	{
	   temp = pos;
	}
	for (int i = 0; i < temp; ++i)
	{
		items[i]->print();
	}
}