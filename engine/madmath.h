
#ifndef MADMATH_H
#define MADMATH_H

#include "base.h"


#ifndef MADMATH_INLINE
#define MADMATH_INLINE static inline
#endif


#define PI32 3.14159265359f
#define PI64 3.14159265358979323846


#define Max(val0, val1) (val0 > val1 ? val0 : val1)
#define Min(val0, val1) (val0 < val1 ? val0 : val1)
#define Clamp(val, min, max) (val < min ? min : (val > max ? max : val))
#define Sign(val)  ((val < 0) ? -1 : 1)
#define Abs(val)       ((val < 0) ? -(val) : val)



#define Floor(x)      __builtin_floorf(x)
#define Trunc(x)      __builtin_truncf(x)
#define Mod(x, limit) __builtin_fmodf(x, limit)
#define Cos(theta)    __builtin_cosf(theta)
#define Acos(val)     __builtin_acosf(val)
#define Sin(theta)    __builtin_sinf(theta)
#define Asin(theta)   __builtin_asinf(theta)
#define Tan(theta)    __builtin_tanf(theta)
#define Atan2(y,x)    __builtin_atan2f(y,x)
#define Sqrt(x)       __builtin_sqrtf(x)

typedef union CvtF32ToI32{
	float f;
	uint64_t i;
} CvtF32ToI32;

#define F(x) (((CvtF32ToI32) { .i = (x) }).f)


MADMATH_INLINE void
Fast_cos_sin(float theta, float *cos_result, float *sin_result) {
	f32 y_sign = 1.0f;
	f32 x_sign = 1.0f;

	if (theta < PI32 / 2) {
	} else if (theta < PI32) {
		theta = PI32 - theta;
		x_sign = -1.0f;
	} else if (theta < 3 * PI32 / 2) {
		theta = theta - PI32;
		y_sign = -1.0f;
		x_sign = -1.0f;
	} else {
		theta = PI32 * 2 - theta;
		y_sign = -1.0f;
	}

	// theta in 0, pi/2
	float y, x;
	if (theta < PI32/4.0f) {
		float theta2 = theta * theta;
		// Calculates sin(theta) for theta in [0, pi/4].
		y = theta * (F(0x3F800000) + theta2 * (F(0xBE2AAAA0) + theta2 * (F(0x3C0882C0) + theta2 * F(0xB94C6000))));
		// Calculates cos(theta) for theta in [0, pi/4].
		x = F(0x3F800000) + theta2 * (F(0xBEFFFFDA) + theta2 * (F(0x3D2A9F60) + theta2 * F(0xBAB22C00)));
	}
	else {
		theta = PI32 / 2 - theta;
		float theta2 = theta * theta;
		// Calculates cos(theta) for theta in [0, pi/4].
		y = F(0x3F800000) + theta2 * (F(0xBEFFFFDA) + theta2 * (F(0x3D2A9F60) + theta2 * F(0xBAB22C00)));
		// Calculates sin(theta) for theta in [0, pi/4].
		x = theta * (F(0x3F800000) + theta2 * (F(0xBE2AAAA0) + theta2 * (F(0x3C0882C0) + theta2 * F(0xB94C6000))));
	}

	y *= y_sign;
	x *= x_sign;

	*sin_result = y;
	*cos_result = x;
}



MADMATH_INLINE float
Square(float x) {
	return x*x;
}

MADMATH_INLINE float
Lerp(float a, float b, float t) {
	return (1-t) * a + (b * t);
}

MADMATH_INLINE float
Radians(float degrees) {
	return degrees * PI32 / 180.0f;
}

MADMATH_INLINE float
Degrees(float radians) {
	return radians * 180.0f / PI32;
}

typedef struct {
	union {
		struct {
			float x, y;
		};
		struct {
			float r, g;
		};
		struct {
			float s, t;
		};
		float data[2];
	};
} Vec2;


#define V2(val_x,val_y) (Vec2){.x=val_x, .y=val_y}

MADMATH_INLINE Vec2
V2_Add(Vec2 v0, Vec2 v1) {
	Vec2 result;
	result.x = v0.x + v1.x;
	result.y = v0.y + v1.y;
	return result;
}

MADMATH_INLINE Vec2
V2_Sub(Vec2 v0, Vec2 v1) {
	Vec2 result;
	result.x = v0.x - v1.x;
	result.y = v0.y - v1.y;
	return result;
}

MADMATH_INLINE Vec2
V2_Mul(Vec2 v0, Vec2 v1) {
	Vec2 result;
	result.x = v0.x * v1.x;
	result.y = v0.y * v1.y;
	return result;
}

MADMATH_INLINE Vec2
V2_Mulf(Vec2 v0, float scalar) {
	Vec2 result;
	result.x = v0.x * scalar;
	result.y = v0.y * scalar;
	return result;
}

MADMATH_INLINE float
V2_Dot(Vec2 v0, Vec2 v1) {
	float result = (v0.x * v1.x) + (v0.y * v1.y);
	return result;
}

MADMATH_INLINE float
V2_Cross(Vec2 v0, Vec2 v1) {
	float result = (v0.x * v1.y) - (v0.y * v1.x);
	return result;
}

MADMATH_INLINE float
V2_Cross3(Vec2 v0, Vec2 v1, Vec2 v2) {
	float result = V2_Cross(V2_Sub(v1, v0), V2_Sub(v2, v0));
	return result;
}

MADMATH_INLINE float
V2_Lensq(Vec2 v) {
	return (v.x * v.x) + (v.y * v.y);
}

