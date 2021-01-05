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
		int value = (_q.y - _p.y) * (_r.x - _q.x) - (_q.x - _p.x) * (_r.y - _q.x);

		if (value == 0) return 0;
		return (value > 0) ? 1 : 2;
	}

	bool CheckIntersection(Edge* _edgeOne, Edge* _edgeTwo) {
		int o1 = CheckOrientation(_edgeOne->start, _edgeOne->end, _edgeTwo->start);
		int o2 = CheckOrientation(_edgeOne->start, _edgeOne->end, _edgeTwo->end);
		int o3 = CheckOrientation(_edgeTwo->start, _edgeTwo->end, _edgeOne->start);
		int o4 = CheckOrientation(_edgeTwo->start, _edgeTwo->end, _edgeOne->end);

		if (o1 != o2 && o3 != o4) {
			return true;
		}

		if (o1 == 0 && CheckSegment(_edgeOne->start, _edgeTwo->start, _edgeOne->end)) {
			return true;
		}
		if (o2 == 0 && CheckSegment(_edgeOne->start, _edgeTwo->end, _edgeOne->end)) {
			return true;
		}
		if (o3 == 0 && CheckSegment(_edgeTwo->start, _edgeOne->start, _edgeTwo->end)) {
			return true;
		}
		if (o4 == 0 && CheckSegment(_edgeTwo->start, _edgeOne->end, _edgeTwo->end)) {
			return true;
		}

		return false;
	}
};

