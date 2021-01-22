#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>

using namespace std;


// lop nay duoc dung de tao bang du lieu hien thi
class Table
{
public:
	typedef std::vector< std::string > Row;
	Table(char horizontal, char vertical) :
		_horizontal(horizontal),
		_vertical(vertical)
	{
		_maxWidth = 0;
	}
	void add(string const & content)
	{
		_current.push_back(content);
	}
	void endOfRow()
	{
		_rows.push_back(_current);
		_current.assign(0, "");
	}
	void widthOfCols()
	{
		if (_rows.empty()) return;
		int rows = _rows.size();
		int cols = _rows[0].size();
		_widths.resize(cols);
		for (int i = 0; i < cols; ++i)
		{
			int width = 0;
			for (int j = 0; j < rows; ++j)
			{
				width = max(width, (int)_rows[j][i].length());
			}
			_widths[i] = width + 1;
			_maxWidth += _widths[i] + 1;
		}
	}
	void print()
	{
		int rows = _rows.size();
		int cols = _rows[0].size();
		cout << setfill(_horizontal);
		cout << setw(_maxWidth) << "" << _vertical << endl;
		cout << setfill(' ');
		for (int i = 0; i < rows; ++i)
		{
			for (int j = 0; j < cols; ++j)
			{
				cout << _vertical << setw(_widths[j]) << left << _rows[i][j];
				if (j == cols - 1)
					cout << _vertical << endl;
			}
			cout << setfill(_horizontal);
			cout << setw(_maxWidth) << "" << _vertical << endl;
			cout << setfill(' ');
		}
	}
private:
	char _horizontal;
	char _vertical;
	int _maxWidth;
	Row _current;
	vector<Row> _rows;
	vector<int> _widths;
};

// lop san pham trong sieu thi
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
		: id(id),
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

// lop sieu thi
class Market
{
public:
	Market() {}
	void add(Product const & product);
	void add();
	void print();
	void print(vector<Product> v);
	vector<Product> getProducts() { return products; }
	void manage();
	vector<Product> searchByName(string _name);
	vector<Product> searchByID(string _id);
	vector<Product> searchByPrice(long long _price);
private:
	vector<Product> products;
};

void Market::add(Product const & product)
{
	products.push_back(product);
}

