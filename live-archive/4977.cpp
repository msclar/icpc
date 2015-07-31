// 4977 - Enter the dragon (CERC 2010)
// Author: Melanie Sclar

#include <iostream>
#include <set>
#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;

int forecast[1000009];
int ultimaLluvia[1000009]; // ultima lluvia en el lago i

int main () {
	int z, n, m;
	set <int> noLlueve;
	vector < pair<int, int> > respuesta;
	
	cin >> z;
	for (int tc = 1; tc <= z; tc++) {
		noLlueve.clear();
		respuesta.clear();
		bool hayRespuesta = true;
		
		cin >> n >> m;
		for (int lake = 1; lake <= n; lake++) {
			ultimaLluvia[lake] = -1;
		}
		
		for (int d = 0; d < m; d++) {
			cin >> forecast[d];
			
			if (forecast[d] == 0) {
				noLlueve.insert(d);
			}
			else {
				std::set<int>::iterator itElem = noLlueve.upper_bound(ultimaLluvia[forecast[d]]);
				if (itElem == noLlueve.end() || *itElem >= d) {
					hayRespuesta = false;
				}
				else {
					respuesta.push_back(make_pair(*itElem, forecast[d]));
					noLlueve.erase(itElem);
				}
				ultimaLluvia[forecast[d]] = d;
			}
			
		}
		
		sort(respuesta.begin(), respuesta.end());
		if (hayRespuesta) {
			cout << "YES" << endl;
			int rtaSize = (int) respuesta.size(), actual = 0;
			bool yaImprimi = false;
			for (int i = 0; i < m; i++) {
				if (forecast[i] != 0)
					continue;
				
				if (yaImprimi)
					cout << " ";
				yaImprimi = true;
					
				if (actual < rtaSize && respuesta[actual].first == i) {
					cout << respuesta[actual].second;
					actual++;
				}
				else {
					cout << 0;
				}
			}
			cout << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
	return 0;
}
