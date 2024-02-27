// ora.cpp:
// OVERLOAD OPERATORI MATEMATICI (qui vediamo solo il + e il -
// OVERLOAD OPERATORI INCREMENTO/DECREMENTO (++ E --): PREFISSI (e postfissi?)
// OVERLOAD OPERATORI DI INPUT / OUTPUT (>> e <<)
// OVERLOAD OPERATORI DI CONFRONTO E ASSEGNAZIONE (> < >= <= ==  = )
// DOPPIO OVERLOAD DI UN OPERATORE (Esempio +)


// CLASSE ORA: ore e minuti

#include <iostream>
#include <fstream>
using namespace std;

class Ora {
		int ore, minuti;

	public:
		Ora() {
			ore = minuti = 0;
		}

		Ora(int o, int m) {
			ore = o;
			minuti = m;
		}
		void print() {
			print(cout);
		};
		
		void print(ostream &out) {
			out << ore << ":" << minuti;
		};



		Ora operator+(Ora o); // Ora + Ora = Ora    Overload del +
		Ora operator-(Ora o); // Ora - Ora = Ora    Overload del -

		// OVERLOAD OPERATORI ++ e –-
		Ora & operator++();
		Ora & operator--();

		friend istream & operator>>(istream &in,  Ora &d);
		friend ostream & operator<<(ostream &out, Ora &d);

		friend int oracmp(Ora a, Ora b);

		Ora operator+(int minuti); // Operatore +: Ora + int = Ora

		bool operator >(Ora o);
		bool operator <(Ora o);
		bool operator >=(Ora o);
		bool operator <=(Ora o);
		bool operator !=(Ora o);
		bool operator ==(Ora o);
};

Ora Ora::operator+(Ora o) { // Ora + Ora = Ora
	Ora dep = *this;
	dep.minuti += o.minuti;
	while (dep.minuti >= 60)
		dep.ore++, dep.minuti -= 60;
	dep.ore += o.ore;
	if (dep.ore > 24)
		dep.ore %= 24;
	return dep;
}

// Ora Ora::operator-(Ora o) // CODIFICARE COME ESERCIZIO

Ora Ora::operator-(Ora o) {
	Ora app;
	app.minuti = minuti - o.minuti;
	app.ore = ore - o.ore;

	if (app.minuti < 0) {
		app.minuti += 60;
		app.ore--;
	}

	if (app.ore < 0)
		app.ore += 24;
	return app;
}

Ora & Ora::operator++() { // Overload ++
	Ora dep(0, 1); // NOTA: NON è il richiamo di una funzione,
	// ma di un costruttore
	*this = *this + dep;
	return *this;
}

istream & operator>>(istream &in, Ora &d)
// nota: NON è un metodo ma una funzione friend
{
	cout << "Ora---->";
	in >> d.ore;
	cout << "Minuti->";
	in >> d.minuti;
	in.get();   // invio pendente
	return in;  // per impilare eventualmente come cin >> n1 >> n2;
}

ostream & operator<<(ostream &out, Ora &d) {
	d.print(out);
	return out;
}


Ora Ora::operator+(int minuti)
// OVERLOAD DOPPIO dell'Operatore + --> Ora + int minuti = Ora
{
	Ora dep; // dep.ore  è azzerato
	dep.minuti = minuti;
	*this = *this + dep; // Precedente overload del +
	return *this;
}


int oracmp(Ora a, Ora b) {
	if (a.ore != b.ore)
		return a.ore - b.ore;
	return a.minuti - b.minuti;
}

bool Ora::operator>(Ora o) {
	return oracmp(*this, o) > 0;  // Overload > (maggiore)
}

bool Ora::operator<(Ora o) {
	return oracmp(*this, o) < 0;
}

bool Ora::operator>=(Ora o) {
	return oracmp(*this, o) >= 0;
}

bool Ora::operator<=(Ora o) {
	return oracmp(*this, o) <= 0;
}

bool Ora::operator!=(Ora o) {
	return oracmp(*this, o) != 0;
}

bool Ora::operator==(Ora o) {
	return oracmp(*this, o) == 0;
}

int main() {
	Ora a(12, 20), b(10, 10), c;
	ofstream fw("out.txt");
	
	cout << a << endl;
	fw << b << endl;
	
	cin >> a >> b;
	if (a > b)
		cout << "A > B";
	if (a >= b)
		cout << "A >= B";
	if (a < b)
		cout << "A < B";
	if (a <= b)
		cout << "A <= B";
	fw.close();
	
	return 0;
}