MADMATH_INLINE float
V2_Len(Vec2 v) {
	return Sqrt((v.x * v.x) + (v.y * v.y));
}

MADMATH_INLINE Vec2
V2_Normalize(Vec2 v) {
	float inv_len = 1.0f/V2_Len(v);
	Vec2 result;
	result.x = v.x * inv_len;
	result.y = v.y * inv_len;
	return result;
}

MADMATH_INLINE Vec2
V2_Lerp(Vec2 v0, Vec2 v1, float t) {
	Vec2 result;
	result.x = Lerp(v0.x, v1.x, t);
	result.y = Lerp(v0.y, v1.y, t);
	return result;
}

MADMATH_INLINE Vec2
V2_Nlerp(Vec2 v0, Vec2 v1, float t) {
	Vec2 result;
	result.x = Lerp(v0.x, v1.x, t);
	result.y = Lerp(v0.y, v1.y, t);
	return V2_Normalize(result);
}


typedef struct {
	union {
		struct {
			float x, y, z;
		};
		struct {
			float r, g, b;
		};
		struct {
			Vec2 xy;
			float _dummy_z;
		};
		struct {
			Vec2 rg;
			float _dummy_b;
		};
		struct {
			float _dummy_x;
			Vec2 yz;
		};
		struct {
			float _dummy_r;
			Vec2 gb;
		};
		float data[3];
	};
} Vec3;

#define V3(val_x, val_y, val_z) (Vec3){.x=val_x, .y=val_y, .z=val_z}

MADMATH_INLINE Vec3
V3_Add(Vec3 v0, Vec3 v1) {
	Vec3 result;
	result.x = v0.x + v1.x;
	result.y = v0.y + v1.y;
	result.z = v0.z + v1.z;
	return result;
}

MADMATH_INLINE Vec3
V3_Sub(Vec3 v0, Vec3 v1) {
	Vec3 result;
	result.x = v0.x - v1.x;
	result.y = v0.y - v1.y;
	result.z = v0.z - v1.z;
	return result;
}

MADMATH_INLINE Vec3
V3_Mul(Vec3 v0, Vec3 v1) {
	Vec3 result;
	result.x = v0.x * v1.x;
	result.y = v0.y * v1.y;
	result.z = v0.z * v1.z;
	return result;
}

MADMATH_INLINE Vec3
V3_Mulf(Vec3 v, float scalar) {
	Vec3 result;
	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return result;
}

MADMATH_INLINE float
V3_Dot(Vec3 v0, Vec3 v1) {
	float result = (v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z);
	return result;
}

MADMATH_INLINE Vec3
V3_Cross(Vec3 v0, Vec3 v1) {
	Vec3 result;
	result.x = (v0.y * v1.z) - (v0.z * v1.y);
	result.y = (v0.x * v1.z) - (v0.z * v1.x);
	result.z = (v0.x * v1.y) - (v0.y * v1.x);
	return result;
}

MADMATH_INLINE Vec3
V3_Cross3(Vec3 v0, Vec3 v1, Vec3 v2) {
	Vec3 result = V3_Cross(V3_Sub(v1, v0), V3_Sub(v2, v0));
	return result;
}

MADMATH_INLINE float
V3_Len(Vec3 v) {
	return Sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

MADMATH_INLINE Vec3
V3_Normalize(Vec3 v) {
	float inv_len = 1.0f/V3_Len(v);
	Vec3 result;
	result.x = v.x * inv_len;
	result.y = v.y * inv_len;
	result.z = v.z * inv_len;
	return result;
}

MADMATH_INLINE Vec3
V3_Lerp(Vec3 v0, Vec3 v1, float t) {
	Vec3 result;
	result.x = Lerp(v0.x, v1.x, t);
	result.y = Lerp(v0.y, v1.y, t);
	result.z = Lerp(v0.z, v1.z, t);
	return result;
}

MADMATH_INLINE Vec3
V3_Nlerp(Vec3 v0, Vec3 v1, float t) {
	Vec3 result;
	result.x = Lerp(v0.x, v1.x, t);
	result.y = Lerp(v0.y, v1.y, t);
	result.z = Lerp(v0.z, v1.z, t);
	return V3_Normalize(result);
}



typedef struct {
	union {
		struct {
			float x, y, z, w;
		};
		struct {
			float r, g, b, a;
		};
		struct {
			Vec3 xyz;
			float  _dummy0;
		};
		struct {
			float  _dummy1;
			Vec3 yzw;
		};
		struct {
			Vec3 rgb;
			float  _dummy2;
		};
		struct {
			float  _dummy3;
			Vec3 gba;
		};
		struct {
			Vec2 xy;
			Vec2 zw;
		};
		struct {
			float  _dummy4;
			Vec2 yz;
			float  _dummy5;
		};
		struct {
			Vec2 rg;
			Vec2 ba;
		};
		struct {
			float  _dummy6;
			Vec2 gb;
			float  _dummy7;
		};
		float data[4];
	};
} Vec4;

#define V4(val_x, val_y, val_z, val_w) (Vec4){.x=val_x, .y=val_y, .z=val_z, .w=val_w}

MADMATH_INLINE Vec4
V4_Add(Vec4 v0, Vec4 v1) {
	Vec4 result;
	result.x = v0.x + v1.x;
	result.y = v0.y + v1.y;
	result.z = v0.z + v1.z;
	result.w = v0.w + v1.w;
	return result;
}

MADMATH_INLINE Vec4
V4_Sub(Vec4 v0, Vec4 v1) {
	Vec4 result;
	result.x = v0.x - v1.x;
	result.y = v0.y - v1.y;
	result.z = v0.z - v1.z;
	result.w = v0.w - v1.w;
	return result;
}

MADMATH_INLINE Vec4
V4_Mul(Vec4 v0, Vec4 v1) {
	Vec4 result;
	result.x = v0.x * v1.x;
	result.y = v0.y * v1.y;
	result.z = v0.z * v1.z;
	result.w = v0.w * v1.w;
	return result;
}

MADMATH_INLINE Vec4
V4_Mulf(Vec4 v, float scalar) {
	Vec4 result;
	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	result.w = v.w * scalar;
	return result;
}

MADMATH_INLINE float
V4_Dot(Vec4 v0, Vec4 v1) {
	float result = (v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z) + (v0.w * v1.w);
	return result;
}

MADMATH_INLINE float
V4_Len(Vec4 v) {
	return Sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w));
}

