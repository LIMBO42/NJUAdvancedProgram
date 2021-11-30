#include"MathUtils.h"
#include<vector>
#include <random>
#include <unordered_map>
#include <ctime>
#include <algorithm>
#include <stdlib.h>
#include <random>
using namespace std;
/*
void VERIFY_TRUE(bool condition, int line) {
    if (!condition) {
        std::cout << 0 << std::endl;
    }
    else {
        std::cout << 1 << std::endl;
    }
}

class newComplex
{
private:
    int real; // 实部
    int imag; // 虚部
public:
    newComplex() = default;
    newComplex(int real, int imag) {
        this->real = real;
        this->imag = imag;
    }
    int getReal() {
        return real;
    }
    int getImag() {
        return imag;
    }
    // TODO 重载+, 实现复数的相加
    newComplex operator+(const newComplex& c);

    // TODO 重载-, 实现复数的相减
    newComplex operator-(const newComplex& c);

    // TODO 重载*, 实现负数的相乘
    newComplex operator*(const newComplex& c);

    // TODO 重载/, 实现复数的相除
    newComplex operator/(const newComplex& c);

    // 重载<<, 输出格式为a+bi，a和b分别是复数的实部和虚部,没有空格，不需要输出回车
    // 注意:a或b为复数的输出示例，-1-3i
    friend ostream& operator << (ostream& out, const newComplex& c);
    // 重载>>, 读取a+bi格式的输入，格式同上。
    friend istream& operator >> (istream& in, newComplex& c);
};


bool newjudgeAdd(int x, int y) {
	int sum = x + y;
	if (x > 0 && y > 0 && sum < 0) return false;
	if (x < 0 && y < 0 && sum > 0) return false;
	return true;
}
newComplex newComplex::operator+(const newComplex& c)
{

	if (!newjudgeAdd(real, c.real)) {
		throw  OverFlow("newComplex add overflow!\n");
	}
	if (!newjudgeAdd(imag, c.imag)) {
		throw  OverFlow("newComplex add overflow!\n");
	}
	int realSum = real + c.real;
	int imagSum = imag + c.imag;
	return newComplex(realSum, imagSum);
}

bool newjudgeMinus(int x, int y) {
	if (y == INT_MIN) {
		if (x >= 0) return false;
		else return true;
	}
	return newjudgeAdd(x, -y);
}

newComplex newComplex::operator-(const newComplex& c)
{

	if (!newjudgeMinus(real, c.real)) {
		throw OverFlow("newComplex add overflow!\n");
	}
	if (!newjudgeMinus(imag, c.imag)) {
		throw OverFlow("newComplex add overflow!\n");
	}
	int realSum = real - c.real;
	int imagSum = imag - c.imag;
	return newComplex(realSum, imagSum);
}

bool newjudgeMul(int x, int y) {
	int mul = x * y;
	if (mul / y != x) return false;
	return true;
}

newComplex newComplex::operator*(const newComplex& c)
{
	if (!newjudgeMul(real, c.real) || !newjudgeMul(imag, c.imag) || !newjudgeMul(real, c.imag) || !newjudgeMul(imag, c.real)) {
		throw  OverFlow("newComplex multiply overflow!\n");
	}
	int realSum = real * c.real - (imag * c.imag);
	int imagSum = real * c.imag + imag * c.real;

	return newComplex(realSum, imagSum);
}

bool newjudgeDivide(int x, int y) {
	if (y == 0) return false;
	if (x == INT_MIN && y == -1) return false;
	return true;
}

newComplex newComplex::operator/(const newComplex& c)
{
	//ac+bd
	int realx = real * c.imag + imag * c.real;
	int y = c.real * c.real + c.imag * c.imag;
	if (y == 0) throw ArithmeticError("ArithmeticError!\n");
	if (!newjudgeMul(real, c.imag) || !newjudgeMul(imag, c.real) || !newjudgeMul(c.real, c.real) || !newjudgeMul(c.imag, c.imag)) {
		throw  OverFlow("newComplex multiply overflow!\n");
	}
	//bc-ad
	int realy = imag * c.real - real * c.imag;
	if (!newjudgeDivide(realx, y) || !newjudgeDivide(realy, y)) {
		throw OverFlow("newComplex divide overflow!\n");
	}
	int realSum = realx / y;
	int imagSum = realy / y;

	return newComplex(realSum, imagSum);
}

ostream& operator<<(ostream& out, const newComplex& c)
{
	// TODO: 在此处插入 return 语句
	//虚部大于等于0
	if (c.imag >= 0) out << c.real << "+" << c.imag << "i";
	else out << c.real << "-" << -c.imag << "i";
	return out;
}

vector<string> newsplit(const string& str, const string& pattern) {
	vector<string> res;
	if (str == "") return res;
	string strs = str + pattern[0];
	size_t pos = strs.find_first_of(pattern);
	while (pos != strs.npos) {
		string temp = strs.substr(0, pos);
		res.push_back(temp);
		//
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find_first_of(pattern);
	}
	return res;
}

istream& operator>>(istream& in, newComplex& c)
{

	//只考虑 虚数
	string str = "";
	in >> str;
	size_t pos = str.find_last_of("+-");
	//实部
	string real_part = str.substr(0, pos);

	//虚部
	string imag_part = str.substr(pos + 1, str.size());

	c.real = stoi(real_part);


	imag_part = imag_part.substr(0, str.size() - 1);


	c.imag = stoi(imag_part);
	if (str[pos] == '-')	c.imag = -c.imag;
	return in;

}


class newMathUtils {
public:
    // 接受一个表达式字符串并返回计算结果。例如:calculator("(1+2i)+(2+3i)")的结果为3+5i
    static newComplex calculator(string s);
    // 使用函数calculator处理文本文件，输入文件名为 inputFileName, 输出文件名为 outputFileName。
    // 每一行为一个表达式，为了简单起见，我们假定这里的表达式不会触发InvalidExpression异常
    static void processTextFile(string inputFilename, string outputFilename);
};

newComplex newMathUtils::calculator(string s)
{
	//只支持两个复数的计算
	int first_end = s.find_first_of(")");
	string first_newComplex = s.substr(1, first_end - 1);
	char ch = s[first_end + 1];
	string second_newComplex = s.substr(first_end + 3, s.size() - first_end - 4);

	istringstream iss_first(first_newComplex);
	newComplex c1;
	iss_first >> c1;

	istringstream iss_second(second_newComplex);
	newComplex c2;
	iss_second >> c2;
	try {
		if (ch == '+') {
			return c1 + c2;
		}
		else if (ch == '-') {
			return c1 - c2;
		}
		else if (ch == '*') {
			return c1 * c2;
		}
		else if (ch == '/') {
			return c1 / c2;
		}
	}
	catch (ArithmeticError& e) {
		//cout << e.what();
		throw e;
	}
	catch (OverFlow& e) {
		//cout << e.what();
		throw e;
	}
	catch (...) {
		cout << "ERROR" << endl;
	}

	return newComplex(0, 0);
}

void newMathUtils::processTextFile(string inputFilename, string outputFilename)
{
	ifstream in(inputFilename);
	if (!in) throw FileNotFound("Cannot open " + inputFilename + "\n");
	ofstream out(outputFilename);
	if (!out) throw FileNotFound("Cannot open " + outputFilename + "\n");
	string str;
	while (in >> str) {
		newComplex c = calculator(str);
		out << c << endl;
	}
}

vector<int> random_permut(int n)
{
	vector<int> temp;
	for (int i = 0; i < n; i++)
		temp.push_back(i);
	std::random_device rng;
	std::mt19937 urng(rng());
	std::shuffle(temp.begin(), temp.end(), urng);
	//std::random_shuffle(temp.begin(), temp.end());
	return temp;
}*/



