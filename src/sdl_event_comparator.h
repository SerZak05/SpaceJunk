#pragma once
#include <SDL.h>
#include <utility>
#include "action.h"

class SDL_Event_comp {
public:
	bool operator()(const SDL_Event& aa, const SDL_Event& bb) const {
		SDL_Event a = aa;
		SDL_Event b = bb;
		char* va = reinterpret_cast<char*>(&a);
		char* vb = reinterpret_cast<char*>(&b);
		int n = sizeof(a);
		for (int i = 0; i < n; ++i) {
			if (va[i] != vb[i]) return va[i] < vb[i];
		}
		return false;
	}
};

class Pair_comp {
public:
	bool operator() (const std::pair<SDL_Event, ActionType>& a, const std::pair<SDL_Event, ActionType>& b) const {
		SDL_Event_comp comp;
		bool res1 = comp(a.first, b.first);
		bool res2 = comp(b.first, a.first);
		if (res1 || res2)
			return res1;
		return a.second < b.second;
	}
};