MADMATH_INLINE Vec4
V4_Normalize(Vec4 v) {
	float inv_len = 1.0f/V4_Len(v);
	Vec4 result;
	result.x = v.x * inv_len;
	result.y = v.y * inv_len;
	result.z = v.z * inv_len;
	result.w = v.w * inv_len;
	return result;
}

MADMATH_INLINE Vec4
V4_Lerp(Vec4 v0, Vec4 v1, float t) {
	Vec4 result;
	result.x = Lerp(v0.x, v1.x, t);
	result.y = Lerp(v0.y, v1.y, t);
	result.z = Lerp(v0.z, v1.z, t);
	result.w = Lerp(v0.w, v1.w, t);
	return result;
}

MADMATH_INLINE Vec4
V4_Nlerp(Vec4 v0, Vec4 v1, float t) {
	Vec4 result;
	result.x = Lerp(v0.x, v1.x, t);
	result.y = Lerp(v0.y, v1.y, t);
	result.z = Lerp(v0.z, v1.z, t);
	result.w = Lerp(v0.w, v1.w, t);
	return V4_Normalize(result);
}


typedef struct {
	union {
		struct {
			float m00, m01,
				m10, m11;
		};
		float data[2*2];
	};
} Mat2;

#define M2(val_m00, val_m01, val_m10, val_m11) (Mat2){\
														.m00 = val_m00, .m01 = val_m01, \
														.m10 = val_m10, .m11 = val_m11  \
													 }

MADMATH_INLINE Mat2
M2_Diagonal(float d) {
	Mat2 result;
	result.m00 = d;    result.m01 = 0.0f;
	result.m10 = 0.0f; result.m11 = d;
	return result;
}

MADMATH_INLINE Mat2
M2_Rotate(float theta) {
	float cos_theta = Cos(theta);
	float sin_theta = Sin(theta);
	Mat2 result;
	result.m00 = cos_theta; result.m01 = -sin_theta;
	result.m10 = sin_theta; result.m11 =  cos_theta;
	return result;
}

MADMATH_INLINE Mat2
M2_Transpose(Mat2 m) {
	Mat2 result;
	result.m00 = m.m00; result.m01 = m.m10;
	result.m10 = m.m01; result.m11 = m.m11;
	return result;
}

MADMATH_INLINE float
M2_Det(Mat2 m) {
	return m.m00 * m.m11 - m.m01 * m.m10;
}


MADMATH_INLINE bool
M2_Inverse(Mat2 m, Mat2 *m_out) {
	float det = M2_Det(m);
	if (det == 0.0f) {
		return false;
	}
	float inv_det = 1.0f/det;
	Mat2 result;
	result.m00 =  m.m11 * inv_det; result.m01 = -m.m01 * inv_det;
	result.m10 = -m.m10 * inv_det; result.m11 =  m.m00 * inv_det;
	*m_out = result;
	return true;
}

MADMATH_INLINE Mat2
M2_Mul(Mat2 a, Mat2 b) {
	Mat2 result;
	result.m00 = a.m00 * b.m00 + a.m01 * b.m10;  // Dot(a.row0, b.col0)
	result.m01 = a.m00 * b.m01 + a.m01 * b.m11;  // Dot(a.row0, b.col1)
	result.m10 = a.m10 * b.m00 + a.m11 * b.m10;  // Dot(a.row1, b.col0)
	result.m01 = a.m10 * b.m01 + a.m11 * b.m11;  // Dot(a.row1, b.col1)
	return result;
}

MADMATH_INLINE Vec2
Mul_v2_m2(Vec2 v, Mat2 m) {
	Vec2 result;
	result.x = v.x * m.m00 + v.y * m.m01;
	result.y = v.x * m.m10 + v.y * m.m11;
	return result;
}



typedef struct {
	union {
		struct {
			float m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23,
				m30, m31, m32, m33;
		};
		float data[4*4];
	};
} Mat4;

#define M4(val_m00, val_m01, val_m02, val_m03, val_m10, val_m11, val_m12, val_m13, val_m20, val_m21, val_m22, val_m23, val_m30, val_m31, val_m32, val_m33) (Mat4){\
														.m00 = val_m00, .m01 = val_m01, .m02 = val_m02, .m03 = val_m03, \
														.m10 = val_m10, .m11 = val_m11, .m12 = val_m12, .m13 = val_m13, \
														.m20 = val_m20, .m21 = val_m21, .m22 = val_m22, .m23 = val_m23, \
														.m30 = val_m30, .m31 = val_m31, .m32 = val_m32, .m33 = val_m33 \
													 }

