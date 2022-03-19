double sqrtz(double _val) {
	double low = 0;
	double high = _val;
	double mid = 0;

	while (high - low > 0.0000001) {
		mid = low + (high - low) / 2;
		if (mid*mid > _val) {
			high = mid;
		}
		else {
			low = mid;
		}
	}
	return mid;
}

#pragma region Vectors
typedef struct Vector2
{
	float x, y;

}Vector2, *PVector2;

typedef struct Vector3
{
	float x, y, z;
	Vector3()
	{
		x = y = z = 0;
	}
	Vector3(float x, float y, float z)
	{
		this->x = x; this->y = y; this->z = z;
	}
	const bool operator== (Vector3 const &Vector)
	{
		return (this->x == Vector.x && this->y == Vector.y && this->z == Vector.z);
	}
	const Vector3& operator+ (Vector3 const &Vector)
	{
		return Vector3(this->x + Vector.x, this->y + Vector.y, this->z + Vector.z);
	}
	const Vector3& operator- (Vector3 const &Vector)
	{
		return Vector3(this->x - Vector.x, this->y - Vector.y, this->z - Vector.z);
	}

	float Distance(Vector3 const &Vector)
	{
		return sqrtz(DistanceEx(Vector));
	}
	float DistanceEx(Vector3 const &Vector)
	{
		float _x = this->x - Vector.x, _y = this->y - Vector.y, _z = this->z - Vector.z;
		return ((_x * _x) + (_y * _y) + (_z * _z));
	}
	const Vector3 &RoundHalfUp()
	{
		return Vector3(floor(this->x + 0.5), floor(this->y + 0.5), floor(this->z + 0.5));
	}\
		const Vector3 &RoundHalfDown()
	{
		return Vector3(floor(this->x + 0.5), floor(this->y + 0.5), floor(this->z + 0.5));
	}
} Vector3, *PVector3;
typedef struct Vector4
{
    float x, y, z, a;
    Vector4(){ x = y = z = a = 0;}
    Vector4(float x, float y, float z, float a){
            this->x = x;
            this->y = y;
            this->z = z;
            this->a = a;
    }
 
} Vector4, *PVector4;
#pragma endregion

namespace Adr{
	enum addies{
		//General
		R_SetFrameFog = 0x4A0700,
		FPS = 0x36DA70,
		Cbuff_AddText = 0x2B1C14,

		//Huds
		R_RegisterFont = 0x459C6C,
		Material_RegisterHandle = 0x46540C,
		R_AddCmdDrawText = 0x473658,
		R_AddCmdDrawStretchPic = 0x472E78,
	};
};

enum Buttons
{
    R1 = 0x4B,
    L1 = 0x43,
    R2 = 0xE7,
    L2 = 0xDB,
    R3 = 0xD3,
    L3 = 0xC3,
    Down = 255,
    Left = 0x10B,
    Right = 0x117,
    Up = 0xF3,
    Cross = 0x13,
    Square = 0x27,
    Triangle = 0x33,
    Circle = 0x1B,
};
bool detect(Buttons Button)
{
	return (*(char*)(0xCBCBC0 + Button) != 0);
}