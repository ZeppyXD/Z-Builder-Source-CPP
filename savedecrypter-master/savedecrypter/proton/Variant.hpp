#pragma once
#ifndef Variant_h__
#define Variant_h__
#include <string>
#include <vector>
#include "plat.h"
#include "../ClanLib-2.0/Sources/API/Core/Math/vec2.h"
#include "../ClanLib-2.0/Sources/API/Core/Math/vec3.h"
#include "../ClanLib-2.0/Sources/API/Core/Math/rect.h"

#include "../ClanLib-2.0/Sources/API/Core/Math/mat3.h"
#include "../ClanLib-2.0/Sources/API/Core/Math/mat4.h"
#include "../ClanLib-2.0/Sources/API/Core/Math/line_segment.h"
#include "../ClanLib-2.0/Sources/API/Core/Math/circle.h"
using std::string;

class Entity;
class EntityComponent;
class VariantList;

enum eInterpolateType
{
	INTERPOLATE_LINEAR = 0,
	INTERPOLATE_SMOOTHSTEP,
	INTERPOLATE_EASE_TO,
	INTERPOLATE_EASE_FROM,
	INTERPOLATE_EASE_TO_QUARTIC,
	INTERPOLATE_EASE_FROM_QUARTIC,
	INTERPOLATE_BOUNCE_TO,
	INTERPOLATE_SMOOTHSTEP_AS_COLOR,
	INTERPOLATE_LINEAR_AS_COLOR

};

#define C_VAR_SPACE_BYTES 16 //enough to fit a rect

//signals are ignored when copying these
class Variant
{
public:

	enum eType
	{
		type_a,
		type_b,
		type_c,
		type_d,
		type_e,
		type_f,
		type_g,
		type_x,
		type_y,
		type_z

	};
	Variant(uint32 var) { SetDefaults(); Set(var); }
	Variant(int32 var) { SetDefaults(); Set(var); }

	Variant(float var) { SetDefaults(); Set(var); }
	Variant(const std::string& var) { SetDefaults(); Set(var); }
	Variant(float x, float y) { SetDefaults(); Set(CL_Vec2f(x, y)); }
	Variant(float x, float y, float z) { SetDefaults(); Set(CL_Vec3f(x, y, z)); }
	Variant(const CL_Vec2f& v2) { SetDefaults(); Set(v2); }
	Variant(const CL_Vec3f& v3) { SetDefaults(); Set(v3); }
	Variant(const CL_Rectf& r) { SetDefaults(); Set(r); }
	Variant(Entity* pEnt) { SetDefaults(); Set(pEnt); }
	Variant(EntityComponent* pEnt) { SetDefaults(); Set(pEnt); }

	Variant()
	{
		SetDefaults();
	}
	~Variant();


	void Reset()
	{
		m_type = type_a;
	}

	void Set(const Variant& v);
	void SetVariant(Variant* pVar) /*needed this because boost was confused... */;

	void Set(float var)
	{
		m_type = type_b; *((float*)m_var) = var;
	}

	float& get_y()
	{
		if (m_type == type_a) Set(float(0));
		return  *((float*)m_var);
	}
	const float& get_y() const
	{
		return  *((float*)m_var);
	}

	void Set(const Entity* pEnt)
	{
		m_type = type_g;   m_pVoid = (void*)pEnt;
	}

	Entity* get_b()
	{
		if (m_type == type_a) Set((Entity*)NULL);
		return  ((Entity*)m_pVoid);
	}
	const Entity* get_b() const
	{
		return  ((Entity*)m_pVoid);
	}

	void Set(const EntityComponent* pEnt)
	{
		m_type = type_x;   m_pVoid = (void*)pEnt;
	}

	EntityComponent* get_m()
	{
		if (m_type == type_a) Set((Entity*)NULL);
		return  ((EntityComponent*)m_pVoid);
	}
	const EntityComponent* get_m() const
	{
		return  ((EntityComponent*)m_pVoid);
	}

	void Set(uint32 var)
	{
		m_type = type_f; *((uint32*)m_var) = var;
	}

	uint32& get_d()
	{
		if (m_type == type_a) Set(uint32(0));
		return  *((uint32*)m_var);
	}
	const uint32& get_d() const
	{
		return  *((uint32*)m_var);
	}

	void Set(int32 var)
	{
		m_type = type_z; *((int32*)m_var) = var;
	}

	int32& get_a()
	{
		if (m_type == type_a) Set(int32(0));
		return  *((int32*)m_var);
	}
	const int32& get_a() const
	{
		return  *((int32*)m_var);
	}

	void Set(std::string const& var);
	string& get_h()
	{
		return m_string;
	}
	const string& get_h() const
	{
		return m_string;
	}

	void Set(CL_Vec2f const& var)
	{
		m_type = type_d; *((CL_Vec2f*)m_var) = var;
	}
	CL_Vec2f& get_g()
	{
		if (m_type == type_a)
		{
			//set a default
			Set(CL_Vec2f(0, 0));
		}
		return  *((CL_Vec2f*)m_var);
	}
	const CL_Vec2f& get_g() const
	{
		return  *((CL_Vec2f*)m_var);
	}

	void Set(float x, float y)
	{
		Set(CL_Vec2f(x, y));
	}

	void Set(CL_Vec3f const& var)
	{
		m_type = type_e; *((CL_Vec3f*)m_var) = var;
	}
	CL_Vec3f& get_p()
	{
		if (m_type == type_a)
		{
			//set a default
			Set(CL_Vec3f(0, 0, 0));
		}
		return  *((CL_Vec3f*)m_var);
	}
	const CL_Vec3f& get_p() const
	{
		return  *((CL_Vec3f*)m_var);
	}

	void Set(CL_Rectf const& var)
	{
		m_type = type_y; *((CL_Rectf*)m_var) = var;
	}
	CL_Rectf& get_q()
	{
		if (m_type == type_a)
		{
			//set a default
			Set(CL_Rectf(0, 0, 0, 0));
		}
		return  *((CL_Rectf*)m_var);
	}
	const CL_Rectf& get_q() const
	{
		return  *((CL_Rectf*)m_var);
	}


	void Set(float x, float y, float z)
	{
		Set(CL_Vec3f(x, y, z));
	}


	eType get() const { return m_type; }
	std::string Print();


	Variant(const Variant& v)
	{
		SetDefaults();
		//our special copy won't include the sig crap, that stuff can't be copied
		*this = v;
	}


	Variant& operator= (const Variant& rhs)
	{
		m_type = rhs.m_type;
		m_pVoid = rhs.m_pVoid;
		memcpy(m_var, rhs.m_var, C_VAR_SPACE_BYTES);
		m_string = rhs.m_string;

		return *this;
	}

	Variant& operator+=(const Variant& rhs);

	Variant& operator-=(const Variant& rhs);

	bool operator==(const Variant& rhs) const;

	bool operator!=(const Variant& rhs) const;

private:

	void SetDefaults()
	{
		m_type = type_a;
	}
	eType m_type;
	void* m_pVoid;

	union
	{
		byte m_var[C_VAR_SPACE_BYTES]; //large enough so we can use the space for all the datatypes we care about

		//don't actually use these, these unions help me look at vars when debugging easier
		float m_as_floats[4];
		uint32 m_as_uint32s[4];
		int32 m_as_int32s[4];
	};
	std::string m_string;

};


inline Variant operator+(Variant lhs, const Variant& rhs);
inline Variant operator-(Variant lhs, const Variant& rhs);

#endif 