MADMATH_INLINE Mat4
M4_Diagonal(float d) {
	Mat4 result;
	result.m00 = d;    result.m01 = 0.0f; result.m02 = 0.0f; result.m03 = 0.0f;
	result.m10 = 0.0f; result.m11 = d;    result.m12 = 0.0f; result.m13 = 0.0f;
	result.m20 = 0.0f; result.m21 = 0.0f; result.m22 = d;    result.m23 = 0.0f;
	result.m30 = 0.0f; result.m31 = 0.0f; result.m32 = 0.0f; result.m33 = d;
	return result;
}


MADMATH_INLINE Mat4
M4_Translate(Vec3 translation) {
	Mat4 result;
	result = M4_Diagonal(1.0f);
	result.m03 = translation.x;
	result.m13 = translation.y;
	result.m23 = translation.z;
	return result;
}

MADMATH_INLINE Mat4
M4_Scale(Vec3 scale) {
	Mat4 result;
	result = M4_Diagonal(1.0f);
	result.m00 = scale.x;
	result.m11 = scale.y;
	result.m22 = scale.z;
	return result;
}

MADMATH_INLINE Mat4
M4_Rotate(float angle, Vec3 axis) {

    axis = V3_Normalize(axis);

    float sin_theta = Sin(angle);
    float cos_theta = Cos(angle);
    float cos_value = 1.0f - cos_theta;

    Mat4 result = M4_Diagonal(1.0f);

    result.m00 = (axis.x * axis.x * cos_value) + cos_theta;
    result.m10 = (axis.x * axis.y * cos_value) + (axis.z * sin_theta);
    result.m20 = (axis.x * axis.z * cos_value) - (axis.y * sin_theta);

    result.m01 = (axis.y * axis.x * cos_value) - (axis.z * sin_theta);
    result.m11 = (axis.y * axis.y * cos_value) + cos_theta;
    result.m21 = (axis.y * axis.z * cos_value) + (axis.x * sin_theta);

    result.m02 = (axis.z * axis.x * cos_value) + (axis.y * sin_theta);
    result.m12 = (axis.z * axis.y * cos_value) - (axis.x * sin_theta);
    result.m22 = (axis.z * axis.z * cos_value) + cos_theta;

    return result;
}


MADMATH_INLINE Mat4
M4_Transpose(Mat4 m) {
	Mat4 result;
	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			result.data[col*4+row] = m.data[row*4+col];
		}
	}
	return result;
}


MADMATH_INLINE Mat4
M4_Inverse(Mat4 m) {

	float A2323 = m.m22 * m.m33 - m.m23 * m.m32;
	float A1323 = m.m21 * m.m33 - m.m23 * m.m31;
	float A1223 = m.m21 * m.m32 - m.m22 * m.m31;
	float A0323 = m.m20 * m.m33 - m.m23 * m.m30;
	float A0223 = m.m20 * m.m32 - m.m22 * m.m30;
	float A0123 = m.m20 * m.m31 - m.m21 * m.m30;
	float A2313 = m.m12 * m.m33 - m.m13 * m.m32;
	float A1313 = m.m11 * m.m33 - m.m13 * m.m31;
	float A1213 = m.m11 * m.m32 - m.m12 * m.m31;
	float A2312 = m.m12 * m.m23 - m.m13 * m.m22;
	float A1312 = m.m11 * m.m23 - m.m13 * m.m21;
	float A1212 = m.m11 * m.m22 - m.m12 * m.m21;
	float A0313 = m.m10 * m.m33 - m.m13 * m.m30;
	float A0213 = m.m10 * m.m32 - m.m12 * m.m30;
	float A0312 = m.m10 * m.m23 - m.m13 * m.m20;
	float A0212 = m.m10 * m.m22 - m.m12 * m.m20;
	float A0113 = m.m10 * m.m31 - m.m11 * m.m30;
	float A0112 = m.m10 * m.m21 - m.m11 * m.m20;

	float det =
		m.m00 * ( m.m11 * A2323 - m.m12 * A1323 + m.m13 * A1223 ) -
		m.m01 * ( m.m10 * A2323 - m.m12 * A0323 + m.m13 * A0223 ) +
		m.m02 * ( m.m10 * A1323 - m.m11 * A0323 + m.m13 * A0123 ) -
		m.m03 * ( m.m10 * A1223 - m.m11 * A0223 + m.m12 * A0123 ) ;

	if (det == 0.0f) {
		return (Mat4) {0};
	}

	det = 1 / det;

	Mat4 result;
	result.m00 = det *   ( m.m11 * A2323 - m.m12 * A1323 + m.m13 * A1223 );
	result.m01 = det * - ( m.m01 * A2323 - m.m02 * A1323 + m.m03 * A1223 );
	result.m02 = det *   ( m.m01 * A2313 - m.m02 * A1313 + m.m03 * A1213 );
	result.m03 = det * - ( m.m01 * A2312 - m.m02 * A1312 + m.m03 * A1212 );
	result.m10 = det * - ( m.m10 * A2323 - m.m12 * A0323 + m.m13 * A0223 );
	result.m11 = det *   ( m.m00 * A2323 - m.m02 * A0323 + m.m03 * A0223 );
	result.m12 = det * - ( m.m00 * A2313 - m.m02 * A0313 + m.m03 * A0213 );
	result.m13 = det *   ( m.m00 * A2312 - m.m02 * A0312 + m.m03 * A0212 );
	result.m20 = det *   ( m.m10 * A1323 - m.m11 * A0323 + m.m13 * A0123 );
	result.m21 = det * - ( m.m00 * A1323 - m.m01 * A0323 + m.m03 * A0123 );
	result.m22 = det *   ( m.m00 * A1313 - m.m01 * A0313 + m.m03 * A0113 );
	result.m23 = det * - ( m.m00 * A1312 - m.m01 * A0312 + m.m03 * A0112 );
	result.m30 = det * - ( m.m10 * A1223 - m.m11 * A0223 + m.m12 * A0123 );
	result.m31 = det *   ( m.m00 * A1223 - m.m01 * A0223 + m.m02 * A0123 );
	result.m32 = det * - ( m.m00 * A1213 - m.m01 * A0213 + m.m02 * A0113 );
	result.m33 = det *   ( m.m00 * A1212 - m.m01 * A0212 + m.m02 * A0112 );

	return result;
}


