#pragma once
#include <SDL.h>

struct Edge {
	SDL_Point start;
	SDL_Point end;
};

struct Ray {
	Edge edge;
	bool intersected;
};

class RayCastingTools {
public:
	int GetMax(int _a, int _b) {
		if (_a > _b) return _a;
		return _b;
	}

	int GetMin(int _a, int _b) {
		if (_a > _b) return _b;
		return _a;
	}

	bool CheckSegment(SDL_Point _p, SDL_Point _q, SDL_Point _r) {
		if (_q.x <= GetMax(_p.x, _r.x) && _q.x >= GetMin(_p.x, _r.x) &&
			_q.y <= GetMax(_p.y, _r.y) && _q.y >= GetMin(_p.y, _r.y)) {
			return true;
		}
		return false;
	}

	int CheckOrientation(SDL_Point _p, SDL_Point _q, SDL_Point _r) {
		int value = (_q.y - _p.y) * (_r.x - _q.x) - (_q.x - _p.x) * (_r.y - _q.y);

		if (value == 0) return 0;
		return (value > 0) ? 1 : 2;
	}

	bool CheckIntersection(Edge* _one, Edge* _two) {
		int o1 = CheckOrientation(_one->start, _one->end, _two->start);
		int o2 = CheckOrientation(_one->start, _one->end, _two->end);
		int o3 = CheckOrientation(_two->start, _two->end, _one->start);
		int o4 = CheckOrientation(_two->start, _two->end, _one->end);

		if (o1 != o2 && o3 != o4) {
			return true;
		}

		if (o1 == 0 && CheckSegment(_one->start, _two->start, _one->end)) {
			return true;
		}
		if (o2 == 0 && CheckSegment(_one->start, _two->end, _one->end)) {
			return true;
		}
		if (o3 == 0 && CheckSegment(_two->start, _one->start, _two->end)) {
			return true;
		}
		if (o4 == 0 && CheckSegment(_two->start, _one->end, _two->end)) {
			return true;
		}

		return false;
	}
};