//vector<int> nums{ INT_MAX,INT_MIN,0,INT_MAX - 1,INT_MIN + 1,INT_MAX/2,INT_MIN/2,2,-2,1,-1,3};

vector<int> nums{0,1,-1,12,45367,-234,-8788,8897,2,-2,66,-66,5712,-6781};

string generate(int i,int j) {
	string res = "(";
	res += to_string(nums[i]);
	if (nums[j] >= 0) {
		res += "+";
	}
	res += to_string(nums[j])+"i";
	res += ")";
	//cout << res << endl;
	return res;
}
vector<string> compute;
void str_complex(){
	vector<string> res;
	for (int i = 0; i < nums.size(); ++i) {
		for (int j = 0; j < nums.size(); ++j) {
			res.push_back(generate(i,j));
		}
	}
	for (int i = 0; i < res.size(); ++i) {
		for (int j = 0; j < res.size(); ++j) {
			compute.push_back(res[i] + "+" + res[j]);
			compute.push_back(res[i] + "-" + res[j]);
			compute.push_back(res[i] + "*" + res[j]);
			compute.push_back(res[i] + "/" + res[j]);
		}
	}
}
/*
vector<string> Astr = {
"(2147483646-1i)+(-2+1i)",
"(0-2i)+(2147483647+2i)",
"(-2147483647-1073741824i)+(-2-1i)",
"(-2147483648+0i)/(0+0i)",
"(-2147483648-2i)*(2147483647-1i)",
"(-2147483648+1i)+(0+1073741823i)",
"(2147483646-1i)*(-1+1073741823i)",
"(2147483646+2i)*(1073741823-2147483647i)",
"(0+1i)+(2+1i)",
"(0-1i)*(-2+0i)",
"(-2147483648+2147483647i)*(2-2i)",
"(-2147483648-2i)+(3+2i)",
};*/
vector<string> Astr ={
	"(1+2i)+(3+4i)",
	"(-1-2i)/(3-4i)",
	"(7-8i)*(-9+10i)",
	"(7-8i)-(-9+10i)"
};
void A() {
	for (size_t i = 0; i < Astr.size(); ++i) {
		try {
			cout << MathUtils::calculator(Astr[i]) << endl;
		}
		catch (ArithmeticError& e) {
			cout << e.what();
		}
		catch (OverFlow& e) {
			cout << e.what();
		}
		catch (...) {
			cout << "ERROR" << endl;
		}
	}
}