MADMATH_INLINE Mat4
M4_Orthographic(float left, float right, float bottom, float top, float near_, float far_) {
    Mat4 result = M4_Diagonal(1.0f);

    result.m00 = 2.0f / (right - left);
    result.m11 = 2.0f / (top - bottom);
    result.m22 = 2.0f / (near_ - far_);

    result.m03 = (left + right) / (left - right);
    result.m13 = (bottom + top) / (bottom - top);
    result.m23 = (far_ + near_) / (near_ - far_);

    return result;
}


MADMATH_INLINE Mat4
M4_Perspective(float fov, float aspect_ratio, float near_, float far_) {

    // See https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluPerspective.xml

    float cotan_fov = 1.0f / Tan(fov * 0.5f);

	Mat4 result = M4_Diagonal(1.0f);
    result.m00 = cotan_fov / aspect_ratio;
    result.m11 = cotan_fov;
    result.m23 = (2.0f * near_ * far_) / (near_ - far_);
    result.m22 = (near_ + far_) / (near_ - far_);
    result.m32 = -1.0f;
    result.m33 = 0.0f;

    return result;
}

MADMATH_INLINE Mat4
M4_Mul(Mat4 left, Mat4 right) {
	Mat4 result;
	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			float sum = 0;
			for (int cel = 0; cel < 4; ++cel) {
				sum = sum + left.data[row*4+cel] * right.data[cel*4+col];
			}
			result.data[row*4+col] = sum;
		}
	}
	return result;
}



MADMATH_INLINE Vec4
Mul_v4_m4(Vec4 v, Mat4 m) {
	Vec4 result;
	result.x = v.x * m.m00 + v.y * m.m01 + v.z * m.m02 + v.w * m.m03;
	result.y = v.x * m.m10 + v.y * m.m11 + v.z * m.m12 + v.w * m.m13;
	result.z = v.x * m.m20 + v.y * m.m21 + v.z * m.m22 + v.w * m.m23;
	result.w = v.x * m.m30 + v.y * m.m31 + v.z * m.m32 + v.w * m.m33;
	return result;
}





// Get from https://halt.software/dead-simple-layouts/




typedef struct {
	Vec2 min, max;
} Rect;


#define RECT(min_x, min_y, max_x, max_y) (Rect){ .min = V2(min_x, min_y), .max = V2(max_x, max_y) }

MADMATH_INLINE Rect
RECT_Cut_left(Rect *rect, float a) {
	float minx = rect->min.x;
	rect->min.x = Min(rect->max.x, minx+a);
	Rect result = RECT(minx, rect->min.y, rect->min.x, rect->max.y);
	return result;
}



MADMATH_INLINE Rect
RECT_Cut_right(Rect *rect, float a) {
	float maxx = rect->max.x;
	rect->max.x = Max(rect->min.x, maxx-a);
	Rect result = RECT(rect->max.x, rect->min.y, maxx, rect->max.y);
	return result;
}



MADMATH_INLINE Rect
RECT_Cut_top(Rect *rect, float a) {
	float maxy = rect->max.y;
	rect->max.y = Max(rect->min.y, rect->max.y-a);
	Rect result = RECT(rect->min.x, rect->max.y, rect->max.x, maxy);
	return result;
}



MADMATH_INLINE Rect
RECT_Cut_bottom(Rect *rect, float a) {
	float miny = rect->min.y;
	rect->min.y = Min(rect->max.y, rect->min.y+a);
	Rect result = RECT(rect->min.x, miny, rect->max.x, rect->min.y);
	return result;
}


MADMATH_INLINE float
RECT_Width(Rect rect) {
	return rect.max.x - rect.min.x;
}


MADMATH_INLINE float
RECT_Height(Rect rect) {
	return rect.max.y - rect.min.y;
}



typedef struct {
	union {
		struct {
			uint8_t r, g, b, a;
		};
		uint32_t pack32;
	};
} Color;


#define COLOR(val_r, val_g, val_b, val_a) (Color){.r=val_r, .g=val_g, .b=val_b ,.a=val_a}