void Market::add()
{
	cout << "Nhap so luong san pham can them: ";
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

void Market::print(vector<Product> v)
{
	Table t('-', '|');
	t.add("Ma san pham");
	t.add("Ten san pham");
	t.add("So luong");
	t.add("Gia moi sp(VND)");
	t.add("Ngay nhap hang");
	t.add("Nhan vien");
	t.endOfRow();
	for (int i = 0; i < v.size(); ++i)
	{
		t.add(v[i].getID());
		t.add(v[i].getName());
		t.add(to_string(v[i].getQuantity()));
		t.add(to_string(v[i].getPrice()));
		t.add(v[i].getImportDate());
		t.add(v[i].getEmployee());
		t.endOfRow();
	}
	t.widthOfCols();
	t.print();
}

vector<Product> Market::searchByName(string _name)
{
	// doi ten can tim thanh het chu thuong
	transform(_name.begin(), _name.end(), _name.begin(), [](unsigned char c) {
		return tolower(c);
	});
	int n = products.size();
	// vector chua san pham duoc tim thay
	vector<Product> ans;
	// luu lai ten san pham va id
	vector<pair<int, string>> product_name;
	for (int i = 0; i < n; ++i)
	{
		string name = products[i].getName();
		// chuyen doi thanh ten in thuong
		transform(name.begin(), name.end(), name.begin(), [](unsigned char c) {
			return tolower(c);
		});
		product_name.push_back({ i, name });
	}
	// sap xep cac san pham hien co trong sieu thi theo ten
	sort(product_name.begin(), product_name.end(), [](pair<int, string> a, pair<int, string> b) {
		return a.second.compare(b.second) < 0;
	});

	// thuc hien thuat toan tim kiem nhi phan de tim san pham
	int a = 0, b = n - 1;
	while (a <= b)
	{
		int k = (a + b) / 2;
		int value = product_name[k].second.compare(_name);
		if (value == 0) // tim thay san pham
		{
			ans.push_back(products[product_name[k].first]);
			int l = k - 1;
			while (l >= 0 && product_name[l].second.compare(_name) == 0)
			{
				ans.push_back(products[product_name[l].first]);
				l--;
			}
			int r = k + 1;
			while (r < n && product_name[r].second.compare(_name) == 0)
			{
				ans.push_back(products[product_name[r].first]);
				r++;
			}
			break;
		}
		else if (value < 0)
		{
			a = k + 1;
		}
		else
			b = k - 1;
	}

	// tra ve ket qua
	return ans;
}

vector<Product> Market::searchByID(string _id)
{
	// doi ma can tim thanh het chu thuong
	transform(_id.begin(), _id.end(), _id.begin(), [](unsigned char c) {
		return tolower(c);
	});
	int n = products.size();
	// vector chua san pham duoc tim thay
	vector<Product> ans;
	// luu lai ma san pham va index
	vector<pair<int, string>> product_name;
	for (int i = 0; i < n; ++i)
	{
		string id = products[i].getID();
		// chuyen doi thanh ma in thuong
		transform(id.begin(), id.end(), id.begin(), [](unsigned char c) {
			return tolower(c);
		});
		product_name.push_back({ i, id });
	}
	// sap xep cac san pham hien co trong sieu thi theo ma san pham
	sort(product_name.begin(), product_name.end(), [](pair<int, string> a, pair<int, string> b) {
		return a.second.compare(b.second) < 0;
	});

	// thuc hien thuat toan tim kiem nhi phan de tim san pham
	int a = 0, b = n - 1;
	while (a <= b)
	{
		int k = (a + b) / 2;
		int value = product_name[k].second.compare(_id);
		if (value == 0) // tim thay san pham
		{
			ans.push_back(products[product_name[k].first]);
			break;
		}
		else if (value < 0)
		{
			a = k + 1;
		}
		else
			b = k - 1;
	}

	// tra ve ket qua
	return ans;
}

vector<Product> Market::searchByPrice(long long _price)
{
	int n = products.size();
	// vector chua san pham duoc tim thay
	vector<Product> ans;
	// sap xep cac san pham hien co trong sieu thi theo gia san pham
	vector<Product> _products = products;
	sort(_products.begin(), _products.end(), [](Product a, Product b) {
		return a.getPrice() < b.getPrice();
	});

	// thuc hien thuat toan tim kiem nhi phan de tim san pham
	int a = 0, b = n - 1;
	while (a <= b)
	{
		int k = (a + b) / 2;
		long long price = _products[k].getPrice();
		if (price == _price) // tim thay san pham
		{
			ans.push_back(_products[k]);
			int l = k - 1;
			while (l >= 0 && _products[l].getPrice() == _price)
			{
				ans.push_back(_products[l]);
				l--;
			}
			int r = k + 1;
			while (r < n && _products[r].getPrice() == _price)
			{
				ans.push_back(_products[r]);
				r++;
			}
			break;
		}
		else if (price < _price)
		{
			a = k + 1;
		}
		else
			b = k - 1;
	}

	// tra ve ket qua
	return ans;
}

void Market::manage()
{
	while (1)
	{
		cout << "Chuong trinh quan ly xuat nhap san pham cua sieu thi" << endl;
		cout << "1. Nhap du lieu san pham" << endl;
		cout << "2. Xuat du lieu kho" << endl;
		cout << "3. Tim kiem san pham theo ten san pham" << endl;
		cout << "4. Tim kiem san pham theo ma san pham" << endl;
		cout << "5. Tim kiem san pham theo gia san pham" << endl;
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
		case 3:
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << '\t' << "Nhap ten san pham can tim: ";
			string name;
			getline(cin, name);
			vector<Product> ans = searchByName(name);
			cout << '\t' << "Ket qua tim kiem san pham ten " << name << " la: " << endl;
			print(ans);
			break;
		}
		case 4:
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << '\t' << "Nhap ma san pham can tim: ";
			string id;
			getline(cin, id);
			vector<Product> ans = searchByID(id);
			cout << '\t' << "Ket qua tim kiem san pham co ID " << id << " la: " << endl;
			print(ans);
			break;
		}
		case 5:
		{
			cout << '\t' << "Nhap gia san pham can tim: ";
			long long price;
			cin >> price;
			vector<Product> ans = searchByPrice(price);
			cout << '\t' << "Ket qua tim kiem san pham co gia = " << price << " la: " << endl;
			print(ans);
			break;
		}
		case 0:
			return;
		default:
			break;
		}
		cout << "_______________________________________________________________________" << endl;
	}
}

int main()
{
	Market market;
	market.manage();

	return 0;
}