/*
vector<string> Bstr = {
"(2147483646+3i)+(-2147483648+2i)",
"(-2147483647+2147483647i)-(1073741823+3i)",
"(2147483646+0i)+(2147483647+3i)",
"(-1-2147483648i)/(1+2i)",
"(2147483646+2147483646i)-(3+0i)",
"(-2147483647+0i)*(-2147483648-2147483647i)",
"(-2147483647+0i)+(2+2147483646i)",
"(2147483647+2147483646i)+(0-2i)",
"(-2147483647-2i)/(0+2147483646i)",
"(-2147483648-2i)/(2+3i)",
"(2147483646+3i)+(2147483646+1073741823i)",
"(2147483646+3i)-(-1+0i)",
};
*/
vector<string> Bstr={
"(5+6i)-(8-9i)"
};
void B() {
	for (size_t i = 0; i < Bstr.size(); ++i) {
		try {
			cout << MathUtils::calculator(Bstr[i]) << endl;
		}
		catch (ArithmeticError& e) {
			cout << e.what();
		}
		catch (OverFlow& e) {
			cout << e.what();
		}
		catch (...) {
			cout << "ERROR" << endl;
		}
	}
}

void C() {
	////srand((int)time(0));
	auto t = time(NULL);
	//srand(t);
	//cout << "time " << t<< endl;
	int index = 0;
	for (int i = 0; i < 24; i++) {
		try {
			index = rand() % compute.size();
			//cout << "index "<< index <<endl;
			cout<< MathUtils::calculator(compute[index])<<endl;
			//cout << compute[index] << endl;
		}
		catch (ArithmeticError& e) {
			cout << e.what();
		}
		catch (OverFlow& e) {
			cout << e.what();
		}
		catch (...) {
			cout << "ERROR" << endl;
			//cout << compute[index] << endl;
		}
	}
}


void D() {
	for(int i=0;i<10000;++i);
	C();
}

void E() {
	for(int i=0;i<10000;++i);
	C();
}

void F() {
	
	try {
		MathUtils::processTextFile("input1.txt", "output.txt"); // "input.txt"不存在
	}
	catch (FileNotFound& e) {
		cout << e.what();
	}
	catch (...) {
		cout << "ERROR" << endl;
	}
	C();
	/*
	try {
		MathUtils::processTextFile("input2.txt", "output.txt"); // "input2.txt"存在
		cout << "True" << endl;
	}
	catch (FileNotFound& e) {
		cout << e.what();
	}
	catch (...) {
		cout << "ERROR" << endl;
	}*/
}

void G() {
	//srand((int)time(0));
	const string file = "complex_input.txt";
	ofstream out(file);
	for (int i = 0; i < 24; i++) {
		int index = rand() % compute.size();
		out << compute[index] << endl;
	}
	out.close();
	ifstream in(file);
	string s;
	while (in >> s) {
		try {
			cout << MathUtils::calculator(s) << endl;
		}
		catch (ArithmeticError& e) {
			cout << e.what();
		}
		catch (OverFlow& e) {
			cout << e.what();
		}
		catch (...) {
			cout << "ERROR" << endl;
		}
	}
	in.close();
	remove(file.c_str());
}

void H() {
	//srand((int)time(0));
	const string file = "complex_input.txt";
	ofstream out(file);
	for (int i = 0; i < 24; i++) {
		int index = rand() % compute.size();
		out << compute[index] << endl;
	}
	out.close();
	ifstream in(file);
	string s;
	while (in >> s) {
		try {
			cout << MathUtils::calculator(s) << endl;
		}
		catch (ArithmeticError& e) {
			cout << e.what();
		}
		catch (OverFlow& e) {
			cout << e.what();
		}
		catch (...) {
			cout << "ERROR" << endl;
		}
	}
	in.close();
	remove(file.c_str());
}

void I() {
	C();
}

void J() {
	C();
}


int main() {
	////srand((int)time(0));
	str_complex();
	int num;
	cin >> num;
	switch (num) {
	case 1:
		A();
		break;
	case 2:
		C();
		break;
	case 3:
		C();
		break;
	case 4:
		D();
		break;
	case 5:
		E();
		break;
	case 6:
		F();
		break;
	case 7:
		G();
		break;
	case 8:
		H();
		break;
	case 9:
		I();
		
		break;
	case 10:
		J();
		break;
	default:
		break;
	}
	

	
}