// Colors taken from raylib
#define LIGHTGRAY  COLOR(200, 200, 200, 255)
#define GRAY       COLOR(130, 130, 130, 255)
#define DARKGRAY   COLOR(80,  80,  80,  255)
#define YELLOW     COLOR(253, 249, 0,   255)
#define GOLD       COLOR(255, 203, 0,   255)
#define ORANGE     COLOR(255, 161, 0,   255)
#define PINK       COLOR(255, 109, 194, 255)
#define RED        COLOR(230, 41,  55,  255)
#define MAROON     COLOR(190, 33,  55,  255)
#define GREEN      COLOR(0,   228, 48,  255)
#define LIME       COLOR(0,   158, 47,  255)
#define DARKGREEN  COLOR(0,   117, 44,  255)
#define SKYBLUE    COLOR(102, 191, 255, 255)
#define BLUE       COLOR(0,   121, 241, 255)
#define DARKBLUE   COLOR(0,   82,  172, 255)
#define PURPLE     COLOR(200, 122, 255, 255)
#define VIOLET     COLOR(135, 60,  190, 255)
#define DARKPURPLE COLOR(112, 31,  126, 255)
#define BEIGE      COLOR(211, 176, 131, 255)
#define BROWN      COLOR(127, 106, 79,  255)
#define DARKBROWN  COLOR(76,  63,  47,  255)
#define WHITE      COLOR(255, 255, 255, 255)
#define BLACK      COLOR(0,   0,   0,   255)
#define BLANK      COLOR(0,   0,   0,   0)
#define MAGENTA    COLOR(255, 0,   255, 255)
#define RAYWHITE   COLOR(245, 245, 245, 255)


MADMATH_INLINE Vec4
Color_to_Vec4(Color c) {
	Vec4 result;
	result.r = (f32)c.r / 255.0f;
	result.g = (f32)c.g / 255.0f;
	result.b = (f32)c.b / 255.0f;
	result.a = (f32)c.a / 255.0f;
	return result;
}

MADMATH_INLINE Color
Color_lerp(Color c0, Color c1, float t) {
	float t8f = t * 256.0f;
	uint32_t t32 = (uint32_t)t8f;
	uint32_t r = ((256-t32)*(uint32_t)c0.r + t32*(uint32_t)c1.r)/256;
	uint32_t g = ((256-t32)*(uint32_t)c0.g + t32*(uint32_t)c1.g)/256;
	uint32_t b = ((256-t32)*(uint32_t)c0.b + t32*(uint32_t)c1.b)/256;
	uint32_t a = ((256-t32)*(uint32_t)c0.a + t32*(uint32_t)c1.a)/256;
	return COLOR(r, g, b ,a);
}

MADMATH_INLINE Color
V4_To_Color(Vec4 n) {
	float max = Max(Abs(n.x), Max(Abs(n.y), Max(Abs(n.z), Abs(n.w))));
	if (max == 0.0f) max = 1.0f;
	float d = (127.5f) / max;
	Color result;
	result.r = (uint8_t)(n.x * d + 127.5f);
	result.g = (uint8_t)(n.y * d + 127.5f);
	result.b = (uint8_t)(n.z * d + 127.5f);
	result.a = (uint8_t)(n.w * d + 127.5f);
	return result;
}





// This is a copy paste from https://github.com/wangyi-fudan/wyhash

// This is free and unencumbered software released into the public domain under The Unlicense (http://unlicense.org/)
// main repo: https://github.com/wangyi-fudan/wyhash
// author: 王一 Wang Yi <godspeed_china@yeah.net>
// contributors: Reini Urban, Dietrich Epp, Joshua Haberman, Tommy Ettinger, Daniel Lemire, Otmar Ertl, cocowalla, leo-yuriev, Diego Barrios Romero, paulie-g, dumblob, Yann Collet, ivte-ms, hyb, James Z.M. Gao, easyaspi314 (Devin), TheOneric

/* quick example:
   string s="fjsakfdsjkf";
   uint64_t hash=wyhash(s.c_str(), s.size(), 0, _wyp);
*/

#ifndef wyhash_final_version_3
#define wyhash_final_version_3

#ifndef WYHASH_CONDOM
//protections that produce different results:
//1: normal valid behavior
//2: extra protection against entropy loss (probability=2^-63), aka. "blind multiplication"
#define WYHASH_CONDOM 1
#endif

#ifndef WYHASH_32BIT_MUM
//0: normal version, slow on 32 bit systems
//1: faster on 32 bit systems but produces different results, incompatible with wy2u0k function
#define WYHASH_32BIT_MUM 0  
#endif

//includes
#include <stdint.h>
#include <string.h>
#if defined(_MSC_VER) && defined(_M_X64)
  #include <intrin.h>
  #pragma intrinsic(_umul128)
#endif

//likely and unlikely macros
#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
  #define _likely_(x)  __builtin_expect(x,1)
  #define _unlikely_(x)  __builtin_expect(x,0)
#else
  #define _likely_(x) (x)
  #define _unlikely_(x) (x)
#endif

//128bit multiply function
static inline uint64_t _wyrot(uint64_t x) { return (x>>32)|(x<<32); }
static inline void _wymum(uint64_t *A, uint64_t *B){
#if(WYHASH_32BIT_MUM)
  uint64_t hh=(*A>>32)*(*B>>32), hl=(*A>>32)*(uint32_t)*B, lh=(uint32_t)*A*(*B>>32), ll=(uint64_t)(uint32_t)*A*(uint32_t)*B;
  #if(WYHASH_CONDOM>1)
  *A^=_wyrot(hl)^hh; *B^=_wyrot(lh)^ll;
  #else
  *A=_wyrot(hl)^hh; *B=_wyrot(lh)^ll;
  #endif
#elif defined(__SIZEOF_INT128__)
  __uint128_t r=*A; r*=*B; 
  #if(WYHASH_CONDOM>1)
  *A^=(uint64_t)r; *B^=(uint64_t)(r>>64);
  #else
  *A=(uint64_t)r; *B=(uint64_t)(r>>64);
  #endif
#elif defined(_MSC_VER) && defined(_M_X64)
  #if(WYHASH_CONDOM>1)
  uint64_t  a,  b;
  a=_umul128(*A,*B,&b);
  *A^=a;  *B^=b;
  #else
  *A=_umul128(*A,*B,B);
  #endif
#else
  uint64_t ha=*A>>32, hb=*B>>32, la=(uint32_t)*A, lb=(uint32_t)*B, hi, lo;
  uint64_t rh=ha*hb, rm0=ha*lb, rm1=hb*la, rl=la*lb, t=rl+(rm0<<32), c=t<rl;
  lo=t+(rm1<<32); c+=lo<t; hi=rh+(rm0>>32)+(rm1>>32)+c;
  #if(WYHASH_CONDOM>1)
  *A^=lo;  *B^=hi;
  #else
  *A=lo;  *B=hi;
  #endif
#endif
}

