// Back to the polygon (FCEyN UBA ICPC Selection 2007)
// Author: Melanie Sclar

#include <iostream>
#include <cstdio>
#include <set>
#include <cmath>
using namespace std;

typedef pair<int,int> punto;
typedef pair<punto,punto> segmento;

punto creoVector (punto origen, punto destino) {
	return make_pair(destino.first - origen.first, destino.second - origen.second);
}

int productoCruz (punto u, punto v) {
	return u.first * v.second - u.second * v.first;
}

int main () {
	#ifdef ACMTUYO 
		freopen("a.in", "r", stdin);
	#endif
	
	int n;
	int x[4], y[4];
	set<segmento> borde;
	set<punto> puntos;
	
	while (cin >> n && n != -1) {
		borde.clear();
		puntos.clear();

		for (int j = 0; j < n-2; j++) {
			cin >> x[0] >> y[0] >> x[1] >> y[1] >> x[2] >> y[2];
			
			// hallo segmentos del borde
			for (int i = 0; i < 3; i++) {
				punto nuevoPunto = make_pair(x[i], y[i]);
				if (puntos.count(nuevoPunto) == 0)
					puntos.insert(nuevoPunto);
				
				segmento segmOrdenado = make_pair(make_pair(x[i], y[i]), make_pair(x[(i+1)%3], y[(i+1)%3]));
				
				segmento segmReflejado = make_pair(make_pair(x[(i+1)%3], y[(i+1)%3]),
												   make_pair(x[i], y[i]));
				
				if (borde.count(segmOrdenado) == 0) {
					borde.insert(segmOrdenado);
					borde.insert(segmReflejado);
				}
				else {
					borde.erase(segmOrdenado);
					borde.erase(segmReflejado);
				}
			}
		}
		
		punto primerPunto = *puntos.begin();
		std::set<segmento>::iterator itNext = 
				borde.lower_bound(make_pair(primerPunto, make_pair(-1001,-1001)));
			
		punto candidato1 = itNext->second; itNext++;
		punto candidato2 = itNext->second;

		punto puntoActual, proximoPunto;
		if (productoCruz(creoVector(primerPunto,candidato1),creoVector(primerPunto,candidato2)) >= 0) {
			puntoActual = candidato2;
		}
		else {
			puntoActual = candidato1;
		}
		borde.erase(make_pair(primerPunto, puntoActual));
		borde.erase(make_pair(puntoActual, primerPunto));
			
		cout << primerPunto.first << " " << primerPunto.second;
		while (!borde.empty()) {
			cout << " " << puntoActual.first << " " << puntoActual.second;
			std::set<segmento>::iterator itNext = 
				borde.lower_bound(make_pair(puntoActual, make_pair(-1001,-1001)));
			proximoPunto = itNext->second;
			
			borde.erase(make_pair(puntoActual, proximoPunto));
			borde.erase(make_pair(proximoPunto, puntoActual));
			puntoActual = proximoPunto;
		}
		cout << endl;
	}
	return 0;
}
