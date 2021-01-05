#pragma once
#include "table.h"


class Product
{
private:
	string id;			// ma san pham
	string name;		// ten san pham
	int quantity;		// so luong
	long long price;	// gia san pham / 1 cai
	string importDate;	// ngay nhap
	string employee;	// ten nhan vien nhap hang
public:
	Product() {}
	Product(string id, string name, int quantity, long long price, string importDate, string employee)
	:	id(id),
		name(name),
		quantity(quantity),
		price(price),
		importDate(importDate),
		employee(employee)
	{ }
	string getID() { return id; }
	string getName() { return name; }
	int getQuantity() { return quantity; }
	long long getPrice() { return price; }
	string getImportDate() { return importDate; }
	string getEmployee() { return employee; }
	void setID(string id)
	{
		this->id = id;
	}
	void setName(string name)
	{
		this->name = name;
	}
	void setQuantity(int quantity)
	{
		this->quantity = quantity;
	}
	void setPrice(long long price)
	{
		this->price = price;
	}
	void setImportDate(string importDate)
	{
		this->importDate = importDate;
	}
	void setEmployee(string employee)
	{
		this->employee = employee;
	}
};

class Market
{
public:
	Market(){}
	void add(Product const & product);
	void add();
	void print();
	vector<Product> getProducts() { return products; }
	void manage();
private:
	vector<Product> products;
};

void Market::add(Product const & product)
{
	products.push_back(product);
}

void Market::add()
{
	cout << "Nhap so luong san pham: ";
	int n;
	cin >> n;
	products.resize(n);
	string id;
	string name;
	int quantity;
	long long price;
	string importDate;
	string employee;
	for (int i = 0; i < n; ++i)
	{
		cout << '\t' << "Nhap du lieu san pham thu: " << i + 1 << endl;
		cout << '\t' << '\t' << "Ma san pham: ";
		cin >> id;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << '\t' << '\t' << "Ten san pham: ";
		getline(cin, name);
		cout << '\t' << '\t' << "So luong: ";
		cin >> quantity;
		cout << '\t' << '\t' << "Gia san pham: ";
		cin >> price;
		cout << '\t' << '\t' << "Ngay nhap kho: ";
		cin >> importDate;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << '\t' << '\t' << "Ten nhan vien: ";
		getline(cin, employee);
		products[i].setID(id);
		products[i].setName(name);
		products[i].setQuantity(quantity);
		products[i].setPrice(price);
		products[i].setImportDate(importDate);
		products[i].setEmployee(employee);
	}
}

void Market::print()
{
	Table t('-', '|');
	t.add("Ma san pham");
	t.add("Ten san pham");
	t.add("So luong");
	t.add("Gia moi sp(VND)");
	t.add("Ngay nhap hang");
	t.add("Nhan vien");
	t.endOfRow();
	for (int i = 0; i < products.size(); ++i)
	{
		t.add(products[i].getID());
		t.add(products[i].getName());
		t.add(to_string(products[i].getQuantity()));
		t.add(to_string(products[i].getPrice()));
		t.add(products[i].getImportDate());
		t.add(products[i].getEmployee());
		t.endOfRow();
	}
	t.widthOfCols();
	t.print();
}

void Market::manage()
{
	while (1)
	{
		cout << "Chuong trinh quan ly xuat nhap san pham cua sieu thi" << endl;
		cout << "1. Nhap du lieu san pham" << endl;
		cout << "2. Xuat du lieu kho" << endl;
		cout << "0. Ket thuc chuong trinh" << endl;
		int option;
		cin >> option;
		switch (option)
		{
		case 1:
			add();
			break;
		case 2:
			print();
			break;
		case 0:
			return;
		default:
			break;
		}
		cout << "_______________________________________________________________________" << endl;
	}
}