//multiply and xor mix function, aka MUM
static inline uint64_t _wymix(uint64_t A, uint64_t B){ _wymum(&A,&B); return A^B; }

//endian macros
#ifndef WYHASH_LITTLE_ENDIAN
  #if defined(_WIN32) || defined(__LITTLE_ENDIAN__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
    #define WYHASH_LITTLE_ENDIAN 1
  #elif defined(__BIG_ENDIAN__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
    #define WYHASH_LITTLE_ENDIAN 0
  #else
    #warning could not determine endianness! Falling back to little endian.
    #define WYHASH_LITTLE_ENDIAN 1
  #endif
#endif

//read functions
#if (WYHASH_LITTLE_ENDIAN)
static inline uint64_t _wyr8(const uint8_t *p) { uint64_t v; memcpy(&v, p, 8); return v;}
static inline uint64_t _wyr4(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v;}
#elif defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
static inline uint64_t _wyr8(const uint8_t *p) { uint64_t v; memcpy(&v, p, 8); return __builtin_bswap64(v);}
static inline uint64_t _wyr4(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return __builtin_bswap32(v);}
#elif defined(_MSC_VER)
static inline uint64_t _wyr8(const uint8_t *p) { uint64_t v; memcpy(&v, p, 8); return _byteswap_uint64(v);}
static inline uint64_t _wyr4(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return _byteswap_ulong(v);}
#else
static inline uint64_t _wyr8(const uint8_t *p) {
  uint64_t v; memcpy(&v, p, 8);
  return (((v >> 56) & 0xff)| ((v >> 40) & 0xff00)| ((v >> 24) & 0xff0000)| ((v >>  8) & 0xff000000)| ((v <<  8) & 0xff00000000)| ((v << 24) & 0xff0000000000)| ((v << 40) & 0xff000000000000)| ((v << 56) & 0xff00000000000000));
}
static inline uint64_t _wyr4(const uint8_t *p) {
  uint32_t v; memcpy(&v, p, 4);
  return (((v >> 24) & 0xff)| ((v >>  8) & 0xff00)| ((v <<  8) & 0xff0000)| ((v << 24) & 0xff000000));
}
#endif
static inline uint64_t _wyr3(const uint8_t *p, size_t k) { return (((uint64_t)p[0])<<16)|(((uint64_t)p[k>>1])<<8)|p[k-1];}
//wyhash main function
static inline uint64_t wyhash(const void *key, size_t len, uint64_t seed, const uint64_t *secret){
  const uint8_t *p=(const uint8_t *)key; seed^=*secret;	uint64_t	a,	b;
  if(_likely_(len<=16)){
    if(_likely_(len>=4)){ a=(_wyr4(p)<<32)|_wyr4(p+((len>>3)<<2)); b=(_wyr4(p+len-4)<<32)|_wyr4(p+len-4-((len>>3)<<2)); }
    else if(_likely_(len>0)){ a=_wyr3(p,len); b=0;}
    else a=b=0;
  }
  else{
    size_t i=len; 
    if(_unlikely_(i>48)){
      uint64_t see1=seed, see2=seed;
      do{
        seed=_wymix(_wyr8(p)^secret[1],_wyr8(p+8)^seed);
        see1=_wymix(_wyr8(p+16)^secret[2],_wyr8(p+24)^see1);
        see2=_wymix(_wyr8(p+32)^secret[3],_wyr8(p+40)^see2);
        p+=48; i-=48;
      }while(_likely_(i>48));
      seed^=see1^see2;
    }
    while(_unlikely_(i>16)){  seed=_wymix(_wyr8(p)^secret[1],_wyr8(p+8)^seed);  i-=16; p+=16;  }
    a=_wyr8(p+i-16);  b=_wyr8(p+i-8);
  }
  return _wymix(secret[1]^len,_wymix(a^secret[1],b^seed));
}

//the default secret parameters
static const uint64_t _wyp[4] = {0xa0761d6478bd642full, 0xe7037ed1a0b428dbull, 0x8ebc6af09c88c6e3ull, 0x589965cc75374cc3ull};

//a useful 64bit-64bit mix function to produce deterministic pseudo random numbers that can pass BigCrush and PractRand
static inline uint64_t wyhash64(uint64_t A, uint64_t B){ A^=0xa0761d6478bd642full; B^=0xe7037ed1a0b428dbull; _wymum(&A,&B); return _wymix(A^0xa0761d6478bd642full,B^0xe7037ed1a0b428dbull);}

//The wyrand PRNG that pass BigCrush and PractRand
static inline uint64_t wyrand(uint64_t *seed){ *seed+=0xa0761d6478bd642full; return _wymix(*seed,*seed^0xe7037ed1a0b428dbull);}

