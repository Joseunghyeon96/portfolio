#ifndef UTILS_H_
#define UTILS_H_

// ==================================================================================
struct Vector2 {
	float x;
	float y;

	const int X() const{ return (int)x; }
	const int Y() const{ return (int)y; }
	Vector2(float x = 0, float y = 0) : x(x), y(y) {}
	Vector2(const Vector2& other) : Vector2(other.x, other.y) {}

	static Vector2 zero;
	static Vector2 ones;
	static Vector2 up;
	static Vector2 down;
	static Vector2 left;
	static Vector2 right;

	float magnitude() {
		return sqrt(this->sqrMagnitude());
	}

	double sqrMagnitude() {
		return (double)x * x + y * y;
	}

	Vector2 operator-(const Vector2& other) {
		return Vector2{ this->x - other.x, this->y - other.y };
	}

	static friend Vector2 operator-(Vector2& a, const Vector2& b);

	static float Distance(Vector2& a, const Vector2& b);
	
	void operator=(const Vector2& other)
 	{
		this->x = other.x;
		this->y = other.y;
	}
	Vector2 operator+(const Vector2& other) {
		return Vector2{ this->x + other.x, this->y + other.y };
	}
	bool operator==(const Vector2& other) {
		return (x == other.x && y == other.y);
	}

	Vector2& operator+=(const Vector2& other) {
		x += other.x, y += other.y;
		return *this;
	}

	Vector2& operator-=(const Vector2& other) {
		x -= other.x, y -= other.y;
		return *this;
	}
};

// ==================================================================================

enum class KeyCode {
	Space = 0,
	Left,
	Right,
	Up,
	Down,

	Esc,
	Enter,

	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
};


static vector<WORD> keyCodeTable{
	VK_SPACE, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
	VK_ESCAPE, VK_RETURN,
	0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
	0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A
};


// ==================================================================================

int Random_Range(int min, int max);
void setColor(int foreground, int background);
#endif 