//convert any 64 bit pseudo random numbers to uniform distribution [0,1). It can be combined with wyrand, wyhash64 or wyhash.
static inline double wy2u01(uint64_t r){ const double _wynorm=1.0/(1ull<<52); return (r>>12)*_wynorm;}

//convert any 64 bit pseudo random numbers to APPROXIMATE Gaussian distribution. It can be combined with wyrand, wyhash64 or wyhash.
static inline double wy2gau(uint64_t r){ const double _wynorm=1.0/(1ull<<20); return ((r&0x1fffff)+((r>>21)&0x1fffff)+((r>>42)&0x1fffff))*_wynorm-3.0;}

#if(!WYHASH_32BIT_MUM)
//fast range integer random number generation on [0,k) credit to Daniel Lemire. May not work when WYHASH_32BIT_MUM=1. It can be combined with wyrand, wyhash64 or wyhash.
static inline uint64_t wy2u0k(uint64_t r, uint64_t k){ _wymum(&r,&k); return k; }
#endif

//make your own secret
static inline void make_secret(uint64_t seed, uint64_t *secret){
  uint8_t c[] = {15, 23, 27, 29, 30, 39, 43, 45, 46, 51, 53, 54, 57, 58, 60, 71, 75, 77, 78, 83, 85, 86, 89, 90, 92, 99, 101, 102, 105, 106, 108, 113, 114, 116, 120, 135, 139, 141, 142, 147, 149, 150, 153, 154, 156, 163, 165, 166, 169, 170, 172, 177, 178, 180, 184, 195, 197, 198, 201, 202, 204, 209, 210, 212, 216, 225, 226, 228, 232, 240 };
  for(size_t i=0;i<4;i++){
    uint8_t ok;
    do{
      ok=1; secret[i]=0;
      for(size_t j=0;j<64;j+=8) secret[i]|=((uint64_t)c[wyrand(&seed)%sizeof(c)])<<j;
      if(secret[i]%2==0){ ok=0; continue; }
      for(size_t j=0;j<i;j++) {
#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
        if(__builtin_popcountll(secret[j]^secret[i])!=32){ ok=0; break; }
#elif defined(_MSC_VER) && defined(_M_X64)
        if(_mm_popcnt_u64(secret[j]^secret[i])!=32){ ok=0; break; }
#else
        //manual popcount
        uint64_t x = secret[j]^secret[i];
        x -= (x >> 1) & 0x5555555555555555;
        x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
        x = (x + (x >> 4)) & 0x0f0f0f0f0f0f0f0f;
        x = (x * 0x0101010101010101) >> 56;
        if(x!=32){ ok=0; break; }
#endif
      }
    }while(!ok);
  }
}

/*  This is world's fastest hash map: 2x faster than bytell_hash_map.
    It does not store the keys, but only the hash/signature of keys.
    First we use pos=hash1(key) to approximately locate the bucket.
    Then we search signature=hash2(key) from pos linearly.
    If we find a bucket with matched signature we report the bucket
    Or if we meet a bucket whose signifure=0, we report a new position to insert
    The signature collision probability is very low as we usually searched N~10 buckets.
    By combining hash1 and hash2, we acturally have 128 bit anti-collision strength.
    hash1 and hash2 can be the same function, resulting lower collision resistance but faster.
    The signature is 64 bit, but can be modified to 32 bit if necessary for save space.
    The above two can be activated by define WYHASHMAP_WEAK_SMALL_FAST
    simple examples:
    const	size_t	size=213432;
    vector<wyhashmap_t>	idx(size);	//	allocate the index of fixed size. idx MUST be zeroed.
    vector<value_class>	value(size);	//	we only care about the index, user should maintain his own value vectors.
    string  key="dhskfhdsj"	//	the object to be inserted into idx
    size_t	pos=wyhashmap(idx.data(), idx.size(), key.c_str(), key.size(), 1);	//	get the position and insert
    if(pos<size)	value[pos]++;	//	we process the vallue
    else	cerr<<"map is full\n";
    pos=wyhashmap(idx.data(), idx.size(), key.c_str(), key.size(), 0);	// just lookup by setting insert=0
    if(pos<size)	value[pos]++;	//	we process the vallue
    else	cerr<<"the key does not exist\n";
*/
#ifdef	WYHASHMAP_WEAK_SMALL_FAST	// for small hashmaps whose size < 2^24 and acceptable collision
typedef	uint32_t	wyhashmap_t;
#else
typedef	uint64_t	wyhashmap_t;
#endif

static	inline	size_t	wyhashmap(wyhashmap_t	*idx,	size_t	idx_size,	const	void *key, size_t	key_size,	uint8_t	insert, uint64_t *secret){
	size_t	i=1;	uint64_t	h2;	wyhashmap_t	sig;
	do{	sig=h2=wyhash(key,key_size,i,secret);	i++;	}while(_unlikely_(!sig));
#ifdef	WYHASHMAP_WEAK_SMALL_FAST
	size_t	i0=wy2u0k(h2,idx_size);
#else
	size_t	i0=wy2u0k(wyhash(key,key_size,0,secret),idx_size);
#endif
	for(i=i0;	i<idx_size&&idx[i]&&idx[i]!=sig;	i++);
	if(_unlikely_(i==idx_size)){
		for(i=0;	i<i0&&idx[i]&&idx[i]!=sig;  i++);
		if(i==i0)	return	idx_size;
	}
	if(!idx[i]){
		if(insert)	idx[i]=sig;
		else	return	idx_size;
	}
	return	i;
}
#endif

/* The Unlicense
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.
In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
For more information, please refer to <http://unlicense.org/>
*/

#endif // MADMATH_H

